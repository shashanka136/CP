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
int n[4],a[4][N],ind[4],ord[4],ans[4];
int mn = 1e6;

bool cmp(const int &i, const int &j){
	return (a[i][ind[i]] < a[j][ind[j]]) || (a[i][ind[i]] == a[j][ind[j]] && i < j);
}

void solve(){
	for(int j =0; j<4; j++){
		cin>>n[j];
		INP(a[j],n[j]);
		sort(a[j],a[j]+n[j]);
	}
	fill(ind,ind+4,0);
	function<bool(void)> inrange = [&](){
		for(int i =0; i<4; i++){
			if(ind[i] >= n[i]) return false;
		}
		return true;
	};
	iota(ord,ord+4,0);
	while(inrange()){
		sort(ord,ord+4, cmp);
		if(a[ord[3]][ind[ord[3]]] - a[ord[0]][ind[ord[0]]] < mn){
			mn = a[ord[3]][ind[ord[3]]] - a[ord[0]][ind[ord[0]]];
			for(int i=0; i<4; i++) ans[i] = a[i][ind[i]];
		}
		ind[ord[0]]++;	
	}
	for(int i =0; i<4; i++){
		cout<<ans[i]<<" ";
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