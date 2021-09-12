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
int n;
string s;
void solve(){
	cin>>n>>s;
	n = s.size();
	vector<int> pos(2,-1);
	vector<char> ch(2);
	ch[0] = 'O';
	ch[1] = 'X';
	for(int i =0; i<n;i++){
		for(int j =0; j<2; j++){
			if(pos[j] == -1 && s[i] == ch[j]) pos[j] = i;
		}
	}
	if(pos[0] == -1 || pos[1] == -1){
		cout<<0<<endl;
		return;
	}
	int x = pos[0] < pos[1]? 0 : 1;
	int cnt = 0, cr = 0, lst = -1;
	for(int i =0; i<n;i++){
		if(s[i] == ch[x^1]){
			(cr += lst+1)%=mod;
			x ^= 1;
			lst = i;
		}else if(s[i] == ch[x]){
			lst = i;
		}
		(cnt += cr)%=mod;
	}
	cout<<cnt<<endl;
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