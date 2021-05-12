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
// #define endl '\n'
#define all(v) v.begin(), v.end()
const ll mod = 998244353;

//
const int N = 1e5+4;
const int M = 1e3+15;

template <typename bit>
struct stk {
	stack<int> st;
	stack<bit> stsum;
	stk(){
		bit temp = 0;
		temp.set(0);
		stsum.push(temp);
	}
	void push(int x){
		st.push(x);
		bit temp = stsum.top();
		for(int i = M-x-1; i>=0; i--){
			if(temp.test(i)) temp.set(i+x);
		}
		stsum.push(temp);
	}
	int pop(){
		int x = st.top();
		st.pop();
		stsum.pop();
		return x;
	}
	inline bool empty(){
		return st.empty();
	}
	
};
stk<bitset<M>> s1, s2;
int n,s;
int a[N];
int cr,sum;
int ans = N;
void solve(){
	cin>>n>>s;
	INP(a,n);
	int l=0,r=0;
	cr =0;sum = 0;
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
		bitset<M> temp1= s1.stsum.top(); 
		bitset<M> temp2= s2.stsum.top(); 
		for(int i=0; i<=s;i++){
			if(temp1.test(i) && temp2.test(s-i)) return true;
		}
		return false;
	};
	while(r<n){
		s2.push(a[r]);
		while(l <=r && rem() && good()){
			l++;
		}
		if(l <= r) s1.push(a[l]);
		if(good()){
			// trace(l,r);
			ans =min(ans, r-l+1);
		}
		r++;
	}
	if(ans == N) ans = -1;
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