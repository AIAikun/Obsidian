#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int INF=1000000000;
const int MAX=200;
int n,m;
int dis[MAX][MAX];
void Floyd(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dis[i][k]<INF&&dis[k][j]<INF&&dis[i][k]+dis[k][j]<dis[i][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
}
int main(){
    int u,v,w;
    fill(dis[0],dis[0]+MAX*MAX,INF);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        dis[i][i]=0;
    }
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        dis[u][v]=w;
    }
    Floyd();
    for (int i = 0; i < n; i++)
    {
        for(int j=0;j<n;j++){
            cout<<dis[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}