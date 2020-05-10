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
void inorder(Node* root){//�ǵݹ��������
    stack<Node*> s;
    s.push(root);
    int flag=0;
    while(!s.empty()){
        Node* topNode=s.top();
        if(topNode->left&&!flag){//����������
            s.push(topNode->left);
        }
        else{//�������Ѿ����ʽ�������ӡ���ֵ
            cout<<topNode->val<<" ";
            s.pop();
            
            if(topNode->right){//����������
                s.push(topNode->right);
                flag=0;
            }
            else{//�������״̬
                flag=1;
            }
        }
    }
}
void preorder(Node* root){//�ǵݹ�ǰ�����
    stack<Node*> s;
    s.push(root);
    int flag=0;
    while(!s.empty()){
        Node *topNode=s.top();
        if(flag==0)cout<<topNode->val<<" ";//���±����Ĺ����вŴ�ӡ���ڵ��ֵ
        if(topNode->left&&!flag){//����������
            s.push(topNode->left);
        }
        else{
            s.pop();//�������Ѿ�������
            if(topNode->right){//�����������ڣ�����������
                s.push(topNode->right);
                flag=0;
            }
            else{//����������״̬
                flag=1;
            }
        }
    }
}
void postorder(Node* root){//�ǵݹ�������
    stack<Node*> s;
    s.push(root);
    int flag=0;//��־�Ƿ��ڻ���״̬
    Node *last=NULL;
    while(!s.empty()){
        Node *topNode=s.top();

        if(topNode->left&&!flag){//���·������ӽڵ�
            s.push(topNode->left);
        }
        else{
            
            if(topNode->right&&topNode->right!=last){//���Ǵ����ӽڵ����������
                s.push(topNode->right);
                flag=0;
            }
            else{//��ʼ����״̬����ӡ��ǰ����ֵ��������ǰ���
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