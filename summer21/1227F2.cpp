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
const int N = 2e5+5;
int n,k;
int h[N],cnt;
int ans,cr;

struct factorial{
	int n;
	ll mod;
	int *a;
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
			a[0] = inv(1);
			a[1] = inv(1);
			for(int i = 2; i<n;i++){
				a[i] = int(1ll*inv(i)*a[i-1]%mod);
			}
		}
	}
};

factorial fo1(N,mod,0), fo2(N,mod,1);

int comb(int n, int r){
	if(r < 0 || r > n) return 0;
	if(r == 0 || r == n) return 1;
	return 1ll*fo1.a[n]*fo2.a[r]%mod*fo2.a[n-r]%mod;
}

int calc(int a){
	return 1ll*comb(cnt,a)*fo1.powm(k-2,a)%mod*
	((cnt-a)%2 == 1? fo1.powm(2,cnt-a-1): 
		1ll*fo1.powm(2,mod-2)*(fo1.powm(2,cnt-a) - comb(cnt-a, (cnt-a)/2) + mod)%mod)%mod;
}
void solve(){
	cin>>n>>k;
	INP(h,n);
	if(k==1){
		cout<<0<<endl;
		return;
	}
	cnt = 0;
	for(int i =1; i<n; i++){
		cnt += h[i-1] != h[i];
	}
	cnt += h[n-1] != h[0];
	int ans = 0;
	for(int a = 0; a< cnt; a++){
		ans = (ans + calc(a))%mod;
	}
	ans = 1ll*ans*fo1.powm(k,n-cnt)%mod;
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
	//cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}