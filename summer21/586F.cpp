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
const int inf = 1e9;
typedef pair<int, pii> ppi;
string s;
int n,l[3][27],x,y,z,mskcop,ind;
vi cr(3,0);
map<pii,pii> s1,s2;
map<int, char> mp;
void solve(){
	mp[0] = 'L';
	mp[1] = 'M';
	mp[2] = 'W';
	cin>>n;
	for(int i =0; i<n; i++){
		cin>>l[0][i]>>l[1][i]>>l[2][i];
	}
	if(n == 0){
		int cnt = 0;
		string st = "";
		for(int i =0; i<3; i++){
			if(l[i][0] == 0 && cnt < 2) cnt++, st += mp[i];
		}
		if(cnt == 2){
			cout<<st<<endl;
		}else{
			cout<<"Impossible"<<endl;
		}
		return;
	}
	map<pii, pii>::iterator it1,it2,ittemp;
	z = n/2;
	x = pow(3,z);
	y = pow(3,n-z);
	for(int msk = 0; msk<x; msk++){
		mskcop = msk;
		cr = vi{0,0,0};
		for(int i =0; i<z; i++){
			ind = mskcop%3;
			for(int j =0; j<3; j++){
				if(j == ind) continue;
				cr[j] += l[j][i];
			}
			mskcop /=3;
		}
		cr[0] -= cr[2];
		cr[1] -= cr[2];
		ittemp = s1.find(MP(cr[0],cr[1]));
		if(ittemp == s1.end() || cr[2] > ittemp->S.S){
			s1[MP(cr[0],cr[1])] = MP(msk,cr[2]);			
		}
	}
	for(int msk = 0; msk<y; msk++){
		mskcop = msk;
		cr = vi{0,0,0};
		for(int i =z; i<n; i++){
			ind = mskcop%3;
			for(int j =0; j<3; j++){
				if(j == ind) continue;
				cr[j] += l[j][i];
			}
			mskcop /=3;
		}
		cr[0] -= cr[2];
		cr[1] -= cr[2];
		ittemp = s2.find(MP(cr[0],cr[1]));
		if(ittemp == s2.end() || cr[2] > ittemp->S.S){
			s2[MP(cr[0],cr[1])] = MP(msk,cr[2]);			
		}
	}
	int mx = -inf;
	for(auto it = s1.begin(); it != s1.end(); it++){
		ittemp = s2.find(MP(-it->F.F, -it->F.S));
		if(ittemp == s2.end()) continue;
		if(ittemp->S.S+it->S.S > mx){
			mx = ittemp->S.S+it->S.S;
			it1 = it;
			it2 = ittemp;
		}
	}
	// ittemp = s1.lower_bound(vi{0,0,-inf});
	// if(ittemp->F[2] > mx){
	// 	mx = ittemp->F[2];
	// 	it1 = ittemp;
	// 	it2 = s2.end();
	// }
	// ittemp = s2.lower_bound(vi{0,0,-inf});
	// if(ittemp->F[2] > mx){
	// 	mx = ittemp->F[2];
	// 	it2 = ittemp;
	// 	it1 = s1.end();
	// }
	if(mx == -inf){
		cout<<"Impossible"<<endl;
		return;
	}
	for(int i =0; i<z; i++){
		ind = (it1->S.F)%3;
		for(int j =0; j<3; j++){
			if(j == ind) continue;
			cout<<mp[j];
		}
		cout<<endl;
		(it1->S.F) /=3;
	}
	for(int i =z; i<n; i++){
		ind = (it2->S.F)%3;
		for(int j =0; j<3; j++){
			if(j == ind) continue;
			cout<<mp[j];
		}
		cout<<endl;
		(it2->S.F) /=3;
	}
	return;
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