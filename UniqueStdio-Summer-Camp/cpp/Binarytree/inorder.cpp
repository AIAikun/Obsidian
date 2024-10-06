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
void NInOrder(node* root)
{
    vector<int> result;
    stack<node*> s;

    if (root == NULL)
        return ;

    while (root || !s.empty())
    {
        while (root)
        {
            s.push(root);
            root = root->lchild;
        }
        root = s.top();
        result.push_back(root->data);
        s.pop();
        root = root->rchild;
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
void inorder(node *root){
    if(root==NULL)  return;
    inorder(root->lchild);
    cout<<root->data<<endl;
    inorder(root->rchild);
}
int main(){
    int Array[10]={1,2,3,4,5,6,7,8,9,10};
    node* L=creat(Array,0);
    NInOrder(L);
    return 0;
}
