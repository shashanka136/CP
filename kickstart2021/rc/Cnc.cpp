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
int tmp;
int tot[3],w,e,ind[3];
ld p[3],c[3],y,totc;
vector<char> v{'R', 'S', 'P'};
bool cmp(const int &i, const int &j){
	return (c[i] > c[j]) || (c[i] == c[j] && (p[(i+1)%3] > p[(j+1)%3]));
}
bool cmp1(const int &i, const int &j){
	return (p[(i+1)%3] > p[(j+1)%3]) || ((p[(i+1)%3] == p[(j+1)%3]) && c[i]>c[j]);
}
void solve(){
	cin>>w>>e;
	fill(tot,tot+3,0);
	cout<<v[0];
	tot[0]++;
	for(int i = 1; i<60; i++){
		int x = rand()%i;
		x++;
		int an = 2;
		for(int j = 0; j<3; j++){
			if(x <= tot[(j+1)%3]){
				an = j;
				break;
			}
			x -= tot[(j+1)%3];
		}
		cout<<v[(an+2)%3];
		tot[(an+2)%3]++;
		// if(y == ld(0) || ld(x) < ld(1)/y){
		// 	sort(ind,ind+3,cmp1);
		// }else{
		// 	sort(ind,ind+3,cmp);
		// }
	}
	cout<<endl;
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
	cin>>t>>tmp;
	iota(ind,ind+3,0);
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
	// while(t--){
	// 	solve();
	// }
}