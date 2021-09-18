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
const int N = 3e5+5;

vi st[N],en[N];

int n,d,k,s,e,h;

void solve(){
	cin>>d>>n>>k;
	for(int i=0; i<n; i++){
		cin>>h>>s>>e;
		st[s].PB(h);
		en[e].PB(h);
	}
	// trace(MP(st,d+1));
	// trace(MP(en,d+1));
	multiset<int> tp, ntp;
	function<int(void)> mn = [&](){
		if(tp.empty()) return -1;
		return *(tp.begin());
	};
	function<int(void)> mx = [&](){
		if(ntp.empty()) return -1;
		auto it = ntp.end();
		it--;
		return *(it);
	};
	ll ans  = 0,cr =0;
	for(int i =1; i<=d; i++){
		// trace(i,ans,cr);
		for(int x : st[i]){
			if(sz(tp) < k){
				tp.insert(x);
				cr += x;
			}else{
				int tmp = mn();
				if(x > tmp){
					tp.erase(tp.find(tmp));
					tp.insert(x);
					ntp.insert(tmp);
					cr += x-tmp;
				}else{
					ntp.insert(x);
				}
			}
		}
		// trace(i,ans,cr);
		// trace(tp,ntp);
		ans = max(ans,cr);
		for(int x : en[i]){
			if(ntp.find(x) != ntp.end()){
				ntp.erase(ntp.find(x));
			}else{
				int tmp = mx();
				// trace(i,x,tmp);
				if(tmp != -1) ntp.erase(ntp.find(tmp));
				// trace(i,x,tmp);
				// trace(tp);
				tp.erase(tp.find(x));
				// trace(i,x,tmp);
				if(tmp != -1)tp.insert(tmp);
				// trace(i,x,tmp);
				cr -= x;
				if(tmp != -1){
					cr += tmp;
				}
			}
		}
		// trace(i,ans,cr);
	}
	cout<<ans<<endl;
	fill(st,st+d+1, vi(0));
	fill(en,en+d+1, vi(0));
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
}