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
int n,q;
int a[N];
int l,r;
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
	void get_prime_factors(vector<int> &v, int x){
		v.clear();
		while(x > 1){
			v.PB(a[x]);
			while(a[x] == v.back()) x /= a[x];
		}
		return;
	}

	void get_prime_and_counts(vector<pair<int,int>> &v, int x){
		v.clear();
		while(x > 1){
			int cr = a[x];
			int cnt = 0;
			while(a[x] == cr){
				cnt++;
				x /= cr;
			}
			v.PB(MP(cr,cnt));
		}
	}
	void get_prime_counts(vector<int> &v, int x){
		v.clear();
		while(x > 1){
			int cr = a[x];
			int cnt = 0;
			while(a[x] == cr){
				cnt++;
				x /= cr;
			}
			v.PB(cnt);
		}
	}
};
seive fo(N);
int lst[N],nxt[N];
void solve(){
	cin>>n>>q;
	INP(a,n);
	fill(lst,lst+N,n);
	nxt[n] = n;
	vector<int> v;
	for(int i =n-1; i>=0; i--){
		nxt[i] = nxt[i+1];
		fo.get_prime_factors(v,a[i]);
		for(auto &x : v){
			nxt[i] = min(nxt[i], lst[x]);
			lst[x] = i;
		}
	}
	// for(int i=0; i<n; i++) trace(i,nxt[i]);
	int z = log2(n);
	// trace(z);
	vvi dp(n+1,vi(z+1,n));
	for(int i =0; i<=n;i++){
		dp[i][0] = nxt[i];
	}
	for(int j =1; j<= z; j++){
		for(int i =0; i<=n; i++){
			// trace(i,j,dp[i][j-1]);
			dp[i][j] = dp[dp[i][j-1]][j-1];
		}
	}
	for(int i =0; i<q;i++){
		cin>>l>>r;
		l--, r--;
		int cnt = 1;
		for(int j = z; j>=0; j--){
			// trace(i,j,l,r,dp[l][j]);
			if(dp[l][j] <= r){
				// trace(i,j,l,r);
				cnt+= (1<<j); l = dp[l][j];
			}
		}
		cout<<cnt<<endl;
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