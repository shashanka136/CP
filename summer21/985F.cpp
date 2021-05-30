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
int n,m,x,y,len,z;
string s;
vi v1, v2;
void no(){
	cout<<"NO"<<endl;
}
void yes(){
	cout<<"YES"<<endl;
}

bool res(int & a, int b){
	if(b == -1) return false;
	if(a == -1){
		a = b; return false;
	}
	if(a != b) return true;
	return false;
}

bool isom(int x, int y, int len, vi &v1, vi &v2){
	if(len == 1){
		v1.assign(26,-1);
		v2.assign(26,-1);
		v1[s[x]-'a'] = s[y]-'a';
		v2[s[y]-'a'] = s[x]-'a';
		return true;
	}
	z = len>>1;
	if(!isom(x,y,z, v1, v2)){
		return false;
	}	
	vi v3,v4;
	if(!isom(x+z,y+z,len-z,v3,v4)){
		return false;
	}
	for(int i =0; i<26; i++){
		if(res(v1[i], v3[i])) return false;
		if(res(v2[i], v4[i])) return false;
	}
	return true;
}

void solve(){
	cin>>n>>m>>s;
	for(int i =0; i<m; i++){
		cin>>x>>y>>len;
		x--,y--;
		if(isom(x,y,len,v1, v2)){
			yes();
		}else{
			no();
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