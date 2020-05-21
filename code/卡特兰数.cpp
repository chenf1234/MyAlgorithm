/*问题描述：
 *有2*n人排成两排，要求每排站n个人，
 *每排身高都是从低到高排列，相对应的位置第2排的人要比第一排的1高，求所有的排列方式
 *所有的排列方式的总数为卡特兰数
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int ansnum=0;
void solve(vector<int> nums,int vis[],int count,vector<int> ans){
    if(count==nums.size()){
        ansnum++;
        cout<<"case: "<<ansnum<<endl;
        for(int i=0;i<nums.size();i+=2){
            printf("%-5d",ans[i]);
        }
        cout<<endl;
        for(int i=1;i<nums.size();i+=2){
            printf("%-5d",ans[i]);
        }
        cout<<endl<<endl;;
    }
    for(int i=0;i<nums.size();i++){
        if(vis[i]==1) continue;
        else{
           
            if(count%2==0){//偶数位是身高矮的
                if(count==0||(nums[i]>ans[count-2])){
                    vis[i]=1;
                    ans.push_back(nums[i]);
                    solve(nums,vis,count+1,ans);
                    vis[i]=0;
                    ans.pop_back();
                }

            }
            else{
                if(nums[i]>ans[count-1]){//比前一位要高
                    if((count>=2&&nums[i]>ans[count-2])||count==1){
                        vis[i]=1;
                        ans.push_back(nums[i]);
                        solve(nums,vis,count+1,ans);
                        vis[i]=0;
                        ans.pop_back();
                    }
                }
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    vector<int> nums;
    //for(int i=1;i<=n;i++)nums.push_back(i);
    cout<<"please input n person's height:"<<endl;
    for(int i=0;i<n;i++){
        int height;
        cin>>height;
        nums.push_back(height);
    }
    sort(nums.begin(),nums.end());
    int vis[n];
    vector<int> ans;
    memset(vis,0,sizeof(vis));
    solve(nums,vis,0,ans);
    cout<<"total number of the answer is "<<ansnum<<endl;
}