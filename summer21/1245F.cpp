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
ll l,r,a,b,cnt1,cnt2, cr1, cr2,indic;
ll ans = 0;
bool com[35][35];
vi vecl, vecr;
int log2(int x){
	return 31 - __builtin_clz(x);
}

/*------power function with mod, and inverse modulo prime number------*/
ll pow(ll a, int b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}
void solve(){
	cin>>l>>r;
	vecl.clear();
	vecr.clear();
	r++;
	ans = 0;
	indic = 0;
	if(l == 0) indic++;
	if(l != 0) l--;
	vecl.PB(32);
	for(int i = 34; i>=0; i--){
		for(int j = 34; j>=0; j--){
			com[i][j] = false;
		}
	}
	for(int i =31; i>=0; i--){
		if(l>>i&1) vecl.PB(i);
		if(r>>i&1) vecr.PB(i);
	}
	vecl.PB(-1);
	// trace(vecl);
	if(l != 0){
		a = log2(l);
		b = log2(r);
		if(a == b){
			cout<<0<<endl;
			return;
		}
	}
	for(int i =0; i<sz(vecr); i++){
		for(int j = 0; j<sz(vecl); j++){
			com[i+1][j+1] = com[i][j+1] || com[i+1][j] || vecr[i] == vecl[j];
			// if(com[i+1][j+1]) trace(i+1,j+1);
		}
	}
	// trace(vecl, vecr);
	cnt1 = 0;
	for(int i =0; i<sz(vecr); i++){
		for(int j =1; j<sz(vecl); j++){
			// trace(i,j,vecr[i]-1, vecl[j-1]-1, vecl[j]);
			if(com[i][j]) break;
			// trace(i,j,vecr[i]-1, vecl[j-1]-1, vecl[j]);
			for(a = vecr[i]-1; a>= -1; a--){
				cnt1 = i == 0? a : vecr[0];
				bool fo = 0;
				for(int k =1; k<j; k++){
					if(a == vecl[k]){fo = 1; break;}
				}
				if(fo) continue;
				for(b = vecl[j-1]-1; b>vecl[j]; b--){
					cnt2 = j == 1? b : vecl[1];
					if(cnt1 <= cnt2) continue;
					if(a == b) continue;
					fo = 0;
					for(int k =0; k<i; k++){
						if(b == vecr[k]){fo = 1; break;}
					}
					if(fo) continue;
					// trace(cnt1, cnt2, a,b,ans);
					if(a > cnt2){
						ans += pow(3,b) * pow(2,a-b-1-(j-1));
					}else if(a > b){
						cr2 =0;
						for(cr1 = j-1; cr1>=0 && vecl[cr1]<a; cr1--,cr2++);
						ans += pow(3,b) * pow(2,a-b-1-cr2);
					}else{
						cr2 =0;
						// trace(i-1,b);
						for(cr1 = i-1; cr1>=0 && vecr[cr1]<b; cr1--,cr2++);
						// trace(cr2);
						ans += pow(3,max(a,0ll)) * pow(2,b-a-1-cr2);
					}
					// trace(ans);
				}
			}
		}
	}
	cout<<2*ans + indic*(2*r-1)<<endl;
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
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}