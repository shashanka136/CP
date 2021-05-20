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

int n,m;

pii a[52],b[52];
vector<int> x,y;
dinic fo;
void solve(){
	cin>>n>>m;

	for(int i =0; i<m; i++){
		cin>>a[i].F>>a[i].S>>b[i].F>>b[i].S;
		a[i].F--;
		a[i].S--;
		x.PB(a[i].F);
		x.PB(b[i].F);
		y.PB(a[i].S);
		y.PB(b[i].S);
	}
	if(m == 0){
		cout<<0<<endl;
		return;
	}
	sort(all(x));
	sort(all(y));
	auto it = unique(all(x));
	x.resize(distance(x.begin(), it));
	it = unique(all(y));
	y.resize(distance(y.begin(), it));
	fo.init(sz(x) + sz(y));
	for(int i = 1; i<sz(x); i++){
		fo.add(0,i,x[i] - x[i-1]);
	}
	for(int i = 1; i<sz(y); i++){
		fo.add(sz(x)+i-1,sz(x)+sz(y)-1,y[i] - y[i-1]);
	}

	for(int i =1; i<sz(x); i++){
		for(int j =1; j<sz(y); j++){
			for(int k=0; k<m;k++){
				if(x[i-1] >= a[k].F && x[i] <= b[k].F && 
					y[j-1] >= a[k].S && y[j] <= b[k].S){
					fo.add(i,sz(x)+j-1, 1ll*(x[i]-x[i-1])*(y[j]-y[j-1]));
					break;
				}
			}
		}
	}
	int mx = fo.maxflow(0,sz(x)+sz(y)-1);
	cout<<mx<<endl;
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