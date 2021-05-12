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
const int N = 1e3+5;
int n;
ll p,sum,ans,cr;
ll mn1,mn2;
int a[N],ind1,ind2;
void solve(){
	cin>>n>>p;
	INP(a,n);
	sum = 0;
	for(int i =0; i<n; i++){
		sum += a[i];
	}
	ans = 0;
	ans += 1ll*n*(p/sum);
	p %= sum;
	// trace(ans,p);
	int l=0,r=0;
	cr = 0;
	ind1 = -1;
	mn1 = -1;
	while(r<n){
		cr += a[r];
		while(l <= r && cr > sum-p){
			cr -= a[l]; l++;
		}
		if(r-l+1 > mn1){
			mn1 = r-l+1;
			ind1 = (r+1)%n;
		}
		r++;
	}
	// trace(mn1,ind1);
	mn1 = n-mn1;
	cr = 0;
	l = r = 0;
	while(r<n){
		cr += a[r];
		while(l <= r && cr-a[l] >= p){
			cr -= a[l]; l++;
		}
		if(cr >= p && r-l+1 < mn1){
			mn1 = r-l+1;
			ind1 = l;
		}
		r++;
	}
	// trace(mn1, ind1);
	cout<<ind1+1<<" "<<ans+mn1<<endl;
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