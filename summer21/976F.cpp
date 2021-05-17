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
int n1,n2,m,u,v;
int deg1[2003],deg2[2003];
int mindeg =3000;
vi ans[2003];
edkarp fo;
pii ed[2004];
void solve(){
	cin>>n1>>n2>>m;
	fill(deg1, deg1+n1,0);
	fill(deg2, deg2+n2,0);
	for(int i =0; i<m; i++){
		cin>>u>>v;
		ed[i].F = u;
		ed[i].S = v;
		deg1[u]++;
		deg2[v]++;
	}
	for(int i =1; i<=n1; i++){
		mindeg = min(mindeg, deg1[i]);
	}
	for(int i =1; i<=n2; i++){
		mindeg = min(mindeg, deg2[i]);
	}
	fo.init(n1+n2+2);
	for(int i =1; i<=n1; i++){
		fo.add(0, i, deg1[i]-mindeg);
	}
	for(int i =0; i<m; i++){
		fo.add(ed[i].F, ed[i].S+n1,1);
	}
	for(int i =n1+1; i<=n1+n2; i++){
		fo.add(i, n1+n2+1, deg2[i-n1] - mindeg);
	}
	int cr = mindeg;
	while(cr >= 0){
		u = fo.maxflow(0,n1+n2+1);
		for(int i =n1; i<n1+m; i++){
			if(fo.edges[2*i].cap == 1){
				ans[cr].PB(i-n1+1);
			}
		}
		for(int i =0; i<n1; i++){
			fo.edges[2*i].cap++;
		}
		for(int i =n1+m; i<n1+m+n2; i++){
			fo.edges[2*i].cap++;
		}
		cr--;
	}
	for(int i =0; i<=mindeg; i++){
		cout<<sz(ans[i])<<" ";
		for(auto x : ans[i]) cout<<x<<" ";
		cout<<endl;
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