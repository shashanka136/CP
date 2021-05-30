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

struct polyhash{
	static const int p1 = 31;
	static const int p2 = 53;
	static const int mod = 1e9 + 7;
	vector<int> pp1,pp2,pp1inv, pp2inv;
	/*------power function with mod, and inverse modulo prime number------*/
	static int powm(int a, int b) {
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
	static int inv(int i) { //mod must be prime and i must be coprime with mod
		return powm(i, int(mod) - 2);
	}
	void init(int n){
		pp1.assign(n+1,1);
		pp2.assign(n+1,1);
		for(int i =1; i<=n; i++){
			pp1[i] = 1ll*pp1[i-1] * p1%mod;
			pp2[i] = 1ll*pp2[i-1] * p2%mod;
		}
		pp1inv.assign(n+1,1);
		pp2inv.assign(n+1,1);
		pp1inv[1] = inv(p1);
		pp2inv[1] = inv(p2);
		for(int i =2; i<=n; i++){
			pp1inv[i] = 1ll*pp1inv[i-1] * pp1inv[1]%mod;
			pp2inv[i] = 1ll*pp2inv[i-1] * pp2inv[1]%mod;
		}
	}
};
const int N = 2e5+7;
int n,m,x,y,len,ord[26][N],pref1[26][N],pref2[26][N], cr1, cr2 ;
vector<pii> a(26), b(26);
string s;
polyhash fo;
void no(){
	cout<<"NO"<<endl;
}
void yes(){
	cout<<"YES"<<endl;
}

void solve(){
	cin>>n>>m>>s;
	fo.init(n+1);
	for(int i=0; i<26; i++){
		ord[i][n] = -1;
	}
	for(int j = n-1; j>=0; j--){		
		for(int i =0; i<26; i++){
			ord[i][j] = ord[i][j+1];
		}
		ord[s[j] - 'a'][j]= j;
	}
	for(int i=0; i<26; i++){
		pref1[i][0] = 0;
		pref2[i][0] = 0;
	}
	for(int j = 0; j<n; j++){		
		for(int i =0; i<26; i++){
			pref1[i][j+1] = pref1[i][j];
			pref2[i][j+1] = pref2[i][j];
		}
		(pref1[s[j] - 'a'][j+1] += fo.pp1[j])%=mod;
		(pref2[s[j] - 'a'][j+1] += fo.pp2[j])%=mod;
	}

	for(int i =0; i<m; i++){
		cin>>x>>y>>len;
		x--,y--;
		for(int j = 0; j<26; j++){
			a[j] = MP(max(-1,(ord[j][x] >= x+len? -1: ord[j][x]-x)),j);
			b[j] = MP(max(-1,(ord[j][y] >= y+len? -1: ord[j][y]-y)),j);
		}
		bool indic=0;
		sort(all(a),greater<pii>());
		sort(all(b),greater<pii>());
		// trace(a);
		// trace(b);
		for(int j =0; j<26; j++){
			if(a[j].F != b[j].F){
				indic = 1;
				break;
			}
			if(a[j].F == -1) break;
		}
		if(indic){
			no();
			continue;
		}
		for(int j =0; j<26; j++){
			if(a[j].F == -1) break;
			cr1  = 1ll*fo.pp1inv[x]*(pref1[a[j].S][x+len] - pref1[a[j].S][x])%mod;
			cr2  = 1ll*fo.pp1inv[y]*(pref1[b[j].S][y+len] - pref1[b[j].S][y])%mod;
			if(cr1< 0) cr1 += mod;
			if(cr2< 0) cr2 += mod;
			if(cr1 != cr2){
				indic = 1;
				break;
			}
			cr1  = 1ll*fo.pp2inv[x]*(pref2[a[j].S][x+len] - pref2[a[j].S][x])%mod;
			cr2  = 1ll*fo.pp2inv[y]*(pref2[b[j].S][y+len] - pref2[b[j].S][y])%mod;
			if(cr1< 0) cr1 += mod;
			if(cr2< 0) cr2 += mod;
			if(cr1 != cr2){
				indic = 1;
				break;
			}
		}
		if(indic){
			no();
		}else{
			yes();
		}
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