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
const int N = 1e6+7;
int n,m,cyc[N], len[N], tot,num[N],cr, crcyc,tmp;
bool vis[N];
vector<vector<bool>> poss;
vector<bool> us;
stack<int> st;
vector<string> c,s;
map<char,int> mp;
void solve(){
	cin>>n>>m;
	tot = n*m;
	poss.clear();
	mp['U'] = -m;
	mp['D'] = +m;
	c.assign(n,"");
	s.assign(n,"");
	for(int i =0; i<n; i++){
		cin>>c[i];
	}
	for(int i =0; i<n; i++){
		cin>>s[i];
	}
	fill(vis,vis+tot,false);
	fill(cyc,cyc+tot,-1);
	fill(num,num+tot,-1);
	crcyc = 0;
	// trace(1);
	for(int i =0; i<tot; i++){
		if(vis[i]) continue;
		// trace(8);
		cr = i;
		while(!vis[cr]){
			// trace(cr);
			cyc[cr] = crcyc;
			vis[cr] = true;
			cr += mp[s[cr/m][cr%m]];
			// trace(cr);
		}
		// trace(2);
		st = stack<int>();
		tmp = i;
		while(tmp != cr){
			st.push(tmp);
			tmp += mp[s[tmp/m][tmp%m]];
		}
		// trace(3);
		if(cyc[cr] == crcyc){
			num[cr] = 0;
			us = vector<bool>();
			us.PB(c[cr/m][cr%m] == '0');
			tmp = cr;
			// trace(cr);
			// trace(s[cr/m][cr%m]);
			cr += mp[s[cr/m][cr%m]];
			// trace(cr);
			while(cr != tmp){
				num[cr] = sz(us);
				us.PB(c[cr/m][cr%m] == '0');
				// trace(sz(us));
				cr += mp[s[cr/m][cr%m]];
			}
			poss.PB(us);
			len[crcyc] = sz(us);
			// trace(n,m,len[crcyc]);
			crcyc++;
		}
		// trace(4);
		while(!st.empty()){
			cyc[st.top()] = cyc[cr];
			num[st.top()] = num[cr]-1;
			if(num[st.top()] == -1) num[st.top()] = len[cyc[cr]]-1;
			if(c[st.top()/m][st.top()%m] == '0'){
				poss[cyc[cr]][num[st.top()]] = true; 
			}
			cr = st.top();
			st.pop();
		}
		// trace(5);
	}
	int ans1=0,ans2 = 0;
	// trace(6);
	for(int i =0; i<crcyc; i++){
		// trace(7);
		ans1+= len[i];
		for(int j =0; j<len[i]; j++) if(poss[i][j]) ans2++;
	}
	cout<<ans1<<" "<<ans2<<endl;
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
	mp['L'] = -1;
	mp['R'] = +1;
	/*for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}*/
	while(t--){
		solve();
	}
}