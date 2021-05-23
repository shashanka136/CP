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
int a[N],k,n;
ll sum[N],mxpre,mxsuff,mn,mx;
void solve(){
	cin>>n>>k;
	INP(a,n);
	for(int i =n; i<2*n; i++){
		a[i] = a[i-n];
	}
	sum[0] = 0;
	mn = 0;
	mx = a[0];
	mxpre = -1e6-2;
	for(int i =0; i<n; i++){
		sum[i+1] = sum[i] + a[i];
		mx = max(mx, sum[i+1] - mn);
		mn = min(mn, sum[i+1]);
		mxpre = max(mxpre, sum[i+1]);
	}
	mxsuff = -1e6-2;
	for(int i =n-1; i>=0;i--){
		mxsuff = max(mxsuff,sum[n] - sum[i]);
	}
	if(k == 1){
		cout<<mx<<endl;
	}else{
		cout<<max({mx, 1ll*(k-2)*sum[n] + mxsuff+mxpre, mxsuff+mxpre})<<endl;
	}//mx >= mxsuff,mxpre >= sum[n]
	// trace(mxsuff, mxpre, sum[n], mx);
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