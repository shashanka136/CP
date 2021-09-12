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

struct euler_path{
	struct edge {
		int u, v, num;
		edge(){}
		edge(int _u, int _v): u(_u), v(_v), num(-1) {}
		int get(int t) { return t ^ u ^ v;}
	};
	int n,m;
	vector<vector<pair<int,int>>> fin;
	vector<int> deg;
	vector<edge> edges;
	vector<vector<int>> adj;

	void init(int _n){
		n = _n;
		m = 0;
		adj.assign(n,vector<int>(0));
		deg.assign(n,0);
	}

	void add_edge(int u, int v){
		deg[u]++,deg[v]++;
		adj[u].PB(edges.size());
		adj[v].PB(edges.size());
		edges.emplace_back(u,v);
		m++;
	}

	bool find_eulerian_path(){
		vector<int> cr(n,0);
		function<void(int)> one = [&](int fst){
			stack<pair<int,int>> st;
			st.push(make_pair(fst,-1));
			vector<pair<int,int>> fn;
			while(!st.empty()){	
				int v = st.top().first;
				int edge_num = st.top().second;
				int &i = cr[v];
				for(; i<deg[v] && edges[adj[v][i]].num != -1; i++);
				if(i == deg[v]){
					fn.push_back(st.top());
					st.pop();
				}else{
					st.push(make_pair(edges[adj[v][i]].get(v), adj[v][i]));
					edges[adj[v][i]].num = 0;
					i++;
				}
			}
			fin.PB(fn);
		};
		
		for(int i =0; i<n; i++){
			if(cr[i] != deg[i]) one(i);
		}
		return true;
	}

};

const int N = 1e6+6;
int n,m,fm;
int u,v;
euler_path fo;
bool del[N];
void work(int i, vector<pair<int,int>> &vv){
	// trace(i,(i+1)%fo.m, (i+fo.m-1)%fo.m);
	// trace(sz(fo.fin)); 
	if(vv[i].S >= m) return;
	if(vv[(i+1)%(sz(vv)-1)].S >= m) return;
	if(vv[(i+(sz(vv)-1)-1)%(sz(vv)-1)].S >= m) return;
	del[vv[i].S] = true;
	fm--;
}

void solve(){
	cin>>n>>m;
	fm = m;
	fill(del,del+m,false);
	fo.init(n+1);
	for(int i =0; i<m; i++){
		cin>>u>>v;
		fo.add_edge(u,v);
	}
	for(int i =1; i<=n; i++){
		if(fo.deg[i]&1){
			// trace(i,fo.deg[i]);
			fo.add_edge(0,i);
			// trace(i,fo.deg[i]);
		}
	}
	fo.find_eulerian_path();
	// trace(fo.m);
	// trace(fo.fin);
	for(auto &vv : fo.fin){
		for(int i = 1; i<sz(vv)-1; i+=2){
			work(i,vv);
		}
	}
	cout<<fm<<endl;
	for(int i =0; i<m ;i++){
		if(del[i]) continue;
		cout<<fo.edges[i].u<<" "<<fo.edges[i].v<<endl;
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