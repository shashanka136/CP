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
// #define endl '\n'
#define all(v) v.begin(), v.end()
const ll mod = 998244353;

//
struct edge {
	int u, v, lo;
	int x;
	edge(){}
	edge(int _u, int _v, int _x): u(_u), v(_v), x(_x) {
		lo = -1;
	}
	int get(int t) { return t ^ u ^ v;}
};


const int N = 2e5+5;
int n,m,u,v,w,p[N],cnt1,cnt2;
map<int,vpi> mp;
int fin(int i){
	if(p[i] != i){
		p[i] = fin(p[i]);
	}
	return p[i];
}
void un(int i, int j){
	i = fin(i), j = fin(j);
	if(i == j) return;
	p[i] = j;
}

void solve(){
	cin>>n>>m;
	for(int  i =0; i<m;i++){
		cin>>u>>v>>w;
		u--,v--;
		mp[w].PB(MP(u,v));
		// trace(edges[i].u, edges[i].v);
	}
	// trace(mp);
	if(n == 1 && m == 0){
		cout<<0<<endl;
		return;
	}
	int ans = 0;
	iota(p,p+n,0);
	for(auto [k,val] : mp){
		cnt1 = cnt2 = 0;
		for(auto [u, v] : val){
			u = fin(u);
			v = fin(v);
			if(u != v) cnt1++;
		}
		for(auto [u, v] : val){
			u = fin(u);
			v = fin(v);
			if(u != v){
				cnt2++;
				un(u,v);
			}
		}
		// trace(cnt1, cnt2);
		ans += cnt1-cnt2;
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