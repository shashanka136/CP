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
		edges.emplace_back(v,u,-co,0);
	}
	void shortest_path(int v, vector<int> &d, vector<int> &p) {
		p.assign(n,-1);//we will put edge number in p
		d.assign(n,inf);
		d[v] = 0;
		bool change = false;
		for(int i =0 ; i<n-1; i++){
			change = false;
			for(int j = 0; j< edges.size(); j++){
				if(d[edges[j].u] == inf || edges[j].cap == 0) continue;
				if(d[edges[j].v] > d[edges[j].u] + edges[j].cost){
					d[edges[j].v] = d[edges[j].u] + edges[j].cost;
					p[edges[j].v] = j;
					change = true;
				}
			}
			if(!change) break;
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


void prefix_func(string &s, vi & v){
	int n = s.size();
	v.assign(n,0);
	for(int i =1; i<n; i++){
		int j = v[i-1];
		while(j >= 0 && s[j] != s[i]){
			j = j ==0? -1 : v[j-1];
		}
		v[i] = j+1;
	}
}
int n,m,p[104],x,cr;
string s,w[104];
vi v;
minfl fo;
void solve(){
	cin>>n>>s;
	cin>>m;
	fo.init(n+2);
	fo.add(0,1,0,100);
	for(int i =1; i<=n;i++){
		fo.add(i,i+1,0,100);
	}
	for(int i =0; i<m; i++){
		cin>>w[i]>>p[i];
		prefix_func(w[i],v);
		cr = 0;
		for(int j =0; j<n; j++){
			while(cr >= 0 && s[j] != w[i][cr]){
				cr = cr==0? -1 : v[cr-1];
			}
			cr++;
			if(cr == sz(w[i])){
				cr = v[cr-1];
				fo.add(j-sz(w[i])+2, j+2, -p[i], 1);
			}
		}
	}
	// for(int i =0; i<fo.edges.size(); i++){
	// 	cout<<fo.edges[i].u<<" "<<fo.edges[i].v<<" "<<fo.edges[i].cost<<" "<<fo.edges[i].cap<<endl;
	// }
	cin>>x;
	cout<<-fo.mincost(0,n+1,x)<<endl;
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