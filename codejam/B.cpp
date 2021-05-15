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
int x,y;
string s;
int n;
char c;
int ans ;
void solve(string &s, int &ans){
	if(s[0] == '?'){
		s[0] = 'J';
		solve(s,ans);
		s[0] = 'C';
		solve(s,ans);
		s[0] = '?';
		return;
	}
	if(s[n-1] =='?'){
		s[n-1] = 'J';
		solve(s,ans);
		s[n-1] = 'C';
		solve(s,ans);
		s[n-1] = '?';
		return;
	}
	int cr = 0;
	int j= 0;
	for(int i =1; i<n ;i++){
		if(s[i] == '?') continue;
		if(s[i] == s[j]){
			if((x+y) < 0){
				// trace(s,i,j,cr);
				cr += (x+y)*((i-j)/2);
				// trace(cr);
			}
		}else if(s[i] == 'J'){
			if(x+y < 0){
				cr += (x+y)*((i-j-1)/2);
			}
			cr += x;
		}else{
			if(x+y < 0){
				cr += (x+y)*((i-j-1)/2);
			}
			cr += y;
		}
		j = i;
	}
	// trace(s,cr);
	ans = min(ans, cr);
}
void solve(){
	cin>>x>>y>>s;
	n = sz(s);
	ans = 1e9;
	solve(s,ans);
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
	cin>>t;
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
	// while(t--){
	// 	solve();
	// }
}