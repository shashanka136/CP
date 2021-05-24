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
struct suff_array{
	string s;
	char extra;
	int n;
	int *p, *c, *lcp,*logs, *le, *ri,*par;
	vector<vector<int>> st,invlcp;
	vector<set<int>> se;
	int tot;

	int fin(int i){
		if(par[i] != i){
			par[i] = fin(par[i]);
		}
		return par[i];
	}
	suff_array(){}
	suff_array(string _s,char _c): s(_s), extra(_c){
		s += extra;
		n = s.size();
		p = c = lcp = logs= NULL;
	}
	
	void build(const string &_s, char &_c){//will be used when want to declare it globally
		s = _s;
		s += _c;
		n = s.size();
		p = c = lcp = logs= le = ri= NULL;
	}

	void init(){
		p = new int[n+1];
		c = new int[n+1];
		int cnt[256];
		fill(cnt,cnt+256,0);
		for(int i = 0; i<n;i++){
			cnt[s[i]]++;
		}
		for(int i=1; i <256;i++){
			cnt[i] += cnt[i-1];
		}
		for(int i=n-1;i>=0;i--){
			p[--cnt[s[i]]] = i;
		}
		int cr = 0;
		int lst = s[p[0]];
		c[p[0]] = 0;
		for(int i =1; i<n; i++){
			if(s[p[i]] > lst){
				cr++;
				lst = s[p[i]];
			}
			c[p[i]] = cr; 
		}
		tot = cr+1;
	}

	void get_array(){
		init();
		int lgn = log2(n);
		int *cnew;
		cnew = new int[n+1];
		int *pn;
		pn = new int[n+1];
		int *cnt;
		cnt = new int[n+1];
		for(int k = 0;k<=lgn;k++){
			fill(cnt,cnt+tot,0);
			for(int i=0;i<n;i++){
				pn[i] = p[i] - (1<<k);
				if(pn[i] < 0) pn[i] += n;
			}
			for(int i =0; i<n; i++){
				cnt[c[i]]++;
			}
			for(int i = 1; i<tot; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i = n-1; i>=0; i--){
				p[--cnt[c[pn[i]]]] = pn[i];
			}
			int cr = 0;
			pii lst = MP(c[p[0]],c[(p[0] +(1<<k))%n]);
			cnew[p[0]] = 0;
			for(int i =1; i<n; i++){
				pii pr = MP(c[p[i]],c[(p[i]+(1<<k))%n]);
				if(pr > lst){
					cr++;
					lst = pr;
				}
				cnew[p[i]] = cr; 
			}
			tot = cr+1;
			swap(c,cnew);
		}
	}

	void get_lcp(){
		if(p == NULL) get_array();
		lcp = new int[n];
		int k = 0,a,b;
		for(int i =0; i<n-1; i++){
			a = c[i];
			b = c[i]-1;
			while(s[i+k] == s[p[b]+k]){
				k++;
			}
			lcp[b] = k;
			if(k > 0)k--;
		}
		lcp[n-1] = 0;
	}

	void get_invlcp(){
		if(lcp == NULL) get_lcp();
		invlcp.assign(n, vector<int>(0));
		for(int i = n-1; i>= 0;i--){
			invlcp[lcp[i]].PB(i);
		}
	}

	void ini_se(){
		par = new int[n+1];
		iota(par,par+n+1,0);
		if(p == NULL) get_array();
		se.resize(n);
		for(int i=0;i <n; i++){
			se[i].insert(p[i]);
		}
	}

	int join(int i){
		int j = i+1;
		i = fin(i);
		j = fin(j);
		if(se[i].size() > se[j].size()) swap(i,j);
		par[i] = j;
		int ans = 1e9;
		for(auto &x : se[i]){
			auto it = se[j].lower_bound(x);
			if(it != se[j].end()) ans = min(ans,(*it)-x);
			if(it != se[j].begin()){
				it--;
				ans = min(ans,x - (*it));
			}
		}
		for(auto &x : se[i]){
			se[j].insert(x);
		}
		se[i].clear();
		return ans;
	}

	void get_logs(){
		logs = new int[n+1];
		fill(logs,logs+n+1,0);
		for(int i=2;i<=n;i++){
			logs[i] = logs[i/2] +1;
		}
	}

