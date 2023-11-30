#include <bits/stdc++.h>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    int balance;
    Node(int x){
        data = x;
        left = right = NULL;
        balance = 0;
    }
};

Node* rotateRight(Node* root){
    Node* rootLeft = root->left;
    root->left = rootLeft->right;
    rootLeft->right = root;
    return rootLeft;
}

Node* rotateLeft(Node* root){
    Node* rootRight = root->right;
    root->right = rootRight->left;
    rootRight->left = root;
    return rootRight;
}

Node* rightBalance(Node* root, bool& taller) {
    Node* rightTree = root->right;
    if (rightTree->balance == 1){
        root = rotateLeft(root);
        root->left->balance = 0;
        root->balance = 0;
        rightTree->balance = 0;
    }
    else {
        Node* leftTree = rightTree->left;
        if (leftTree->balance == 1){
            root->balance = -1;
            rightTree->balance = 0;
        }
        else if (leftTree->balance == 0){
            root->balance = 0;
            rightTree->balance = 0;
        }
        else {
            root->balance = 0;
            rightTree->balance = 1;
        }
        leftTree->balance = 0;
        root->right = rotateRight(rightTree);
        root = rotateLeft(root);
    }
    taller = false;
    return root;
}

Node* leftBalance(Node* root, bool &taller){
    Node* leftTree = root->left;
    if (leftTree->balance == -1){
        root = rotateRight(root);
        root->right->balance = 0;
        leftTree->balance = 0;
        root->balance = 0;
    }
    else {
        Node* rightTree = leftTree->right;
        if (rightTree->balance == -1){
            root->balance = 1;
            leftTree->balance = 0;
        }
        else if (rightTree->balance == 0){
            root->balance = 0;
            leftTree->balance = 0;
        }
        else {
            root->balance = 0;
            leftTree->balance = -1;
        }
        rightTree->balance = 0;
        root->left = rotateLeft(leftTree);
        root = rotateRight(root);
    }
    taller = false;
    return root;
}

Node* insertNode(Node* root, int data, bool& taller){
    if (root == NULL){
        taller = true;
        return new Node(data);
    }
    else if (root->data > data){
        root->left = insertNode(root->left, data, taller);
        if (taller){
            if (root->balance == 0){
                root->balance = -1;
            }
            else if (root->balance == 1){
                root->balance = 0;
                taller = false;
            }
            else {
                root = leftBalance(root, taller);
            }
        }
    }
    else{
        root->right = insertNode(root->right,data, taller);
        if (taller){
            if (root->balance == 0){
                root->balance = 1;
            }
            else if (root->balance == -1){
                root->balance = 0;
                taller = false;
            }
            else root = rightBalance(root, taller);
        }
    }
    return root;
}

Node* minNode(Node* root){
    Node* tmp = root;
    while (tmp != NULL && tmp->left != NULL){
        tmp = tmp->left;
    }
    return tmp;
}

Node* deleteRightBalance(Node* root, bool &shorter){

}

Node* deleteLeftBalance(Node* root, bool &shorter){
    
}

void preOrder(Node* root){
    if (root == NULL) return;
    cout << root->data << ' ';
    preOrder(root->left);
    preOrder(root->right);
}

Node* deleteNode(Node* root, int data, bool &shorter, bool &success){
    if (root == NULL){
        shorter = false;
        success = false;
        return root;
    }
    if (root->data > data){
        root->left = deleteNode(root->left, data, shorter, success);
        if (shorter){
            root = deleteRightBalance(root, shorter);
        }
    }
    else if (root->data < data){
        root->right = deleteNode(root->right, data, shorter, success);
        if (shorter){
            root = deleteLeftBalance(root, shorter);
        }
    }
    else {
        if (root->left == NULL){
            Node* tmp = root->right;
            success = true;
            shorter = true;
            delete root;
            return tmp;
        }
        else if (root->right == NULL){
            Node* tmp = root->left;
            success = true;
            shorter = true;
            delete root;
            return tmp;
        }
        else {
            
        }
    }
}

void preOrder(Node *root)  
{  
    if(root != NULL)  
    {   
        preOrder(root->left);  
        preOrder(root->right);  
        cout << root->data << " "; 
    }  
} 

int main(){
    Node* root = NULL;
    int n; cin >> n;
    for (int i = 0; i < n; i++){
        bool taller = false;
        int t; cin >> t;
        root = insertNode(root, t, taller);
    }
    preOrder(root);
}
