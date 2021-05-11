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
const int N = 1e5+4;
int n,m,u,v,p[N];
vector<pair<int,ld>> adj[N];
ld mn[N],val,eps = 1e-8;
void solve(){
	cin>>n>>m;
	for(int i =0; i<m; i++){
		cin>>u>>v>>val;
		u--,v--;
		adj[u].EB(MP(v,val));
	}
	//smallest>= x
	ld l=-1; //a[l] < x
	ld r = 100,mid; // a[r] >= x
	function<bool(void)> good = [&](){
		fill(mn, mn+n,1e9);
		mn[0] = 0;
		for(int i =0; i<n; i++){
			for(auto x : adj[i]){
				mn[x.F] = min(mn[x.F], mn[i] + x.S-mid);
			}
		}
		return mn[n-1] <= 0;
	};
	while(r -l>eps){
		mid = (l+r)/2;
		if(good()){
			r = mid;
		}else{
			l = mid;
		}
	}
	fill(mn, mn+n,1e9);
	fill(p, p+n,-1);
	mn[0] = 0;
	for(int i =0; i<n; i++){
		for(auto x : adj[i]){
			if(mn[x.F]> mn[i] + x.S-r){
				p[x.F] = i;
				mn[x.F] = mn[i] + x.S-r;
			}
		}
	}
	stack<int> st;
	u = n-1;
	while(u != -1){
		st.push(u);
		u = p[u];
	}
	cout<<sz(st)-1<<endl;
	while(!st.empty()){
		cout<<st.top()+1<<" ";
		st.pop();
	}cout<<endl;
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