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
struct seive{
	int* a;
	int n;
	seive(int m): n(m+1){
		a = new int[n];
		int z = sqrt(n);
		iota(a,a+n,0);
		a[0] = 0;//although not defined for 0
		a[1] = 1;
		for(int i=2;i<=z;i++){
			if(a[i]!=i) continue;
			for(int j=i*i;j <n;j+=i){
				if(a[j] != j) continue;
				a[j] = i;
			}
		}
	}
	void get_prime_and_counts(vector<int> &v, vector<int> &cnt, int x){
		v.clear();
		cnt.clear();
		while(x > 1){
			int cr = a[x];
			v.PB(cr);
			cnt.PB(0);
			while(a[x] == cr){
				cnt.back()++;
				x /= cr;
			}
		}
	}
};
const int N = 1e6+4;
const int Q = 2e5+5;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int n,q,a[N],l[Q],r[Q];
int pre[N];
ll ans[Q];
vi prms[N],cnts[N],prpw[N],qis[N],qprms[Q],qpcnt[Q];
vvi fq[Q];
vi prefq[N];
bool vis[N];
seive fo(N);
void solve(){
	cin>>n>>q;
	for(int i =0; i<n; i++){
		cin>>a[i];
		fo.get_prime_and_counts(prms[i], cnts[i], a[i]);
	}//prms is prime factors
	//cnt is how much power of corresponding prime factor
	for(int i =2; i<N;i++){
		if(fo.a[i] != i) continue;
		ll cr = 1;
		while(cr < N){
			prpw[i].PB(cr);
			cr *= i;
		}
		prefq[i].assign(sz(prpw[i]), 0);
	}//prpw is prime powers
	fill(vis,vis+N, false);
	function<void(int,int)> fill_qprms = [&](int ind, int i){
		for(int j=0; j<sz(prms[ind]); j++){
			if(vis[prms[ind][j]]) continue;
			vis[prms[ind][j]] = true;
			qprms[i].PB(prms[ind][j]);
		}
	};
	for(int i =0; i<q; i++){
		cin>>l[i]>>r[i];
		l[i]--, r[i]--;
		qis[l[i]].PB(-i-1);
		qis[r[i]+1].PB(i+1);
		//at most 105 primes = 25 (<100) + 40*2(>100 can't be more than 2)
		for(int j=0; j<40; j++){
			int cr = l[i] + rng()%(r[i]-l[i]+1);
			fill_qprms(cr,i);
		}
		qpcnt[i].assign(sz(qprms[i]),0);
		for(int x : qprms[i]){
			vis[x] = false;
		}
	}
	fill(pre,pre+N,0);
	for(int i=0; i<n; i++){
		for(int x : prms[i]){
			pre[x]++;
		}
		for(int x : qis[i+1]){
			int qnum = x>0? x : -x;
			int lr = x/qnum;
			qnum--;
			for(int j=0; j< sz(qprms[qnum]); j++){
				qpcnt[qnum][j] += pre[qprms[qnum][j]] * lr;
			}
		}
	}
	for(int i=0; i<q; i++){
		vi aux(0);
		aux.swap(qprms[i]);
		for(int j=0; j< sz(aux); j++){
			if(qpcnt[i][j] > (r[i]-l[i]+1)/2){
				fq[i].PB(vi(sz(prpw[aux[j]]), 0));
				qprms[i].PB(aux[j]);
				fq[i].back()[0] = r[i]-l[i]+1 - qpcnt[i][j];
			}
		}
	}
	fill(ans,ans+q,1);
	for(int i=0; i<n; i++){
		for(int j =0; j < sz(prms[i]); j++){
			prefq[prms[i][j]][cnts[i][j]]++;
		}
		for(int x : qis[i+1]){
			int qnum = x>0? x : -x;
			int lr = x/qnum;
			qnum--;
			for(int j=0; j< sz(qprms[qnum]); j++){
				for(int pw =1; pw <sz(fq[qnum][j]); pw++){
					fq[qnum][j][pw] += prefq[qprms[qnum][j]][pw] * lr;
				}
			}
			if(lr == 1){
				for(int j =0; j < sz(qprms[qnum]); j++){
					int cumulative_fq = 0;
					int stopfq = (r[qnum] - l[qnum]+2)/2;
					for(int pw = 0; pw < sz(fq[qnum][j]); pw++){
						cumulative_fq += fq[qnum][j][pw];
						if(cumulative_fq >= stopfq){
							ans[qnum] *= prpw[qprms[qnum][j]][pw];
							break;
						}
					}
				}
			}
		}
	}
	for(int i=0; i<q; i++){
		cout<<ans[i]<<endl;
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