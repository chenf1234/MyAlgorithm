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
int inDegree[1001]={0};//���
int ve[1001]={0};//�¼����翪ʼʱ��
int vl[1001];//�¼���ٿ�ʼʱ��
stack<int> topOrder;//�������¼���ٷ���ʱ��
vector<Node> graph[1001];
int n,m;//n-��������m-�ߵ�����
bool topLogicSort(){
    queue<int> q;
    for(int i=0;i<n;i++){
        if(inDegree[i]==0){//Ѱ�����Ϊ0�Ľ��
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
            }//���¼�v���翪ʼʱ�䣬ȡve[u]+w[u->v]�����ֵ
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
            }//���¼�u����ٷ���ʱ�䣬ȡvl[v]-w[u->v]����Сֵ
        }
    }
    for(int i=0;i<n;i++){
        //���������緢��ʱ��e����ٷ���ʱ��l��e=l�Ļ�ڹؼ�·����
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