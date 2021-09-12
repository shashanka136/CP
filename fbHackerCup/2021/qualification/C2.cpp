/* AUTHOR - SHASHANK AGRAWAL (codeforces - @shashanka136) ( codechef - @shashank_vasu) */
#include <bits/stdc++.h>
#include <sys/resource.h>
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
const int N = 55;
struct edge {
	int u, v;
	edge(int _u, int _v): u(_u), v(_v) {}
	int get(int t) { return t ^ u ^ v;}
};
int n,c[N],u,v;
vector<edge> eds;
vi adj[N];
void solve(){
	cin>>n;
	INP(c,n);
	for(int i = 1; i<n; i++){
		cin>>u>>v;
		u--,v--;
		adj[u].PB(eds.size());
		adj[v].PB(eds.size());
		eds.emplace_back({u,v});
	}
	function<int(int,int)> dfs = [&](int i, int p){
		int ans = 0;
		for(int &x : adj[i]){
			if(x == p) continue;
			ans = max(ans, dfs(x,i));
		}
		ans += c[i];
		return ans;
	};
	vi st;
	for(int x : adj[0]){
		st.PB(dfs(x,0));
	}
	fill(adj,adj+n,vi(0));
	sort(all(st), greater<int>());
	if(sz(st) == 0){
		cout<<c[0]<<endl;
		return;
	}
	if(sz(st) == 1){
		cout<<c[0] + st[0]<<endl;
		return;
	}
	cout<<c[0] + st[0] + st[1]<<endl;
	return;
}

int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	rlimit rlim;
	if(getrlimit(RLIMIT_STACK, &rlim)) return 1;//getrlimit returns -1 when error
	rlim.rlim_cur = rlim.rlim_max;

	if(setrlimit(RLIMIT_STACK, &rlim)) return 2;//setrlimit too returns -1 when error
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	cin>>t;
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
}