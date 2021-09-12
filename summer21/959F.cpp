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
const ll mod = 1e9+7;

//
struct basis {
	vector<int> v;
	int d;
	int sz;
	basis() {}
	basis(int _d) {
		d = _d;
		v.assign(d, 0);
		sz = 0;
	}

	basis operator=(const basis & oth) {
		vector<int> z(oth.v);
		v.swap(z); d = oth.d;
		sz = oth.sz;
		return *this;
	}

	void init(int _d) {
		d = _d;
		v.assign(d, 0);
		sz = 0;
	}

	void insvec(int mask) {
		for (int i = d - 1; i >= 0; i--) {
			if ((mask & 1 << i) == 0) continue; //mask is not set at i

			if (!v[i]) { //there is not any vector already at i
				v[i] = mask;
				++ sz;
				return;
			}
			mask ^= v[i];
		}
	}

	bool present(int x) { //true if x in present in vector space
		for (int i = d - 1; i >= 0; i--) {//represented by current basis
			if ((x & 1 << i) == 0) continue;

			if (!v[i]) { //there is not any vector already at i
				return false;
			}
			x ^= v[i];
		}
		return true;
	}

	int query(int k) { //return kth highest
		int mask = 0;
		int tot = 1 << sz;
		for (int i = d - 1; i >= 0; i--)
			if (v[i]) {
				int hal = tot>>1;
				if ((k <= hal && (mask & 1 << i) == 0) ||
				        (k > hal && (mask & 1 << i) > 0)) mask ^= v[i];

				if (k > hal) k -= hal;
				tot >>= 1;
			}

		return mask;
	}
};
/*------power function with mod, and inverse modulo prime number------*/
int powm(int a, int b, ll mod = mod) {
	int ans = 1;
	b %= (mod - 1);
	if (b < 0) b += mod - 1;
	while (b) {
		if (b & 1) ans = int(1ll * ans * a % mod);
		a = int(1ll * a * a % mod);
		b >>= 1;
	}
	return ans;
}
int inv(int i, ll mod = mod) { //mod must be prime and i must be coprime with mod
	return powm(i, int(mod) - 2, mod);
}

const int N = 1e5+5;
int ans[N],a[N],n,q,l,x;
vpi que[N];
basis fo;
void solve(){
	cin>>n>>q;
	INP(a,n);
	for(int i =0; i<q;i++){
		cin>>l>>x;
		l--;
		que[l].PB(MP(x,i));
	}
	fo.init(20);
	for(int i =0; i<n; i++){
		fo.insvec(a[i]);
		for(auto x : que[i]){
			if(!fo.present(x.F)) ans[x.S] = 0;
			else ans[x.S] = powm(2,i+1 - fo.sz);
		}
	}
	for(int i =0; i<q; i++){
		cout<<ans[i]<<endl;
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