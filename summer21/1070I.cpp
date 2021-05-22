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
struct edge {
	int u, v;
	long long cap;
	edge(){}
	edge(int _u, int _v, long long cap): u(_u), v(_v), cap(cap) {}
	int get(int t) { return t ^ u ^ v;}
};

struct dinic{
	const long long inf = 1e18;
	int n,st,tar;
	vector<edge> edges;
	vector<vector<int>> adj;
	vector<int> lvl,from;

	inline int comp(int i){ return i^1;}//compliment edge

	inline int par(int i, int edge_num){ return edges[edge_num].get(i);}
	
	void init(int _n){
		n = _n;
		adj.assign(n, vector<int>(0));
		edges.assign(0, edge());
	}

	void add(int u, int v, long long cap){
		adj[u].push_back(edges.size());
		edges.emplace_back(u,v,cap);
		adj[v].push_back(edges.size());
		edges.emplace_back(v,u,0);
	}

	void bfs(){
		lvl.assign(n,-1);
		lvl[st] = 0;
		queue<int> q;
		q.push(st);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(int i : adj[u]){
				if(lvl[par(u,i)] != -1 || edges[i].cap == 0) continue;
				lvl[par(u,i)] = lvl[u] +1;
				q.push(par(u,i));
			}
		}
	}

	int dfs(int u, long long mnflow){
		if(u == tar) return mnflow;
		for(int& i = from[u]; i < adj[u].size(); i++){
			int v = par(u,adj[u][i]);
			if(lvl[v] != lvl[u] +1 || edges[adj[u][i]].cap == 0) continue;
			int ret = dfs(v,min(mnflow, edges[adj[u][i]].cap));
			if(ret == 0) continue;
			edges[adj[u][i]].cap -= ret;
			edges[comp(adj[u][i])].cap += ret;
			return ret;
		}
		return 0;
	}

	long long maxflow(int _st, int _tar){
		st = _st;
		tar = _tar;
		long long flow = 0;
		while(1){
			bfs();
			if(lvl[tar] == -1) break;
			from.assign(n,0);
			while(long long nf = dfs(st, inf)){
				flow += nf;
			}
		}
		return flow;
	}
};
//takes O(E*sqrt(v)) for unit graph
const int N = 620;
int n,m,k,deg[N],u,v,req,ans[N];
dinic fo;
void solve(){
	cin>>n>>m>>k;
	fill(ans,ans+m+1,-1);
	fill(deg,deg+n,0);
	fo.init(n+m+2);
	req = 0;
	for(int i =1; i<=m; i++){
		cin>>u>>v;
		fo.add(i,u+m,1);
		fo.add(i,v+m,1);
		fo.add(0,i,1);
		u--,v--;
		deg[u]++;deg[v]++;
	}
	for(int i =0; i<n; i++){
		if(deg[i] > k){
			fo.add(m+i+1, n+m+1, 2*(deg[i]-k));
			req += 2*(deg[i]-k);
		}
	}
	int x = fo.maxflow(0,n+m+1);
	if(x != req){
		for(int i =0; i<m; i++) cout<<0<<" ";
		cout<<endl;
		return;
	}
	int cr = 1,indic;
	for(int i =m+1; i<=m+n; i++){
		if(deg[i-m-1] <= k) continue;
		indic = 0;
		for(int j : fo.adj[i]){
			if(fo.par(i,j) > m || fo.edges[j].cap == 0) continue;
			ans[fo.par(i,j)] = cr;
			if(indic) cr++;
			indic ^= 1;
		}
	}
	for(int i = 1; i<=m; i++){
		if(ans[i] == -1) ans[i] = cr++;
		cout<<ans[i]<<" ";
	}
	cout<<endl;
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
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}