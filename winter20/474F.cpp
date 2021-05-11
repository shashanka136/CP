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
int gcd(int a , int b) {
    if(b==0) return a;
    a%=b;
    return gcd(b,a);
}
struct item {
    int n, g,cnt;
    item(): n(INT_MAX), g(0), cnt(1) {}
    item(int x): n(x), g(x), cnt(1) {}
    item operator+(const item& oth) { //operation to merge
        item r;//default is done for sum
        r.n = min(n,oth.n);//must be a associative function
        r.g = gcd(g, oth.g);
        if(n == oth.n && n == r.n) {
            r.cnt = cnt + oth.cnt;
        } else if(n == r.n) {
            r.cnt = cnt;
        } else {
            r.cnt = oth.cnt;
        }
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
    inline int le(int x) {
        return 2 * x + 1;
    }
    inline int ri(int x) {
        return 2 * x + 2;
    }
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
        node anl, anr;
        r++;
        for(l += n,r+=n; l < r; l>>=1, r>>=1) {
            if(l&1) anl = anl + st[l++];//if l is right child then it's parent is not included
            if(r&1) anr = st[--r] + anr;// if r is right child then r-1 is left child and same thing
            //parent is not included
        }
        return anl + anr;
    }

    /*int kth(int k, int l, int r, int p) {
    	if(l == r){ return l;}
    	int m = l+r>>1;
    	if(st[le(p)].n >= k) return kth(k,l,m,le(p));
    	else return kth(k-st[le(p)].n,m+1,r,ri(p));
    }

    int kth(int k) {
    	return kth(k, 0, n - 1, 0);
    }*/
};
typedef segtree<item> segm;
const int N = 1e5+5;
int n,q;
vi s;
int l,r;
item z;
segm fo;
void solve() {
    cin>>n;
    s.assign(n,0);
    INP(s,n);
    fo.build(s);
    cin>>q;
    for(int i =0; i<q; i++) {
        cin>>l>>r;
        l--;
        r--;
        z = fo.query(l,r);
        if(z.g == z.n) {
            cout<<r-l+1 - z.cnt<<endl;
        } else {
            cout<<r-l+1<<endl;
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