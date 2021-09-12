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
int n,m,u,v,sqn,p[N];
int ind[N],dep[N],cnt;
vi adj[N];

void dfs(int i){
	ind[i] = 0;
	for(int &j : adj[i]){
		if(j == p[i]) continue;
		if(ind[j] != -1){
			if(dep[i]-dep[j]+1 >= sqn){
				cout<<2<<endl;
				cout<<dep[i]-dep[j]+1<<endl;
				while(i!=-1 && dep[i] >= dep[j]){
					cout<<i+1<<" ";
					i = p[i];
				}
				cout<<endl;
				exit(0);
			}
		}else{
			p[j] = i;
			dep[j] = dep[i] +1;
			dfs(j);
		}
	}
	if(ind[i] == 0){
		for(int &j : adj[i]){
			ind[j] = 1;
		}
	}
}
void solve(){
	cin>>n>>m;
	for(int i =0; i<m; i++){
		cin>>u>>v;
		u--,v--;
		adj[u].PB(v);
		adj[v].PB(u);
	}
	sqn = sqrt(n);
	sqn += (sqn*sqn != n);
	p[0] = -1;
	fill(ind,ind+n,-1);
	ind[0] = 1;
	dep[0] = 0;
	dfs(0);
	cout<<1<<endl;
	cnt = sqn;
	for(int i=0; i<n&&cnt;i++){
		if(ind[i] == 0){
			cout<<i+1<<" ";
			cnt--;
		}
	}
	cout<<endl;
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
	// cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}