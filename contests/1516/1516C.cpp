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
int n;
int a[104];
int sm;
void solve(){
	cin>>n;
	INP(a,n);
	sm = 0;
	for(int i =0; i<n; i++){
		sm += a[i];
	}
	if(sm%2 != 0){
		cout<<0<<endl;return;
	}
	sm /= 2;
	trace(sm);
	vvi dp(sm+1,vi(n+1,0)); 
	dp[0][0] = 1;
	trace(dp[0][0]);
	for(int i =0; i<=sm ;i++){
		for(int j = 1; j<=n; j++){
			if(i >= a[j-1]) dp[i][j] = dp[i][j-1] | dp[i-a[j-1]][j-1];
		}
	}
	trace(dp[sm][n]);
	if(dp[sm][n] == 0){
		cout<<0<<endl;
		return;
	}
	int gc = 0;
	for(int i =0; i<n; i++){
		gc = __gcd(a[i], gc);
	}
	int x= 1;
	while(true){
		if(gc%(x<<1)){
			break;
		}else{
			x <<= 1;
		}
	}
	int ind=0;
	for(int i =0; i<n; i++){
		if((a[i]/x)%2){
			ind = i;
			break;
		}
	}
	cout<<1<<endl<<ind+1<<endl;
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