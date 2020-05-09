#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f
using namespace std;
struct Tree_node{
    int node_id;
    int weight;//最小生成树的该节点的父节点到该节点的边权
    Tree_node(){}
    Tree_node(int id,int w){
        node_id=id;
        weight=w;
    }
};
vector<Tree_node> graph[1001];
int pre[1001]={};
int vis[1001]={0};
int d[1001]={};
int n;//节点数量
int m;//边的条数
struct Tree{
    int id;
    int child_num;//子节点数量
    vector<Tree *> child;
    Tree(){
        id=0;
        child_num=0;
        child.clear();
    }
};
int prim(int s){
    for(int i=0;i<n;i++) pre[i]=i;
    fill(d,d+n,INF);
    d[s]=0;
    int ans=0;
    for(int i=0;i<n;i++){
        int u=-1,MIN=INF;
        for(int j=0;j<n;j++){
            if(d[j]<MIN&&vis[j]==0){
                MIN=d[j];
                u=j;
            }
        }
        if(u==-1) return ans;
        ans+=d[u];
        vis[u]=1;
        for(int j=0;j<graph[u].size();j++){
            int cur=graph[u][j].node_id;
            int cur_dis=graph[u][j].weight;
            if(cur_dis<d[cur]&&vis[cur]==0){
                d[cur]=cur_dis;
                pre[cur]=u;
            }

        }
    }
    return ans;
}
void create(int s,Tree* &root,vector<int> t[]){
    int num=0;
    root=new Tree();
    root->id=s;
    //cout<<s<<endl;
    for(int i=0;i<t[s].size();i++){
        //root->child[num]=new Tree();
        root->child.push_back(NULL);
        create(t[s][i],root->child[num],t);
        num++;
    }
    root->child_num=num;
}
Tree* create_tree(int s){
    vector<int> t[n];
    for(int i=0;i<n;i++){
        //cout<<pre[i]<<" "<<i<<endl;
        if(pre[i]!=i){
            t[pre[i]].push_back(i);//构造出所有子节点
        }
    }
    Tree *root;
    create(s,root,t);
    return root;
}
void print_tree(Tree *root){
    int num=root->child_num;
    cout<<root->id<<endl;
    if(num==0) return ;
    for(int i=0;i<num;i++){
        print_tree(root->child[i]);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    
    for(int i=0;i<m;i++){
        int begin,next,dis;
        scanf("%d%d%d",&begin,&next,&dis);
        graph[begin].push_back(Tree_node(next,dis));
        graph[next].push_back(Tree_node(begin,dis));
    }
    
    cout<<prim(0)<<endl;
    Tree* root=create_tree(0);
    print_tree(root);
    return 0;
}