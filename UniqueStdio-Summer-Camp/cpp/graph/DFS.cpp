vector<int> ADJ[MAX];//MAX是最大顶点数
int n;//n是顶点数
bool vis[MAX]=false;
void DFS(int u,int depth){
    vis[u]=true;//标记为已访问
    /*如果对u进行一些操作，可以在此处进行*/
    for(int i=0;i<ADJ[u].size();i++){
        int v=ADJ[u][i];
        if(!vis[v]){
            DFS(v,depth+1);
        }
    }
}
void DFSTrave(){
    for (int u = 0; u < n; u++)
    {
        if(!vis[u]){
            DFS(u,1);
        }
    }
}