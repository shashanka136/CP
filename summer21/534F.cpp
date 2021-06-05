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
#define cnt(i,n) (((((i<<1|i)^i)>>1)>>n)&1)
#define tot(i) cnt(i,0) + cnt(i,1) + cnt(i,2)+ cnt(i,3) + cnt(i,4)
//((i<<1|i)^i)>>1 taking only first bit of continuous set bits
int n,m,z;
int a[7],b[25],ans[25];
set<vi> tried[25];

void calc(int col, vi &cr){
	// trace(col,cr);
	if(col == m+1){
		// trace(cr);
		for(int r =0; r<n; r++) if(cr[r] != a[r]) return;
		for(int r =0; r<n; r++){
			for(int c =1; c<=m; c++){
				cout<<".*"[ans[c]>>r&1];
			}
			cout<<endl;
		}
		exit(0);
	}
	if(tried[col].find(cr) != tried[col].end()) return;
	for(int msk = 0; msk<z; msk++){
		if( tot(msk) != b[col]) continue;
		// trace(col,cr,msk);
		ans[col] = msk;
		vi newcr = cr;
		bool fo = 0;
		// trace(msk,ans[col-1]);
		for(int i =0; i<n ;i++){
			if(msk>>i&1 && !(ans[col-1]>>i&1)) newcr[i]++;
			if(newcr[i] > a[i] || a[i]-newcr[i] > (m-col+1)/2){
				// trace(i,newcr[i], a[i], m, col);
				fo = 1; break;
			}
		}
		// trace(col,cr,msk,newcr);
		if(fo) continue;
		// trace(col,cr,msk);
		calc(col+1,newcr);
	}
	tried[col].insert(cr);
}

void solve(){
	cin>>n>>m;
	for(int i= 0; i<n;i++){
		cin>>a[i];
	}
	b[0] = 0;
	for(int i= 1; i<=m;i++){
		cin>>b[i];
	}
	z = 1<<n;
	vi x(n,0);
	calc(1,x);
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