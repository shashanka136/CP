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
const int N = 2e5;
int n,u,v,tot[N],vis[N],p[N],p1,p2;
ll cnt;
vi adj[N];

void dfs(int i, int par){
	p[i] = par;
	tot[i] = 1;
	for(int &x: adj[i]){
		if(x == par) continue;
		dfs(x,i);
		tot[i] += tot[x];
	}
}
void solve(){
	cin>>n;
	for(int i=1; i<n; i++){
		cin>>u>>v;
		adj[u].PB(v);		
		adj[v].PB(u);		
	}
	dfs(0,0);
	fill(vis,vis+n,0);
	cnt = 0;
	for(int &x : adj[0]){
		cnt += 1ll*tot[x]*(tot[x]-1)/2;
	}
	cout<<cnt<<" ";
	p1 = 0, p2 = 0;
	vis[0] = 1;
	cnt = 1ll*n*(n-1)/2 - cnt;
	int cr,ptr;
	stack<int> st;
	// trace(p1,p2,cnt,tot[p1],tot[p2]);
	for(cr =1; cr<n; cr++){
		if(vis[cr]){
			cout<<0<<" ";
			continue;
		}
		ptr = cr;
		while(!vis[ptr]){
			st.push(ptr);
			vis[ptr] = true;
			ptr = p[ptr];
		}
		if(ptr == p1){
			p1 = cr;
		}else if(ptr == p2){
			p2 = cr;
		}else{
			cout<<cnt<<" ";
			cr++;
			for(;cr <=n; cr++){
				cout<<0<<" ";
			}
			cout<<endl;
			break;
		}
		// trace(p1,p2,cnt,tot[p1],tot[p2]);
		while(!st.empty()){
			tot[ptr] -= tot[st.top()];
			ptr = st.top();
			st.pop();
		}
		// trace(p1,p2,cnt,tot[p1],tot[p2]);
		cout<<cnt - 1ll*tot[p1]*tot[p2]<<" ";
		cnt = 1ll*tot[p1]*tot[p2];
	}
	if(cr == n){
		cout<<cnt<<endl;
	}
	for(int i =0; i<n; i++){
		adj[i].clear();
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
	cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}