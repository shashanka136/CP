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
int n,r,tin[N],tout[N],u,v,a[N],ind[N],indi[N],z,ind1,ind2;
int dep[N],cr,m,p,q,lgn;
int depst[N][20], deplst[N][20];
int ans[N][20][20];
vi nd[N];
vi adj[N];

bool cmp(const int &i, const int &j){
	return (dep[i] < dep[j]) || (dep[i] == dep[j] && tin[i] < tin[j]);
}

void mn(int &x, int y){
	x = min(x,y);
}
void mx(int &x, int y){
	x = max(x,y);
}
int log2(int x){
	return 31 - __builtin_clz(x);
}
void solve(){
	cin>>n>>r;
	r--;
	INP(a,n);
	for(int i =1; i<n; i++){
		cin>>u>>v;
		u--,v--;
		adj[u].PB(v);
		adj[v].PB(u);
	}
	dep[r] = 0;
	cr = 0;
	function<void(int, int)> dfs = [&](int i, int p){
		tin[i] = cr++;
		for(int j : adj[i]){
			if(j == p) continue;
			dep[j] = dep[i]+1;
			nd[dep[j]].PB(j);
			dfs(j,i);
		}
		tout[i] = cr;
	};
	dfs(r,-1);
	iota(ind,ind+n,0);
	sort(ind,ind+n,cmp);
	for(int i =0; i<n; i++){
		indi[ind[i]] = i;
	}
	lgn = log2(n);
	function<int(int, int, pii)> lb = [&](int l, int r, pii dt){
		int mid;
		while(l < r){
			mid = l+r>>1;
			if(MP(dep[ind[mid]], tin[ind[mid]]) >= dt){
				r = mid;
			}else{
				l = mid+1;
			}
		}
		return l;
	};
	for(int i = 0; i<n; i++){
		for(int j = 0; j<=lgn; j++){
			depst[i][j] = lb(0,n,MP(dep[ind[i]]+(1<<j), tin[ind[i]]+1));
			deplst[i][j] = lb(0,n,MP(dep[ind[i]]+(1<<j), tout[ind[i]]+1));
		}
	}
	for(int i =0; i<n; i++){
		ans[i][0][0] = a[ind[i]];//2^k blocked subtree, [i, i+2^j)
	}
	for(int k = 0; k<=lgn; k++){
		if(k != 0){
			for(int i =0; i<n; i++){
				ans[i][0][k] = ans[i][0][k-1];
				ind1 = depst[i][k-1], ind2 = deplst[i][k-1];
				// trace(i,k,ind1,ind2, ans[i][0][k]);
				if(ind1 == ind2) continue;
				z = log2(ind2-ind1);
				mn(ans[i][0][k], min(ans[ind1][z][k-1], ans[ind2-(1<<z)][z][k-1]));
				// trace(i,k,ind1,ind2, ans[i][0][k]);
			}
		}
		for(int j = 1; j<=lgn; j++){
			for(int i =0; i<n; i++){
				if(i + (1<<j) >n) break;
				ans[i][j][k] = min(ans[i][j-1][k], ans[i+(1<<(j-1))][j-1][k]);
			}
		}
	}
	// for(int k = 0; k<=lgn; k++){
	// 	for(int j = 0; j<=lgn; j++){
	// 		for(int i =0; i<n; i++){
	// 			if(i + (1<<j) >n) break;
	// 			cout<<ans[i][j][k]<<" ";
	// 		}
	// 		cout<<endl;
	// 	}
	// 	cout<<endl;
	// }
	cin>>m;
	int lst = 0,le,ri; 
	for(int i =0; i<m; i++){
		cin>>p>>q;
		p = (p+lst)%n;
		q = (q+lst)%n;
		p = indi[p];
		lst = 1e9;
		le = ri = p;
		ri++;
		q++;
		// trace(p,q);
		for(int j = lgn; j>= 0 && le != ri; j--){
			if((1<<j) <= q){
				// trace(q,j,le,ri,lst);
				// trace(le,ri);
				z = log2(ri-le);
				mn(lst,min(ans[le][z][j], ans[ri-(1<<z)][z][j]));
				le = depst[le][j];
				ri--;
				ri = deplst[ri][j];
				q -= (1<<j);
				// trace(q,j,le,ri,lst);
			}
		}
		cout<<lst<<endl;
	}
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
