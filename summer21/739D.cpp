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
struct edge {
	int u, v;
	int cap;
	edge(int _u, int _v, int cap): u(_u), v(_v), cap(cap) {}
	int get(int t) { return t ^ u ^ v;}
};

struct dinic{
	const int inf = 1e9;
	int n,st,tar;
	vector<edge> edges;
	vector<vector<int>> adj;
	vector<int> lvl,from;

	inline int comp(int i){ return i^1;}//compliment edge

	inline int par(int i, int edge_num){ return edges[edge_num].get(i);}
	
	void init(int _n){
		n = _n;
		adj.assign(n, vector<int>(0));
		edges.clear();
	}

	void add(int u, int v, int cap){
		adj[u].push_back(edges.size());
		edges.emplace_back(u,v,cap);
		adj[v].push_back(edges.size());
		edges.emplace_back(v,u,0);
	}

	void bfs(){
		lvl.assign(n,-1);
		lvl[st] = 0;
		queue<int> q;
		q.push(st);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(int i : adj[u]){
				if(lvl[par(u,i)] != -1 || edges[i].cap == 0) continue;
				lvl[par(u,i)] = lvl[u] +1;
				q.push(par(u,i));
			}
		}
	}

	int dfs(int u, int mnflow){
		if(u == tar) return mnflow;
		for(int& i = from[u]; i < adj[u].size(); i++){
			int v = par(u,adj[u][i]);
			if(lvl[v] != lvl[u] +1 || edges[adj[u][i]].cap == 0) continue;
			int ret = dfs(v,min(mnflow, edges[adj[u][i]].cap));
			if(ret == 0) continue;
			edges[adj[u][i]].cap -= ret;
			edges[comp(adj[u][i])].cap += ret;
			return ret;
		}
		return 0;
	}

	int maxflow(int _st, int _tar){
		st = _st;
		tar = _tar;
		int flow = 0;
		while(1){
			bfs();
			if(lvl[tar] == -1) break;
			from.assign(n,0);
			while(int nf = dfs(st, inf)){
				flow += nf;
			}
		}
		return flow;
	}
};
//takes O(E*sqrt(v)) for unit graph
const int N = 304;
int n,pre[N], cyc[N],mx,ind,mxpre[N], cnt[N];
int pos[N][N],req,st,tar,apre[N], acyc[N],to,ans[N],mid;
pii invpos[N*N];
vi fin[N][N];
string s;
dinic fo;
int inp(){
	cin>>s;
	if(s[0] == '?') return -1;
	else{
		return stoi(s);
	}
}

bool once(){
	st = 0,tar = 1,req = 0;
	mid = 0;
	fill(mxpre, mxpre+n+1,-1);
	fill(cnt, cnt+n+1,0);
	for(int i =0; i<n; i++){
		if(cyc[i] != -1 && pre[i] == 0){
		}else{
			pos[0][i] = tar;
			mid = tar;
			invpos[tar++] = MP(i,0);
		}
		if(cyc[i] != -1){
			if(pre[i] == 0) cnt[cyc[i]]++;
			mxpre[cyc[i]] = max({0, pre[i], mxpre[cyc[i]]});
		}
	}

	for(int i = 1; i<=n; i++){
		for(int j = 0; j <= mxpre[i]; j++){
			pos[i][j] = tar;
			invpos[tar++] = MP(j,i);
		}
	}
	fo.init(tar+1);
	for(int i = 0; i<n; i++){
		if(cyc[i] == -1 || pre[i] != 0){
			fo.add(0,pos[0][i],1);
		}
	}
	for(int i = 1; i<=n; i++){
		if(mxpre[i] == -1) continue;
		int j=i*(cnt[i]/i);
		if(j == 0 || j < cnt[i]) j += i;
		if(j > cnt[i])fo.add(pos[i][0], tar, j-cnt[i]);
		req += j -cnt[i];
		for(int j = 1; j<= mxpre[i]; j++){
			fo.add(pos[i][j], tar, 1);
		}
		req += mxpre[i];
	}
	if(req > n) return false;//can be changed ig
	for(int i =0; i<n ;i++){
		if(cyc[i] != -1 && pre[i] == 0) continue;
		if(cyc[i] != -1 && pre[i] != -1){
			fo.add(pos[0][i], pos[cyc[i]][pre[i]], 1);
		}else if(cyc[i] != -1){
			for(int j = 0; j<= mxpre[cyc[i]]; j++){
				fo.add(pos[0][i], pos[cyc[i]][j], 1);
			}
		}else if(pre[i] != -1){
			for(int j = 1; j<= n; j++){
				if( pre[i] <= mxpre[j]){
					fo.add(pos[0][i], pos[j][pre[i]], 1);
				}
			}
		}else{
			for(int j = mid+1; j< tar; j++){
				fo.add(pos[0][i], j, 1);
			}
		}
	}
	int fl = fo.maxflow(0,tar);
	if(fl != req) return false;
	for(int i =0; i<n; i++){
		if(cyc[i] != -1 && pre[i] == 0){
			apre[i] = pre[i], acyc[i] = cyc[i];
			continue;
		}
		if(fo.edges[fo.adj[pos[0][i]][0]].cap){
			for(int x : fo.adj[pos[0][i]]){
				to = fo.par(pos[0][i],x);
				if(to == 0) continue;
				if(fo.edges[x].cap) continue;
				apre[i] = invpos[to].F;
				acyc[i] = invpos[to].S;
				break;
			}
		}else{
			apre[i] = -1;
			for(int x : fo.adj[pos[0][i]]){
				to = fo.par(pos[0][i],x);
				if(to == 0) continue;
				if(invpos[to].F == 0) continue;
				apre[i] = invpos[to].F;
				acyc[i] = invpos[to].S;
				break;
			}
			if(apre[i] == -1){
				if(pre[i] == -1 && cyc[i] == -1){
					apre[i] = 0, acyc[i] = 1;
				}else if( pre[i] == -1){
					apre[i] = 1, acyc[i] = cyc[i];
				}else if(pre[i] == 0){//cyc will be -1
					apre[i] = 0, acyc[i] = 1;
				}else{
					return false;//can't be satisfied
				}
			}
		}
	}

	for(int i =0; i<n;i++){
		fin[acyc[i]][apre[i]].PB(i);
	}
	for(int i = 1; i<=n; i++){
		if(fin[i][0].empty()) continue;
		int lst = 0;
		assert(sz(fin[i][0])%i == 0);
		for(int j = 1; j < sz(fin[i][0]); j++){
			if(j%i){
				ans[fin[i][0][j-1]] = fin[i][0][j];
			}else{
				ans[fin[i][0][j-1]] = fin[i][0][lst];
				lst = j;
			}
		}
		ans[fin[i][0][sz(fin[i][0])-1]] = fin[i][0][lst];
		for(int j = 1; j <n; j++){
			if(fin[i][j].empty()) break;
			for(auto x : fin[i][j]) ans[x] = fin[i][j-1][0];
		}
	}
	for(int i =0; i<n; i++){
		cout<<ans[i]+1<<" ";
	}
	cout<<endl;
	return true;
}
void solve(){
	cin>>n;
	mx = -1;ind = -1;
	for(int i =0; i<n; i++){
		pre[i] = inp();
		cyc[i] = inp();
		if(cyc[i] == -1 && pre[i] > mx){
			mx = pre[i];
			ind = i;
		}
	}
	if(once()) return;
	if(ind != -1){
		for(int i = 1; i<=n;i++){//setting different cycle lengths
			cyc[ind] = i;
			if(once()) return; 
		}
	}
	cout<<-1<<endl;
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