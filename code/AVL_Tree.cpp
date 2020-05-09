#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct Node{
    int weight;
    int height;
    Node *left;
    Node *right;
    
};
int n,k;
Node *newNode(int val){
    Node *n=new Node;
    n->weight=val;
    n->height=1;
    n->left=NULL;
    n->right=NULL;
    return n;
}
int getHeight(Node *root){
    if(root==NULL)return 0;
    else return root->height;
}
void updateheight(Node* root){
    root->height=max(getHeight(root->left),getHeight(root->right))+1;
}
int get(Node* root){
    return getHeight(root->left)-getHeight(root->right);
}
Node *L(Node* root){
    Node *tmp=root->right;
    root->right=tmp->left;
    tmp->left=root;
    updateheight(root);
    updateheight(tmp);
    root=tmp;
    return root;
}
Node *R(Node *root){
    Node* tmp=root->left;
    root->left=tmp->right;
    tmp->right=root;
    updateheight(root);
    updateheight(tmp);
    root=tmp;
    return root;
}
Node *insert(Node* root,int val){
    if(root==NULL){
        root=newNode(val);
        return root;
    }
    if(val>root->weight){
        //cout<<"left "<<val<<endl;
        root->right=insert(root->right,val);
        updateheight(root);
        if(get(root)==-2){
            if(get(root->right)==1){
                root->right=R(root->right);
                root=L(root);
            }
            else if(get(root->right)==-1){
                root=L(root);
            }
        }
    }
    else {
        root->left=insert(root->left,val);
        updateheight(root);
        if(get(root)==2){
            if(get(root->left)==1){
                root=R(root);
            }
            else if(get(root->left)==-1){
                root->left=L(root->left);
                root=R(root);
            }
        }
    }
    return root;
}
bool search(Node *root,int val){
    if(root==NULL) return false;
    if(root->weight==val) return true;
    else if(val<root->weight){
        return search(root->left,val);
    }
    else return search(root->right,val);
}
void in(Node *root){
    if(root==NULL) return;
    printf("%d ",root->weight);
    in(root->left);
    in(root->right);
}
int main(){
    scanf("%d %d",&n,&k);
    Node *root=NULL;
    for(int i=0;i<n;i++){
        int t;
        scanf("%d",&t);
        root=insert(root,t);
    }
    vector<int> v;
    for(int i=0;i<k;i++){
        int t;
        scanf("%d",&t);
        v.push_back(search(root,t));

    }
    //  in(root);
    //  printf("\n");
    for(int i=0;i<k;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}
