vector<int> ADJ[MAX];//MAX是最大顶点数
int n;//n是顶点数   
bool inq[MAX]=false;
void BFS(int u){
    queue<int> q;
    q.push(u);
    inq[u]=true;
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        /*如果对u进行一些操作，可以在此处进行*/
        for(int i=0;i<ADJ[u].size();i++){
            int v=ADJ[u][i];
            if(!inq[v]){
                q.push(v);
                inq[v]=true;
            }
        }
    }
}
void BFSTrave(){
    for(int i=0;i<n;i++){
        if(!inq[i]){
            BFS(i);
        }
    }
}