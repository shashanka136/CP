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

const int N = 1e5+5;
//
map<int,int> mp;
int n, siz[2*N],sqn,q,typ,l,r,p,x,n23;
int cnt[2*N],cr1,cr2,cr3,a[N];
int crt,crl,crr;
struct que{
	int t,l,r;
};
struct ch{
	int p,x;
};

int ind[N],ans[N];

que qs[N];
ch chs[N];
int sqrtre(int n){
	return (sqrtl(1+8*n)-1)/2;
}

int block(int i){
	return i/n23;
}

bool cmp(const int &i, const int &j){
	if(block(qs[i].t) < block(qs[j].t)) return true;
	if(block(qs[i].t) > block(qs[j].t)) return false;
	if(block(qs[i].l) < block(qs[j].l)) return true;
	if(block(qs[i].l) > block(qs[j].l)) return false;
	if(qs[i].r < qs[j].r) return true;
	if(qs[i].r > qs[j].r) return false;
	if(qs[i].t < qs[j].t) return true;
	if(qs[i].t > qs[j].t) return false;
	if(qs[i].l < qs[j].l) return true;
	if(qs[i].l > qs[j].l) return false;
	return true;
}

void solve(){
	cin>>n>>q;
	n23 = cbrt(1ll*n*n);
	sqn = sqrtre(n)+1;
	cr1 = 0;
	for(int i=0; i<n; i++){
		cin>>a[i];
		if(mp.find(a[i]) == mp.end()){
			mp[a[i]] = cr1++;
		}
		a[i] = mp[a[i]];
	}
	cr2 = cr3 = 0;
	for(int i =0; i<q; i++){
		cin>>typ;
		if(typ == 1){
			cin>>l>>r;
			l--,r--;
			qs[cr2++] = {cr3,l,r};
		}else{
			cin>>p>>x;
			p--;
			if(mp.find(x) == mp.end()){
				mp[x] = cr1++;
			}
			x= mp[x];
			chs[cr3++] = {p,x};
		}
	}
	iota(ind,ind+cr2,0);
	fill(cnt,cnt+cr1,0);
	fill(siz,siz+2*N,0);
	sort(ind,ind+cr2,cmp);
	crt = 0, crl = 0, crr = -1;
	function<void(int)> inc = [&](int i){
		if(cnt[a[i]]) siz[cnt[a[i]]]--;
		cnt[a[i]]++;
		siz[cnt[a[i]]]++;
	};
	function<void(int)> exc = [&](int i){
		siz[cnt[a[i]]]--;
		cnt[a[i]]--;
		if(cnt[a[i]])siz[cnt[a[i]]]++;
	};
	function<void(int)> exe = [&](int i){
		if(chs[i].p >= crl && chs[i].p <= crr){
			siz[cnt[a[chs[i].p]]]--;
			cnt[a[chs[i].p]]--;
			if(cnt[a[chs[i].p]])siz[cnt[a[chs[i].p]]]++;
		}
		swap(a[chs[i].p], chs[i].x);
		if(chs[i].p >= crl && chs[i].p <= crr){
			if(cnt[a[chs[i].p]]) siz[cnt[a[chs[i].p]]]--;
			cnt[a[chs[i].p]]++;
			siz[cnt[a[chs[i].p]]]++;
		}
	};
	for(int i =0; i<cr2; i++){
		trace(qs[ind[i]].t,qs[ind[i]].l,qs[ind[i]].r);
		while(crr < qs[ind[i]].r){
			inc(++crr);
		}
		while(crr > qs[ind[i]].r){
			exc(crr--);
		}
		while(crl < qs[ind[i]].l){
			exc(crl++);
		}
		while(crl > qs[ind[i]].l){
			inc(--crl);
		}
		while(crt < qs[ind[i]].t){
			exe(crt++);
		}
		while(crt > qs[ind[i]].t){
			exe(--crt);
		}
		// trace(MP(siz,10),MP(cnt,10));
		for(int j =1; j<= sqn; j++){
			if(siz[j] == 0){
				ans[ind[i]] = j;
				break;
			}
		}
	}
	for(int i =0; i<cr2; i++){
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
	// cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}