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
int n;
pii xy[60];
int mxx = -1,mxy = -1,mnx = 51,mny = 51;
map<int,int> mpx,mpy;
void solve(){
	cin>>n;
	for(int i =0; i<=4*n; i++){
		cin>>xy[i].F>>xy[i].S;
		mpx[xy[i].F]++;
		mpy[xy[i].S]++;
	}
	trace(mpx);
	auto it = mpx.begin();
	while(it->S == 1) it++;
	mnx = it->F;
	it = mpx.end();it--;
	while(it->S == 1) it--;
	mxx = it->F;
	it = mpy.begin();
	while(it->S == 1) it++;
	mny = it->F;
	it = mpy.end();it--;
	while(it->S == 1) it--;
	mxy = it->F;
	trace(mxx, mxy, mnx, mny);
	for(int i =0; i<=4*n; i++){
		if(xy[i].F == mnx && xy[i].S <= mxy && xy[i].S >= mny) continue;
		if(xy[i].F == mxx && xy[i].S <= mxy && xy[i].S >= mny) continue;
		if(xy[i].S == mny && xy[i].F <= mxx && xy[i].F >= mnx) continue;
		if(xy[i].S == mxy && xy[i].F <= mxx && xy[i].F >= mnx) continue;
		cout<<xy[i].F<<" "<<xy[i].S<<endl;
		return;
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