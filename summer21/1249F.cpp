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
const int N = 205;
int dp[N][N],a[N],n,k,u,v;

vi adj[N];

void solve(){
	cin>>n>>k;
	INP(a,n);
	for(int i =0; i<=n; i++){
		for(int j =0; j<=n; j++){
			dp[i][j] = 0;
		}
	}
	for(int i =0; i<n-1; i++){
		cin>>u>>v;
		u--,v--;
		adj[u].PB(v);
		adj[v].PB(u);
	}
	function<void(int, int)> dfs = [&](int i, int p){
		dp[i][0] = a[i];
		for(auto x : adj[i]){
			if(x == p) continue;
			dfs(x,i);
			for(int j =k/2; j<k; j++){
				dp[i][j+1] += dp[x][j];
			}
			dp[i][0] += dp[x][k];
		}
		for(int j = 0; 2*j+1 < k; j++){
			dp[i][j+1] = 0;
			for(auto x: adj[i]){
				if(x == p) continue;
				dp[i][j+1] = max(dp[i][j+1], dp[x][j] + dp[i][k-j] - dp[x][k-j-1]);
			}
		}
		for(int j = k-1; j>=0; j--){
			dp[i][j] = max(dp[i][j], dp[i][j+1]);
		}
	};
	dfs(0,-1);
	cout<<dp[0][0]<<endl;
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