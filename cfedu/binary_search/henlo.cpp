#include <bits/stdc++.h>
using namespace std;
int n,gx[2][3];
int p[3],c[3];

bool cmp(const int &i, const int &j){
	return (double(gx[1][i])/gx[0][i]> double(gx[1][j])/gx[0][j]);
}
int main(){
	cin>>n;
	for(int i =0; i<2; i++){
		for(int j =0; j<3; j++){
			cin>>gx[i][j];
		}
	}
	iota(p,p+3,0);
	fill(c,c+3,0);
	sort(p,p+3, cmp);
	for(int i = 0;i <3; i++){
		if(gx[1][p[i]] <= gx[0][p[i]]) break;
		c[p[i]] = n / gx[0][p[i]];
		n -= c[p[i]] * gx[0][p[i]];
	}
	for(int i = 0;i <3; i++){
		n += c[i] * gx[1][i];
		c[i] = 0;
	}
	for(int i = 2;i >=0; i--){
		if(gx[1][p[i]] >= gx[0][p[i]]) break;
		c[p[i]] = n / gx[1][p[i]];
		n -= c[p[i]] * gx[1][p[i]];
	}
	for(int i = 0;i <3; i++){
		n += c[i] * gx[0][i];
	}
	cout<<n<<endl;
	return 0;
}