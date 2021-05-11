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
int n,a,b,h,d;
char c;
const int N = 1e7+5;
int st[N], lazy[N], mx[N], le[N], ri[N], cr = 1,lval = -1e9-10;

void push(int l, int r, int p){
	if(lazy[p] == lval) return;
	st[p] = lazy[p] *(r-l+1);
	mx[p] = max(0, lazy[p] * (r-l+1));
	if(l == r){
		lazy[p] = lval; return;
	}
	if(le[p] == -1){
		le[p] = cr; 
		st[cr] = 0, lazy[cr] = lval;
		mx[cr] = 0;
		cr++;
	}
	if(ri[p] == -1){
		ri[p] = cr;
		st[cr] = 0, lazy[cr] = lval;
		mx[cr] = 0;
		cr++;
	}
	lazy[le[p]] = lazy[p];
	lazy[ri[p]] = lazy[p];
	lazy[p] = lval; return;
}

void add(int a, int b, int d, int l, int r, int p){
	push(l,r,p);
	if(a > r || b < l) return;
	if(a <=l && r <= b){
		lazy[p]= d ;
		push(l,r,p);
		return;
	}
	int m = l+r>>1;
	if(le[p] == -1){
		le[p] = cr; 
		st[cr] = 0, lazy[cr] = lval;
		mx[cr] = 0;
		cr++;
	}
	if(ri[p] == -1){
		ri[p] = cr;
		st[cr] = 0, lazy[cr] = lval;
		mx[cr] = 0;
		cr++;
	}
	add(a,b,d,l,m,le[p]);
	add(a,b,d,m+1,r,ri[p]);
	st[p] = st[le[p]] + st[ri[p]];
	mx[p] = max(mx[le[p]], st[le[p]] + mx[ri[p]]);
}
void add(int a, int b, int d){
	add(a,b,d,0,n-1,0);
}
int find(int h, int l, int r, int p){
	push(l,r,p);
	if(l == r) return l;
	int m = l+r>>1;
	if(le[p] != -1){
		push(l,m,le[p]);
		if(mx[le[p]] >h)
			return find(h,l,m,le[p]);
	}
	if(ri[p] == -1){
		ri[p] = cr; 
		st[cr] = 0, mx[cr] = 0;
		cr++;
	}
	if(le[p] != -1) return find(h - st[le[p]], m+1,r, ri[p]);
	return find(h, m+1,r, ri[p]);
}
int find(int h){
	push(0,n-1,0);
	if(mx[0] <= h) return n;
	return find(h, 0, n-1, 0);
}
void solve(){
	cin>>n;
	cin>>c;
	fill(le, le + N, -1);
	fill(ri, ri + N, -1);
	fill(lazy,lazy +N, lval);
	st[0] = 0;
	mx[0] = 0;
	// trace(2);
	while(c != 'E'){
		if(c == 'I'){
			cin>>a>>b>>d;
			a--,b--;
			// trace(a,b,d);
			add(a,b,d);
		}else{
			cin>>h;
			cout<<find(h)<<endl;
		}
		// trace(2);
		cin>>c;
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