	void get_st(){
		if(lcp == NULL) get_lcp();
		if(logs == NULL) get_logs();//precalculated value of int(log2(i))
		st.assign(n, vector<int>(logs[n] + 1));//sparse_table for min range query
		for(int i =0; i<n-1; i++){
			st[i][0] = lcp[i];
		}
		st[n-1][0] = 0;
		for(int j = 1; j <=logs[n]; j++){
			for(int i = 0; i+(1<<j) <=n;i++){
				st[i][j] = min(st[i][j-1], st[i+(1<<j-1)][j-1]);
			}
		}
	}

	void get_le_ri(){
		if(lcp == NULL) get_lcp();
		le = new int[n];//le[i] will store the index where first small or equal value appear in left
		ri = new int[n];//le[i] will store the index where first small value appear in right
		stack<int> stac;
		for(int i=1; i <n-1;i++){
			while(!stac.empty() && lcp[stac.top()] > lcp[i]){
				ri[stac.top()] = i;
				stac.pop();
			}
			stac.push(i);
		}
		while(!stac.empty()){
			ri[stac.top()] = n-1;
			stac.pop();
		}
		for(int i = n-2;i > 0; i--){
			while(!stac.empty() && lcp[stac.top()] >= lcp[i]){
				le[stac.top()] = i;
				stac.pop();
			}
			stac.push(i);
		}
		while(!stac.empty()){
			le[stac.top()] = 0;
			stac.pop();
		}
	}
	int Lcp(int i,int j){//get_st must be called already
		if(i == j) return n-1-i;
		int l = c[i], r = c[j];
		if(l > r) swap(l,r);
		r--;
		int po = logs[r-l+1];
		int mn = min(st[l][po], st[r+1-(1<<po)][po]);
		return mn;
	}


	int lower_bound(const string& t) {
		int k = t.size();
		int l = 0, r = n, mid;
		while (r>l) {
			mid = l+r>>1;
			if(s.substr(p[mid], k) < t){
				l = mid+1;
			}else{
				r = mid;
			}
		}
		return l;
	}

	int upper_bound(const string& t) {
		int k = t.size();
		int l = 0, r = n, mid;
		while(r > l) {
			mid = l+r>>1;
			if(s.substr(p[mid], k) <= t){
				l = mid+1;
			}else{
				r = mid;
			}
		}
		return l;
	}

	bool comp(const pair<int,int> &i,const pair<int,int> &j){//comparing substrings
		int z = Lcp(i.F-1,j.F-1), len1 = i.S-i.F+1, len2 = j.S-j.F+1;
		if(z >= min(len1,len2)){
			return (len1 < len2) || (len1==len2 && i<j);
		}
		return s[i.F+z-1]<s[j.F+z-1];
	}
};
int n,pos[304],ind1,ind2,ans,lcp[304][304],cr,cnt;
string w[304],s;
void solve(){
	cin>>n;
	INP(w,n);
	s = "";
	for(int i =0; i<n; i++){
		for(int j = 0; j< sz(w[i]); j++) s += w[i][j];
		s += ',';
	}
	suff_array fo(s,'$');
	pos[0] = sz(w[0])-1;
	for(int i=1; i<n; i++){
		pos[i] = pos[i-1]+sz(w[i])+1;
	}
	fo.get_st();
	int mx = 0;
	for(int i=0; i<n; i++){
		ind1 = i ==0? 0: pos[i-1] +2;
		lcp[i][i] = n-i;
		for(int j = i+1; j<n; j++){
			ind2 = pos[j-1] +2;
			ans = fo.Lcp(ind1,ind2);
			ans = min(ind2-ind1, ans);
			ans += ind1-1;
			int it = upper_bound(pos+i,pos+j,ans-1) - pos;
			it--;
			lcp[i][j] = it-i+1;
		}
	}
	for(int i = 0; i<n; i++){
		ind1 = i ==0? 0: pos[i-1] +2;
		for(int len = 1; len <= n/2; len++){
			cr = 0;
			cnt = 0;
			while(cr < n){
				if(lcp[i][cr] >= len){
					cr += len;
					cnt++;
				}else{
					cr++;
				}
			}
			if(cnt > 1)mx = max(mx, cnt*(pos[i+len-1] - ind1+1 -len));
		}
	}
	cout<<sz(s)-1-mx<<endl;
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