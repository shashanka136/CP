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
const int N = 504;
int _n,n,tot,mx_span=0;
int a[N][N],b[N][N];
int max_w[2*N];
bool vis[2*N];
int r[N],c[N],nr[N],nc[N];

int weight(int u, int v){
	if((u >= n) == (v >= n)){
		return -2e9;
	}
	if( u >v) swap(u,v);
	if(b[u][v-n] == 0) return -2e9;
	return b[u][v-n];
}
void solve(){
	cin>>n;
	mx_span = 0;
	fill(nr,nr+n,0);
	fill(vis,vis+2*n,false);
	fill(max_w,max_w+2*n,-1);
	fill(nc,nc+n,0);
	tot = 0;
	for(int i =0; i<n; i++){
		for(int j=0; j<n; j++){
			cin>>a[i][j];
			if(a[i][j] == -1){
				nr[i]++;
				nc[j]++;
			}
		}
	}
	for(int i =0; i<n; i++){
		for(int j=0; j<n; j++){
			cin>>b[i][j];
			tot += b[i][j];
		}
	}
	INP(r,n);
	INP(c,n);
	_n = 2*n;
	for(int i =0; i<_n; i++){
		if(vis[i]) continue;
		max_w[i] = 0;
		for(int k = i; k <_n; k++){
			int ver = -1;
			for(int j = i; j <_n; j++){
				if(!vis[j] && (ver == -1 || max_w[j] > max_w[ver])){
					ver = j;
				}
			}
			// trace(i,ver);
			if(ver == -1 || max_w[ver] == -1) break;
			// trace(i,ver);
			mx_span += max_w[ver];
			vis[ver] = true;
			for(int j = i; j < _n; j++){
				if(!vis[j] && weight(ver,j) > max_w[j]){
					// trace(ver, j, weight(ver, j));
					max_w[j] = weight(ver,j);
				}
			}
		}
		// trace(i,mx_span);
	}
	cout<<tot-mx_span<<endl;
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