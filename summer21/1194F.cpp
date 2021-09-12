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

const int N = 2e5+7;
int n,p1,p2;
ll tot;
ll sum;
ll tim,lsum;
int ans = 1;
int cr;
factorial fo(N,mod,0), foinv(N,mod,1);

int comb(int n, int r){
	if(r < 0 || r > n) return 0;
	if(r == 0 || r == n) return 1;
	return 1ll*fo.a[n]*foinv.a[r]%mod*foinv.a[n-r]%mod;
}

void solve(){
	cin>>n>>tot;
	cin>>tim;
	sum = lsum = tim;
	ans = 0;
	for(int i =1; i<n; i++){
		cin>>tim;
		sum += tim;
		p1 = min(max(tot-sum+1,0ll),1ll*i + 1);
		p2 = max(min(tot-lsum,1ll*i), -1ll);
		cr =0;
		// trace(p1,p2);
		for(int j = p1; j<=p2; j++){
			cr += comb(i,j);
			cr %= mod;
		}
		ans += 1ll*fo.powm(foinv.a[2],i+1)*cr%mod*i%mod;
		ans %= mod;
		// trace(ans);
		p1 = min(max(tot-sum,0ll),1ll*i + 1);
		p2 = max(min(tot-lsum,1ll*i), -1ll);
		cr =0;
		// trace(p1,p2);
		for(int j = p1; j<=p2; j++){
			cr += comb(i,j);
			cr %= mod;
		}
		ans += 1ll*fo.powm(foinv.a[2],i+1)*cr%mod*i%mod;
		ans %= mod;
		lsum = sum;
		// trace(ans);
	}
	// trace(ans);
	sum = max(lsum +1, tot+1);
	p1 = min(max(tot-sum+1,0ll),1ll*n + 1);
	p2 = max(min(tot-lsum,1ll*n), -1ll);
	cr =0;
	for(int j = p1; j<=p2; j++){
		cr += comb(n,j);
		cr %= mod;
	}
	ans += 1ll*fo.powm(foinv.a[2],n)*cr%mod*n%mod;
	ans %= mod;
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