#include <iostream>
#include <cstring>
using namespace std;
int Next[1010];
void getNext(string s,int len){
    Next[0]=-1;
    int j=-1;
    for(int i=1;i<len;i++){
        while(j!=-1&&s[i]!=s[j+1]){
            j=Next[j];
        }
        if(s[i]==s[j+1]){
            j++;
        }
        Next[i]=j;
    }
}
int KMP(string s,string p){
    int ans=0;
    int len=s.length();
    int m=p.length();
    int j=-1;
    for(int i=0;i<len;i++){
        while(j!=-1&&s[i]!=p[j+1]){
            j=Next[j];
        }
        if(s[i]==p[j+1]){
            j++;
        }
        if(j==m-1){
            ans++;
            j=Next[j];
        }
    }
    return ans;
}
int main(){
    string s,p;
    cin>>s>>p;
    getNext(p,p.length());
    int ans=KMP(s,p);
    cout<<ans<<endl;
    return 0;
}