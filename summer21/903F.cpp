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
const int N = 1e3+6;
const int M = 1<<12;
const int inf = 1e9;
string s[4];
int dp[N][4][M],n,a[4],lsti,lstj,newi, newj,ind,newmask,setones;

void solve(){
	cin>>n;
	INP(a,4);
	for(int i =0; i<4; i++){
		cin>>s[i];
		s[i] += "....";
	}
	n += 4;
	for(int i =0; i<=n; i++){
		for(int j =0; j<4; j++){
			for(int msk =0; msk <M; msk++){
				dp[i][j][msk] = inf;
			}
		}
	}
	dp[2][3][0] = 0;//all are * ofc more work
	for(int i =2; i<n; i++)for(int j = 0; j<4; j++){
		ind = 4*i +j -11;
		if(ind < 0) continue;
	for(int msk = 0; msk <M; msk++){
		lsti = ind/4;
		lstj = ind%4;
		if(lstj == 0 && i+1 < n){
			dp[i+1][3][M-1] = min(dp[i+1][3][M-1], dp[i][j][msk] + a[3]);
		}
		if((msk&1) || (s[lstj][lsti] == '.')){
			newi = i + (j+1)/4;
			newj = (j+1)%4;
			dp[newi][newj][msk>>1] = min(dp[newi][newj][msk>>1], dp[i][j][msk]);
		}
		for(int len = 1; len <=min(3,4-lstj); len++){
			newmask = msk;
			setones = (1<<len)-1;
			for(int k =0; k<len; k++){
				newmask |= (setones<<(4*k));
			}
			dp[i][j][newmask] = min(dp[i][j][newmask], dp[i][j][msk] + a[len-1]);
		}
	}
	}
	cout<<dp[n][0][0]<<endl;
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