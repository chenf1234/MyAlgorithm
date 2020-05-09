#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<cstring>
using namespace std;
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
int inDegree[1001]={0};//入度
int ve[1001]={0};//事件最早开始时间
int vl[1001];//事件最迟开始时间
stack<int> topOrder;//用于求事件最迟发生时间
vector<Node> graph[1001];
int n,m;//n-顶点数，m-边的条数
bool topLogicSort(){
    queue<int> q;
    for(int i=0;i<n;i++){
        if(inDegree[i]==0){//寻找入度为0的结点
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        topOrder.push(u);
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i].v;
            int w=graph[u][i].dis;
            if(ve[u]+w>ve[v]){
                ve[v]=ve[u]+w;
            }//求事件v最早开始时间，取ve[u]+w[u->v]的最大值
            inDegree[v]--;
            if(inDegree[v]==0)q.push(v);
        }
    }
    if(topOrder.size()==n)return true;
    else return false;
}
int criticalpath(){
    memset(ve,0,sizeof(ve));
    if(!topLogicSort()){
        return -1;
    }
    int MAX=0;
    for(int i=0;i<n;i++){
        if(ve[i]>MAX) MAX=ve[i];
    }
    fill(vl,vl+n,MAX);
    while(!topOrder.empty()){
        int u=topOrder.top();
        topOrder.pop();
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i].v;
            int w=graph[u][i].dis;
            if(vl[u]>vl[v]-w){
                vl[u]=vl[v]-w;
            }//求事件u的最迟发生时间，取vl[v]-w[u->v]的最小值
        }
    }
    for(int i=0;i<n;i++){
        //计算活动的最早发生时间e和最迟发生时间l；e=l的活动在关键路径上
        int e=ve[i];
        for(int j=0;j<graph[i].size();j++){
            int l=vl[graph[i][j].v]-graph[i][j].dis;
            if(e==l){
                printf("%d -> %d\n",i,graph[i][j].v);
            }
        }
    }
    return MAX;
}
int main(){
    scanf("%d%d",&n,&m);
    
    for(int i=0;i<m;i++){
        int begin,next,dis;
        scanf("%d%d%d",&begin,&next,&dis);
        graph[begin].push_back(Node(next,dis));
        inDegree[next]++;
    }
    cout<<criticalpath()<<endl;
}