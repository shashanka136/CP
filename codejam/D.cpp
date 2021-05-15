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
// #define endl '\n'
#define all(v) v.begin(), v.end()
const ll mod = 998244353;

//
int n,q;
string s;
int ans,m,tmp;
map<vi,int> mp;
void ask_query(int a, int b, int c){
	vi x{a,b,c};
	sort(all(x));
	if(mp.find(x) != mp.end()){
		// trace(x, mp[x]);
		ans = mp[x]; return;
	}
	cout<<a<<" "<<b<<" "<<c<<endl;
	cin>>ans;
	mp[x] = ans;
}
bool get_same(vi &v, int l, int m, int r){
	ask_query(v[l], v[l+1], v[m]);
	// trace(v,l,m,r);
	if(ans == v[m]){
		ask_query(v[m],v[l+1], v[m+1]);
		if(ans == v[m]){
			// trace(1);
			return false;//opposite
		}else{
			// trace(2);
			return true;
		}
	}else{
		tmp = ans;
		ask_query(ans, v[m],v[m+1]);
		if(ans == v[m] && tmp == v[l]){ return false;}
		if(ans == v[m] && tmp == v[l+1]){ return true;}
		if(tmp == v[l]){ return true;}
		if(tmp == v[l+1]){return false;}
	}
	return true;
}

void execute(vi &v, vi &fin, int &i, int &j){
	ask_query(v[i],v[j],v[j+1]);
	if(ans == v[i]){
		fin.PB(v[j]);
		fin.PB(v[i]);
		i++,j++;
	}else if(ans == v[j]){
		fin.PB(v[i]);
		i++;
	}else{
		fin.PB(v[j]);
		fin.PB(v[j+1]);
		j+=2;
	}
}
void merge(vi &v, int l, int m, int r){
	// trace(l,r,m);
	// if(l == 0 && r== 7) trace(v);
	if(!get_same(v,l,m,r)){
		reverse(v.begin()+m, v.begin()+r);
	}
	// if(l == 0 && r== 7) trace(v);
	vi temp;
	int i=l, j = m;
	while(i !=m && j != r){
		if(m-i > r-j){
			execute(v,temp,j,i);
		}else if(m-i < r-j || m-i != 1){
			execute(v,temp,i,j);
		}else{
			ask_query(temp.back(), v[i], v[j]);
			temp.PB(ans);
			temp.PB(v[i]+v[j]-ans);
			i++,j++;
		}
	}
	while(i !=m ){
		temp.PB(v[i]);i++;
	}
	while(j != r){
		temp.PB(v[j]);j++;
	}
	assert(sz(temp) == r-l);
	for(int i =l; i<r; i++){
		v[i] = temp[i-l];
	}
}
void medianSort(vi &v, int l, int r){
	if(r-l <=2) return;
	if(r-l == 3){
		ask_query(v[l],v[l+1],v[l+2]);
		if(ans == v[l]){
			swap(v[l], v[l+1]);
		}else if(ans == v[l+2]){
			swap(v[l+2], v[l+1]);
		}
		return;
	}
	m = l+r>>1;
	medianSort(v,l,m);
	m = l+r>>1;
	medianSort(v,m,r);
	m = l+r>>1;
	merge(v,l,m,r);
}
void solve(){
	mp.clear();
	vi v(n);
	iota(all(v), 1);
	medianSort(v,0,n);
	for(int i =0; i<n; i++){
		cout<<v[i]<<" ";
	}cout<<endl;
	cin>>ans;
	if(ans == 1) return;
	else exit(0);
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
	cin>>t>>n>>q;
	// for(int i=1; i<=t; i++){
	// 	cout<<"Case #"<<i<<": ";
	// 	solve();
	// }
	while(t--){
		solve();
	}
}