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
const int N = 1e5+4;
vpi adj[N];
int n,m,d,u,v,val;
int dep[N],p[N];
void solve(){
	cin>>n>>m>>d;
	for(int i =0; i<m; i++){
		cin>>u>>v>>val;
		u--,v--;
		adj[u].EB(MP(v,val));
	}
	function<bool(int)> bfs = [&](int vl){
		queue<int> q;
		q.push(0);
		fill(dep,dep+n, -1);
		dep[0] = 0;
		while(!q.empty()){
			int i = q.front();
			if(i == n-1) break;
			q.pop();
			for(auto x : adj[i]){
				if(dep[x.F] != -1 || x.S > vl) continue;
				dep[x.F] = dep[i] +1;
				q.push(x.F);
			}
		}
		return dep[n-1] != -1 && dep[n-1] <=d; 
	};
	if(!bfs(1e9)){
		cout<<-1<<endl;
		return;
	}
	//smallest>= x
	int l=-1; //a[l] < x
	int r = 1e9,mid; // a[r] >= x
	while(r > l+1){
		mid = l+r>>1;
		if(bfs(mid)){
			r = mid;
		}else{
			l = mid;
		}
	}
	queue<int> q;
	q.push(0);
	fill(dep,dep+n, -1);
	dep[0] = 0;
	while(!q.empty()){
		int i = q.front();
		if(i == n-1) break;
		q.pop();
		for(auto x : adj[i]){
			if(dep[x.F] != -1 || x.S > r) continue;
			dep[x.F] = dep[i] +1;
			p[x.F] = i;
			q.push(x.F);
		}
	}
	cout<<dep[n-1]<<endl;
	stack<int> st;
	st.push(n-1);
	while(st.top() != 0){
		st.push(p[st.top()]);
	}
	while(! st.empty()){
		cout<<st.top()+1<<" ";
		st.pop();
	}cout<<endl;
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