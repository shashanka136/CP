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
vector<int> a[4];
int x,n,ans =0, cr1,cr2,tot;
string s;
void solve(){
	cin>>n;
	for(int i = 0; i<n; i++){
		cin>>s;
		if(s == "00"){
			cin>>x;
			a[0].PB(x);
		}else if(s == "01"){
			cin>>x;
			a[1].PB(x);
		}else if(s == "10"){
			cin>>x;
			a[2].PB(x);
		}else if(s == "11"){
			cin>>x;
			a[3].PB(x);
		}
	}
	sort(all(a[1]), greater<int>());
	sort(all(a[2]), greater<int>());
	sort(all(a[0]), greater<int>());
	tot = cr1=cr2=sz(a[3]);
	for(auto &x : a[3]){
		ans += x;
	}
	int z = min(sz(a[1]),sz(a[2]));
	for(int i=0; i<z; i++){
		ans+= a[1][i] + a[2][i];
	}
	if(sz(a[1]) > sz(a[2])){
		a[0].insert(a[0].end(), a[1].begin()+z, a[1].end());
	}else{
		a[0].insert(a[0].end(), a[2].begin()+z, a[2].end());
	}
	sort(all(a[0]), greater<int>());
	for(int i =0; i<min(sz(a[3]), sz(a[0])); i++){
		ans += a[0][i];
	}
	cout<<ans<<endl;
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