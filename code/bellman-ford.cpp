#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
#define INF 0x3f3f3f3f
struct Node {
    int v;
    int dis;
    Node(int v,int dis){
        this->v=v;
        this->dis=dis;
    }
    Node(){}
    friend bool operator <(const Node&  m,const Node& n){
        return m.dis>n.dis;
    }
};
vector<Node> graph[1001];
int pre[1001];
int d[1001]={};
int n;//顶点个数
bool Bellman_Ford(int s){
    fill(d,d+n,INF);
    d[s]=0;
    for(int i=0;i<n;i++){
        pre[i]=i;
    }
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<graph[j].size();k++){
                int next=graph[j][k].v;
                int dis=graph[j][k].dis;
                if(d[j]+dis<d[next]){
                    d[next]=d[j]+dis;
                    pre[next]=j;
                }
            }
        }
    }
    //判断负环
    for(int j=0;j<n;j++){
        for(int k=0;k<graph[j].size();k++){
            int next=graph[j][k].v;
            int dis=graph[j][k].dis;
            if(d[j]+dis<d[next]){
                return false;
            }
        }
    }
    return true;
}
void print_path(int s){
    if(pre[s]==s){
        printf("%d",s);
        return;
    }
    print_path(pre[s]);
    printf("->%d",s);
}
int main(){
    int m;//边的条数
    int s;//起点
    scanf("%d%d%d",&n,&m,&s);
    
    for(int i=0;i<m;i++){
        int begin,next,dis;
        scanf("%d%d%d",&begin,&next,&dis);
        graph[begin].push_back(Node(next,dis));
        //graph[next].push_back(Node(begin,dis));
    }
    if(Bellman_Ford(s)){
        for(int i=0;i<n;i++){
            printf("%d : %d\n",i,d[i]);
            print_path(i);
            printf("\n");
        }
    }
    //printf("\n");
}