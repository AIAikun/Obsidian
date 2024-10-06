#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
struct node
{
    int data;
    node *next;
};
node *creat(int Array[]){
    node *p,*pre,*head;
    head=new node;
    head->next=NULL;
    pre=head;
    for(int i=0;i<5;i++){
        p=new node;
        p->data=Array[i];
        p->next=NULL;
        pre->next=p;
        pre=p;
    }
    return head;
}
int main(){
    int Array[5]={1,2,3,4,5};
    node* L=creat(Array);
    L=L->next;
    while(L!=NULL){
        cout<<L->data<<endl;
        L=L->next;
    }
    delete L;
    return 0;
}
