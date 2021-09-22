/* AUTHOR - MAHADEV( codechef - @har_harmahadev) */
#include <bits/stdc++.h>
#ifdef STAC
#include <sys/resource.h>
#endif
#pragma GCC optimize("-O3")
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
const ll mod = 1e9+7;

const int N = 1e5+5;
ll a[N];
int n,q,le[N],ri[N],ind[5*N],l[5*N],r[5*N],blksz,ans[5*N];
int block(int i){
	return i/blksz;
}

void solve(){
	cin>>n>>q;
	blksz = sqrt(n)+1;
	INP(a,n);
	map<ll,int> mp;
	for(int i =0; i<n; i++){
		mp[a[i]] = i;
	}
	stack<ll> st;
	fill(le,le+n,-1);
	fill(ri,ri+n,-1);
	for(int i=0; i<n; i++){
		while(!st.empty() && a[st.top()] < a[i]){
			ri[st.top()] = i;
			st.pop();
		}
		le[i] = st.empty()? -1 : st.top();
		st.push(i);
	}
	while(!st.empty()){
		ri[st.top()] = n;
		st.pop();
	}
	vpi intervs;
	for(int i =0; i<n; i++){
		if(i-le[i] < ri[i]-i){
			for(int j = le[i]+1; j<=i; j++){
				if(a[i]%a[j] != 0) continue;
				if(mp.find(a[i]/a[j]) == mp.end()) continue;
				if(mp[a[i]/a[j]] >= ri[i] || mp[a[i]/a[j]] < i) continue;
				intervs.PB(MP(j, mp[a[i]/a[j]]));
			}
		}else{
			for(int j = i; j<ri[i]; j++){
				if(a[i]%a[j] != 0) continue;
				if(mp.find(a[i]/a[j]) == mp.end()) continue;
				if(mp[a[i]/a[j]] <= le[i] || mp[a[i]/a[j]] > i) continue;
				intervs.PB(MP(mp[a[i]/a[j]], j));
			}
		}
	}
	vi lef[n], rig[n];
	for(auto x : intervs){
		lef[x.F].PB(x.S);
		rig[x.S].PB(x.F);
	}
	for(int i =0; i<n; i++){
		sort(all(lef[i]));
		sort(all(rig[i]));
	}
	for(int i=0;i<q;i++){
		cin>>l[i]>>r[i];
		l[i]--,r[i]--;
	}
	function<bool(int,int)> cmp = [&](const int &i, const int &j){
		return (block(l[i]) < block(l[j])) || (block(l[i]) == block(l[j]) && r[i] < r[j]);
	};
	iota(ind,ind+q,0);
	sort(ind,ind+q,cmp);
	int ml = 0, mr = -1;
	int curr = 0;
	function<void(int,int)> add = [&](int i, int typ){
		if(typ == 0){
			int in = upper_bound(all(lef[i]), mr) -lef[i].begin() ;
			curr += in;
		}else{
			int in = lower_bound(all(rig[i]), ml) -rig[i].begin() ;
			curr += sz(rig[i])-in;
		}
	};
	function<void(int,int)> rem = [&](int i, int typ){
		if(typ == 0){
			int in = upper_bound(all(lef[i]), mr) -lef[i].begin() ;
			curr -= in;
		}else{
			int in = lower_bound(all(rig[i]), ml) -rig[i].begin() ;
			curr -= sz(rig[i])-in;
		}
	};
	for(int i =0; i<q; i++){
		while(mr < r[ind[i]]){
			mr++;
			add(mr,1);
		}
		while(mr > r[ind[i]]){
			rem(mr,1);
			mr--;
		}
		while(ml < l[ind[i]]){
			rem(ml,0);
			ml++;
		}
		while(ml > l[ind[i]]){
			ml--;
			add(ml,0);
		}
		ans[ind[i]] = curr;
	}
	for(int i =0; i<q; i++){
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
	cin>>t;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}