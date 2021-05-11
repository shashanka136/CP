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
#define INP(v,n) f(i,0,n,1) cin>>v[i];
#define OUT(v,n) f(i,0,n,1){ cout<<v[i]<<" ";}cout<<endl;
#define endl '\n'
#define all(v) v.begin(), v.end()
const ll mod = 998244353;

//

struct item {
	int n;
	item(int x = 1e9): n(x) {}
	item operator+(const item& oth) { //operation to merge
		item r;//default is done for sum
		r.n = min(n, oth.n);//must be a associative function
		return r;
	}
};

template<class node>
struct segtree {
	int n;
	vector<node> st;

	void init(int _n) { //give some default value value if required
		n = _n;
		st.assign(2 * n, node());
	}
	inline int le(int x) {return 2 * x + 1;}
	inline int ri(int x) {return 2 * x + 2;}
	//change vector to int* if required in both build

	void build(vector<int> &a) {
		init(a.size());
		for (int i = n; i < 2 * n; i++)
			st[i] = a[i - n];
		for (int i = n - 1; i > 0; i--)
			st[i] = st[i << 1] + st[i << 1 | 1];
	}

	void build(int _n) {
		init(_n);
		int a;
		for (int i = n; i < 2 * n; i++){
			cin>>a;
			st[i] = a;
		}
		for (int i = n - 1; i > 0; i--)
			st[i] = st[i << 1] + st[i << 1 | 1];
	}

	void set(int i, int x) {
		for (st[i += n] = x; i >>= 1; )
			st[i] = st[i<<1] + st[i<<1|1];
	}

	node query(int l, int r) {
		node anl, anr;r++;
		for(l += n,r+=n;l < r; l>>=1, r>>=1){
			if(l&1) anl = anl + st[l++];//if l is right child then it's parent is not included
			if(r&1) anr = st[--r] + anr;// if r is right child then r-1 is left child and same thing
			//parent is not included
		}
		return anl + anr;
	}
};
typedef segtree<item> segm;

const int N = 15e4+5;
int inf = 1e9;
vi adj[3][N];
int n[4],m[3],u,v,a[3][N],x,lst,an;
segm fo[2];
void solve(){
	for(int i =0; i<4; i++) cin>>n[i];
	fo[0].build(n[0]);
	for(int i =0; i<3; i++){
		for(int j =0; j<n[i+1]; j++){
			cin>>a[i][j];
		}
	}
	for(int i =0; i<3; i++){
		cin>>m[i];
		for(int j = 0; j<m[i]; j++){
			cin>>u>>v;
			u--,v--;
			adj[i][v].EB(u);
		}
		for(int j =0; j<n[i+1]; j++){
			sort(all(adj[i][j]));
		}
	}
	x = 1;
	for(int i = 0; i<3; i++){
		fo[x].init(n[i+1]);
		for(int j =0; j<n[i+1]; j++){
			lst = 0, an = inf;
			for(auto &y : adj[i][j]){
				if(y > lst){
					an = min(an, fo[x^1].query(lst,y-1).n);
				}
				lst = y+1;
			}
			if(n[i] > lst){
				an = min(an, fo[x^1].query(lst,n[i]-1).n);
			}
			trace(i,j,an);
			fo[x].set(j,a[i][j]+an);
		}
		x ^=1;
	}
	x ^= 1;
	an = fo[x].query(0, n[3]-1).n;
	if(an == inf) an = -1;
	cout<<an<<endl;
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
	//cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}