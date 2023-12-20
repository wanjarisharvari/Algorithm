# include <iostream>
# include <cstdlib>
using namespace std;

struct node {
    int data;
    struct node* right;
    struct node* left;
};

struct node* newnode(int data){
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->data = data ;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preorder(struct node* node, int level){
    if(node==NULL) return;
    cout<<node->data<<" "<<"["<<level<<"]"<<" ";
    preorder(node->left,level+1);
    preorder(node->right,level+1);
}

struct node* search(struct node* root , int num){
    if(root == NULL || root->data == num) return root;
    if(num<root->data) return search(root->left,num);
    else return search(root->right,num);
}

struct node* insert(struct node* node, int num){
    if(node==NULL) return newnode(num);
    if(num<node->data) node->left=insert(node->left,num);
    else if (num>node->data) node->right=insert(node->right,num);
    else cout<<"node is present";
    return node;
}

int getmax(struct node* node){
    while(node->right!=NULL) node=node->right;
    return node->data;
}

struct node* getmin(struct node* node){
    if(node->left != NULL) return getmin(node->left);
    else return node;
}

struct node* del(struct node* node,int key){
    if(search(node,key) == NULL)  cout<<"the key is not present";
    else{
    if(node==NULL) return NULL;
    if(key<node->data) node->left=del(node->left,key);
    if(key>node->data) node->right=del(node->right,key);
    else{
        if(node->left==NULL && node->right==NULL){
            free(node); 
            return NULL;
        }
        else if(node->left==NULL && node->right!=NULL){
            struct node* temp = node->right;
            free(node);
            return temp;
        }
        else if(node->left!=NULL && node->right==NULL){
            struct node* temp = node->left;
            free(node);
            return temp;
        }
        else{
            struct node* temp = getmin(node->right);
            node->data=temp->data;
            node->right = del(node->right, temp->data);

        }
    }
    return node;
    }
}

int main(){
    int arr[] = {5,7,9,-7,-15,9};
    /*struct node* root = newnode(arr[0]);
    insert(root,5);
    preorder(root,0);
    cout<<endl;
    insert(root,7);
    preorder(root,0);
    cout<<endl;
    insert(root,9);
    preorder(root,0);
    cout<<endl;
    del(root,7);
    preorder(root,0);
    cout<<endl;
    del(root,15);
    preorder(root,0);*/

    return 0;
}