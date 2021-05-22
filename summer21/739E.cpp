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
	int cost;
	edge(){}
	edge(int _u, int _v, int _c, int _cap): u(_u), v(_v), cost(_c), cap(_cap) {}
	int get(int t) { return t ^ u ^ v;}
};
const int inf = 1e9;
template <class edge, int inf>
class edkarp {
public:
	vector<edge> edges;
	vector<vector<int>> adj;
	int n;

	void init(int _n){
		n = _n;
		adj.assign(n, vector<int>(0));
	}

	inline int comp(int i){ return i^1;}//compliment edge

	inline int par(int i, int edge_num){ return edges[edge_num].get(i);}
	
	void add(int u, int v, long double co, int capac) {//co is cost, capac is capacity
		adj[u].emplace_back(edges.size());//adding an oriented edge
		edges.emplace_back(u,v,co,capac);
		adj[v].emplace_back(edges.size());
		edges.emplace_back(v,u,-co,0);
	}
	void shortest_path(int v, vector<ll> &d, vector<int> &p) {
		p.assign(n,-1);//we will put edge number in p
		d.assign(n,ll(1e18));
		vector<bool> inq(n,false);
		d[v] = 0;
		queue<int> q;
		q.push(v);
		inq[v] = true;
		while (!q.empty()) {
			int i = q.front();
			q.pop();
			inq[i] = false;
			for (auto &x : adj[i]) {
				int u = par(i,x);
				if (edges[x].cap && d[u] > d[i] + edges[x].cost) {
					d[u] = d[i] + edges[x].cost;
 					p[u] = x;
					if(!inq[u]){
						q.push(u);
						inq[u] = true;
					}
				}
			}
		}
	}

	ll mincost(int st, int tar, int k = inf) {
		// if there is need to upgrade number of nodes in graph
		vector<int> p;
		vector<ll> d;//num is the number of nodes
		int flow = 0;
		ll cost = 0;
		int nf;//new flow

		while(flow < k){
			shortest_path(st, d,p);
			if(d[tar] == ll(1e18)) break;
			nf = k-flow;
			int cr = tar;
			while(cr != st){
				nf = min(nf, edges[p[cr]].cap);
				cr = par(cr,p[cr]);
			}
			flow += nf;
			cost += nf*d[tar];
			cr = tar;
			while(cr != st){
				edges[p[cr]].cap -= nf;
				edges[comp(p[cr])].cap += nf;
				cr = par(cr,p[cr]);
			}
		}
		// if(flow < k) return -1;
		return cost;
	}
};
typedef edkarp<edge,inf> minfl;
//if you want to return mincost for maxflow change -1 to cost in mincost function
int n,a,b;
ld p[2002], q;
minfl fo;
void solve(){
	cin>>n>>a>>b;
	fo.init(n+4);
	fo.add(0,n+1,0,a);
	fo.add(0,n+2,0,b);
	for(int i =1; i<=n; i++){
		cin>>p[i];
		fo.add(n+1,i,-ll(1e9*p[i]),1);
		fo.add(i,n+3,0,1);
	}
	for(int i =1; i<=n; i++){
		cin>>q;
		fo.add(n+2,i,-ll(1e9*q),1);
		fo.add(i,n+3,ll(1e9*p[i]*q),1);
	}
	cout<<fixed<<setprecision(10)<<-((ld)(fo.mincost(0,n+3,a+b+1)))/1e9<<endl;;
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