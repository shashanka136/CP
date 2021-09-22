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
const ll mod = 1e9+7;

//
struct factorial{
	int n;
	ll mod;
	int *a,*ainv;
	/*------power function with mod, and inverse modulo prime number------*/
	int powm(int a, int b){
		int ans = 1;
		while(b){
			if(b&1) ans = int(1ll*ans*a%mod);
			a = int(1ll*a*a%mod);
			b >>=1;
		}
		return ans;
	}
	int inv(int i){//mod must be prime and i must be coprime with mod
		return powm(i,int(mod)-2);
	}

	factorial(int m, ll mod,int inverse): n(m+1), mod(mod){
		if(inverse == 0){
			a = new int[n];
			a[0] = 1;
			a[1] = 1;
			for(int i = 2; i<n;i++){
				a[i] = int(1ll*i*a[i-1]%mod);
			}
		}else{
			a = new int[n];
			a[0] = 1;
			a[1] = 1;
			for(int i = 2; i<n;i++){
				a[i] = int(1ll*i*a[i-1]%mod);
			}
			ainv = new int[n];
			ainv[n-1] = inv(a[n-1]);
			ainv[0] = inv(1);
			for(int i = n-1; i>0;i--){
				ainv[i-1] = int(1ll*i*ainv[i]%mod);
			}
		}
	}
};
const int N = 3e3+5;
const int W = 1e5+5;
int h,w,n;
int r[N],c[N],ind[N], dp[N];
factorial fo(int(2e5+10),mod,1);

bool cmp(const int &i, const int &j){
	return (r[i] < r[j]) || (r[i] == r[j] && c[i] < c[j]);
}

int ways(int r, int c){
	return 1ll*fo.a[r+c]*fo.ainv[r]%mod*fo.ainv[c]%mod;
}
void solve(){
	cin>>h>>w>>n;
	for(int i=0; i<n; i++){
		cin>>r[i]>>c[i];
	}
	iota(ind, ind+n,0);
	sort(ind, ind+n,cmp);
	ind[n] = n;
	r[n] = h, c[n] = w;
	for(int i=0;i<=n; i++){
		dp[i] = ways(r[ind[i]]-1, c[ind[i]]-1);
		// trace(i,dp[i],ind[i], r[ind[i]], c[ind[i]]);
		// stack<pair<int,int>> st;
		// for(int j =0; j<=mp[c[ind[i]]]; j++){

		// }
		for(int j =0; j<i; j++){
			if(c[ind[j]] > c[ind[i]]) continue;
			dp[i] -= (1ll*dp[j]*ways(r[ind[i]]-r[ind[j]], c[ind[i]] - c[ind[j]])%mod);
			(dp[i] += mod)%=mod;
		}
		// trace(i,dp[i],ind[i], r[ind[i]], c[ind[i]]);
		// mxr[mp[c[ind[i]]]] = r[ind[i]];
	}
	cout<<dp[n]<<endl;
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