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
int n,sn;
string s[103], st;
map<pii,int> mp[103];
int c[103];
vector<string> v,v1,v2;
vector<int> vin;

string sum(string str1, string str2){
    if (str1.length() > str2.length())
        swap(str1, str2);
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i=0; i<n1; i++){
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    for (int i=n1; i<n2; i++){
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    if (carry)
        str.push_back(carry+'0');
    reverse(str.begin(), str.end());
 
    return str;
}


string multiply(string& num1, string& num2){
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";
    vector<int> result(len1 + len2, 0);
    int i_n1 = 0;
    int i_n2 = 0;
    for (int i=len1-1; i>=0; i--){
        int carry = 0;
        int n1 = num1[i] - '0';
        i_n2 = 0;          
        for (int j=len2-1; j>=0; j--){
            int n2 = num2[j] - '0';
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
            carry = sum/10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        i_n1++;
    }
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
    if (i == -1)
    return "0";
    string s = "";
    while (i >= 0)
        s += std::to_string(result[i--]);
    return s;
}

inline int fi(){ return sz(v)-3;}
inline int se(){ return sz(v)-2;}
inline int th(){ return sz(v)-1;}
vector<string> extr(string &s){
	vector<string> v(3);
	int i =0;
	for(;s[i] != '*'; i++);
	v[0] = s.substr(0,i);
	int j = sz(s) - 1;
	for(;s[j]!='+'; j--);
	v[1] = s.substr(i+1,j-i-1);
	v[2] = s.substr(j+1);
}
void process(int i){
	sn = sz(s[i]);
	for(int j =0; j<sn; j++){
		if(s[i][j] == ')'){
			string sfin;
			int vfin;
			if(vin[fi()]){
				v1 = extr(v[fi()]);
			}
			if(vin[th()]){
				v2 = extr(v[th()]);
			}
			if(v[se] == '*'){
				if(vin[fi()] & vin[se()]){
					if(v1[1] == v2[1]){
						sfin = sum(v1[0],v2[0]) + '*' + v1[1] + '+' + sum(v1[2], v2[2]);
					}else{

					}
				}else if(vin[fi()]){

				}else if(vin[se()]){

				}else{

				}
			}else if(v[se] == '+'){
				if(vin[fi()] & vin[se()]){
					if(v1[1] == v2[1]){
						sfin = sum(v1[0],v2[0]) + '*' + v1[1] + '+' + sum(v1[2], v2[2]);
					}else{
						
					}
				}else if(vin[fi()]){

				}else if(vin[se()]){

				}else{
					
				}
			}else{
				if(vin[fi()] & vin[se()]){
					if(v1[1] == v2[1]){

					}else{
						
					}
				}else if(vin[fi()]){

				}else if(vin[se()]){

				}else{
					
				}
			}
		}
	}
}
void solve(){
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>s[i];
		mp[i].clear();
		process(i);
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
	for(int i=1; i<=t; i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
	// while(t--){
	// 	solve();
	// }
}