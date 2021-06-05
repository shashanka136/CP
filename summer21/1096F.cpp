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
//(x+y)C2/2sum_i of (x*y1 + x1*y)/(x+y)
const int N = 2e5+5;
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
int n,tot,ans,p[N],cnt,x,y,bit[N],alr;
bool pre[N];
vi vs;

/*-----------BIT----------*/
void ins(int i, int x){
	while(i<=n){
		bit[i] += x;
		i += (i&-i);
	}
}
int sum(int i){
	int ans = 0;
	while(i > 0){
		ans += bit[i];
		i = (i&i-1);
	}
	return ans;
}

void solve(){
	cin>>n;

	fill(pre,pre+n+1,false);
	fill(bit,bit+n+1,0);
	tot = 0;
	alr = 0;
	for(int i =0; i<n; i++){
		cin>>p[i];
		if(p[i] == -1) tot++;
		else{
			alr += i-tot-sum(p[i]);
			if(alr >= mod) alr -=mod;
			pre[p[i]]= true;
			ins(p[i],1);
		}
	}
	for(int i =1; i<=n; i++){
		if(!pre[i]) vs.PB(i);
	}
	cnt =0,ans = 0;
	for(int i=0; i<n; i++){
		if(p[i] == -1){
			cnt++;
			continue;
		}
		x = lower_bound(all(vs), p[i]) -vs.begin();
		y = tot - x;
		ans += (1ll*x*(tot-cnt)%mod + 1ll*y*cnt%mod)%mod;
		if(ans >= mod) ans -= mod;
	}
	if(tot != 0) ans = 1ll*ans*inv(tot)%mod;
	if(tot != 0) ans += 1ll*tot*(tot-1)%mod*inv(4)%mod;
	if(ans >= mod) ans -= mod;
	ans += alr;
	if(ans >= mod) ans -= mod;
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