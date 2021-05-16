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
// #define endl '\n'
#define all(v) v.begin(), v.end()
const ll mod = 998244353;

//
struct edge {
	int u, v, lo;
	ll x;
	edge(){}
	edge(int _u, int _v, ll _x): u(_u), v(_v), x(_x) {
		lo = -1;
	}
	int get(int t) { return t ^ u ^ v;}
};

const int inf = INT_MAX;
struct item {
	int mx,cnt;
	item(int x = 0): mx(x), cnt(1) {}
	item operator+(const item& oth) { //operation to merge
		item r;//default is done for sum
		r.mx = max(mx, oth.mx);
		if(mx == oth.mx){
			r.cnt = cnt+oth.cnt;
		}else if( mx > oth.mx){
			r.cnt = cnt;
		}else{
			r.cnt = oth.cnt;
		}
		return r;
	}
};

template<class node>
struct segtree {
	int n;
	vector<node> st;

	void init(int _n) { //give some default value value if required
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

	void set(int i, ll x) {
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
};
typedef segtree<item> segm;

template<class node, class edge>
struct hld {
	int n,t;
	vector<int> tot, up, in, out, down, dep, par;
	vector<vector<ll>> val;
	vector<edge> edges;
	vector<vector<int>> adj;
	vector<segtree<node>> st;
	void init(int _n) {
		n = _n;t=0;
		st.resize(n); val.resize(n);
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
	// cerr<<v<<endl;
	// trace(adj[v]);
		int r = edges[adj[v][0]].get(v);
		for (auto& i : adj[v]) {//remember to emplace back in val[0]
			int u = edges[i].get(v);
			if (u == p) continue;
			up[u] = (u == r ? up[v] : u);
			val[up[u]].EB(edges[i].x);
			dfs_hld(u, v);
			if (u == r) down[v] = down[u];
		}
		out[v] = t;
	}

	void flst() {
		for (int i = 0; i < n; i++) {
			if (st[up[i]].n == 0) {
				st[up[i]].build(val[up[i]]);
			}
		}
	}
	void make(){
		dfs_tot();
		dfs_hld();
		flst();
	}
	int hin(int i) { //return index in heavy path
		return dep[i] - dep[up[i]];
	}

	void set(int i, ll x) {
		st[up[i]].set(hin(i), x);
	}

	node query(int l, int r) {// l,r on same heavy path
		return st[up[l]].query(hin(l), hin(r));
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
		res = res + st[up[a]].query(hin(a) + 1, hin(b)); // query [in[a],in[b]];
		return res;
	}
};
typedef hld<item, edge> hldm;
const int N = 2e5+5;
int n,m,u,v,w,p[N];
edge edges[N];
hldm fo;
item fo1,fo2;
int fin(int i){
	if(p[i] != i){
		p[i] = fin(p[i]);
	}
	return p[i];
}
void un(int i, int j){
	i = fin(i), j = fin(j);
	if(i == j) return;
	p[i] = j;
}

bool cmp(const edge &i, const edge &j){
	return (i.x < j.x);
}
void solve(){
	cin>>n>>m;
	for(int  i =0; i<m;i++){
		cin>>u>>v>>w;
		u--,v--;
		edges[i] = edge(u,v,w);
		// trace(edges[i].u, edges[i].v);
	}
	if(n == 1 && m == 0){
		cout<<0<<endl;
		return;
	}
	fo.init(n);
	sort(edges, edges+m,cmp);
	iota(p,p+n,0);
	for(int i =0; i<m;i++){
		// trace(edges[i].u, edges[i].v);
		u = fin(edges[i].u);
		v = fin(edges[i].v);
		if(u == v){
			edges[i].lo = 0;
		}else{
			un(u,v);
			// trace(edges[i].u, edges[i].v, edges[i].x);
			fo.add_edge(edges[i].u, edges[i].v, edges[i].x);
			edges[i].lo = 1;
		}
	}
	fo.val[0].EB(0);
	fo.make();
	int ans = 0;
	for(int i =0; i<m; i++){
		if(edges[i].lo == 0){
			fo1 = fo.path_query(edges[i].u, edges[i].v);
			// trace(i,fo1.mx, fo1.cnt, edges[i].u, edges[i].v, edges[i].x);
			fo2.mx = edges[i].x;
			fo2.cnt = 1;
			fo1 = fo1 + fo2;
			if(fo1.cnt > 1) ans++;
		}
	}
	cout<<ans<<endl;
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