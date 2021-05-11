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
const int N = 1e5+4;
int n,d,mnl;
ld a[N],p[N],mn,eps = 1e-10;


void solve(){
	cin>>n>>d;
	INP(a,n);
	//smallest>= x
	p[0] = 0;
	ld l=0; //a[l] < x
	ld r = 101,mid; // a[r] >= x
	function<bool(void)> good = [&](){
		for(int i =0; i<n; i++){
			p[i+1] = p[i] + a[i] -mid;
		}
		mn = 0;
		for(int i=d; i<=n; i++){
			if(p[i] >= mn) return true;
			mn = min(mn,p[i+1-d]);
		}
		return false;
	};
	while(r-l > eps){
		mid = (l+r)/2;
		if(good()){
			l = mid;
		}else{
			r = mid;
		}
	}
	for(int i =0; i<n; i++){
		p[i+1] = p[i] + a[i] -l;
	}
	mn = 0;
	mnl = 0;
	// cout<<l<<endl;
	for(int i=d; i<=n; i++){
		if(p[i] >= mn){
			cout<<mnl+1<<" "<<i<<endl;
			return;
		}
		if(mn > p[i+1-d]){
			mnl = i+1-d;
			mn = p[i+1-d];
		}
	}
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