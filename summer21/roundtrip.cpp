#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int n,m;
void dfs(vector<vector<int> > &adj,vector<bool> &vis,vector<int>& parent,int start,vector<int> &ans,int &flag){
    vis[start]=true;
    for(unsigned int i=0;i<adj[start].size();i++){
        if(!vis[adj[start][i]]) {
                parent[adj[start][i]]=start;
                dfs(adj,vis,parent,adj[start][i],ans,flag);
        }
        else {
           if(adj[start][i]!=parent[start]){
               //cout<<"DOWN"<<'\n';
               if(flag==1){
                return;
               }
               flag=1;
               int temp=start;
               ans.push_back(adj[start][i]);
               while(temp!=adj[start][i]){
                   ans.push_back(temp);
                   temp=parent[temp];
               }
               ans.push_back(temp);
               reverse(ans.begin(),ans.end());
               cout<<ans.size()<<'\n';
               for(unsigned int i=0;i<ans.size();i++){
                    cout<<ans[i]+1<<" ";
               }
               return;
           }
        }
    }
 
}
 
int main()
{
    cin>>n>>m;
    vector<vector<int> > adj(n);
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    vector<bool> vis(n,false);
    vector<int> parent(n,-1);
    vector<int> ans;
     int flag=0;
    for(int i=0;i<n;i++){
       if(!vis[i]){
         if(flag==1) break;
         dfs(adj,vis,parent,i,ans,flag);
       }
    }
    if(flag==0) cout<<"IMPOSSIBLE"<<'\n';
    //cout<<ans.size()<<endl;
 
 
    return 0;
}