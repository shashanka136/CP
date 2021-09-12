/* AUTHOR - SHASHANK AGRAWAL (codeforces - @shashanka136) ( codechef - @shashank_vasu) */
#include <bits/stdc++.h>
#include <sys/resource.h>
#pragma GCC optimize("-O3")
// #pragma GCC target("avx,avx2,fma")
using namespace std;
#ifdef TRACE
#include "/users/shashankagrawal/Desktop/CP/trace.h"
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

string s;
int n,k;
char a,b;
void solve(){
	cin>>s>>k;
	n = sz(s);
	vvi v(26,vector<int>(26,-1));
	for(int i =0; i<k; i++){
		cin>>a>>b;
		v[a-'A'][b-'A'] = 1;
	}
	for(int i = 0; i<26; i++){
		v[i][i] = 0;
	}
	for(int k =0; k<26;k++){
		for(int i =0; i<26;i++){
			for(int j =0; j<26;j++){
				if(i == k || j == k) continue;
				if(i == j) continue;
				if(v[i][k] == -1 || v[k][j] == -1) continue;
				if(v[i][j] == -1) v[i][j] = v[i][k] + v[k][j];
				v[i][j] = min(v[i][j], v[i][k] + v[k][j]);
			}
		}
	}
	int mn = 1e9;
	for(int i = 0; i< 26; i++){
		int cost =0;
		int fo = 0;
		for(int j = 0; j<n; j++){
			if(v[s[j] - 'A'][i] == -1){
				fo = 1;break;
			}
			cost += v[s[j] - 'A'][i];
		}
		if(fo == 0)mn = min(mn, cost);
	}
	if(mn == int(1e9)) mn = -1;
	cout<<mn<<endl;
}

int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	rlimit rlim;
	if(getrlimit(RLIMIT_STACK, &rlim)) return 1;//getrlimit returns -1 when error
	rlim.rlim_cur = rlim.rlim_max;

	if(setrlimit(RLIMIT_STACK, &rlim)) return 2;//setrlimit too returns -1 when error

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	cin>>t;
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
}