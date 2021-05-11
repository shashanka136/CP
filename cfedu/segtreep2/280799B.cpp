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
    ll n;
    item_lazy(ll x = 0): n(x) {}

    item_lazy operator*(const item_lazy& oth) { //operation to merge
        item_lazy r;//default is done for sum
        r.n = n ^ oth.n;//must be a associative function
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
        r.n = n + oth.n;
        return r;
    }
    item operator*(const item_lazy& oth) { //operation to merge
        item r;
        r.n = n + oth.n;//must be a associative function
        return r;
    }
};
int a;
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

    void build(vector<int> &a, int l, int r, int p) {
        if (l == r) {
            if (l < int(a.size())) st[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        build(a, l, m, le(p));
        build(a, m + 1, r, ri(p));
        st[p] = st[le(p)] + st[ri(p)];
    }

    void build(vector<int> &a) {
        init(a.size());
        build(a, 0, n - 1, 0);
    }

    void build(int _n, int l, int r, int p) {
        if (l == r) {
            if (l < _n) {
                cin>>a;
                st[p] = a;
            }
            return;
        }
        int m = l + r >> 1;
        build(_n, l, m, le(p));
        build(_n, m + 1, r, ri(p));
        st[p] = st[le(p)] + st[ri(p)];
    }

    void build(int _n) {
        init(_n);
        build(_n,0, n - 1, 0);
    }

    void push(node1 &x, int l, int r, int p) {
        if(!(x == node1())) {
            st[p].n = (r-l+1) - st[p].n;
            if(l != r) {
                lazy[le(p)] = lazy[le(p)] * x;
                lazy[ri(p)] = lazy[ri(p)] * x;
            }
            x = node1();
        }
    }
    void set(int i, int x, int l, int r, int p) {
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
    void set(int i, int x) {
        set(i, x, 0, n - 1, 0);
    }
    void set(int ql, int qr, int x, int l, int r, int p) {
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
    void set(int l, int r, int x) {
        set(l, r, x, 0, n - 1, 0);
    }

    void add(int ql, int qr, int x, int l, int r, int p) {
        push(lazy[p],l,r,p);
        if (qr < l || ql > r) return;
        if (ql <=l && r <= qr) {
            lazy[p] = x;
            push(lazy[p],l,r,p);
            return;
        }
        int m = l + r >> 1;
        add(ql, qr, x, l, m, le(p));
        add(ql, qr, x, m + 1, r, ri(p));
        st[p] = st[le(p)] + st[ri(p)];
    }
    void add(int l, int r, int x) {
        add(l,r,x,0,n-1,0);
    }
    int kth(int k, int l, int r, int p) {
        if(l == r) {
            return l;
        }
        int m = l+r>>1;
        push(lazy[le(p)],l,m,le(p));
        push(lazy[ri(p)],m+1,r,ri(p));
        // trace(l,r,st[le(p)].n);
        if(st[le(p)].n > k) return kth(k,l,m,le(p));
        else return kth(k-st[le(p)].n,m+1,r,ri(p));
    }

    int kth(int k) {
        push(lazy[0],0,n-1,0);
        return kth(k, 0, n - 1, 0);
    }
    void trav(int l, int r, int p) {
        trace(l,r,st[p].n, lazy[p].n);
        if(l == r) return;
        int m = l+r>>1;
        trav(l,m,le(p));
        trav(m+1,r,ri(p));
    }
    void trav() {
        return trav(0,n-1,0);
    }
};
typedef segtree<item, item_lazy> segm;

int n,m,l,r,typ,k;
segm fo;
void solve() {
    cin>>n>>m;
    fo.init(n);
    for(int i =0; i<m; i++) {
        cin>>typ;
        trace(typ);
        if(typ == 1) {
            cin>>l>>r;
            r--;
            fo.add(l,r,1);
        } else {
            cin>>k;
            cout<<fo.kth(k)<<endl;
        }
        // fo.trav();
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