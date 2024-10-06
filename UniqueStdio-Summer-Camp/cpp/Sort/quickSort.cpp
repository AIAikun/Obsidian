#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
int Partiton (int a[],int left,int right){
    int temp=a[left];
    while (left<right)
    {
        while (left<right&&a[right]>=temp)
        {
            right--;
        }
        a[left]=a[right];
        while (left<right&&a[left]<=temp)
        {
            left++;
        }
        a[right]=a[left];
    }
    a[left]=temp;
    return left;
}
void quickSort(int a[],int left,int right){
    if (left<right)
    {
        int pos=Partiton(a,left,right);
        quickSort(a,left,pos-1);
        quickSort(a,pos+1,right);
    }
}
int main(){
    int n;
    cin>>n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    quickSort(a,0,n-1);
    for (int i = 0; i < n; i++)
    {
        cout<<a[i]<<" ";
    }
}