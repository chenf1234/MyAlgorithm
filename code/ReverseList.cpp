/**
 *双向环形链表反转 
 **/
#include <iostream>
using namespace std;
struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
    Node(int d=0){
        data=d;
        next=NULL;
        prev=NULL;
    }
};
Node* createNode(int val){
    Node* n=new Node(val);
    return n;
}
void destroyNode(Node *root){
    delete root;
}
Node* insertNode(int val,Node* root){
    Node *tmp=new Node(val);
    Node *prev=root->prev;
    Node *next=root;
    prev->next=tmp;
    tmp->prev=prev;
    tmp->next=next;
    next->prev=tmp;
    return tmp;
}
void deleteNode(Node *root){
    Node *prev=root->prev;
    Node *next=root->next;
    prev->next=next;
    next->prev=prev;
    destroyNode(root);
}
Node *reverse(Node* root){
    if(root->next==root)return root;//空链表
    Node* end=root->prev;
    Node* left=root->prev;
    Node* cur=root;
    while(cur!=end){
        //cout<<cur->data<<endl;
        Node *right=cur->next;
        cur->next=left;
        cur->prev=right;
        left=cur;
        cur=right;
    }
    Node *right=cur->next;
    cur->next=left;
    cur->prev=right;
    return cur;
}
int main(){
    Node* root=createNode(0);
    root->next=root;
    root->prev=root;
    
    for(int i=0;i<=6;i++){
        insertNode(i,root);
    }
    Node* tmp=root->next;
    while(tmp!=root){
        cout<<tmp->data<<" ";
        tmp=tmp->next;
    }
    cout<<endl;
    root=reverse(root->next);
     tmp=root->next;
    while(tmp!=root){
        cout<<tmp->data<<" ";
        tmp=tmp->next;
    }
    cout<<endl;
    return 0;
}