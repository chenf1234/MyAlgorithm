#include <iostream>
using namespace std;
void ShellSort(int a[],int n){
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=gap;i<n;i++){
            int tmp=a[i];
            int j=i;
            while(j>=gap&&tmp<a[j-gap]){
                a[j]=a[j-gap];
                j-=gap;
            }
            a[j]=tmp;
        }
    }
}
void ShellSort1(int a[],int n){
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=0;i<gap;i++){
            for(int j=i+gap;j<n;j+=gap){
                int tmp=a[j];
                int k=j;
                while(k>=gap&&tmp<a[k-gap]){
                    a[k]=a[k-gap];
                    k-=gap;
                }
                a[k]=tmp;
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++) cin>>a[i];
    ShellSort1(a,n);
    for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
}