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
const int N = 3e5+4;
int n,m,a,b,p[N],an=-1, rel[N];
void no(){
	cout<<"NO"<<endl;
	// exit(0);
}
void yes(){
	cout<<"YES"<<endl;
	// exit(0);
}
int fin(int i){
	if(p[i] != i){
		fin(p[i]);
		rel[i] ^= rel[p[i]];
		p[i] = p[p[i]]; 
	}
	return p[i];
}
void un(int i, int j){
	int x = fin(i), y = fin(j);
	if(x == y) return;
	p[x] = y;
	rel[x] = 1^rel[i]^rel[j];
}
void solve(){
	cin>>n>>m;
	iota(p,p+n,0);
	fill(rel,rel+n,0);
	for(int i=0; i<m; i++){
		cin>>a>>b;
		a--,b--;
		fin(a), fin(b);
		if(p[a] != p[b]){
			un(a,b); continue;
		}
		if(rel[a] == rel[b] && an == -1) an = i+1;
	}
	cout<<an<<endl;
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