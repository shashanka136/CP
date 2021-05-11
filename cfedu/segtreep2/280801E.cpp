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
struct item_lazy {
	ll mn, mx;
	item_lazy(): mn(-1), mx(1e9){}
	item_lazy(ll x): mn(x), mx(x) {}

	item_lazy operator*(const item_lazy& oth) { //operation to merge
		item_lazy r;//default is done for sum
		r.mn = max(mn, oth.mn);
		r.mx = min(mx, oth.mx);
		if(oth.mn  >= mx){
			r.mx = r.mn;
		}else if(mn >= oth.mx){
			r.mn = r.mx;
		}
		return r;
	}
	bool operator==(item_lazy oth) {
		return mn == oth.mn && mx == oth.mx;
	}
};

struct item {
	ll mn, mx;
	item(): mn(1e9), mx(0){}
	item(ll x): mn(x), mx(x) {}
	item operator+(const item& oth) { //operation to merge
		item r;//default is done for sum
		r.mn = min(mn, oth.mn);
		r.mx = max(mx, oth.mx);
		return r;
	}
	item operator*(const item_lazy& oth) { //operation to merge
		item r;
		return r;
	}
};
ll a;
template<class node, class node1>
struct segtree {
	int n;
	vector<node> st;
	vector<node1> lazy;
	void init(int _n) { //give some default value value if required
		n = 1;
		while (n < _n) n *= 2;
		st.assign(2 * n, node());
		lazy.assign(2*n, node1());//initialize with different value if required
	}
	inline int le(int x) {
		return 2 * x + 1;
	}
	inline int ri(int x) {
		return 2 * x + 2;
	}

	void push(node1 &x, int l, int r, int p) {
		if(!(x == node1())) {
			// trace(l,r, x.mn, x.mx);
			if(x.mx <= st[p].mn){
				st[p] = node(x.mx);
			}else if(x.mn >= st[p].mx){
				st[p] = node(x.mn);
			}else{
				st[p].mn = max(x.mn, st[p].mn);
				st[p].mx = min(x.mx, st[p].mx);
			}
			if(l != r) {
				lazy[le(p)] = lazy[le(p)] * x;
				lazy[ri(p)] = lazy[ri(p)] * x;
			}
			// trace(l,r,st[p].mx, st[p].mn);
			x = node1();
		}
	}
	void set(int i, ll x, int l, int r, int p) {
		push(lazy[p],l,r,p);
		if (i < l || i > r) return;
		if (l == r) {
			st[p] = x;
			return;
		}
		int m = l + r >> 1;
		if (i <= m) set(i, x, l, m, le(p));
		else set(i, x, m + 1, r, ri(p));

		st[p] = st[le(p)] + st[ri(p)];
	}
	void set(int i, ll x) {
		set(i, x, 0, n - 1, 0);
	}
	void set(int ql, int qr, ll x, int l, int r, int p) {
		push(lazy[p],l,r,p);
		if (qr < l || ql > r) return;
		if (l == r) {
			st[p] = x;
			return;
		}
		int m = l + r >> 1;
		set(ql, qr, x, l, m, le(p));
		set(ql, qr, x, m + 1, r, ri(p));

		st[p] = st[le(p)] + st[ri(p)];
	}
	void set(int l, int r, ll x) {
		set(l, r, x, 0, n - 1, 0);
	}
	template<int typ>
	void add(int ql, int qr, ll x, int l, int r, int p) {
		push(lazy[p],l,r,p);
		if (qr < l || ql > r) return;
		if (ql <=l && r <= qr) {
			if(typ == 0)lazy[p].mn = x;
			else lazy[p].mx = x;
			push(lazy[p],l,r,p);
			return;
		}
		int m = l + r >> 1;
		add<typ>(ql, qr, x, l, m, le(p));
		add<typ>(ql, qr, x, m + 1, r, ri(p));
		st[p] = st[le(p)] + st[ri(p)];
	}
	template<int typ>
	void add(int l, int r, ll x) {
		add<typ>(l,r,x,0,n-1,0);
	}

	node get(int i, int l, int r, int p) {
		// cout<<"query"<<endl;
		push(lazy[p],l,r,p);
		if (l == r) return st[p];
		int m = l + r >> 1;
		node x;
		if(i <= m)  x = get(i, l, m, le(p));
		else x = get(i, m + 1, r, ri(p));
		st[p] = st[le(p)] + st[ri(p)];
		return x;
	}

	node get(int i) {
		return get(i,0,n-1,0);
	}

	node query(int ql, int qr, int l, int r, int p) {
		// cout<<"query"<<endl;
		push(lazy[p],l,r,p);
		if (r < ql || l > qr) return node();
		if (ql <= l && r <= qr) return st[p];
		int m = l + r >> 1;
		return query(ql, qr, l, m, le(p)) +
			   query(ql, qr, m + 1, r, ri(p));
	}

	node query(int l, int r) {
		return query(l, r, 0, n - 1, 0);
	}
};
typedef segtree<item, item_lazy> segm;

int n,k,l,r,h,typ;
segm fo;
void solve(){
	cin>>n>>k;
	fo.init(n);
	fo.set(0,n-1,0);
	for(int i = 0; i<k; i++){
		cin>>typ>>l>>r>>h;
		// trace(i);
		if(typ == 1)fo.add<0>(l,r,h);
		if(typ == 2)fo.add<1>(l,r,h);
		// for(int i=0; i<n;i++){
		// 	cout<<fo.get(i).mn<<" ";
		// }cout<<endl;
	}
	for(int i=0; i<n;i++){
		cout<<fo.get(i).mn<<endl;
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