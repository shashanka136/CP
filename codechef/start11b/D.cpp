/* AUTHOR - MAHADEV( codechef - @har_harmahadev) */
#include <bits/stdc++.h>
#ifdef STAC
#include <sys/resource.h>
#endif
#pragma GCC optimize("-O3")
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
const ll mod = 1e9+7;

const int N = 1e5+5;

int dp[2][N],b[N],n;
int mn = 0, mx = 1e5;
void solve(){
	cin>>n;
	INP(b,n-1);
	b[n-1] = mn-1;
	dp[0][0] = mx-b[0];
	dp[1][0] = 1;
	for(int i =1; i<n; i++){
		if(b[i] > b[i-1]){
			dp[1][i] = dp[1][i-1];
			dp[0][i] = 1ll*dp[1][i-1]*(mx-b[i])%mod;
		}else if(b[i] < b[i-1]){
			dp[1][i] = 0;
			dp[0][i] = (dp[0][i-1] + 1ll*dp[1][i-1]*(mx-b[i-1]+1)%mod)%mod;
		}else{
			dp[1][i] = (dp[1][i-1] + dp[0][i-1])%mod;
			dp[0][i] = 1ll*dp[1][i-1]*(mx-b[i])%mod;
		}
	}
	cout<<dp[0][n-1]<<endl;
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
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}