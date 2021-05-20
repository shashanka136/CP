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
	int u, v,cap;
	edge(){}
	edge(int _u, int _v, int _cap): u(_u), v(_v), cap(_cap) {}
	int get(int t) { return t ^ u ^ v;}
};
const int inf = 1e9;
struct edkarp {
	vector<edge> edges;
	vector<vector<int>> adj;
	int n;
	void init(int _n){
		n = _n;
		adj.assign(n, vector<int>(0));
	}

	inline int comp(int i){ return i^1;}

	inline int par(int i, int ed){ return edges[ed].get(i);}

	void add(int u, int v, int c) {
		adj[u].emplace_back(edges.size());
		edges.emplace_back(u,v,c);
		adj[v].emplace_back(edges.size());
		edges.emplace_back(u,v,0);
	}
	int bfs(int st, int tar, vector<int> &p) {
		p.assign(n,-1);
		p[st] = -2;
		queue<pair<int, int>> q;
		q.push(MP(st, inf));
		while (!q.empty()) {
			int i = q.front().F, flow = q.front().S;
			q.pop();
			for (auto &x : adj[i]) {
				if (p[par(i,x)] == -1 && edges[x].cap) {
					p[par(i,x)] = x;
					int nf = min(flow, edges[x].cap);
					if (par(i,x) == tar) {
						return nf;
					}
					q.push(MP(par(i,x), nf));
				}
			}
		}
		return 0;
	}

	int maxflow(int st, int tar) {
		// if there is need to upgrade number of nodes in graph
		vector<int> p(n);//num is the number of nodes
		int flow = 0;
		int nf;//new flow

		while (nf = bfs(st, tar, p)) {
			flow += nf;
			int cr = tar;
			while (cr != st) {
				edges[p[cr]].cap -= nf;
				edges[comp(p[cr])].cap += nf;
				cr = par(cr,p[cr]);
			}
		}

		return flow;
	}
};
struct edgeg {
	int u, v,c,lo;
	bool in_loop = false;
	edgeg(){}
	edgeg(int _u, int _v, int _c): u(_u), v(_v), c(_c), lo(-1) {}
	int get(int t) { return t ^ u ^ v;}
};

const int N = 1e4+5;
int n,m,u,v,c, vis[N], p[N],vis1[N];
vi adj[N];
vector<bool> avai;
vector<vector<int>> loops;
vector<edgeg> edges;
edkarp fo;
inline int geta(int x, int edge_num){ return edges[edge_num].get(x);}

void dfs(int i, int par){
	vis[i] = 1;
	vis1[i] = 1;
	for(int x : adj[i]){
		int u = geta(i,x);
		if(u == par) continue;
		if(vis[u]){
			if(!vis1[u]) continue;
			edges[x].in_loop = true;
			vector<int> clrs;
			clrs.PB(edges[x].c);
			u = i;
			while(u != geta(i,x)){
				edges[p[u]].in_loop = true;
				clrs.PB(edges[p[u]].c);
				u = geta(u,p[u]);
			}
			sort(all(clrs));
			auto it = unique(all(clrs));
			if( it != clrs.end()){
				for(auto it1 = clrs.begin(); it1 != it; it1++){
					avai[*it1] = 1;
				}
			}else{
				loops.PB(clrs);
			}
		}else{
			p[u] = x;
			dfs(u,i);
		}
	}
	vis1[i] = 0;
}

void solve(){
	cin>>n>>m;
	avai.assign(m,0);
	for(int i = 0; i<m; i++){
		cin>>u>>v>>c;
		u--,v--,c--;
		adj[u].PB(edges.size());
		adj[v].PB(edges.size());
		edges.EB(u,v,c);
	}
	fill(vis,vis+n,0);
	fill(vis1,vis1+n,0);
	dfs(0,-1);
	int cr = 0;
	for(int i =0; i< sz(edges); i++){
		if(!edges[i].in_loop){
			avai[edges[i].c] = 1;
		}
	}
	fo.init(sz(loops) + m+2);
	for(int i=0; i<sz(loops); i++){
		fo.add(0,i+1,sz(loops[i])-1);
		for(int c : loops[i]){
			if(avai[c]) continue;
			fo.add(i+1, sz(loops)+1+c, 1);
		}
	}
	int flow = 0;
	for(int i=0; i<m; i++){
		flow += avai[i];
	}
	for(int i = sz(loops)+1; i <=sz(loops) + m; i++){
		fo.add(i,sz(loops) + m+1,1);
	}
	flow += fo.maxflow(0,sz(loops) + m+1);
	cout<<flow<<endl;
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