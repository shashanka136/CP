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
const int N = 2e5+5;

struct item_lazy {
    ll n;
    item_lazy(ll x = 0): n(x) {}

    item_lazy operator*(const item_lazy& oth) { //operation to merge
        item_lazy r;//default is done for sum
        r.n = n + oth.n;//must be a associative function
        return r;
    }
    bool operator==(item_lazy oth) {
        return n == oth.n;
    }
};

struct item {
    ll n;
    item(ll x = 0): n(x) {}
    item operator+(const item& oth) { //operation to merge
        item r;//default is done for sum
        r.n = max(n,oth.n);
        return r;
    }
    item operator*(const item_lazy& oth) { //operation to merge
        item r;
        r.n = n + oth.n;//must be a associative function
        return r;
    }
};
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
            st[p] = st[p] * x;
            if(l != r) {
                lazy[le(p)] = lazy[le(p)] * x;
                lazy[ri(p)] = lazy[ri(p)] * x;
            }
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

    void add(int ql, int qr, ll x, int l, int r, int p) {
        push(lazy[p],l,r,p);
        if (qr < l || ql > r) return;
        if (ql <=l && r <= qr) {
            lazy[p] = x;
            // trace(p,st[p].n);
            push(lazy[p],l,r,p);
            // trace(p,st[p].n);
            return;
        }
        int m = l + r >> 1;
        add(ql, qr, x, l, m, le(p));
        add(ql, qr, x, m + 1, r, ri(p));
        st[p] = st[le(p)] + st[ri(p)];
    }
    void add(int l, int r, ll x) {
    	// trace(l,r,x);
        add(l,r,x,0,n-1,0);
    }

    node get(int i, int l, int r, int p) {
        // cout<<"query"<<endl;
        push(lazy[p],l,r,p);
        if (l == r) return st[p];
        int m = l + r >> 1;
        if(i <= m)  return get(i, l, m, le(p));
        else return get(i, m + 1, r, ri(p));
    }

    node get(int i) {
        return get(i,0,n-1,0);
    }

    node query(int ql, int qr, int l, int r, int p) {
        // cout<<"query"<<endl;
        push(lazy[p],l,r,p);
        if (r < ql || l > qr) return node(LLONG_MIN);
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


int n,m,l[N],r[N],a[N];
segm fo;
ll dp[N];
struct event{
	int typ,val,i;
	event(){}
	event(int t, int v, int i): typ(t), val(v), i(i){}

	bool operator<(const event &oth){
		if(val < oth.val) return true;
		if(val > oth.val) return false;
		if(typ < oth.typ) return true;
		return false;
	}
};

event s[2*N];
void solve(){
	cin>>n>>m;
	for(int i =0; i<m; i++){
		cin>>l[i]>>r[i]>>a[i];
		s[2*i] = event(0,l[i], i);
		s[2*i+1] = event(1,r[i], i);
	}
	fo.init(n+1);
	m = m<<1;
	sort(s,s+m);
	dp[0] = 0;
	int j = 0;
	for(int i =1; i<=n; i++){
		while(j < m && s[j].val == i && s[j].typ == 0){
			// trace(0,i-1,a[s[j].i]);
			fo.add(0,i-1,a[s[j].i]);
			j++;
		}
		dp[i] = fo.query(0,i-1).n;
		// trace(i,dp[i]);
		fo.add(i,i,dp[i]);
		// trace(j, s[j].val, s[j].typ);
		while(j <m && s[j].val == i && s[j].typ == 1){
			fo.add(0,l[s[j].i]-1,-a[s[j].i]);
			j++;
		}
	}
	ll ans = 0;
	for(int i =1; i<=n; i++) ans =max(ans, dp[i]);
	cout<<ans<<endl;
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