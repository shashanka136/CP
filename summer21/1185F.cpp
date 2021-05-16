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
const int N = 1e5+7;
const int M = 9;
const int Z = 1<<9;
int n,m,f,b,cr;
int c[N];
int p2[10];
int cntp[Z+10];
int final[Z+10];
vi piz[Z+10];
int finfin[Z*Z];
int mn = INT_MAX, mx= -1,finmem;
pii pizzas = MP(-1,-1);

bool cmp(const int &i, const int &j){
	return (c[i] < c[j]) || (c[i] == c[j] && i < j);
}
void solve(){
	cin>>n>>m;
	for(int i =0; i<10; i++){
		p2[i] = 1<<i;
	}
	fill(cntp,cntp+(Z+10),0);
	fill(final,final+(Z+10),0);
	for(int i =0; i<n; i++){
		cin>>f;
		cr =0;
		for(int j =0; j<f; j++){
			cin>>b;
			cr |= p2[b-1];
		}
		cntp[cr]++;
		// trace(cr,"per");
	}
	for(int i =0; i<m; i++){
		cin>>c[i]>>f;
		cr =0;
		for(int j =0; j<f; j++){
			cin>>b;
			cr |= p2[b-1];
		}
		piz[cr].PB(i);
		sort(all(piz[cr]), cmp);
		if(sz(piz[cr]) > 2){
			piz[cr].POB();
		}
		// trace(cr, piz[cr]);
	}
	for(int i =1; i<Z; i++){
		vi v;
		for(int j=0; j<9; j++){
			if(i>>j&1) v.PB(j);
		}
		for(int j = 1; j<p2[sz(v)]; j++){
			cr =0;
			for(int k =0; k<sz(v); k++){
				if(j>>k&1){
					cr |= p2[v[k]];
				}
			}
			final[i] += cntp[cr];
		}
		// if(final[i] > 0)trace(i,final[i]);
	}
	for(int i = 0; i<Z; i++){
		if(sz(piz[i]) == 2){
			if(final[i] > mx){
				// trace(i,final[i]);
				mx = final[i];
				mn = c[piz[i][0]] + c[piz[i][1]];
				pizzas = MP(piz[i][0], piz[i][1]);
			}else if(final[i] == mx){
				cr = c[piz[i][0]] + c[piz[i][1]];
				if(cr < mn){
					mn = cr;
					pizzas = MP(piz[i][0], piz[i][1]);
				}
			}
		}
		for(int j =i+1; j<Z; j++){
			if(sz(piz[i]) < 1 || sz(piz[j]) < 1) continue;
			cr = c[piz[i][0]] + c[piz[j][0]];
			finmem = final[i|j];
			// trace(i,j,finmem);
			if(finmem > mx){
				mx = finmem;
				mn = cr;
				pizzas = MP(piz[i][0], piz[j][0]);
			}else if(finmem == mx && cr < mn){
				mn = cr;
				pizzas = MP(piz[i][0], piz[j][0]);
			}
		}
	}
	cout<<pizzas.F+1<<" "<<pizzas.S+1<<endl;
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