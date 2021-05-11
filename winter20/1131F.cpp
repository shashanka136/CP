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
int n,x,y;
const int N = 15e4+5;
struct node{
	int val;
	node* nxt;
	node(int val = -1): val(val), nxt(NULL){}
};
node* cabins[N][2];
int p[N];
int fin(int i){
	if(p[i] != i){
		p[i] = fin(p[i]);
	}
	return p[i];
}
void solve(){
	cin>>n;
	iota(p,p+n,0);
	for(int i =0; i<n; i++){
		cabins[i][0] = new node(i);
		cabins[i][1] = cabins[i][0];
	}
	for(int i =0; i<n-1; i++){
		cin>>x>>y;
		x--,y--;
		cabins[fin(x)][1]->nxt = cabins[fin(y)][0];
		cabins[fin(x)][1] = cabins[fin(y)][1];
		p[fin(y)] = fin(x);
	}
	node* z = cabins[fin(0)][0];
	while(z != NULL){
		trace(z->val);
		cout<<z->val+1<<" ";
		z = z->nxt;
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
	//cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}