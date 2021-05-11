#include <bits/stdc++.h>
using namespace std;

int  mod = 1e9 + 7;
int n,m;
int p[251][251];
int dp[4][251][251];
int main(){
	cin>>n>>m;
	for(int i = 0; i<4; i++){
		for(int j =0; j<n; j++){
			for(int k =0; k<m; k++){
				dp[i][j][k] = 0;
			}
		}
	}
	for(int i =0; i<n; i++) for(int j=0; j<m ;j++) cin>>p[i][j];
	for(int i =0; i<n; i++){
		for(int j =0; j<n; j++){
			if(i == 0 && j ==0 ){
				for(int k =0; k<4 ; k++) dp[k][i][j] = p[i][j];
			}else if(i == 0){
				dp[1][i][j] = dp[2][i][j] = dp[3][i][j] = (dp[0][i][j-1] * p[i][j])%mod;
				dp[0][i][j] = (dp[3][i][j] + dp[0][i][j-1])%mod;
			}else if(j == 0){
				dp[1][i][j] = dp[0][i][j] = dp[3][i][j] = (dp[2][i-1][j] * p[i][j])%mod;
				dp[2][i][j] = (dp[3][i][j] + dp[2][i-1][j])%mod;
			}else{
				dp[3][i][j] = ((dp[0][i][j-1]+dp[1][i-1][j-1])%mod+dp[2][i-1][j])%mod*p[i][j]%mod;
				dp[0][i][j] = (dp[3][i][j] + dp[0][i][j-1])%mod;
				dp[1][i][j] = (dp[3][i][j] + dp[1][i-1][j-1])%mod;
				dp[2][i][j] = (dp[3][i][j] + dp[2][i-1][j])%mod;
			}

		}
	}
	cout<<dp[3][n-1][m-1]<<endl;
	return 0;
}