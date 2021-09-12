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
struct edgem {
	int u, v, lo;
	ll x;
	edgem() {}
	edgem(int _u, int _v, ll _x): u(_u), v(_v), x(_x) {
		lo = -1;
	}
	int get(int t) { return t ^ u ^ v;}
};

const ll inf = LLONG_MAX;
struct item {
	ll n;
	item(ll x = 0): n(x) {}
	item operator+(const item& oth) { //operation to merge
		item r;
		r.n = n + oth.n;
		return r;
	}
};

template<class node>
struct segtree {
	ll n;
	vector<node> st;

	void init(ll _n) { //give some default value value if required
		n = _n;
		st.assign(2 * n, node());
	}
	inline int le(int x) {return 2 * x + 1;}
	inline int ri(int x) {return 2 * x + 2;}
	//change vector to int* if required in both build

	void build(vector<ll> &a) {
		init(a.size());
		for (int i = n; i < 2 * n; i++)
			st[i] = a[i - n];
		for (int i = n - 1; i > 0; i--)
			st[i] = st[i << 1] + st[i << 1 | 1];
	}

	void set(int i, ll x) {//change it to int if required
		for (st[i += n] = x; i >>= 1; )
			st[i] = st[i << 1] + st[i << 1 | 1];
	}

	node query(int l, int r) {
		node anl, anr; r++;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) anl = anl + st[l++]; //if l is right child then it's parent is not included
			if (r & 1) anr = st[--r] + anr; // if r is right child then r-1 is left child and same thing
			//parent is not included
		}
		return anl + anr;
	}

	/*int kth(int k, int l, int r, int p) {
		if(l == r){ return l;}
		int m = l+r>>1;
		if(st[le(p)].n >= k) return kth(k,l,m,le(p));
		else return kth(k-st[le(p)].n,m+1,r,ri(p));
	}

	int kth(int k) {
		return kth(k, 0, n - 1, 0);
	}*/
};
typedef segtree<item> segm;

template<class node, class edge>
struct hld {
	int n,t;
	vector<int> tot, up, in, out, down, dep, par;
	vector<ll> val;
	vector<edge> edges;
	vector<vector<int>> adj;
	segtree<node> st;
	void init(int _n) {
		n = _n;t=0;
		val.resize(n);
		tot.assign(n, 0); up.assign(n, 0);
		in.assign(n, 0); out.assign(n, 0); down.assign(n, 0);
		dep.assign(n, 0); par.assign(n, 0);
		adj.assign(n, vector<int>(0));
	}

	void add_edge(int u, int v, int x){
		adj[u].EB(edges.size());
		adj[v].EB(edges.size());
		edges.EB(u,v,x);
	}

	void dfs_tot(int v = 0, int p = -1) {
		tot[v] = 1;
		par[v] = p;
		for (auto &i : adj[v]) {
			int u = edges[i].get(v);
			int r = edges[adj[v][0]].get(v);
			if (u == p) continue;
			dep[u] = dep[v] + 1;
			edges[i].lo = u;//lo represents node of more depth
			dfs_tot(u, v);
			tot[v] += tot[u];
			if (adj[v][0] == p || tot[u] > tot[r]) {
				swap(i, adj[v][0]);
			}
		}
	}

	void dfs_hld(int v = 0, int p = -1) {//dfs_tot must be called first
		in[v] = t++; down[v] = v;
		int r = edges[adj[v][0]].get(v);
		for (auto& i : adj[v]) {//remember to emplace back in val[0]
			int u = edges[i].get(v);
			if (u == p) continue;
			up[u] = (u == r ? up[v] : u);
			dfs_hld(u, v);
			val[in[u]] = edges[i].x;
			if (u == r) down[v] = down[u];
		}
		out[v] = t;
	}

	void flst() {
		st.build(val);
	}

	void make(){
		dfs_tot();dfs_hld();
		flst();
	}
	
	void set(int i, ll x) {
		st.set(in[i], x);
	}

	node query(int l, int r) {// l,r on same heavy path
		return st.query(in[l], in[r]);
	}
	node path_query(int a, int b) { //from a to b
		node res;
		for (; up[a] != up[b]; b = par[up[b]]) {
			if (dep[up[a]] > dep[up[b]])
				swap(a, b);
			//query  [in[up[b]], in[b]]
			res = res + query(up[b], b);
		}
		if (dep[a] > dep[b])
			swap(a, b);
		if (a == b) return res;
		res = res + st.query(in[a] + 1, in[b]); // query [in[a],in[b]];
		return res;
	}
};
typedef hld<item, edgem> hldm;
struct edge {
	int u, v, w;
	edge(){}
	edge(int _u, int _v, int _d): u(_u), v(_v), w(_d) {}
	int get(int t) { return t ^ u ^ v;}
};
const int N = 1e5+5;
const int X = 23;
ll d[X][N];
edge edges[N];
vi adj[N];
bool inst[N];
int n,m,u,v,w;
int dsup[N];
int nodes[N];
hldm fo;
int fin(int i){
	if(dsup[i] != i){
		dsup[i] = fin(dsup[i]);
	}
	return dsup[i];
}
void un(int i, int j){
	i = fin(i), j = fin(j);
	if(i == j) return;
	dsup[i] = j;
}

template <typename T>
void djikstra(int i, int j){
	fill(d[j],d[j]+n,inf);
	set<pair<T,int>> q;
	d[j][i] = 0;
	q.insert(MP(0,i));
	while(!q.empty()){
		int v = q.begin()->second;
		q.erase(q.begin());
		for(int x : adj[v]){
			int u = edges[x].get(v);
			if(d[j][v] + edges[x].w < d[j][u]){
				q.erase(MP(d[j][u],u));
				d[j][u] = d[j][v] + edges[x].w;
				q.insert(MP(d[j][u],u));
			}
		}
	}
}//inf needs to be defined, edges too having attribute w
void solve(){
	cin>>n>>m;
	iota(dsup, dsup+n,0);
	fill(inst, inst+m,false);
	fo.init(n);
	for(int i =0 ;i <m; i++){
		cin>>u>>v>>w;
		u--,v--;
		// trace(i,u,v);
		adj[u].PB(i);
		adj[v].PB(i);
		edges[i] = edge(u,v,w);
		u = fin(u);
		v = fin(v);
		if(u != v){
			fo.add_edge(edges[i].u, edges[i].v, edges[i].w);
			inst[i] = true;
			dsup[u] = v;
		}
	}
	fo.make();
	// trace(MP(inst,m));
	// trace(MP(adj,n));
	// for(int i =0; i<n; i++) trace(i,MP(dis[i],3));
	fill(nodes,nodes+n,-1);
	int cr =0;
	vi inex;
	for(int i =0; i<m; i++){
		if(!inst[i]){
			if(nodes[edges[i].u] == -1){
				djikstra<ll>(edges[i].u,cr);
				inex.PB(edges[i].u);
				nodes[edges[i].u] = cr++;
			}
		}
	}
	// for(int i =0; i<cr ;i++) trace(MP(d[i],n));
	int q;
	cin>>q;
	for(int i =0 ;i <q; i++){
		cin>>u>>v;
		u--,v--;
		if(u == v){
			cout<<0<<endl;
			continue;
		}
		ll ans = fo.path_query(u,v).n;
		// trace(ans);
		for(int j =0; j<cr; j++){
			ans = min(ans, d[j][u] + d[j][v]);
		}
		cout<<ans<<endl;
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
	// cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}