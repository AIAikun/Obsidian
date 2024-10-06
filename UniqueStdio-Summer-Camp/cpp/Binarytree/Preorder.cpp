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
void NPreOrder(node* root)
{
    vector<int> result;
    stack<node*> s;

    if (root == NULL)
        return ;

    while (root || !s.empty())
    {//结束遍历的条件是root为空且栈为空
        while(root)
        {//找到最左结点，并把路径上的所有结点一一访问后入栈
            s.push(root);
            result.push_back(root->data);
            root = root->lchild;
        }
        root = s.top();//取栈顶结点
        s.pop();//弹出栈顶结点
        root = root->rchild;//左和中都访问了再往右访问
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
void preorder(node *root){
    if(root==NULL)  return;
    cout<<root->data<<endl;
    preorder(root->lchild);
    preorder(root->rchild);
}
int main(){
    int Array[10]={1,2,3,4,5,6,7,8,9,10};
    node* L=creat(Array,0);
    NPreOrder(L);
    return 0;
}

