#include <iostream>
using namespace std;
typedef enum{
    Red,Black
}Colors;
struct Node{
    Colors color;
    Node* parent;
    Node* left,*right;
    int val;
    Node(int val=0,Node* p=NULL){
        this->val=val;
        this->color=Red;
        this->parent=p;
        this->left=this->right=NULL;
    }
};
void L(Node*& mroot,Node* root){
    Node* parent=root->parent;
    Node* tmp=root->right;
    root->right=tmp->left;
    if(tmp->left!=NULL)
        tmp->left->parent=root;
    tmp->left=root;
    root->parent=tmp;
    if(parent!=NULL){
        if(parent->left==root){
            parent->left=tmp;
        }
        else parent->right=tmp;
    }
    else mroot=tmp;
    root=tmp;
    root->parent=parent;
    
    
}
void R(Node*& mroot,Node* root){
    Node* parent=root->parent;
    Node* tmp=root->left;
    root->left=tmp->right;
    if(tmp->right!=NULL)
        tmp->right->parent=root;
    tmp->right=root;
    root->parent=tmp;
    if(parent!=NULL){
        if(parent->left==root){
            parent->left=tmp;
        }
        else parent->right=tmp;
    }
    else mroot=tmp;
    root=tmp;
    root->parent=parent;
}
void insertFix(Node*& mroot,Node* root){
    
    if(root->parent&&root->parent->color==Black){
        mroot->color=Black;
        return;
    }//父结点为黑色，无需修正
    else if(root->parent){//存在父结点，且为红色
        
        Node* f=root->parent;
        Node* g=f->parent;
        if(g->left==f){
            Node* s=g->right;//叔叔结点
            if(s&&s->color==Red){//当叔叔结点也是红色时，将父结点、叔叔结点设置为黑色，祖父节点设置为红色，
                f->color=Black;//将祖父节点设置为当前结点重新修正
                s->color=Black;
                g->color=Red;
                insertFix(mroot,g);
            }
            else{//叔叔结点为黑色
                if(f->right==root){//当前结点是父结点的右孩子
                    L(mroot,f);//以父结点设置为当前结点，进行左旋
                    insertFix(mroot,f);//重新修正
                }
                else{//当前结点是父结点的左孩子
                    f->color=Black;//父结点设置为黑色，祖父节点设置为红色，以祖父节点进行右旋
                    g->color=Red;
                    R(mroot,g);
                }
            }
        }
        else{//上面的镜像
            
            Node* s=g->left;
            if(s&&s->color==Red){
                f->color=Black;
                s->color=Black;
                g->color=Red;
                insertFix(mroot,g);
            }
            else{
                
                if(f->left==root){
                    R(mroot,f);
                    insertFix(mroot,f);
                }
                else{
                    f->color=Black;
                    g->color=Red;
                    L(mroot,g);

                }
            }
        }
    }
    mroot->color=Black;
}
void insert(Node*& mroot,Node* root,int val){
    if(mroot==NULL){//第一个插入节点
        mroot=new Node(val);
        mroot->color=Black;
        return;
    }
    else{
        if(val<=root->val){
            if(root->left==NULL){
                
                root->left=new Node(val,root);
                
                insertFix(mroot,root->left);
            }
            else{
                insert(mroot,root->left,val);
            }
        }
        else{
            if(root->right==NULL){
                
                root->right=new Node(val,root);

                insertFix(mroot,root->right);
            }
            else {
                insert(mroot,root->right,val);
            }
        }
    }
}
Node* search(Node* root,int val){
    if(root==NULL) return NULL;
    if(root->val==val)return root;
    else if(root->val<val) return search(root->left,val);
    else return search(root->right,val);
}
void removeFix(Node* &root,Node* child,Node* parent){
    Node* sibling=NULL;
    while((!child||child->color==Black)&&child!=root){
        if(parent->left==child){//左子结点
            sibling=parent->right;
            if(sibling->color==Red){//case1:兄弟结点为红色
                sibling->color=Black;
                parent->color=Red;
                L(root,parent);
                sibling=parent->right;
                //兄弟结点设置为黑色，父结点设置为红色，对父结点左旋
                //左旋后，重新设置x的兄弟结点，即可转换为case2\3\4
            }//注意，左旋后，兄弟集结点一定变成黑色
            if((!sibling->left||sibling->left->color==Black)&&(!sibling->right||sibling->right->color==Black)){
                //case2:兄弟结点w是黑色，w的两个孩子都是黑色的
                sibling->color=Red;
                child=parent;
                parent=parent->parent;
                //x的兄弟结点设置为红色，x的父结点设置为新的x结点
            }
            else{
                if(!sibling->right||sibling->right->color==Black){
                    //case3:x的兄弟结点是黑色的，并且x的左孩子是红色，右孩子是黑色的
                    sibling->left->color=Black;
                    sibling->color=Red;
                    R(root,sibling);
                    sibling=parent->right;
                    //将x的兄弟结点的左孩子设置为黑色，x的兄弟结点设置为红色
                    //x的兄弟结点进行右旋，右旋后，重新设置x的兄弟结点
                }
                //case4:x的兄弟结点是黑色，x兄弟结点的右孩子是红色，左孩子颜色任意
                sibling->color=parent->color;//将x的父结点颜色赋给x的兄弟结点
                parent->color=Black;//x的父结点的颜色设置为黑色
                sibling->right->color=Black;//x的兄弟结点的右子结点颜色设置为黑色
                L(root,parent);//x的父结点进行旋转
                child=root;//设置x为根节点
                break;
            }
        }
        else{//上面的镜像
            sibling=parent->left;
            if(sibling->color==Red){
                sibling->color=Black;
                parent->color=Red;
                R(root,parent);
                sibling=parent->right;
            }
            if((!sibling->left||sibling->left->color==Black)&&(!sibling->right||sibling->right->color==Black)){
                sibling->color=Red;
                child=parent;
                parent=parent->parent;
            }
            else{
                if(!sibling->left||sibling->left->color==Black){
                    //case3:x的兄弟结点是黑色的，并且x的左孩子是黑色，右孩子是红色的
                    sibling->right->color=Black;
                    sibling->color=Red;
                    L(root,sibling);
                    sibling=parent->left;
                    
                }
                sibling->color=parent->color;
                parent->color=Black;
                sibling->left->color=Black;
                R(root,parent);
                child=root;
                break;
            }
        }
    }
    if(child)child->color=Black;
}
void removeNode(Node* &root,Node* del){
    if(del->left!=NULL&&del->right!=NULL){
        //将右子树的最小结点作为替换结点
        Node* replace=del->right;
        while(replace->left!=NULL){
            replace=replace->left;
        }
        del->val=replace->val;
        removeNode(root,replace);//删除该替换结点
        return;
    }
    else{
        Node* child,*father;
        Colors c;//被删除结点的颜色
        child=(del->left==NULL)?del->left:del->right;
        father=del->parent;
        c=del->color;
        if(child)
            child->parent = father;
        if(father){
            if(father->left==del){
                father->left=child;
            }
            else father->right=child;
        }
        else root=child;//删除的是根节点
    
        if(c==Black){//删除的是黑结点时，平衡被破坏
            removeFix(root,child,father);
        }
        delete del;
    }
}
void removeVal(Node*& root,int val){
    Node* del=search(root,val);
    if(del){
        removeNode(root,del);
    }
}
void printval(string s,Node* root){
    cout<<s<<" : ";
    if(root==NULL){
        cout<<"NULL"<<endl;
        return;
    }
    else{
        cout<<root->val<<" , ";
    }
    cout<<"color : ";
    if(root->color==Red) cout<<"red"<<endl;
    else cout<<"black"<<endl;
}
void inorder(Node* root){
    if(root==NULL) return;
    inorder(root->left);
    printval("val",root);
    printval("parent",root->parent);
    printval("left",root->left);
    printval("right",root->right);
    cout<<endl;
    inorder(root->right);

}
int main(){
    int n;
    cin>>n;
    int a[n];
    Node* root=NULL;
    for(int i=0;i<n;i++){
        cin>>a[i];
        insert(root,root,a[i]);
        
        //inorder(root);
    }
    removeVal(root,4);
    inorder(root);
    return 0;

}