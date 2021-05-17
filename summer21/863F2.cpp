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
	int u, v,cost,cap;
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
	
	void add(int u, int v, int co, int capac) {//co is cost, capac is capacity
		adj[u].emplace_back(edges.size());//adding an oriented edge
		edges.emplace_back(u,v,co,capac);
		adj[v].emplace_back(edges.size());
		edges.emplace_back(u,v,-co,0);
	}
	void shortest_path(int v, vector<int> &d, vector<int> &p) {
		p.assign(n,-1);//we will put edge number in p
		d.assign(n,inf);
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

	int mincost(int st, int tar, int k = inf) {
		// if there is need to upgrade number of nodes in graph
		vector<int> p,d;//num is the number of nodes
		int flow = 0, cost = 0;
		int nf;//new flow

		while(flow < k){
			shortest_path(st, d,p);
			if(d[tar] == inf) break;
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

int n,q;
int l,r,v,typ;
int mn[102],mx[102];
void ret(){
	cout<<-1<<endl;
}
minfl fo;
void solve(){
	cin>>n>>q;
	fill(mn,mn+n,1);
	fill(mx,mx+n,n);
	for(int i =0; i<q; i++){
		cin>>typ>>l>>r>>v;
		l--,r--;
		if(typ == 1){
			for(int j =l; j<=r; j++){
				if(mx[j] < v) return ret();
				mn[j] = max(mn[j], v);
			}
		}else{
			for(int j =l; j<=r; j++){
				if(mn[j] > v) return ret();
				mx[j] = min(mx[j], v);
			}
		}
	}
	fo.init(2*n+2);
	for(int i =1; i<=n; i++){
		for(int j=0,k=1; j<n; j++, k+=2){
			fo.add(0,i,k,1);
		}
		fo.add(n+i,2*n+1,0,1);
	}
	for(int i =0; i<n; i++){
		for(int j = mn[i]; j<= mx[i]; j++){
			fo.add(j,n+i+1,0,1);
		}
	}
	cout<<fo.mincost(0,2*n+1)<<endl;
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