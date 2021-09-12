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
const ll mod = 1e9+7;

//
struct edge {
	int u, v, c;
	edge(){}
	edge(int _u, int _v, int _c): u(_u), v(_v), c(_c) {}
	int get(int t) { return t ^ u ^ v;}
	bool operator<(const edge &oth) const{
		return c > oth.c;
	}
};
const int N = 8e5+5;
int n,u,v,c,p[N],siz[N];
edge edges[N];
vi adj[N];
int dp1[N][22], dp2[N][22];

int fin(int i){
	if(p[i] != i){
		p[i] = fin(p[i]);
	}
	return p[i];
}
void un(int i, int j){
	i = fin(i), j = fin(j);
	if(i == j) return;
	if(siz[i] > siz[j]) swap(i,j);
	p[i] = j;
	siz[j] += siz[i];
}

void solve(){
	cin>>n;
	for(int i =1; i<n; i++){
		cin>>u>>v>>c;
		u--,v--;
		adj[u].PB(i-1);
		adj[v].PB(i-1);
		edges[i-1] = {u,v,c};
	}
	function<void(int,int)> dfs1 = [&](int i, int p){
		fill(dp1[i], dp1[i]+22,1);
		for(int j : adj[i]){
			int x = edges[j].get(i);
			if(x == p) continue;
			dfs1(x,i);
			for(int c =1; c<=edges[j].c; c++){
				dp1[i][c] += dp1[x][c];
			}
		}
	};
	function<void(int,int)> dfs2 = [&](int i, int p){
		for(int j : adj[i]){
			int x = edges[j].get(i);
			if(x == p) continue;
			fill(dp2[x], dp2[x]+22,0);
			for(int c =1; c<=edges[j].c; c++){
				dp2[x][c] += dp2[i][c] +dp1[i][c] - dp1[x][c];
			}
			dfs2(x,i);
		}
	};
	dfs1(0,-1);
	// for(int j =0; j<n; j++)
	// trace(j,MP(dp1[j],22));
	fill(dp2[0], dp2[0]+21,0);
	dfs2(0,-1);
	int tot =0;
	sort(edges,edges+n-1);
	iota(p,p+n,0);
	fill(siz,siz+n,1);
	for(int i =0;i<n-1; i++){
		u = fin(edges[i].u);v = fin(edges[i].v);
		tot = (tot + 1ll*siz[u]*siz[v]%mod*edges[i].c%mod)%mod;
		un(u,v);
	}
	int ans = 1;
	for(int i =1; i<n; i++){
		int zi = 0;
		int p,pprev;
		pprev = 0, p = 1ll*dp1[i][20]*dp2[i][20]%mod;
		for(int c = 20; c>0; c--){
			p = 1ll*dp1[i][c]*dp2[i][c]%mod;
			zi = (zi + 1ll*c*(p -pprev+mod)%mod)%mod;
			pprev = p;
		}
		ans = 1ll*ans*(tot-zi+mod)%mod;
	}
	cout<<ans<<endl;
	for(int i =0; i<n; i++) adj[i] = vi(0);
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
	cin>>t;
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
}