#include<bits/stdc++.h>
using namespace std ;

#define ll              long long 
#define pb              push_back
#define all(v)          v.begin(),v.end()
#define sz(a)           (ll)a.size()
#define F               first
#define S               second
#define INF             2000000000000000000
#define popcount(x)     __builtin_popcountll(x)
#define pll             pair<ll,ll>
#define pii             pair<int,int>
#define ld              long double
#ifdef TRACE
#include "/Users/shashankagrawal/Desktop/CP/trace.h"
#else
#define trace(args...)
#endif
const int M = 1000000007;
const int MM = 998244353;

template<typename T, typename U> static inline void amin(T &x, U y){ if(y<x) x=y; }
template<typename T, typename U> static inline void amax(T &x, U y){ if(x<y) x=y; }

#ifdef LOCAL
#define debug(...) debug_out(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) 2351
#endif

const int N = 1e6 + 2;

#define runSieve
bool prime[N];
int pf[N];
void sieve()
{
	int k=sqrt(N-2);
	for(int i=1;i<=N-2;++i)
		prime[i]=true;
	for(int i=2;i<=k;++i)
	{
		if(prime[i])
		{
			for(int k=i*i;k<=N-2;k+=i)
			{
				prime[k]=false;
				pf[k]=i;
			}
		}
	}
}

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<int> q[N];

int pt2[N];
int divs[N][8], fq[N][8], divcnt[N];
int cnt[N];

int f[N][20];


const int QR = 4e5 + 2;

int ans[QR];
int a[N];

int qry[QR][90];

int pt[QR];
int prs[QR][90];

int aux[100];

bool mp[N];
int l[QR], r[QR];

int mxp[N],pw[N][13];

int fnl[QR][13][20];


int _runtimeTerror_()
{
	int n, Q;
	cin >> n >> Q;
	for(int i=1;i<=n;++i)
		cin >> a[i];
	for(int i=2;i<=1e6;++i) {
		ll x = i;
		if(!prime[i])
			continue;
		mxp[i] = 0;
		while(x <= N) {
			++mxp[i];
			x *= i;
		}
		int f = 1;
		int cnt = 0;
		x = 1;
		while(x <= N && cnt < 13) {
			pw[i][cnt] = x;
			++cnt;
			x *= i;
		}
	}
	//mxp is max power of i that is less than n
	for(int i=2;i<=1e6;++i) {
		int tmp = i;
		while(tmp > 1 && !prime[tmp]) {
			int z = pf[tmp];
			divs[i][divcnt[i]] = z;
			int &cnt = fq[i][divcnt[i]];
			while(tmp % z == 0) {
				tmp /= z;
				++cnt;
			}
			if(i <5) trace(i, divcnt[i], divs[i][divcnt[i]], fq[i][divcnt[i]]);
			++divcnt[i];
		}
		if(tmp > 1) {
			divs[i][divcnt[i]] = tmp;
			fq[i][divcnt[i]] = 1;
			++divcnt[i];
		}
	}//divs is prime factors of i
	//divcnt is just number of prime factors
	// fq is frequency of a particular prime factor
	auto get = [&](int x,int i) {
		for(int j=0;j<divcnt[x];++j) {
			if(mp[divs[x][j]] == 0) {
				mp[divs[x][j]] = 1;
				prs[i][pt[i]] = divs[x][j];
				++pt[i];
			}
		}
	};
	for(int i=1;i<=Q;++i) {
		ans[i] = 1;
		cin >> l[i] >> r[i];
		q[r[i]].push_back(i);
		q[l[i]-1].push_back(-i);
		for(int j=0;j<25;++j) {
			int id = l[i] + rng() % (r[i] - l[i] + 1);
			get(a[id],i);
		}
		for(int j=0;j<pt[i];++j) {
			mp[prs[i][j]] = 0;
		}
	}
	// prs[i] is primes which divides random chhosen numbes for query i
	// pt[i] is how many such primes are there
	for(int i=1;i<=n;++i) {
		for(int j=0;j<divcnt[a[i]];++j) {
			++cnt[divs[a[i]][j]];
		}
		for(auto &j:q[i]) {
			int p = j > 0 ? j : -j;
			int fac = j / p;
			for(int k=0;k<pt[p];++k) {
				qry[p][k] += cnt[prs[p][k]] * (fac);
			}
		}
	}//cnt is just taking care of how many numbers is current prime dividing
	//qry[p][k] will tell us how many numbers does prs[p][k] divides
	// in pth query range
	for(int i=1;i<=Q;++i) {
		for(int j=0;j<pt[i];++j) {
			aux[j] = prs[i][j];
		}
		int sz = pt[i];
		pt[i] = 0;
		for(int j=0;j<sz;++j) {
			if(qry[i][j] > (r[i] - l[i] + 1)/2) {
				prs[i][pt[i]] = aux[j];
				fnl[i][pt[i]][0] += r[i] - l[i] + 1 - qry[i][j];
				++pt[i];
			}
		}
		assert(pt[i] < 14);
	}
	//aux is just used as a substitute to prs[i] old values
	//fnl[i][x] is just count of such numbers not div. 
	//by prs[i][j] in ith query
	for(int i=1;i<=n;++i) {
		for(int j=0;j<divcnt[a[i]];++j) {
			++f[divs[a[i]][j]][fq[a[i]][j]];
		}
		for(auto &j:q[i]) {
			int p = j > 0 ? j : -j;
			int fac = j / p;
			for(int k=0;k<pt[p];++k) {
				for(int l=0;l<=mxp[prs[p][k]];++l) {
					fnl[p][k][l] += f[prs[p][k]][l] * fac;
				}   
			}
			if(j > 0) {
				for(int k=0;k<pt[p];++k) {
					int g = 0;
					int len = (r[p] - l[p] + 2)/2;
					for(int l=0;l<=mxp[prs[p][k]];++l) {
						g += fnl[p][k][l];
						if(g >= len) {
							if(prs[p][k] == 2) {
								ans[p] *= 1 << l;
							}
							else {
								ans[p] *= pw[prs[p][k]][l];
							}
							break;
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=Q;++i) {
		cout << ans[i] << "\n";
	}
	return 0;
}

int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	#ifdef runSieve
		sieve();
	#endif
	#ifdef NCR
		initialize();
	#endif
	int TESTS = 1;
	//cin >> TESTS;
	while(TESTS--)
		_runtimeTerror_();
	return 0;
}