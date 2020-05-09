#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node{
    int v;
    int weight;
    Node(int v,int dis){
        this->v=v;
        this->weight=dis;
    }
    Node(){}
};
vector<Node> child[1001];
struct Edge{
    int u,v;
    int weight;
    Edge(){}
    Edge(int u,int v,int edge){
        this->u=u;
        this->v=v;
        this->weight=edge;
    }
    bool operator <(const Edge &e){
        return weight<e.weight;
    }
};
vector<Edge> e;
int n,m;
int father[1001];
int find_father(int a){
    int x=a;
    while(x!=father[x]){
        x=father[x];
    }
    //路径压缩
    while(a!=father[a]){
        int tmp=a;
        a=father[a];
        father[tmp]=x;
    }
    return x;
}
int Kruskal(int begin){
    sort(e.begin(),e.end());
    //cout<<e[1].weight<<endl;
    int cur_num=0;
    int ans=0;
    for(int i=0;i<n;i++){
        father[i]=i;
    }
    for(int i=0;i<m;i++){
        Edge cur=e[i];
        int fau=find_father(cur.u);
        int fav=find_father(cur.v);
        //cout<<cur.u<<" "<<cur.v<<" "<<cur.weight<<endl;
        if(fav!=fau){
            cur_num++;
            ans+=cur.weight;
            father[fau]=fav;
            
            child[cur.u].push_back(Node(cur.v,cur.weight));
            child[cur.v].push_back(Node(cur.u,cur.weight));
            
            if(cur_num==n-1)break;
        }
    }
    if(cur_num==n-1) return ans;
    else return -1;
}
struct Tree{
    int id;
    int weight;//最小生成树的该节点的父节点到该节点的边权
    int child_num;//子节点数量
    vector<Tree *> child;
    Tree(){
        id=0;
        weight=0;
        child_num=0;
        child.clear();
    }
};
int inq[1001];//构建树时，标明该节点是否被处理过
void create_tree(int s,int w,Tree* &root){
    root=new Tree();
    root->id=s;
    root->weight=w;
    int num=0;
    inq[s]=1;
    for(int i=0;i<child[s].size();i++){
        if(!inq[child[s][i].v]){
            root->child.push_back(NULL);
            create_tree(child[s][i].v,child[s][i].weight,root->child[num]);
            num++;
        }
    }
    root->child_num=num;
}
void print_tree(Tree * root){
    int num=root->child_num;
    cout<<root->id<<" "<<root->weight<<endl;
    if(num==0) return ;
    for(int i=0;i<num;i++){
        cout<<root->id<<" ";
        print_tree(root->child[i]);
    }
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        e.push_back(Edge(u,v,w));
    }
    // cout<<endl;
    // for(int i=0;i<m;i++){
    //     cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].weight<<endl;
    // }
    cout<<Kruskal(0)<<endl;
    Tree* root=NULL;
    create_tree(0,0,root);
    cout<<"0 ";
    print_tree(root);
}