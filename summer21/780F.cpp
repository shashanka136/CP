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
const int N = 505;
bitset<N> p[61][N], pcol[61][N], b[61][N], bcol[61][N];
int n,m,u,v,typ;
int cnt = 0;
ll cr;
void solve(){
	cin>>n>>m;
	for(int i =0; i<m;i++){
		cin>>u>>v>>typ;
		u--,v--;
		if(typ == 0){
			p[0][u].set(v);
			pcol[0][v].set(u);
		}else{
			b[0][u].set(v);
			bcol[0][v].set(u);
		}
	}
	for(int k =1; k<=60; k++){
		for(int i = 0; i<n; i++){
			for(int j =0; j<n; j++){
				if((p[k-1][i] & bcol[k-1][j]).any()){
					p[k][i].set(j);
					pcol[k][j].set(i);
				}
				if((b[k-1][i] & pcol[k-1][j]).any()){
					b[k][i].set(j);
					bcol[k][j].set(i);
				}
			}
		}
	}
	// trace(p[1][0]);
	vector<int> reach{0};
	cr = 0;
	for(int k = 60; k>=0; k--){
		bitset<N> tmp(0);
		for(int x : reach){
			if(cnt){
				tmp |= b[k][x];
			}else{
				tmp |= p[k][x];
			}
		}
		if(!tmp.any()) continue;
		cr += 1ll<<k;
		if(k == 60) break;
		cnt ^= 1;
		vi tmpre;
		for(int i =0; i<n; i++){
			if(tmp.test(i)){
				tmpre.PB(i);
			}
		}
		reach.swap(tmpre);
	}
	if(cr > (ll)1e18) cr =-1;
	cout<<cr<<endl;
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