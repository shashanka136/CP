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
const int N = 1e5+5;
int n;
pll a[N];

void solve(){
	cin>>n;
	for(int i = 0; i<n; i++){
		cin>>a[i].S>>a[i].F;
	}
	sort(a,a+n,greater<pll>());
	ll tot = 0,inf = 1e14+1,ans =0;

	for(int i =0; i<n;i++){
		while(n > i && a[n-1].F <= tot){
			ans += a[n-1].S;
			tot += a[n-1].S;
			n--;
		}
		if(i == n) break;
		while(n>i+1 && tot+a[i].S >= a[n-1].F){
			if(tot >= a[i].F) ans += 1ll*max(a[n-1].F-tot,0ll);
			else ans += 2ll*max(a[n-1].F-tot,0ll);
			a[i].S -= max(a[n-1].F-tot,0ll);
			tot += max(a[n-1].F-tot,0ll);
			ans += a[n-1].S;
			tot += a[n-1].S;
			n--;
		}
		if(a[i].F <= tot+a[i].S){
			ans += max(0ll,a[i].F-tot)*2 + min(tot+a[i].S-a[i].F, a[i].S);
			tot += a[i].S;
		}else{
			ans += 2ll*a[i].S;
			tot+= a[i].S;
		}
	}
	// for(int i =0; i<n; i++){
	// 	if(a[i].F <= tot+a[i].S){
	// 		ans += max(0ll,a[i].F-tot)*2 + min(tot+a[i].S-a[i].F, a[i].S);
	// 		tot += a[i].S;
	// 		a[i].F = -1;
	// 	}
	// }
	// for(int i =n-1; i>=0; i--){
	// 	if(a[i].F == -1) continue;
		// if(a[i].F <= tot+a[i].S){
		// 	ans += max(0ll,a[i].F-tot)*2 + min(tot+a[i].S-a[i].F, a[i].S);
		// 	tot += a[i].S;
		// }else{
		// 	ans += 2ll*a[i].S;
		// 	tot+= a[i].S;
		// }
	// }
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