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
const int N = 304;
int n;
int v[N][N];
vi dx{0,0,1,1,1,-1,-1,-1}, dy{1,-1,1,-1,0,1,-1,0};
pii a,b;
pii operator+(const pii &a, const pii &b){
	return MP(a.F + b.F, a.S + b.S);
}
pii operator-(const pii &a, const pii &b){
	return MP(a.F - b.F, a.S - b.S);
}
pii newb(pii a, pii b){
	pii x = a-b;
	x.F = x.F >0? 1: x.F <0? -1 : 0;
	x.S = x.S >0? 1: x.S <0? -1 : 0;
	return b+x;
}
ll dp[N][N][3*N];
void solve(){
	cin>>n>>a.F>>a.S>>b.F>>b.S;
	for(int i =0; i<n; i++){
		for(int j = 0; j<n; j++){
			fill(dp[i+1][j+1], dp[i+1][j+1] +3*N,-1);
			cin>>v[i][j];
		}
	}
	function<ll(pii,int)> get = [&](pii a, int trn){
		if(trn >= max(abs(a.F-b.F), abs(a.S-b.S))) return 0ll;
		if(dp[a.F][a.S][trn] != -1){
			return dp[a.F][a.S][trn];
		}
		dp[a.F][a.S][trn] = 0;
		for(int i=0; i<8; i++){
			pii newa = a+MP(dx[i], dy[i]);
			if(newa.F >n || newa.F < 1) continue;
			if(newa.S >n || newa.S < 1) continue;
			// trace(a,b,newa);
			dp[a.F][a.S][trn] = max(dp[a.F][a.S][trn], 1ll*v[newa.F-1][newa.S-1] + get(newa,trn+1));
		}
		return dp[a.F][a.S][trn];
	};
	cout<<get(a,0)<<endl;
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