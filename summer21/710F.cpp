/* AUTHOR - SHASHANK AGRAWAL (codeforces - @shashanka136) ( codechef - @shashank_vasu) */
#include <bits/stdc++.h>
#ifdef STAC
#include <sys/resource.h>
#endif
#pragma GCC optimize("-O3")
// #pragma GCC target("avx,avx2,fma")
using namespace std;
#ifdef TRACE
#include "/Users/shashankagrawal/Desktop/CP/trace.h"
#else
#define trace(args...)
#endif
typedef long long ll;
typedef long double ld;
typedef vector<ll> vl;		typedef vector<int> vi;
typedef vector<vl> vvl;	  	typedef vector<vi> vvi;
typedef pair<ll, ll> pll;	typedef pair<int, int> pii;
typedef vector<pll> vpl;	typedef vector<pii> vpi;
typedef vector<vpl> vvpl;	typedef vector<vpi> vvpi;
#define S second
#define F first
#define V vector
#define MP make_pair
#define PB push_back
#define EB emplace_back
#define POB pop_back
#define PF push_front
#define POF pop_front
#define sz(x) (int)x.size()
#define f(i,j,k,l) for(int i =(int)j; i!=(int)k; i = i + l) 
#define fn(i,n) for(int i = 0; i<n; i++)
#define INP(v,n) f(i,0,n,1) cin>>v[i];
#define OUT(v,n) f(i,0,n,1){ cout<<v[i]<<" ";}cout<<endl;
// #define endl '\n'
#define all(v) v.begin(), v.end()
const ll mod = 998244353;

//
const int K = 26;//alphabet size
const int N = 4*(3e5+100);
const int lgn = 20;
struct node {
	int nx[K];
	int p = -1; char pch; int sl = -1; //suffix_link
	int nxl = -1;//next leaf
	int cntl = -1;// count of leafs on suffix link
	int go[K];
	node(int p = -1, char c = ' '): p(p), pch(c) {
		fill(begin(nx), end(nx), -1);
		fill(begin(go), end(go), -1);
	}
};
int m;
node t[N];
string a[N];
vector<int> ids;
int getid(){
	int fn = ids.back();
	ids.pop_back();
	t[fn] = node();
	return fn;
}
void retid(int id){
	ids.push_back(id);
}

inline int getin(char c) { //modify accordingly
	return c - 'a';
}
void ins(string const& s, int rt) {
	int v = rt;
	for (char c : s) {
		int z = getin(c);
		if (t[v].nx[z] == -1) {
			int fn = getid();
			t[v].nx[z] = fn;
			t[fn] = node(v, c);
		}
		v = t[v].nx[z];
	}
	t[v].nxl = v;
}

int get_sl(int v, int rt) {
	if(t[v].sl != -1) return t[v].sl;
	if (v == rt || t[v].p == rt) return t[v].sl = rt;
	int pv = get_sl(t[v].p, rt);
	int z = getin(t[v].pch);
	while(pv != rt && t[pv].nx[z] == -1){
		pv = get_sl(pv, rt);
	}
	return t[v].sl = (t[pv].nx[z] == -1? rt: t[pv].nx[z]);
}

int go(int v, char c, int rt) {
	int z = getin(c);
	if (t[v].go[z] == -1) {
		if (t[v].nx[z] != -1)
			t[v].go[z] = t[v].nx[z];
		else if (v == rt)
			t[v].go[z] = rt;
		else
			t[v].go[z] = go(get_sl(v,rt), c, rt);
	}
	return t[v].go[z];
}

int get_nxl(int v, int rt) {//next terminal
	if (t[v].nxl == -1) {
		int tmp = get_sl(v, rt);
		if (tmp == rt) {
			t[v].nxl = rt;
		} else {
			t[v].nxl = get_nxl(tmp, rt);
		}
	}
	return t[v].nxl;
}

int get_cntl(int v, int rt){
	if(t[v].cntl == -1){
		int vv = get_nxl(v,rt);
		if(vv == rt){
			return t[v].cntl = 0;
		}
		t[v].cntl = 1 + get_cntl(get_sl(vv, rt), rt);
	}
	return t[v].cntl;
}

void clear_trie(int v){
	fn(i,K) if(t[v].nx[i] != -1) clear_trie(t[v].nx[i]);
	retid(v);
}

int build(int rt, vector<int>& ids){
	clear_trie(rt);
	rt = getid();
	for(int i : ids) ins(a[i], rt);
	return rt;
}

int cntle(int i, int rt){
	int an = 0;
	int v = rt;
	for(int j =0; j< sz(a[i]); j++){
		v = go(v,a[i][j], rt);
		an += get_cntl(v,rt);
	}
	return an;
}

struct blocks{
	int rt[lgn];
	vector<int> block[lgn];
	void init(){
		for(int i =0; i<lgn; i++){
			rt[i] = getid();
			block[i].clear();
		}
	}

	void ins(int i){
		vector<int> cr(1,i);
		for(int i =0; i<lgn; i++){
			if(sz(block[i]) == sz(cr)){
				cr.insert(cr.end(), all(block[i]));
				block[i].clear();
				rt[i] = build(rt[i], block[i]);
			}else{
				block[i] = cr;
				rt[i] = build(rt[i], block[i]);
				break;
			}
		}
	}

	ll getans(int i){
		ll an = 0;
		for(int j =0; j<lgn; j++){
			an += cntle(i, rt[j]);
		}
		return an;
	}
};

int typ;
blocks fo1, fo2;
void solve(){
	cin>>m;
	for(int i =0; i<N;i++) ids.PB(i);
	// trace(m);
	fo1.init();
	// trace(m);
	fo2.init();
	// trace(m);
	for(int i =0; i<m; i++){
		cin>>typ>>a[i];
		// trace(typ, a[i]);
		if(typ == 1){
			fo1.ins(i);
		}else if(typ == 2){
			fo2.ins(i);
		}else{
			cout<<fo1.getans(i) - fo2.getans(i)<<endl;
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
#ifdef STAC
	rlimit rlim;
	if(getrlimit(RLIMIT_STACK, &rlim)) return 1;//getrlimit returns -1 when error
	rlim.rlim_cur = rlim.rlim_max;

	if(setrlimit(RLIMIT_STACK, &rlim)) return 2;//setrlimit too returns -1 when error
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	// cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}