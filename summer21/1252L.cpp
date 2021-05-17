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
const int N = 2e3+5;
int n,k,m,bval;
int a[N],c[N];
bool vis[N];
map<int,vi> b;
edkarp fo;
void solve(){
	cin>>n>>k;
	for(int i =0; i<n; i++){
		cin>>a[i]>>m;
		a[i]--;
		for(int j =0; j<m;j++){
			cin>>bval;
			b[bval].PB(i);
		}
	}
	for(int i =0; i<k; i++) cin>>c[i];
	if(k < n-1){
		cout<<-1<<endl;
		return;
	}
	fill(vis,vis+n,false);
	int st =0;
	while(!vis[st]){
		vis[st] = true;
		st = a[st];
	}
	int tmp = 0;
	while(tmp != st){
		vis[tmp] = false;
		tmp = a[tmp];
	}
	int cyclen = 0;
	for(int i=0;i<n;i++)if(vis[i])cyclen++;
	fo.init(3+n+k);
	fo.add(0,1,cyclen-1);
	for(int i=0;i<n;i++){
		if(vis[i]){
			fo.add(1,2+i,1);
		}else{
			fo.add(0,2+i,1);
		}
	}
	for(int i=0;i<k;i++){
		vi &v = b[c[i]];
		for(auto x : v){
			fo.add(2+x,n+2+i,1);
		}
		fo.add(n+2+i,n+2+k,1);
	}
	int flow = fo.maxflow(0,n+2+k);
	if(flow != n-1){
		cout<<-1<<endl;
		return;
	}
	for(int i =0; i<k; i++){
		if(fo.cap[n+2+i][n+2+k] != 0){
			cout<<0<<" "<<0<<endl;
			continue;
		}
		vi &v = b[c[i]];
		for(auto x : v){
			if(fo.cap[2+x][n+2+i] == 0){
				cout<<x+1<<" "<<a[x]+1<<endl;
				break;
			}
		}
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