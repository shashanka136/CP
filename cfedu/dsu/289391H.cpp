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
const int N = 5e4+3;
const int M = 1e5+5;
int n,m,u,v,w,p[N];
bool pre[M];
ll s;
struct edge {
	int u, v,w,in;
	edge(){}
	edge(int _u, int _v, int _w, int _in): u(_u), v(_v), w(_w), in(_in) {}
	int get(int t) { return t ^ u ^ v;}
	bool operator<(const edge& oth){
		return w > oth.w;
	}
};
edge fo[M];

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
	cin>>n>>m>>s;
	iota(p,p+n,0);
	fill(pre, pre+m,false);
	for(int i=0; i<m; i++){
		cin>>u>>v>>w;
		u--,v--;
		fo[i] = edge(u,v,w,i+1);
	}
	sort(fo, fo+m);
	for(int i =0; i<m; i++){
		if(fin(fo[i].u) == fin(fo[i].v)) continue;
		pre[i] = true;
		un(fo[i].u, fo[i].v);
	}
	int i = m-1,ans =0;
	vi an;
	while(i >= 0){
		if(pre[i] || s < fo[i].w){
			i--;continue;
		}
		s -= fo[i].w;
		an.PB(fo[i].in);
		ans++;
		i--;
	}
	cout<<ans<<endl;
	sort(all(an));
	OUT(an,ans);
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