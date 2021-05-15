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
const int N = 1e6+10;
int n;

struct seive{
	int* a;
	int n;
	seive(int m): n(m+1){
		a = new int[n];
		iota(a,a+n,0);
		a[0] = 0;//although not defined for 0
		a[1] = 1;
		for(int i=2;i<n;i++){
			if(a[i]!=i) continue;
			for(int j=2*i;j <n;j+=i){
				if(a[j] != j) continue;
				a[j] = i;
			}
		}
	}
	void get_primes(vector<int> &v, int x){
		v.clear();
		while(x > 1){
			int cr = a[x];
			int cnt = 0;
			while(a[x] == cr){
				x /= cr;
			}
			v.PB(cr);
		}
	}
};

seive fo(N);
int dp1[N],dp2[N];
int get_dp2(int i){
	vi v;
	if(i <2) return 0;
	if(dp2[i] != -1) return dp2[i];
	if(fo.a[i] == i) return 1;
	dp2[i] = 0;
	// fo.get_primes(v,i);
	for(int j = 2; j<=sqrt(i); j++){
		if(i%j != 0) continue;
		if(i/j > 2)dp2[i] = max(dp2[i], get_dp2(i/j -1));
		if(j > 2) dp2[i] = max(dp2[i], get_dp2(j -1));
	}
	dp2[i] += 1;
	return dp2[i];
}
int get_dp1(int i){
	vi v;
	if(i <3) return 0;
	if(dp1[i] != -1) return dp1[i];
	// fo.get_primes(v,i);
	dp1[i] = 0;
	for(int j = 3; j<=sqrt(i); j++){
		if(i%j != 0) continue;
		if(i/j > 2)dp1[i] = max(dp1[i], get_dp2(i/j -1));
		dp1[i] = max(dp1[i], get_dp2(j -1));
	}
	dp1[i] += 1;
	return dp1[i];
}

void solve(){
	cin>>n;
	cout<<get_dp1(n)<<endl;
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
	fill(dp1,dp1+N,-1);
	fill(dp2,dp2+N,-1);
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
	// while(t--){
	// 	solve();
	// }
}