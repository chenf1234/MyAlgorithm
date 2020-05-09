#include<iostream>
#include<vector>
using namespace std;
vector<int> factor={0};//实现最小堆

void upAdjust(int l,int r){
    int i=r,j=r/2;
    while(j>=l){
        if(factor[j]>=factor[i]){
            swap(factor[j],factor[i]);
            i=j;
            j=i/2;
        }
        else break;
    }
}
void downAdjust(int l,int r){
    int i=l,j=2*l;
    while(j<=r){
        if(j+1<=r&&factor[j+1]<factor[j]){
            j=j+1;
        }
        if(factor[j]<factor[i]){
            swap(factor[j],factor[i]);
            i=j;
            j=2*i;
        }
        else break;
    }
}
void insert(int t){
    factor.push_back(t);
    upAdjust(1,factor.size()-1);
}
void delete_heap(){
    swap(factor[factor.size()-1],factor[1]);
    factor.pop_back();
    downAdjust(1,factor.size()-1);
}
void create_heap(){
    int size=factor.size()-1;
    for(int i=size/2;i>=1;i--){
        downAdjust(i,size);
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int t;
        cin>>t;
        //insert(t);
        factor.push_back(t);
    }
    create_heap();
    // for(int i=1;i<=n;i++){
    //     cout<<factor[i]<<" ";
    // }
    // cout<<endl;
    for(int i=1;i<=n;i++){

        cout<<factor[1]<<" ";
        delete_heap();
    }
    cout<<endl;
}