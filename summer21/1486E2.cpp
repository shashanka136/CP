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
const int N = 1e5+5;
int n,m,u,v,w,d1[N], d2[51][N];
vpi adj[N];
void solve(){
	cin>>n>>m;
	for(int i =0; i<m; i++){
		cin>>u>>v>>w;
		u--,v--;
		adj[u].PB(MP(v,w));
		adj[v].PB(MP(u,w));
	}
	fill(d1,d1+n,-1);
	for(int i =0; i<=50; i++) fill(d2[i],d2[i]+n,-1);
	d1[0] = 0;
	set<pair<int,pii>> q;
	q.insert(MP(-1,MP(0,0)));// weight, d, ind
	while(!q.empty()){
		pii p = q.begin()->S;
		w = q.begin()->F;
		q.erase(q.begin());
		if(w == -1){
			for(auto x : adj[p.S]){
				if(d2[x.S][x.F] == -1 || p.F + (x.S)*(x.S) < d2[x.S][x.F]){
					auto it = q.find(MP(x.S, MP(d2[x.S][x.F], x.F)));
					if(it != q.end()){
						q.erase(it);
					}
					d2[x.S][x.F] = p.F + (x.S)*(x.S);
					q.insert(MP(x.S, MP(d2[x.S][x.F], x.F)));
				}
			}
		}else{
			for(auto x : adj[p.S]){
				if(d1[x.F] == -1 || p.F + (2*w + x.S)*(x.S) < d1[x.F]){
					auto it = q.find(MP(-1, MP(d1[x.F], x.F)));
					if(it != q.end()){
						q.erase(it);
					}
					d1[x.F] = p.F + (2*w + x.S)*(x.S); 
					q.insert(MP(-1, MP(d1[x.F], x.F)));
				}
			}
		}
	}
	OUT(d1,n);
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