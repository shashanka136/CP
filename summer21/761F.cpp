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
const int K = 3e5+6;
const int A = 26;
struct pt{
	int x,y;
};
pt b[K], c[K];
string a[N];
char ch[K];
ll dp1[N][N][A], dp2[N][N][A];
int n,m,k;
inline int ind(char c){ return c - 'a';}
void solve(){
	cin>>n>>m>>k;
	INP(a,n);
	for(int i = 0 ;i<=n+1; i++){
		for(int j = 0; j<= m+1; j++){
			for(int l = 0; l<A; l++){
				dp1[i][j][l] = 0;
				dp2[i][j][l] = 0;
			}
		}
	}
	for(int i =0; i<k; i++){
		cin>>b[i].x>>b[i].y>>c[i].x>>c[i].y>>ch[i];
		dp1[b[i].x][b[i].y][ind(ch[i])] +=1;
		dp1[c[i].x+1][c[i].y+1][ind(ch[i])] += 1;
		dp1[c[i].x+1][b[i].y][ind(ch[i])] -= 1;
		dp1[b[i].x][c[i].y+1][ind(ch[i])] -= 1;
	}
	for(int i = 1 ;i<=n+1; i++){
		for(int j = 1; j<= m+1; j++){
			if(i != 1 && j != 1) dp2[i-1][j-1][ind(a[i-2][j-2])] = k;
			for(int l = 0; l<A; l++){
				dp1[i][j][l] += dp1[i][j-1][l];
				dp1[i][j-1][l] += dp1[i-1][j-1][l];
				dp2[i-1][j-1][l] += dp1[i-1][j-1][l];
				if(i == 1 || j == 1) continue;
				dp2[i-1][j-1][ind(a[i-2][j-2])] -= dp1[i-1][j-1][l];
				if(l != 0) dp1[i-1][j-1][0] += dp1[i-1][j-1][l] *abs(l - ind(a[i-2][j-2]));
				else dp1[i-1][j-1][0] = dp1[i-1][j-1][l] *abs(l - ind(a[i-2][j-2]));
				// dp1[i-1][j-1][l] += dp1[i-2][j-1][l] + dp1[i-1][j-2][l] - dp1[i-2][j-2][l];
			}
			if(i != 1 && j != 1){
				for(int l = 0; l<A; l++){
					// trace(i-1,j-1,l,dp2[i-1][j-1][l]);
					dp2[i-1][j-1][l] += dp2[i-2][j-1][l] + dp2[i-1][j-2][l] - dp2[i-2][j-2][l];
					// trace(i-1,j-1,l,dp2[i-1][j-1][l]);
				}
				dp1[i-1][j-1][0] += dp1[i-2][j-1][0] + dp1[i-1][j-2][0] - dp1[i-2][j-2][0];
			}
		}
	}
	ll mn = 1e18;
	for(int i = 0; i<k; i++){
		ll cr = dp1[n][m][0] - dp1[c[i].x][c[i].y][0] - dp1[b[i].x-1][b[i].y-1][0]
				 + dp1[b[i].x-1][c[i].y][0] +dp1[c[i].x][b[i].y-1][0];
		for(int l = 0; l < A; l++){
			cr += (dp2[c[i].x][c[i].y][l] + dp2[b[i].x-1][b[i].y-1][l]
				 - dp2[b[i].x-1][c[i].y][l] -dp2[c[i].x][b[i].y-1][l]) * abs(l - ind(ch[i]));
		}
		mn = min(mn,cr);
	}
	cout<<mn<<endl;
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
	// cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}