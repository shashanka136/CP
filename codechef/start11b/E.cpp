/* AUTHOR - MAHADEV( codechef - @har_harmahadev) */
#include <bits/stdc++.h>
#ifdef STAC
#include <sys/resource.h>
#endif
#pragma GCC optimize("-O3")
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

const int N = 2e5+5;

int n;
vi ord[N];

struct item {
	int n;
	item(int x = 0): n(x) {
	}
	item operator+(const item& oth) { //operation to merge
		item r;//default is done for sum
		r.n = max(n,oth.n);//must be a associative function
		return r;
	}
};

template<class node>
struct segtree {
	int n;
	vector<node> st;

	void init(int _n) { //give some default value value if required
		n = _n;
		st.assign(2 * n, node());
	}
	inline int le(int x) {return 2 * x + 1;}
	inline int ri(int x) {return 2 * x + 2;}
	//change vector to int* if required in both build

	void build(vector<int> &a) {
		init(a.size());
		for (int i = n; i < 2 * n; i++)
			st[i] = a[i - n];
		for (int i = n - 1; i > 0; i--)
			st[i] = st[i << 1] + st[i << 1 | 1];
	}

	void set(int i, int x) {
		for (st[i += n] = x; i >>= 1; )
			st[i] = st[i<<1] + st[i<<1|1];
	}

	node query(int l, int r) {
		node anl, anr;r++;
		for(l += n,r+=n;l < r; l>>=1, r>>=1){
			if(l&1) anl = anl + st[l++];//if l is right child then it's parent is not included
			if(r&1) anr = st[--r] + anr;// if r is right child then r-1 is left child and same thing
			//parent is not included
		}
		return anl + anr;
	}
};
typedef segtree<item> segm;

void solve(){
	cin>>n;
	vi a(n);
	priority_queue<int> b[n+1];
	INP(a,n);
	for(int i =0; i<n; i++){
		b[a[i]].push(-i);
	}
	segm fo;
	fo.build(a);
	for(int i =0; i<n ;i++){
		int mx = fo.query(i,min(n-1,i+i)).n;
		ord[mx].PB(i+1);
		int cr = fo.query(i,i).n;
		if(mx != cr){
			int mxind = -b[mx].top();
			int crind = -b[cr].top();
			fo.set(mxind,cr);
			b[mx].pop();
			b[cr].pop();
			b[cr].push(-mxind);
		}else{
			b[cr].pop();
		}
	}
	vi cr(n+1,0);
	for(int i=0; i<n; i++){
		cout<<ord[a[i]][cr[a[i]]]<<" ";
		cr[a[i]]++;
	}
	cout<<endl;
	for(int i =0; i<=n; i++) ord[i] = vi(0);
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