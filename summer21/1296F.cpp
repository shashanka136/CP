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
const int N = 5e3+5;
struct edge {
	int u, v;
	edge(){}
	edge(int _u, int _v): u(_u), v(_v) {}
	int get(int t) { return t ^ u ^ v;}
};

struct query {
	int u, v, mn;
	query(){}
	query(int _u, int _v, int _mn): u(_u), v(_v), mn(_mn) {}
};
int n, m, ans[N], p[N], u, v, ind[N],g,cnt;

vector<edge> edges;
vector<query> qs;
vi adj[N];

bool cmp(const int &i, const int &j){
	return (qs[i].mn > qs[j].mn) || (qs[i].mn == qs[j].mn && i < j);
}
void solve(){
	cin>>n;
	fill(ans,ans+n,-1);
	for(int i =1; i<n; i++){
		cin>>u>>v;
		u--,v--;
		adj[u].PB(sz(edges));
		adj[v].PB(sz(edges));
		edges.EB(u,v);
	}
	cin>>m;
	// for(int i=0;i<n;i++) trace(i,adj[i]);
	for(int i =0; i<m; i++){
		cin>>u>>v>>g;
		u--,v--;
		qs.EB(u,v,g);
	}
	iota(ind,ind+m,0);
	sort(ind,ind+m,cmp);

	function<void(int, int)> dfs = [&](int i, int par){
		for(int &x : adj[i]){
			if(x == par) continue;
			p[edges[x].get(i)] = x;
			dfs(edges[x].get(i), x);
		}
	};
	for(int i =0; i<m;i++){
		fill(p,p+n,-1);
		u = qs[ind[i]].u;
		v = qs[ind[i]].v;
		g = qs[ind[i]].mn;
		dfs(u,-1);
		cnt = 0;
		while(v != u){
			if(ans[p[v]] != -1){
			// trace(v,u,p[v]);
				if(ans[p[v]] == g) cnt++;
				v = edges[p[v]].get(v);
				continue;
			}
			// trace(v,u);
			ans[p[v]] = g;
			cnt++;
			v = edges[p[v]].get(v);
		}
		if(cnt == 0){
			cout<<-1<<endl;
			return;
		}
	}
	for(int i =0; i<n-1; i++){
		if(ans[i] == -1) ans[i] = 1e6;
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
	//cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}