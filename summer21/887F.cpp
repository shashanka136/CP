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
template<typename T>
struct stk {
	stack<T> st, stmin2, stmin;
	stk(){
		stmin.push(MP(INT_MAX,-1));
		stmin2.push(MP(INT_MAX,-1));
	}
	void push(T x){
		st.push(x);
		if(x.F < stmin.top().F){
			stmin2.push(stmin.top());
			stmin.push(x);
		}else if(x.F < stmin2.top().F){
			stmin.push(stmin.top());
			stmin2.push(x);
		}else{
			stmin.push(stmin.top());
			stmin2.push(stmin2.top());
		}
	}
	T pop(){
		T x = st.top();
		st.pop();
		stmin2.pop();
		stmin.pop();
		return x;
	}
	inline bool empty(){
		return st.empty();
	}
	inline T mn2(){
		return stmin2.top();
	}
	inline T mn(){
		return stmin.top();
	}
};

template<typename T, class stk>
struct quest{
	stk<T> st1, st2;// <-- st1|st2 <--
	quest(){}

	inline void trans(){
		if(st1.empty()){
			while(!st2.empty()){
				st1.push(st2.top());
				st2.pop();
			}
		}
	}
	void push(T x){
		st2.push(x);
	}

	T pop(){
		trans();
		st1.pop();
	}

	T front(){
		trans();
		return st1.top(); 
	}
	inline bool empty(){
		return st1.empty() && st2.empty();
	}
	inline T mn2(){
		trans();
		stk<T> tmp;
		tmp.push(st1.mn());
		tmp.push(st1.mn2());
		tmp.push(st2.mn());
		tmp.push(st2.mn2());
		return tmp.mn2();
	}
	inline T mn(){
		trans();
		stk<T> tmp;
		tmp.push(st1.mn());
		tmp.push(st2.mn());
		return tmp.mn();
	}
};
void no(){
	cout<<"NO"<<endl;
	exit(0);
}
void yes(){
	cout<<"YES"<<endl;
	exit(0);
}
quest<pii,stk> fo;
const int N = 5e5+6;
int n,k,a[N],sm[N],fst = -1, mnp;
vi adj[N];
pii p1,p2;
void solve(){
	cin>>n>>k;
	INP(a,n);
	a[n] =0;
	fill(sm,sm+n+1,0);
	if(k == n){
		return yes();
	}
	for(int i =0; i<k; i++){
		fo.push(MP(a[i],i));
	}

	for(int i=0; i+k<n;i++){
		fo.pop();
		fo.push(MP(a[i+k],i+k));
		p1 = fo.mn();
		p2 = fo.mn2();
		sm[i+1] = sm[i];
		if(p2.F < a[i]) continue;
		if(p1.F < a[i]){
			adj[p1.S].PB(i);
			continue;
		}
		sm[i+1]++;
		if(fst == -1){
			fst = i;
			mnp = p1.S;
		}
	}
	for(int i =n-k;i<n; i++){
		sm[i+1] = sm[i];
	}
	if(fst == -1){
		return yes();
	}
	if(fst == n-k-1) return no();
	while(!fo.empty()) fo.pop();
	for(int i = mnp+1; i<=min(mnp+1+k, n); i++){
		fo.push(MP(a[i],i));
	}
	p1 = fo.mn();
	for(int i = fst+k+1; i<n;i++){
		if(a[i] >= a[fst]) continue;
		if(sm[n] -sm[mnp+1]) continue;
		bool foo = false;
		for(int &x : adj[i]){
			if(a[x] > a[mnp]) continue;
			foo = true;break;
		}
		if(foo) continue;
		if(p1.F >= a[i]) continue;
		return yes();
	}
	return no();
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