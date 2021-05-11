#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define min3(a,b,c) min(min(a,b),c)
#define max3(a,b,c) max(max(a,b),c)
#define endl '\n'
#define INF INT_MAX
const ll mod = (ll)1e9 + 7;

void printVector(vector<int> &v){
	for(auto x:v)
		cout<<x<<" ";
    cout<<"\n";
}

void solve(){
    ll n,k;
    cin>>n>>k;
    ll h[n];
    for(int i=0;i<n;i++){
    	cin>>h[i];
    }
    if(h[1]-h[0]>k-1){
    	cout<<"NO"<<endl;
    	return;
    }
    for(int i=2;i<n;i++){
    	if(h[i]-h[i-1]>2*(k-1)){
    		cout<<"NO"<<endl;
    		return;
    	}
    }
    for(int i=0;i<n-2;i++){
		if(h[i]-h[i+1]>2*(k-1)){
			cout<<"NO"<<endl;
			return;
		}
    }
    if(h[n-2]-h[n-1]>k-1){
    	cout<<"NO"<<endl;
    	return;
    }
    cout<<"YES"<<endl;
    return;
}

int main(){
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--){
        solve();
    }
}