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
const ll inf = 1e18;
//
const int N = 2e3+5;
int a[N][N];
ll dp[N][N];
int n,m,w,x,y;
pii v;
ll mn1 = inf,mn2 = inf;
vi dx{1,-1,0,0}, dy{0,0,1,-1};

// inline int x(int v){ return v%N;}
// inline int y(int v){ return v/N;}
// inline int val(int x, int y){ return N*y+x;}
void bfs(int xv, int yv,int indic){
	for(int i =1; i<=n; i++){
		for(int j =1; j<=m; j++){
			dp[i][j] = -1;
		}
	}
	dp[xv][yv] = 0;
	queue<pii> q;
	q.push(MP(xv,yv));
	while(!q.empty()){
		v = q.front();
		q.pop();
		if(a[v.F][v.S] > 0){
			if(indic) mn2 = min(mn2, dp[v.F][v.S] + a[v.F][v.S]);
			else mn1 = min(mn1, dp[v.F][v.S] + a[v.F][v.S]);
		}
		for(int i =0; i<4; i++){
			x = v.F + dx[i];
			y = v.S + dy[i];
			if(a[x][y] == -1 || dp[x][y] != -1) continue;
			dp[x][y] = dp[v.F][v.S] + w;
			q.push(MP(x,y));
		}
	}
}

void solve(){
	cin>>n>>m>>w;
	for(int i =1; i<=n; i++){
		a[i][0] = a[i][m+1] = -1;
		for(int j =1; j<=m; j++){
			cin>>a[i][j];
		}
	}
	for(int j =1; j<=m; j++){
		a[0][j] = a[n+1][j] = -1;
	}
	bfs(n,m,1);
	bfs(1,1,0);
	if(dp[n][m] == -1) dp[n][m] = inf;
	dp[n][m] = min(dp[n][m], mn1+mn2);
	if(dp[n][m] == inf) dp[n][m] = -1;
	cout<<dp[n][m]<<endl;
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