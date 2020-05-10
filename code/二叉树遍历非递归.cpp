#include <iostream>
#include <stack>
using namespace std;
struct Node{
    int val;
    Node* left,*right;
    Node(int val){
        this->val=val;
        left=right=NULL;
    }  
    Node(){
        this->val=0;
        left=right=NULL;
    }
};
void inorder(Node* root){//非递归中序遍历
    stack<Node*> s;
    s.push(root);
    int flag=0;
    while(!s.empty()){
        Node* topNode=s.top();
        if(topNode->left&&!flag){//访问左子树
            s.push(topNode->left);
        }
        else{//左子树已经访问结束，打印结点值
            cout<<topNode->val<<" ";
            s.pop();
            
            if(topNode->right){//访问右子树
                s.push(topNode->right);
                flag=0;
            }
            else{//进入回溯状态
                flag=1;
            }
        }
    }
}
void preorder(Node* root){//非递归前序遍历
    stack<Node*> s;
    s.push(root);
    int flag=0;
    while(!s.empty()){
        Node *topNode=s.top();
        if(flag==0)cout<<topNode->val<<" ";//向下遍历的过程中才打印根节点的值
        if(topNode->left&&!flag){//访问左子树
            s.push(topNode->left);
        }
        else{
            s.pop();//左子树已经访问完
            if(topNode->right){//若右子树存在，遍历右子树
                s.push(topNode->right);
                flag=0;
            }
            else{//否则进入回溯状态
                flag=1;
            }
        }
    }
}
void postorder(Node* root){//非递归后序遍历
    stack<Node*> s;
    s.push(root);
    int flag=0;//标志是否处于回溯状态
    Node *last=NULL;
    while(!s.empty()){
        Node *topNode=s.top();

        if(topNode->left&&!flag){//向下访问左子节点
            s.push(topNode->left);
        }
        else{
            
            if(topNode->right&&topNode->right!=last){//不是从右子节点回溯上来的
                s.push(topNode->right);
                flag=0;
            }
            else{//开始回溯状态，打印当前结点的值，弹出当前结点
                s.pop();
                cout<<topNode->val<<" ";
                //last=topNode;
                flag=1;
            }
        }
        last=topNode;
    }
}
int main(){
    Node* root=new Node(1);
    root->left=new Node(2);
    root->left->left=new Node(3);
    root->left->right=new Node(4);
    root->left->left->right=new Node(5);
    root->left->left->right->left=new Node(9);
    //root->left->left->left=new Node(9);
    root->right=new Node(6);
    root->right->left=new Node(8);
    root->right->right=new Node(7);
    inorder(root);cout<<endl;
    preorder(root);cout<<endl;
    postorder(root);cout<<endl;
    return 0;
}