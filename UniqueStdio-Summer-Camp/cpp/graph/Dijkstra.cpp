struct Node
{
    int v,dis;//v是顶点，dis是边权
};
vector<Node> ADJ[MAX];//MAX是最大顶点数
int n;//n是顶点数
int d[MAX];//d[i]表示从源点s到顶点i的最短距离
bool vis[MAX]=false;
void Dijkstra(int s){
    fill(d,d+MAX,INF);
    d[s]=0;
    for(int i=0;i<n;i++){
        int u=-1,MIN=INF;
        for(int j=0;j<n;j++){
            if(!vis[j]&&d[j]<MIN){
                u=j;
                MIN=d[j];
            }
        }
        if(u==-1) return;
        vis[u]=true;
        for(int j=0;j<ADJ[u].size();j++){
            int v=ADJ[u][j].v;
            int dis=ADJ[u][j].dis;
            if(!vis[v]&&d[u]+dis<d[v]){
                d[v]=d[u]+dis;
            }
        }
    }