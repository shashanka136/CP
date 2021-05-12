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
ll n,a[N];

struct stk {
	stack<ll> st, stgcd;
	stk(){
		stgcd.push(0);
	}
	void push(ll x){
		st.push(x);
		stgcd.push(__gcd(stgcd.top(), x));
	}
	ll pop(){
		ll x = st.top();
		st.pop();
		stgcd.pop();
		return x;
	}
	inline bool empty(){
		return st.empty();
	}
	inline ll gcd(){
		return stgcd.top();
	}
};
stk s1,s2;
int ans = 1e6;
void solve(){
	cin>>n;
	INP(a,n);
	int l=0,r=0;
	function<bool(void)> rem = [&](){
		if(s1.empty()){
			while(!s2.empty()){
				s1.push(s2.pop());
			}
		}
		s1.pop();
		return true;
	};
	function<bool(void)> good = [&](){
		if(s1.gcd() == 0) return s2.gcd() == 1;
		if(__gcd(s1.gcd(), s2.gcd()) == 1) return true;
		return false;
	};
	while(r<n){
		s2.push(a[r]);
		while(l <= r && rem() && good()){
			l++;
		}
		if(l <= r) s1.push(a[l]);
		if(good()) ans =min(ans, r-l+1);
		r++;
	}
	if(ans == ll(1e6)) ans = -1;
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