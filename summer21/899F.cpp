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
const int N = 2e5+5;
int n,m,bit[N],l,r,ind,sum[N];
char c;
set<int> pos[63];
string s;

int get_ind(char c){
	if(c-'a' >=0 && c-'a' <26){
		return c-'a';
	}
	if(c-'A' >=0 && c-'A' <26){
		return 26+(c-'A');
	}
	if(c-'0' >=0 && c-'0' <10){
		return 52+c-'0';
	}
	return 0;
}
/*-----------BIT----------*/
void ins(int i, int x){
	while(i<=n){
		bit[i] += x;
		i += (i&-i);
	}
}

int lift(int k){
	int pos = 0,sum = 0;
	for(int i = 20; i>=0;i--){
		int z = pos + (1<<i);
		if(z <= n && sum + bit[z] <k){
			pos = z;
			sum += bit[z];
		}
	}
	return pos+1;
}
void solve(){
	cin>>n>>m>>s;
	bit[0] = 0;//no need tho
	for(int i =0; i<n;i++){
		pos[get_ind(s[i])].insert(i+1);
		bit[i+1] =(i+1)&(-i-1); 
	}
	for(int i =0; i<m;i++){
		cin>>l>>r>>c;
		l = lift(l);
		r = lift(r);
		ind = get_ind(c);
		assert(r >=l);
		auto it1 = pos[ind].lower_bound(l);
		auto it2 = pos[ind].upper_bound(r);
		while(it1 != it2){
			ins(*it1,-1);
			it1 = pos[ind].erase(it1);
		}
	}
	sum[0] = 0;
	for(int i = 1; i<=n; i++){
		sum[i] = bit[i] + sum[i&i-1];
		if(sum[i]-sum[i-1]) cout<<s[i-1];
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
	//cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}