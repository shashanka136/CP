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
ll n,m,t[1000],z[1000],y[1000], a[1000];
ll num(ll tim, ll i){
	ll x = tim /a[i];
	tim -= x*a[i];
	return x*z[i] + min(z[i], tim/t[i]);
}
bool good(ll tim){
	ll tot = 0;
	for(int i =0; i<n; i++){
		tot += num(tim, i);
		if(tot >= m)return true;
	}
	return false;
}
void solve(){
	cin>>m>>n;
	for(int i=0; i<n; i++){
		cin>>t[i]>>z[i]>>y[i];
		a[i] = z[i]*t[i] + y[i];
	}
	//smallest>= x
	ll l=-1; //a[l] < x
	ll r = 2e9,mid; // a[r] >= x
	while(r > l+1){
		mid = l+r>>1;
		if(good(mid)){
			r = mid;
		}else{
			l = mid;
		}
	}
	cout<<r<<endl;
	for(int i =0; i<n; i++){
		ll nm = num(r,i);
		if(nm >= m){
			cout<<m<<" ";
			m = 0;
		}else{
			cout<<nm<<" ";
			m -= nm;
		}
	}
	cout<<endl;
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