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
	int u, v, w;
	edge(){}
	edge(int _u, int _v, int _d): u(_u), v(_v), w(_d) {}
	int get(int t) { return t ^ u ^ v;}
};
const int N = 1e5+5;
const int X = 23;
const ll inf = 1e18;
ll d[X][N];
edge edges[N];
vi adj[N];
bool inst[N];
int p[N][20],dep[N],n,m,u,v,w;
ll dis[N][20];
int dsup[N];
int nodes[N];

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

void dfs(int i, int pr){
	for(auto y : adj[i]){
		if(!inst[y]) continue;
		int x = edges[y].get(i);
		if(x == pr) continue;
		dep[x] = dep[i]+1;
		// trace(i,y,x);
		p[x][0] = i;
		dis[x][0] = edges[y].w;
		f(j,1,19,1) p[x][j] = p[p[x][j-1]][j-1];
		f(j,1,19,1) dis[x][j] = dis[x][j-1] + dis[p[x][j-1]][j-1];
		dfs(x,i);
	}
}
void swap(int &i, int &j){
	if(dep[i]  >dep[j]) return;
	int tmp = j;
	j = i;
	i = tmp;
}

ll uplift(int &i, int diff){
	ll ans = 0;
	f(bit,0,19,1){
		if(diff>>bit&1){
			// trace(i,bit,dis[i][bit]);
			ans += dis[i][bit];
			i = p[i][bit];
		}
	}
	return ans;
}

ll lca(int i, int j){
	swap(i,j);
	int diff = dep[i] - dep[j];
	// trace(i,j,diff);
	ll ans = uplift(i,diff);
	if(i == j) return ans;
	f(bit,18,-1,-1){
		if(p[i][bit] != p[j][bit]){
			ans += dis[i][bit];
			ans += dis[j][bit];
			i = p[i][bit];
			j = p[j][bit];
		}
	}
	ans += dis[i][0];
	ans += dis[j][0];
	return ans;
}//declare adj,dep,p

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
			inst[i] = true;
			dsup[u] = v;
		}
	}
	// trace(MP(inst,m));
	// trace(MP(adj,n));
	fill(p[0], p[0] + 20,0);
	dep[0] = 0;
	dfs(0,-1);
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
		ll ans = lca(u,v);
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