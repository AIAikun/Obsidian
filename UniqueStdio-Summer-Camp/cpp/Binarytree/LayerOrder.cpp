#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<stack>
#include<vector>
#include<queue>
using namespace std;
struct node
{
    int data;
    node *lchild;
    node *rchild;
};
node* creat(int Array[],int i){
    if(Array[i]==0||i>=10) return NULL;
    node* root=new node;
    root->data=Array[i];
    root->lchild=creat(Array,2*i+1);
    root->rchild=creat(Array,2*i+2);
    return root;
}
void LayerOrder (node* root)
{
    queue<node*> q;
    q.push(root);
    while (!q.empty())
    {
        node* cur = q.front();
        cout << cur->data << endl;
        q.pop();
        if (cur->lchild)
            q.push(cur->lchild);
        if (cur->rchild)
            q.push(cur->rchild);
    }
}
int main(){
    int Array[10]={1,2,3,4,5,6,7,8,9,10};
    node* L=creat(Array,0);
    LayerOrder(L);
    return 0;
}