#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<stack>
#include<vector>
using namespace std;
struct node
{
    int data;
    node *lchild;
    node *rchild;
};  
void NPostOrder(node* root)
{
    vector<int> result;
    stack<node*> s;
    node* cur = root;
    node* pre = NULL;

    if (root == NULL)
        return ;

    while (cur)
    {//走到最左孩子
        s.push(cur);
        cur = cur->lchild;
    }

    while (!s.empty())
    {
        cur = s.top();
        if (cur->rchild == NULL || cur->rchild == pre)
        {//当一个结点的右孩子为空或者被访问过的时候则表示该结点可以被访问
            result.push_back(cur->data);
            pre = cur;
            s.pop();
        }
        else
        {//否则访问右孩子
            cur = cur->rchild;
            while (cur)
            {
                s.push(cur);
                cur = cur->lchild;
            }
        }
    }
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
}
node* creat(int Array[],int i){
    if(Array[i]==0||i>=10) return NULL;
    node* root=new node;
    root->data=Array[i];
    root->lchild=creat(Array,2*i+1);
    root->rchild=creat(Array,2*i+2);
    return root;
}
void postorder(node *root){
    if(root==NULL)  return;
    postorder(root->lchild);
    postorder(root->rchild);
    cout<<root->data<<endl;
}
int main(){
    int Array[10]={1,2,3,4,5,6,7,8,9,10};
    node* L=creat(Array,0);
    NPostOrder(L);
    return 0;
}
