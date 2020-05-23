#include <iostream>
using namespace std;
struct Node{
    int val;
    Node* left,*right;
    Node(int v=0){
        val=v;
        left=right=NULL;
    }
};

Node* findpreNode(Node* root){//寻找前序结点
    Node* preNode=root->left;
    if(preNode){
        //右子结点等于当前结点时要停止
        while(preNode->right&&preNode->right!=root){
            preNode=preNode->right;
        }
        return preNode;
    }
    return NULL;

}

void MorrisInorderTraverse(Node* root){//中序遍历
    while(root){
        if(root->left==NULL){//没有左子结点，打印当前结点的值,进入右自节点
            cout<<root->val<<" ";
            root=root->right;

        }
        else{
            Node* preNode=findpreNode(root);
            //前序结点的右节点为空，设置前序结点的右节点为当前结点，并进入当前结点的左子结点
            if(preNode->right==NULL){
                preNode->right=root;
                root=root->left;
            }
            //否则，打印当前结点，断开前序结点的右连接，并进入当前结点的右子结点
            else if(preNode->right==root){
                cout<<root->val<<" ";
                preNode->right=NULL;
                root=root->right;
            }
        }
    }
}

void MorrisPreorderTraverse(Node* root){//前序遍历
    while(root){
        if(root->left==NULL){//没有左子结点，打印当前结点的值,进入右自节点
            cout<<root->val<<" ";
            root=root->right;

        }
        else{
            Node* preNode=findpreNode(root);
            //前序结点的右节点为空，设置前序结点的右节点为当前结点，并进入当前结点的左子结点
            if(preNode->right==NULL){
                cout<<root->val<<" ";
                preNode->right=root;
                root=root->left;
            }
            //否则，打印当前结点，断开前序结点的右连接，并进入当前结点的右子结点
            else if(preNode->right==root){
                
                preNode->right=NULL;
                root=root->right;
            }
        }
    }
}

int main(){
    Node* root=new Node(5);
    root->left=new Node(3);
    root->right=new Node(7);
    root->left->left=new Node(2);
    root->left->right=new Node(4);
    root->right->right=new Node(9);
    root->right->right->left=new Node(8);
    root->right->right->right=new Node(10);
    MorrisInorderTraverse(root);
    printf("\n");
    MorrisPreorderTraverse(root);
    printf("\n");
}
