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
const int N = 3e5+4;
int comps;
int p[N], siz[N];
stack<int> lens;
stack<int> mods;
void init(int n){
	comps = n;
	fill(siz,siz+n,1);
	iota(p,p+n,0);
}
void persist(){
	lens.push(sz(mods));
}
void rollback(){
	while(sz(mods) > lens.top()){
		p[mods.top()] = mods.top();
		siz[p[mods.top()]] -= siz[mods.top()];
		comps += 1;
		mods.pop();
	}
	lens.pop();
}
int fin(int i){
	while(p[i]!= i){
		i = p[i];
	}
	return p[i];
}
void un(int i, int j){
	i = fin(i), j = fin(j);
	if(i == j) return;
	if(siz[i] > siz[j]) swap(i,j);
	mods.push(i);
	p[i] = j;
	comps -= 1;
	siz[j] += siz[i];
}
// class persistentdsu {
// public:
	
// };
// typedef persistentdsu pdsu;
int n,m,u,v;
map<pii,int> in;
pii edg[N];
struct query{
	int l,r;
	query(){}
	query(int _l, int _r): l(_l), r(_r){}
};
char c;
vector<query> ques;
void solve(){
	cin>>n>>m;
	init(n);
	for(int i =0; i<m; i++){
		cin>>c;
		if(c == '?'){
			ques.EB(query(i,i));
		}else if(c== '+'){
			cin>>u>>v;
			u--,v--;
			if( u > v) swap(u,v);
			edg[i] = MP(u,v);
			in[MP(u,v)] = i;
		}else if(c == '-'){
			cin>>u>>v;
			u--,v--;
			if( u > v) swap(u,v);
			ques.EB(query(in[MP(u,v)], i));
			in.erase(MP(u,v));
		}
	}
	for(auto &x : in){
		ques.EB(query(x.S, m));

	}
	function<void(int,int,vector<query>&)> sol = [&](int l, int r, vector<query> ques){
		if(l == r){
			persist();
			for(query &q : ques){
				if(q.l != q.r && l >= q.l && r <= q.r){
					un(edg[q.l].F, edg[q.l].S);
				}
			}
			for(query &q : ques){
				if(q.l == q.r && q.l == l){
					cout<<comps<<endl;
				}
			}
			rollback();
			return;
		}
		vector<query> qs;
		persist();
		for(query &q : ques){
			if(q.l != q.r && l >= q.l && r <= q.r){
				un(edg[q.l].F, edg[q.l].S);
			}else if(min(r,q.r) >= max(l,q.l)){
				qs.EB(q);
			}
		}
		int mid = l+r>>1;
		sol(l,mid,qs);
		sol(mid+1,r, qs);
		rollback();
	};
	sol(0,m,ques);
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