#include <iostream>
using namespace std;
struct Node{
    int data;
    Node *left;
    Node* right;
    Node(){
        data=0;
        left=NULL;
        right=NULL;
    }
};
void insert(Node* &root,int x){
    if(root==NULL){
        root=new Node();
        root->data=x;
        return;
    }
    if(x<=root->data){
        insert(root->left,x);
    }
    else insert(root->right,x);
}
int findmax(Node* root){
    if(root->right!=NULL){
        return findmax(root->right);
    }
    else return root->data;
}
int findmin(Node* root){
    while(root->left!=NULL){
        root=root->left;
    }
    return root->data;
}
void delete_node(Node* &root,int x){
    //cout<<root->data<<endl;
    if(root==NULL)return;
    if(x<root->data){
        delete_node(root->left,x);
    }
    else if(x>root->data){
        delete_node(root->right,x);
    }
    else{
        if(root->left==NULL&&root->right==NULL){

            root=NULL;
        }
        else if(root->left!=NULL){
            int val=findmax(root->left);
            //cout<<"max:"<<val<<endl;
            root->data=val;
            delete_node(root->left,val);
        }
        else{
            int val=findmin(root->right);
            //cout<<"min:"<<val<<endl;
            root->data=val;
            delete_node(root->right,val);
        }
    }
}
void print_tree(Node *root){
    if(root==NULL) return;
    cout<<root->data<<" ";
    print_tree(root->left);
    print_tree(root->right);
}
void find_k(Node *root,int &val,int &count,int k){
    if(root==NULL)return ;
    find_k(root->left,val,count,k);
    if(count==k)return;
    count++;
    if(count==k){
        val=root->data;
        return;
    }
    find_k(root->right,val,count,k);
    if(count==k)return ;
}
int main(){
    int m;
    Node *root=NULL;
    cin>>m;
    for(int i=0;i<m;i++){
        int t;
        cin>>t;
        insert(root,t);
    }
    print_tree(root);
    cout<<endl;
    int num;
    cin>>num;
    delete_node(root,num);
    print_tree(root);
    cout<<endl;
    int val=0;
    int count=0;
    find_k(root,val,count,5);
    cout<<val<<endl;
}