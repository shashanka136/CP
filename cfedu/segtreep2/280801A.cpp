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
typedef vector<ll> vl;
typedef vector<int> vi;
typedef vector<vl> vvl;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpl;
typedef vector<pii> vpi;
typedef vector<vpl> vvpl;
typedef vector<vpi> vvpi;
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
    ll n,num;
    item_lazy(ll x = 0, ll nm = -1): n(x),num(nm) {}

    item_lazy operator*(const item_lazy& oth) { //operation to merge
        item_lazy r;//default is done for sum
        r.n = n + oth.n;//must be a associative function
        r.num = max(num,oth.num);
        return r;
    }
    bool operator==(item_lazy oth) {
        return n == oth.n;
    }
};

struct item_lazy2 {
    ll n,num;
    item_lazy2(ll x = -1, ll nm = -1): n(x), num(nm) {}

    item_lazy2 operator*(const item_lazy2& oth) { //operation to merge
        item_lazy2 r;//default is done for sum
        if( num < oth.num) r.n = oth.n;//must be a associative function
        else r.n = n;
        r.num = max(num, oth.num);
        return r;
    }
    bool operator==(item_lazy2 oth) {
        return n == oth.n;
    }
};

struct item {
    ll n;
    item(ll x = 0): n(x) {}
    item operator+(const item& oth) { //operation to merge
        item r;//default is done for sum
        r.n = n + oth.n;
        return r;
    }
    item operator*(const item_lazy& oth) { //operation to merge
        item r;
        r.n = r.n + oth.n;//must be a associative function
        return r;
    }
};
int a;
template<class node, class node1, class node2>
struct segtree {
    int n;
    vector<node> st;
    vector<node1> lazy;
    vector<node2> lazy2;
    void init(int _n) { //give some default value value if required
        n = 1;
        while (n < _n) n *= 2;
        st.assign(2 * n, node());
        lazy.assign(2*n, node1());//initialize with different value if required
        lazy2.assign(2*n, node2());//initialize with different value if required
    }
    inline int le(int x) {
        return 2 * x + 1;
    }
    inline int ri(int x) {
        return 2 * x + 2;
    }

    void push(node1& x, node2& y, int l, int r, int p) {
        if(!(y == node2())) {
            st[p].n = y.n * (r-l+1);
            if(l != r) {
                lazy2[le(p)] = lazy2[le(p)] * y;
                lazy2[ri(p)] = lazy2[ri(p)] * y;
            }
        }
        if(x.num <= y.num) x = node1();
        if(!(x == node1())) {
            st[p].n = st[p].n + x.n *(r-l+1);
            if(l != r) {
                lazy[le(p)] = lazy[le(p)] * x;
                lazy[ri(p)] = lazy[ri(p)] * x;
            }
            x = node1();
        }
        y = node2();
    }
    void set(int ql, int qr, ll x, int l, int r, int p, int i) {
        push(lazy[p],lazy2[p],l,r,p);
        if (qr < l || ql > r) return;
        if (ql <= l && r <= qr) {
            lazy2[p] = {x, i};
            push(lazy[p],lazy2[p], l,r,p);
            return;
        }
        int m = l + r >> 1;
        set(ql, qr, x, l, m, le(p), i);
        set(ql, qr, x, m + 1, r, ri(p), i);

        st[p] = st[le(p)] + st[ri(p)];
    }
    void set(int l, int r, ll x, int i) {
        set(l, r, x, 0, n - 1, 0, i);
    }

    void add(int ql, int qr, ll x, int l, int r, int p, int i) {
        push(lazy[p],lazy2[p], l,r,p);
        if (qr < l || ql > r) return;
        if (ql <=l && r <= qr) {
            lazy[p] = {x,i};
            push(lazy[p],lazy2[p], l,r,p);
            return;
        }
        int m = l + r >> 1;
        add(ql, qr, x, l, m, le(p), i);
        add(ql, qr, x, m + 1, r, ri(p), i);
        st[p] = st[le(p)] + st[ri(p)];
    }
    void add(int l, int r, ll x, int i) {
        add(l,r,x,0,n-1,0,i);
    }
    node query(int ql, int qr, int l, int r, int p) {
        // cout<<"query"<<endl;
        push(lazy[p],lazy2[p],l,r,p);
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
typedef segtree<item, item_lazy, item_lazy2> segm;

int n,m,l,r,v,typ;
segm fo;
void solve() {
    cin>>n>>m;
    fo.init(n);
    for(int i = 0; i<m; i++) {
        cin>>typ;
        if(typ == 1) {
            cin>>l>>r>>v;
            r--;
            fo.set(l,r,v,i);
        } else if(typ == 2) {
            cin>>l>>r>>v;
            r--;
            fo.add(l,r,v,i);
        } else {
            cin>>l>>r;
            r--;
            cout<<fo.query(l,r).n<<endl;
        }
    }
}

int main() {
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
    while(t--) {
        solve();
    }
}