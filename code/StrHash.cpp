#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
const LL P=10000019;
#define MAXN 1010
LL powP[MAXN],hash1[MAXN],hash2[MAXN];
vector<pair<int,vector<int> > >pr1,pr2;
void init(int len){
    powP[0]=1;
    for(int i=1;i<=len;i++){
        powP[i]=(powP[i-1]*P)%MOD;
    }
}
void calH(LL H[],int len,string s){
    H[0]=0;
    for(int i=1;i<=len;i++){
        H[i]=(H[i-1]*P+s[i-1])%MOD;
    }
}
int calSubH(LL H[],int i,int j){
    
    return ((H[j]-H[i-1]*powP[j-i+1])%MOD+MOD)%MOD;
}
void SubH(LL H[],int len,vector<pair<int,vector<int> > >& pr){
    for(int i=0;i<len;i++){
        for(int j=i;j<len;j++){
            int val=calSubH(H,i+1,j+1);
            pr.push_back(make_pair(val,vector<int>({i,j})));
        }
    }
}   
vector<int> GetAns(){
    int ans=0;
    vector<int> pos;
    for(int i=0;i<pr1.size();i++){
        for(int j=0;j<pr2.size();j++){
            if(pr1[i].first==pr2[j].first){
                vector<int> tmp=pr1[i].second;
                if(tmp[1]-tmp[0]+1>ans){
                    //cout<<ans<<endl;
                    ans=tmp[1]-tmp[0]+1;
                    pos=tmp;
                }
            }
        }
    }
    return pos;
}

int main(){
    string s1,s2;
    cin>>s1>>s2;
    init(max(s1.length(),s2.length()));
    calH(hash1,s1.length(),s1);
    calH(hash2,s2.length(),s2);
    SubH(hash1,s1.length(),pr1);
    SubH(hash2,s2.length(),pr2);
    vector<int> ans=GetAns();
    int i=ans[1],j=ans[0];
    cout<<s1.substr(j,i-j+1)<<endl;
    return 0;
}