#include <bits/stdc++.h>

using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;

    Node(int x){
        data = x;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node* root){
    if (root == NULL){
        return 0;
    }
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalance(Node* root){
    if (root == NULL){
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);  
}

Node* rootateRight(Node* y){
    Node* x = y->left;
    Node* z = x->right;
    x->right = y;
    y->left = z;
    return x; 
}

Node* rootateLeft(Node* x){
    Node* y = x->right;
    Node* z = x->left;
    y->left = x;
    x->right = z;
    return y;
}

Node* insertNode(Node* root, int data){
    if (root == NULL){
        return new Node(data);
    }
    if (root->data > data){
        root->left = insertNode(root->left, data);
    }
    else if (root->data <= data){
        root->right = insertNode(root->right, data);
    }
    // can bang
    int bf = getBalance(root);
    if (bf > 1 && data < root->left->data){
        return rootateRight(root);
    }
    if (bf < -1 && data >= root->right->data){
        return rootateLeft(root);
    }
    if (bf > 1 && data >= root->left->data){
        root->left = rootateLeft(root->left);
        return rootateRight(root);
    }
    if (bf < -1 && data < root->right->data){
        root->right = rootateRight(root->right);
        return rootateLeft(root);
    }
    return root;
}

Node* minNode(Node* root){
    Node* tmp = root;
    while (tmp != NULL && tmp->left != NULL){
        tmp = tmp->left;
    }
    return  tmp;
}

Node* deleteNode(Node* root, int data){
    if (root == NULL) return root;
    if (root->data > data){
        root->left = deleteNode(root->left, data);
    }
    else if (root->data < data){
        root->right = deleteNode(root->right, data);
    }
    else {
        if (root->right == NULL){
            Node* tmp = root->left;
            delete root;
            return tmp;
        }
        else if (root->left == NULL){
            Node* tmp = root->right;
            delete root;
            return tmp;
        }
        else {
            Node* min_Node = minNode(root->right);
            root->data = min_Node->data;
            root->right = deleteNode(root->right, min_Node->data);
        }
    }
    int bf = getBalance(root);
    if (bf > 1 && getBalance(root->left) >= 0){
        return rootateRight(root);
    }
    if (bf > 1 && getBalance(root->right) < 0){
        root->left = rootateLeft(root->left);
        return rootateRight(root);
    }
    if (bf < -1 && getBalance(root->right) <= 0){
        return rootateLeft(root);
    }
    if (bf < -1 && getBalance(root->right) > 0){
        root->right = rootateRight(root->right);
        return rootateLeft(root);
    }
    return root;
}



void preOrder(Node* root){
    if (root == NULL) return;
    cout << root->data << ' ';
    preOrder(root->left);
    preOrder(root->right);
}

int main(){
    Node* root = NULL;
    int n; cin >> n;
    while (n--){
        int t; cin >> t;
        root = insertNode(root, t);
    }
    preOrder(root);
}