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
const int N = 2e5+4;
int p1[N],p2[N],n,q,typ,x,y;
int fin1(int i){
	if(p1[i] != i){
		p1[i] = fin1(p1[i]);
	}
	return p1[i];
}
void un1(int i, int j){
	i = fin1(i), j = fin1(j);
	if(i == j) return;
	if(i > j) swap(i,j);
	p1[i] = j;
}
int fin2(int i){
	if(p2[i] != i){
		p2[i] = fin2(p2[i]);
	}
	return p2[i];
}
void un2(int i, int j){
	i = fin2(i), j = fin2(j);
	if(i == j) return;
	if(i > j) swap(i,j);
	p2[i] = j;
}
void no(){
	cout<<"NO"<<endl;
	// exit(0);
}
void yes(){
	cout<<"YES"<<endl;
	// exit(0);
}
void solve(){
	cin>>n>>q;
	iota(p1, p1+n,0);
	iota(p2, p2+n,0);
	for(int i = 0; i< q; i++){
		cin>>typ>>x>>y;
		x--,y--;
		if(typ == 2){
			while(fin1(x) < y){
				un2(fin1(x), fin1(fin1(x)+1));
				un1(fin1(x), fin1(x)+1);
				x = fin1(x);
			}
		}else if(typ == 1){
			un2(fin1(x), fin1(y));
		}else{
			if(fin2(fin1(x)) == fin2(fin1(y))) yes();
			else no();
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