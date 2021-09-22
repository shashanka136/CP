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
int n,x,y,in;
int a[305],b[305],dp[2][305][305];
void solve(){
	cin>>n>>x>>y;
	for(int i =0; i<n ;i++){
		cin>>a[i]>>b[i];
	}
	for(int i =0; i<=300; i++){
		for(int j =0; j<=300; j++){
			dp[0][i][j] = 500;
		}
	}
	dp[0][0][0] = 0;
	in = 0;
	for(int k=0; k<n; k++){
		in ^=1;
		for(int i =0; i<=300; i++){
			for(int j =0; j<=300; j++){
				dp[in][i][j] = dp[in^1][i][j];
			}
		}
		for(int i =0; i<=300; i++){
			for(int j =0; j<=300; j++){
				if(dp[in^1][i][j] == 500) continue;
				dp[in][min(300,i+a[k])][min(300,j+b[k])] = min(dp[in][min(300,i+a[k])][min(300,j+b[k])], 
					dp[in^1][i][j] +1);
			}
		}
	}
	int mn = 500;
	for(int i =x; i<=300; i++){
		for(int j =y; j<=300; j++){
			mn = min(mn, dp[in][i][j]);
		}
	}
	if(mn == 500) mn = -1;
	cout<<mn<<endl;
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