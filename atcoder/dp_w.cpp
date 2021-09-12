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
const int N = 2e5+5;
int n,m,l[N],r[N],a[N];
ll dp[N];
ll cr;
struct event{
	int typ,val,i;
	event(){}
	event(int t, int v, int i): typ(t), val(v), i(i){}

	bool operator<(const event &oth){
		if(val < oth.val) return true;
		if(val > oth.val) return false;
		if(typ < oth.typ) return true;
		return false;
	}
};

event s[2*N];
multiset<int> ls;
void solve(){
	cin>>n>>m;
	for(int i =0; i<m; i++){
		cin>>l[i]>>r[i]>>a[i];
		s[2*i] = event(0,l[i], i);
		s[2*i+1] = event(1,r[i], i);
	}
	sort(s,s+2*m);
	dp[0] = 0;
	int j = 0;
	m <<=1;
	cr = 0;
	for(int i =1; i<=n; i++){
		while(j <m && s[j].val == i-1 && s[j].typ == 1){
			ls.erase(ls.find(l[s[j].i]));
			cr -= a[s[j].i];
			j++;
		}
		while(j < m && s[j].val == i && s[j].typ == 0){
			ls.insert(s[j].val);
			cr += a[s[j].i];
			j++;
		}
		trace(i,cr,ls);
		dp[i] = dp[i-1];
		if(!ls.empty())dp[i] = max(dp[i], cr + dp[(*(ls.begin())) - 1]);
	}
	trace(MP(dp,n));
	cout<<dp[n]<<endl;
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