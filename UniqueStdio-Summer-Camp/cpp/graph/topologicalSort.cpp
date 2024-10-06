vector<int> G[MAX];//MAX是最大顶点数
int n,m,inDegree[MAX];
bool topologicalSort(){
    int num=0;//记录加入拓扑序列的顶点数
    queue<int> q;
    for(int i=0;i<n;i++){
        if(inDegree[i]==0){
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<G[u].size();i++){
            int v=G[u][i];
            inDegree[v]--;
            if(inDegree[v]==0){
                q.push(v);
            }
        }
        G[u].clear();
        num++;
    }
    if(num==n) return true;
    else return false;
    
}