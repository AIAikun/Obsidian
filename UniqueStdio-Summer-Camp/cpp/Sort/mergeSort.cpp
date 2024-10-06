#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn = 100;
int n;
void mergesort(int A[]){
    for(int step = 2; step / 2 <= n; step *= 2) {
        for(int i = 1; i <= n; i += step) {
            sort(A + i, A + min(i + step, n + 1));
        }
    }
}
int main() {
    int A[maxn];
    cin>> n;
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    mergesort(A);
    for(int i = 1; i <= n; i++) {
        cout << A[i] << " ";
    }
    return 0;
}