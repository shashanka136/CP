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
const int N = 2e5+4;
int n,c,d,k;
vi dam[N][4];
ll dp[N][10], temp;
void solve(){
	cin>>n;
	for(int i =0; i<n; i++){
		cin>>k;
		for(int j =0; j<k; j++){
			cin>>c>>d;
			dam[i][c].PB(d);
		}
	}
	for(int i =0; i<=n; i++){
		for(int j =0; j<10; j++){
			dp[i][j] = LLONG_MIN;
		}
	}
	dp[0][0] = 0;
	for(int i =0; i<n; i++){
		for(int j =1; j<=3; j++){
			sort(all(dam[i][j]), greater<int>());
			int nm = j==1?3:1;
			if(sz(dam[i][j]) > nm) dam[i][j].resize(nm);
		}
		vvl cr(4,vl(2,LLONG_MIN));
		cr[0][0] = 0;
		if(sz(dam[i][1]) == 3){
			cr[3][0] = 0;
			for(int &x : dam[i][1]){
				cr[3][0] += x;
			}
			cr[3][1] = cr[3][0] + dam[i][1][0];
		}
		if(sz(dam[i][1]) >=1 && sz(dam[i][2]) == 1){
			cr[2][0] = dam[i][2][0] + dam[i][1][0];
			cr[2][1] = cr[2][0] + max(dam[i][2][0], dam[i][1][0]);
		}
		if(sz(dam[i][1]) >=2){
			temp = 0;
			for(int j=0;j<2;j++){
				temp += dam[i][1][j];
			}
			cr[2][0] = max(cr[2][0], 1ll*temp);
			cr[2][1] = max(cr[2][1], 1ll*temp + dam[i][1][0]);
		}
		for(int j=1; j<=3; j++){
			if(sz(dam[i][j]) >= 1){ 
				cr[1][0] = max(cr[1][0], 1ll*dam[i][j][0]);
				cr[1][1] = max(cr[1][1], 2ll*dam[i][j][0]);
			}
		}
		for(int r = 0; r<10; r++){
			for(int crnum =0; crnum <=3; crnum++){
				int newr = (r+crnum)%10;
				int x = r+crnum >=10? 1:0;
				if(cr[crnum][x] != LLONG_MIN) dp[i+1][newr] =max(dp[i+1][newr], dp[i][r] + cr[crnum][x]);
			}
		}
	}
	ll ans = 0;
	for(int i =0; i<10;i++){
		ans = max(ans, dp[n][i]);
	}
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