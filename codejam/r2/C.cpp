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
const ll mod = 1e9+7;

//
const int N = 1e5+4;

struct factorial{
	int n;
	ll mod;
	int *a;
	/*------power function with mod, and inverse modulo prime number------*/
	int powm(int a, int b){
		int ans = 1;
		while(b){
			if(b&1) ans = int(1ll*ans*a%mod);
			a = int(1ll*a*a%mod);
			b >>=1;
		}
		return ans;
	}
	int inv(int i){//mod must be prime and i must be coprime with mod
		return powm(i,int(mod)-2);
	}

	factorial(int m, ll mod,int inverse): n(m+1), mod(mod){
		if(inverse == 0){
			a = new int[n];
			a[0] = 1;
			a[1] = 1;
			for(int i = 2; i<n;i++){
				a[i] = int(1ll*i*a[i-1]%mod);
			}
		}else{
			a = new int[n];
			a[0] = inv(1);
			a[1] = inv(1);
			for(int i = 2; i<n;i++){
				a[i] = int(1ll*inv(i)*a[i-1]%mod);
			}
		}
	}
};

factorial fo(N,mod,0), foinv(N,mod,1);
int v[N],n,tot[N];
vi adj[N];
int ans[N],rt,lst;

void dfs1(int i){
	tot[i] = 1;
	for(auto x : adj[i]){
		dfs1(x);
		tot[i] += tot[x];
	}
}
void fill_ans(int i){
	ans[i] = fo.a[tot[i]-1];
	for(auto x : adj[i]){
		fill_ans(x);
		ans[i] = 1ll*ans[i]*foinv.a[tot[x]]%mod;
		ans[i] = 1ll*ans[i]*ans[x]%mod;
	}
}
void solve(){
	cin>>n;
	INP(v,n);
	for(int i =0; i<n; i++) adj[i].clear();
	stack<int> st;
	st.push(0);
	if(v[0] != 1){
		cout<<0<<endl;return;
	}
	for(int i = 1; i<n;i++){
		if(v[i] > v[i-1]+1){
			cout<<0<<endl;return;
		}
		lst = -1;
		while(sz(st) > v[i]-1){
			lst = st.top();
			st.pop();
		}
		if(lst != -1){
			adj[i].PB(lst);
		}
		if(!st.empty()){
			if(lst != -1) adj[st.top()].POB();
			adj[st.top()].PB(i);
		}
		st.push(i);
	}
	for(int i =0; i<n; i++){
		trace(i,adj[i]);
	}
	while(sz(st) > 1) st.pop();
	rt = st.top();
	dfs1(rt);
	fill_ans(rt);
	cout<<ans[rt]<<endl;
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