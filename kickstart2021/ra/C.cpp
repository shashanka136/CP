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
const int N = 305;
int r,c,g;
int h[N][N];
ll ans;
vi dx = {0,1,0,-1}, dy = {1,0,-1,0};
void solve(){
	cin>>r>>c;
	set<pair<int,pair<int,int>>> pq;
	for(int i =0; i<r; i++){
		for(int j =0; j<c; j++){
			cin>>g;
			h[i][j] = g;
			pq.insert(MP(g,MP(i,j)));
		}
	}
	int i,j, gcur,ti, tj;
	ans =0 ;
	while(!pq.empty()){
		i = pq.rbegin()->S.F;
		j = pq.rbegin()->S.S;
		gcur = pq.rbegin()->F;
		auto it = pq.end();
		it--;
		pq.erase(it);
		for(int k =0; k<4; k++){
			ti = i+dx[k];
			tj = j+dy[k];
			if(ti < 0 || ti >=r || tj <0 || tj >=c) continue;
			if(h[ti][tj] >= gcur -1) continue;
			pq.erase(pq.find(MP(h[ti][tj], MP(ti, tj))));
			ans += gcur-1 -h[ti][tj];
			h[ti][tj] = gcur-1;
			pq.insert(MP(h[ti][tj], MP(ti, tj)));
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