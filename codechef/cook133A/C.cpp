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
void no(){
	cout<<"NO"<<endl;
	// exit(0);
}
void yes(){
	cout<<"YES"<<endl;
	// exit(0);
}
const int N = 1e5+5;
int n,a,m,b;
vi v;
int gcd(int a , int b){
   if(b==0) return a;
   a%=b;
   return gcd(b,a);
}
void solve(){
	cin>>n;
	v = vi(0);
	for(int i =0; i<n; i++){
		cin>>a;
		if(a%2 == 0) v.PB(a/2);
	}
	m = (n+1)/2;
	if(sz(v) < m) return no();
	int x = 0;
	for(int z : v){
		x = gcd(z,x);
	}
	if(x != 1){
		return no();
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	if(sz(v) <= m) return yes();
	if(m >= 9) return yes();
	int msk = (1<<m)-1;
	while(msk < (1<<sz(v))){
		x = 0;
		for(int i=0; i<sz(v); i++){
			if(msk>>i&1) x = gcd(v[i],x);
		}
		if(x == 1) return yes();
		if(msk == 0) break;
		a = msk & -msk;
		b = msk+a;
		msk = int(((msk^b)>>2)/a) | b;
	}
	return no();
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