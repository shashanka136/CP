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
typedef pair<ld, ld> pld;
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
ld sq(ld a){
	return a*a;
}
ld dis( pld &a, pld &b){
	return sqrt( sq(a.F-b.F) + sq(a.S - b.S)); 
}
int sgn(pld &a, pld &b, pld &c){
	ld x = (b.F - a.F)*c.S - (b.S - a.S)*c.F - a.S*b.F + a.F*b.S;
	if(x > 0) return 1;
	else if(x == 0) return 0;
	else return -1;
}
bool within(pld &a, pld &b, pld &c, pld &d){
	if(sgn(a,b,c) != sgn(a,b,d)) return false;
	if(sgn(c,b,a) != sgn(c,b,d)) return false;
	if(sgn(a,c,b) != sgn(a,c,d)) return false;
	return true;
}

const int N = 305;

void no(){
	cout<<"IMPOSSIBLE"<<endl;
	return;
}
int n;
pld wh[N],bl;
ld inf;
ld ds[N][N];
void solve(){
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>wh[i].F>>wh[i].S;
	}
	cin>>bl.F>>bl.S;
	for(int i =0; i<n; i++){
		for(int j =0; j < n; j++){
			ds[i][j] = dis(wh[i], wh[j]);
		}
	}
	int crsgn;
	ld ans = inf;
	for(int i =0; i<n; i++){
		for(int j = i+1; j<n; j++){
			crsgn = sgn(wh[i],wh[j], bl);
			trace(i,j,crsgn);
			if(crsgn == 0){
				if(ds[i][j] != dis(wh[i],bl) + dis(wh[j],bl)) continue;
				vector<ld> mn(3,inf);
				for(int k=0; k<n;k++){
					if(k == i || k==j) continue;
					crsgn = sgn(wh[i],wh[j], wh[k]);
					mn[crsgn+1] = min(mn[crsgn+1], ds[i][k] + ds[k][j]);
				}
				if(mn[0] != inf && mn[2] != inf)ans = min(ans, mn[0] + mn[2]);
				continue;
			}else{
				for(int k=0; k<n;k++){
					if(k == i || k==j) continue;
					if(!within(wh[i], wh[j], wh[k], bl)) continue;
					ans = min(ans, ds[i][j]+ds[i][k] + ds[k][j]);
				}
			}
		}
	}
	if(ans == inf) return no();
	cout<<fixed<<setprecision(10)<<ans<<endl;
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
	inf = 1;
	for(int i =0; i<18;i++){
		inf *= 10;
	}
	cin>>t;
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
}