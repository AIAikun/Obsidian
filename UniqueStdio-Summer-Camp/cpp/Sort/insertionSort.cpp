#include<iostream>
using namespace std;
int A[1000], n;
void insertionSort();
int main()
{
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>A[i];
    }
    for (int i = 0; i < n; i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}
void insertionSort()
{
    for(int i=1; i<n; i++)
    {
        int key = A[i];
        int j = i-1;
        while(j>=0 && A[j]>key)
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}