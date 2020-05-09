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
int vis[1001]={};
vector<Node> graph[1001];
int pre[1001];
int d[1001]={};
int n;//顶点个数
void Dijkstra(int s){
   
    for(int i=0;i<n;i++){
        pre[i]=i;
    }
    fill(d,d+1001,INF);
    d[s]=0;
    priority_queue<Node> q;
    q.push(Node(s,0));
    for(int i=0;i<n;i++){
        Node cur;
        while(!q.empty()){
            cur=q.top();
            q.pop();
            if(vis[cur.v]==0)break;
        }//寻找第一个为访问过的距离最小点
        if(vis[cur.v]==1)return;//最小点不存在，此时优先队列为空，剩余的未访问的点不可达，返回
        vis[cur.v]=1;
        for(int j=0;j<graph[cur.v].size();j++){
            int next=graph[cur.v][j].v;
            int dis=graph[cur.v][j].dis;
            if(vis[next]==0&&cur.dis+dis<d[next]){
                d[next]=cur.dis+dis;
                q.push(Node(next,d[next]));
                pre[next]=cur.v;
            }
        }
    //     int cur=-1,MIN=INF;
    //     for(int j=0;j<n;j++){
    //         if(vis[j]==0&&d[j]<MIN){
    //             cur=j;
    //             MIN=d[j];
    //         }
    //     }
    //     if(cur==-1)return ;
    //     vis[cur]=1;
    //     for(int j=0;j<graph[cur].size();j++){
    //         int next=graph[cur][j].v;
    //         int dis=graph[cur][j].dis;
    //         if(vis[next]==0&&MIN+dis<d[next]){
    //             d[next]=MIN+dis;
    //             pre[next]=cur;
    //         }
    //     }
    }
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
    }
    
    Dijkstra(s);
    for(int i=0;i<n;i++){
        printf("%d : %d\n",i,d[i]);
        print_path(i);
        printf("\n");
    }
    printf("\n");
}