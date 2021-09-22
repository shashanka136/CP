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
struct line{//If we want to change some struct variable within
	mutable ll k,b,p;//const function then use mutable
	bool operator<(const line& nx) const { return k < nx.k;}
	bool operator<(ll x) const{ return p < x;}
};

struct linecont : multiset<line, less<>> {//inheriting multiset, so that typing can be made easy
	const ll inf = LLONG_MAX;//less<> used for purpose of lower bound
	typedef iterator it;
	ll floor(ll a, ll b){//floor of(a/b)
		return a/b - ((a^b)<0 && a%b);
	}
	bool isect(it m, it n){//check if m is above n where n is part of convex hull
		//also calculate the intersection of m & n, i.e., *m.p
		//m->k <= n->k, return true if m is above n
		// trace(m->k,m->b, m->p);
		// trace(n->k,n->b, n->p);
		if(n == end()){
			m->p = inf; return false;
		}
		if(m->k == n->k) m->p = m->b > n->b ? inf: -inf;
		else m->p = floor(m->b - n->b,n->k - m->k);//m-coordinate of intersection of m & n
		return m->p >= n->p;
	}
	// it erase(it z){//can be used for debugging purpose
	// 	trace(z->k,z->b, z->p);
	// 	return this->std::multiset<line, less<>>::erase(z);
	// }
	void add_line(ll k, ll b){
		it z = insert({k,b,0});
		it y = z++;
		while(isect(y,z)) z = erase(z);//check if any line of greater slope will be lowered
		//and update corresponding value of p
		it x = y;//lines of lower slope can be above current line
		if(x != begin() && isect(--x,y)) isect(x,y = erase(y));//if one more can be deleted
		while((y = x) != begin() && (--x)->p >= y->p){
			isect(x,erase(y));
		}
	}

	ll query(ll x){
		assert(!empty());
		line l = *lower_bound(x);
		return l.k*x+l.b;
	}
};

const int N = 2e5+5;
ll c,n,h[N],dp[N];
linecont fo;
void solve(){
	cin>>n>>c;
	INP(h,n);
	dp[0] = 0;
	fo.add_line(h[0]*2,-dp[0]-h[0]*h[0]);
	for(int i=1;i<n; i++){
		dp[i] = h[i]*h[i] + c -fo.query(h[i]);
		fo.add_line(h[i]*2, -dp[i] - h[i]*h[i]);
	}
	cout<<dp[n-1]<<endl;
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