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

const int N = 2e5;
int n,u,v;
vi adj[N];
int d[N];
int a,b,c,mxd;
vi diam;
const int inf = 2e9;
template < int typ>
void dfs1(int i, int p = -1, int d = 0) {
    if(d > mxd) {
        mxd = d;
        if(typ == 0) a = i;
        else b = i;
    }
    for(auto x: adj[i]) {
        if(x == p) continue;
        dfs1<typ>(x,i,d+1);
    }
}

void dfs2(int i, int p = -1) {
    if(i == b) {
        diam.PB(i);
    } else {
        for(auto x : adj[i]) {
            if(x == p) continue;
            dfs2(x,i);
            if(!diam.empty() && diam.back() == x) {
                diam.PB(i);
                return;
            }
        }
    }
}
void solve() {
    cin>>n;
    for(int i=1; i<n; i++) {
        cin>>u>>v;
        u--,v--;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    mxd = -1;
    dfs1<0>(0);
    trace(a);
    mxd = -1;
    dfs1<1>(a);
    trace(a,b);
    dfs2(a);
    fill(d,d+n,inf);
    mxd =-1, v =-1;
    queue<int> q;
    for(auto x: diam) q.push(x), d[x] = 0;

    while(!q.empty()) {
        u = q.front();
        q.pop();
        if(d[u] > mxd && u != a && u != b) {
            mxd = d[u];
            v= u;
        }
        for(auto x: adj[u]) {
            if(d[x] == inf) d[x] = d[u]+1, q.push(x);
        }
    }
    // OUT(d,n);
    cout<<sz(diam)-1 + mxd<<endl;
    cout<<a+1<<" "<<b+1<<" "<<v+1<<endl;
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