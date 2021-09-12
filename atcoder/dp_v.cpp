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
const int N = 1e5+5;
int n,u,v,m,tot[N];
vi adj[N];
void solve(){
	cin>>n>>m;
	for(int i =1; i<n; i++){
		cin>>u>>v;
		u--,v--;
		adj[u].PB(v);
		adj[v].PB(u);
	}
	function<void(int,int)> dfs1 = [&](int i, int p){
		tot[i] = 1;
		for(int &x : adj[i]){
			if(x == p) continue;
			dfs1(x,i);
			tot[i] = (1ll*tot[i]*(tot[x]+1))%m;
		}
	};
	function<void(int,int, int)> dfs2 = [&](int i, int p, int val){
		vi le(sz(adj[i])+1, 1), ri(sz(adj[i])+1,1);
		for(int j =0; j <sz(adj[i]); j++){
			int x = adj[i][j];
			if(x == p){
				le[j+1] = le[j];
			}else{
				le[j+1] = 1ll*le[j]*(tot[x]+1)%m;
			}
		}
		for(int j =sz(adj[i])-1; j >= 0; j--){
			int x = adj[i][j];
			if(x == p){
				ri[j] = ri[j+1];
			}else{
				ri[j] = 1ll*ri[j+1]*(tot[x]+1)%m;
			}
		}
		tot[i] = 1ll*tot[i]*val%m;
		for(int j =0; j<sz(adj[i]); j++){
			int x = adj[i][j];
			if(x == p) continue;
			dfs2(x,i,(1ll*(1ll*le[j]*ri[j+1]%m)*val%m + 1)%m);
		}
	};
	dfs1(0,-1);
	dfs2(0,-1,1);
	for(int i = 0; i<n; i++){
		cout<<tot[i]<<endl;
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