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
int n,b;
int h[24],ordh[24];
ll p;
bool cmp(const int &i, const int &j){
	return (h[i] < h[j]) || (h[i] == h[j] && i < j);
}
int d,ans;
void solve(){
	fill(h,h+n,0);
	iota(ordh,ordh+n,0);
	for(int i =0; i<n*b; i++){
		cin>>d;
		if(d < 9){
			int j = 0;
			int x = d;
			while(j <n-1 && x > 0){
				if(h[ordh[j+1]] > h[ordh[j]]){
					x--;
				}
				j++;
			}
			while(j > 0 && h[ordh[j]] == b) j--;
			cout<<ordh[j]+1<<endl;
			h[ordh[j]]++;
			sort(ordh,ordh+n,cmp);
		}else{
			int j = n-1;
			while(j > 0 && h[ordh[j]] == b) j--;
			
			cout<<ordh[j]+1<<endl;
			h[ordh[j]]++;
			sort(ordh,ordh+n,cmp);
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
	cin>>t>>n>>b>>p;
	// for(int i=1; i<=t; i++){
	// 	cout<<"Case #"<<i<<": ";
	// 	solve();
	// }
	while(t--){
		solve();
	}
	cin>>ans;
}