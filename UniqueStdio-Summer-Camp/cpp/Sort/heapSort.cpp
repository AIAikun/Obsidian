#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
int heap[1000000],n;
void downAdjust(int low,int high){
    int i=low,j=i*2;
    while(j<=high){
        if(j+1<=high&&heap[j+1]>heap[j]){
            j=j+1;
        }
        if(heap[j]>heap[i]){
            swap(heap[j],heap[i]);
            i=j;
            j=i*2;
        }else{
            break;
        }
    }
}
void creatHeap(){
    for(int i=n/2;i>=1;i--){
        downAdjust(i,n);
    }
}
void heapSort(){
    creatHeap();
    for(int i=n;i>=2;i--){
        swap(heap[1],heap[i]);
        downAdjust(1,i-1);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>heap[i];
    }
    heapSort();
    for(int i=1;i<=n;i++){
        cout<<heap[i]<<" ";
    }
    return 0;
}