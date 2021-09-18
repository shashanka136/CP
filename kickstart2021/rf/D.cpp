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
const int N = 20;
const int pown = 1e6;
int n,m,k;
ll dp[pown];
int l[N],r[N],a[N],u,v;
int adj[N][N];
void solve(){
	cin>>n>>m>>k;
	for(int i =0; i<n; i++) cin>>l[i]>>r[i]>>a[i];

	for(int i=0; i<n; i++){
		for(int j =0; j<n; j++){
			adj[i][j] = 0;
		}
	}
	for(int i =0; i<m; i++){
		cin>>u>>v;
		adj[u][v] = 1, adj[v][u] = 1;
	}
	fill(dp,dp+(1<<n), -1);
	ll tot,ans = 0;
	for(int i =1; i<(1<<n); i++){
		tot = 0;
		vi v;
		for(int j =0; j<n; j++){
			if(i>>j&1){
				v.PB(j);
				tot += a[j];
			}
		}
		// trace(i,tot);
		if(sz(v) ==1){
			dp[i] = 1;
			if(tot == k) ans++;
			continue;
		}
		bool fo = 0;
		dp[i] = 0;
		for(int x : v){
			fo =1;
			if(tot-a[x] > r[x] || tot-a[x] < l[x]) continue;
			fo = 0;
			for(int y : v){
				if(y == x) continue;
				if(adj[y][x]){
					fo = 1; break;
				}
			}
			dp[i] += dp[i^(1<<x)];
			if(!fo) break;
		}
		if(!fo){
			dp[i] = 0;
			continue;
		}
		if(tot == k) ans += dp[i]; 
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
	cin>>t;
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
}