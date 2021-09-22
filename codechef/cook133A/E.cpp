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
ll mod = 998244353;

//
const int N = 2e4+5;
int n,m;
int s[N];
/*------power function with mod, and inverse modulo prime number------*/
int powm(int a, int b, ll mod = mod) {
	int ans = 1;
	b %= (mod - 1);
	if (b < 0) b += mod - 1;
	while (b) {
		if (b & 1) ans = int(1ll * ans * a % mod);
		a = int(1ll * a * a % mod);
		b >>= 1;
	}
	return ans;
}
int inv(int i, ll mod = mod) { //mod must be prime and i must be coprime with mod
	return powm(i, int(mod) - 2, mod);
}
int get(int a, int n){//1<=x<=n, s.t. gcd(a,x) = 1;
	vi pr;
	for(int i=2,j=4,k=5; j<=a; i++,j+=k,k+=2) if(a%i == 0){
		pr.PB(i);
		while(a%i == 0) a/=i;
	}
	if(a != 1) pr.PB(a);
	int np = sz(pr);
	ll ans = 0;
	for(int i =0; i<(1<<np); i++){
		int btc = 0;
		int cr = 1;
		for(int j=0; j<np; j++){
			if(i>>j&1){
				cr *= pr[j];
				btc ^=1;
			}
		}
		ans += btc? -n/cr : n/cr;
	}
	return ans;
}
void solve(){
	cin>>n>>m>>mod;
	for(int i=m-1; i>=0; i--){
		cin>>s[i];
	}
	for(int i =1; i<m; i++){
		if(s[i-1]%s[i]){
			cout<<0<<endl;
			return;
		}
	}
	if(s[m-1] != 1){
		cout<<0<<endl;
		return;
	}
	int ans = inv(n);
	for(int i=1; i<m; i++){
		ans = 1ll*ans*get(s[i-1]/s[i], n/s[i])%mod;
		ans = 1ll*ans*inv(n-n/s[i-1])%mod;
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
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}