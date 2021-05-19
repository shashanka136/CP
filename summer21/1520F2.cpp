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
struct node{
	node* le;
	node* ri;
	int val;
	node(): val(-1), le(NULL), ri(NULL){}
	node(int val): val(val), le(NULL), ri(NULL){}
};
int n,k,ans;
node* rt;

void ask_query(int l, int r){
	cout<<"? "<<l<<" "<<r<<endl;
	cin>>ans;
	if(ans == -1) exit(0);
	ans = r-l+1-ans;
}
void giveans(int x){
	cout<<"! "<<x<<endl;
	// cin>>ans;
	if(ans == -1) exit(0);
}
int kth(node* rt,int k,int l,int r){
	if(l == r){
		rt->val = 0;
		return l;
	}
	if(rt->val >= 0) rt->val--;
	if(rt->le == NULL) rt->le = new node();
	int m = l+r>>1;
	if(rt->le->val == -1){
		ask_query(l,m);
		rt->le->val = ans;
	}
	if(rt->le->val >= k){
		return kth(rt->le, k, l,m);
	}
	if(rt->ri == NULL) rt->ri = new node();
	return kth(rt->ri,k-rt->le->val,m+1,r);
}

void solve(){
	cin>>k;
	int y = kth(rt,k,1,n);
	giveans(y);
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
	cin>>n>>t;
	rt = new node();
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}