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
const int N = 8e5+5;
int n,tot,trans, p, g,lst,xfir,x,posf,firs,bsum;
string s;
void solve(){
	cin>>n>>s;
	n = s.size();
	vector<char> ch(2);
	xfir = -1;
	ch[0] = 'O';
	ch[1] = 'X';
	lst = 0;
	p = 0, g= 0;
	tot = 0;
	trans = 0;
	posf = 0;
	firs = 0;
	bsum = 0;
	x = -1;
	bool b;
	for(int i =0; i<n;i++){
		// trace(i,x,xfir,lst,tot,trans,p,g);
		// trace(firs, posf);
		if(s[i] == '.'){
			b = x != xfir;
			g = (2ll*g%mod + 1ll*tot*tot%mod*trans%mod)%mod;
			g = (g + 1ll*tot*bsum%mod)%mod;
			if(b){
				g = (g + 1ll*posf*(tot-lst + mod)%mod)%mod;
			}else{
				g = (g + 1ll*tot*(posf-lst + mod)%mod)%mod;
			}
			p = (2ll*p%mod + 1ll*trans*tot%mod)%mod;
			if(b) (p += lst)%=mod;
			bsum = 2ll*bsum%mod;
			if(!b) bsum = (1ll*bsum + 1ll*posf + 1ll*tot -1ll*lst + mod)%mod;
			(lst += tot) %= mod;
			tot = (2ll*tot)%mod;
			trans = (2ll*trans)%mod;
			if(b) (trans += 1) %= mod;
		}else{
			tot++;
			if(tot == mod) tot = 0;
			if(x == -1){
				for(int j =0; j<2; j++) if(s[i] == ch[j]) x = j;
				if(x == -1) continue;
				xfir = x;
				posf = (tot-1+mod)%mod;
				lst = tot;
				bsum = 1;
			}else if(s[i] == ch[x]){
				(bsum += (tot-lst+mod)%mod) %= mod;
				lst = tot;
			}else if(s[i] == ch[x^1]){
				if(firs == 0) firs = lst;
				(p += lst) %= mod;
				x ^= 1;
				trans++;trans %= mod;
				lst = tot;
				bsum += 1;
				if(bsum == mod) bsum = 0;
			}
			(g += p) %= mod;
		}
		// trace(i,x,xfir,lst,tot,trans,p,g);
	}
	cout<<g<<endl;
	return;
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