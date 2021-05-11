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
const int N = 2e5+4;
int n,m,u,v,siz[N],p[N],comps;
string s;
struct modify{
	int i,j,si,sj;

};
stack<int> lens;
stack<modify> mods;
void persist(){
	lens.push(sz(mods));
}
void rollback(){
	while(sz(mods) > lens.top()){
		p[mods.top().i] = mods.top().i;
		siz[mods.top().j] = mods.top().sj;
		comps += 1;
		mods.pop();
	}
	lens.pop();
}
int fin(int i){
	while(p[i]!= i){
		i = p[i];
	}
	return p[i];
}
void un(int i, int j){
	i = fin(i), j = fin(j);
	if(i == j) return;
	if(siz[i] > siz[j]) swap(i,j);
	mods.push({i,j,siz[i], siz[j]});
	p[i] = j;
	comps -= 1;
	siz[j] += siz[i];
}
void solve(){
	cin>>n>>m;
	comps= n;
	fill(siz,siz+n,1);
	for(int i =0; i<n; i++) p[i] = i;
	for(int i =0; i<m; i++){
		cin>>s;
		if(s[0] == 'u'){
			cin>>u>>v;
			u--,v--;
			un(u,v);
			cout<<comps<<endl;
		}else if(s[0] == 'p'){
			persist();
		}else{
			rollback();
			cout<<comps<<endl;
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
	//cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}