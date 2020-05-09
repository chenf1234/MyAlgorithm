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
int n;//�������
int inq[1001]={0};//�Ƿ��ڶ�����
int num[1001]={0};//��¼�����Ӵ���
bool SPFA(int s){
    queue<int> q;
    
    for(int i=0;i<n;i++)pre[i]=i;
    inq[s]=1;
    num[s]++;
    fill(d,d+n,INF);
    d[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        inq[u]=0;
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i].v;
            //cout<<"v:"<<v<<endl;
            int dis=graph[u][i].dis;
            if(d[u]+dis<d[v]){
                //cout<<"yes "<<v<<endl;
                d[v]=d[u]+dis;
                pre[v]=u;
                if(!inq[v]){
                    q.push(v);
                    inq[v]=1;
                    num[v]++;
                    if(num[v]>=n)return false;
                }
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
    int m;//�ߵ�����
    int s;//���
    scanf("%d%d%d",&n,&m,&s);
    
    for(int i=0;i<m;i++){
        int begin,next,dis;
        scanf("%d%d%d",&begin,&next,&dis);
        graph[begin].push_back(Node(next,dis));
        //graph[next].push_back(Node(begin,dis));
    }
    if(SPFA(s)){
        for(int i=0;i<n;i++){
            printf("%d : %d\n",i,d[i]);
            print_path(i);
            printf("\n");
        }
    }
    //printf("\n");
}