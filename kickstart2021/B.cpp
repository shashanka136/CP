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
int r,c;
int box[N][N][4];
bitset<N> bn[N];
void solve(){
	int x;
	cin>>r>>c;
	memset(box, 0, sizeof(box));
	for(int i =0; i<= r; i++){
		box[i][0][0] = 0;
		box[i][c+1][2] = 0;
	}
	for(int i =0; i<= c; i++){
		box[0][i][1] = 0;
		box[r+1][i][3] = 0;
	}
	for(int i =0; i<r; i++){
		for(int j =0; j<c; j++){
			cin>>x;
			bn[i][j] = x;
			if(x == 1){
				box[i+1][j+1][0] = box[i+1][j][0] + x;
				box[i+1][j+1][1] = box[i][j+1][1] + x;
			}
		}
	}
	ll ans = 0,mn[8];
	for(int i =r-1; i>=0; i--){
		for(int j =c-1; j>=0; j--){
			if(bn[i].test(j)){
				box[i+1][j+1][2] = box[i+1][j+2][2] + 1;
				box[i+1][j+1][3] = box[i+2][j+1][3] + 1;
				for(int k =0; k<4; k++){
					mn[2*k] = min(box[i+1][j+1][k], box[i+1][j+1][(k+1)%4]/2);
					mn[2*k+1] = min(box[i+1][j+1][k]/2, box[i+1][j+1][(k+1)%4]);
					// trace(i,j,k,mn[2*k],mn[2*k+1]);
				}
				for(int k =0; k<8; k++){
					if(mn[k] > 1) ans += mn[k] -1;
				}
			}
		}
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
	cin>>t;
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
	// while(t--){
	// 	solve();
	// }
}