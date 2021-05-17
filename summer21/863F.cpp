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
const int inf = 1e9;
struct edkarp {
	vector<vector<int>> cap;
	vector<vector<int>> adj;
	int n;
	void init(int _n){
		n = _n;
		cap.assign(n, vector<int>(n, 0));
		adj.assign(n, vector<int>(0));
	}

	void add(int u, int v, int c) {
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
		cap[u][v] = c;
	}
	int bfs(int st, int tar, vector<int> &p) { //p must already be of req. size
		fill(p.begin(), p.end(), -1);
		p[st] = -2;
		queue<pair<int, int>> q;
		q.push(MP(st, inf));
		while (!q.empty()) {
			int i = q.front().F, flow = q.front().S;
			q.pop();
			for (auto &x : adj[i]) {
				if (p[x] == -1 && cap[i][x]) {
					p[x] = i;
					int nf = min(flow, cap[i][x]);
					if (x == tar) {
						return nf;
					}
					q.push(MP(x, nf));
				}
			}
		}
		return 0;
	}

	int maxflow(int st, int tar) {
		// if there is need to upgrade number of nodes in graph
		vector<int> p(n);//num is the number of nodes
		int flow = 0;
		int nf;//new flow

		while (nf = bfs(st, tar, p)) {
			flow += nf;
			int cr = tar;
			while (cr != st) {
				cap[p[cr]][cr] -= nf;
				cap[cr][p[cr]] += nf;
				cr = p[cr];
			}
		}

		return flow;
	}
};
int n,q;
int l,r,v,typ;
bool fix[102];
int mn[102],mx[102],ind[102];
void ret(){
	cout<<-1<<endl;
}
bool cmp(const int &i, const int &j){
	return MP(mn[i],mx[i]) < MP(mn[j],mx[j]);
}
edkarp fo;
void solve(){
	cin>>n>>q;
	fill(mn,mn+n,1);
	fill(mx,mx+n,n);
	fill(fix,fix+n+1,false);
	for(int i =0; i<q; i++){
		cin>>typ>>l>>r>>v;
		l--,r--;
		if(typ == 1){
			for(int j =l; j<=r; j++){
				if(mx[j] < v) return ret();
				mn[j] = max(mn[j], v);
			}
		}else{
			for(int j =l; j<=r; j++){
				if(mn[j] > v) return ret();
				mx[j] = min(mx[j], v);
			}
		}
	}
	int tfl = 0,cr,crlvl = 0;
	ll ans = 0;
	while(tfl != n){
		fo.init(2*n+2);
		for(int i=0;i<n; i++){
			fo.add(0,i+1, 1);
			if(fix[i]) continue;
			fo.add(n+i+1, 2*n+1,1);
			for(int j = mn[i]; j<=mx[i]; j++){
				fo.add(j,n+1+i,1);
			}
		}
		cr= fo.maxflow(0,2*n+1);
		for(int i =0; i<n; i++){
			if(fix[i]) continue;
			if(fo.cap[n+i+1][2*n+1] == 0){
				fix[i] = true;
			}
		}
		trace(crlvl, cr);
		ans += cr*(2*crlvl+1);
		crlvl++;
		tfl += cr;
	}
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