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

int getHeight(Node* root){
    if (root == NULL) return 0;
    return 1 + max (getHeight(root->left), getHeight(root->right));
}

int factor(Node* root){
    if (root == NULL){
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}

Node* rightRotate(Node* root){
    Node* rootLeft = root->left;
    root->left = rootLeft->right;
    rootLeft->right = root;
    return rootLeft;
}

Node* leftRotate(Node* root){
    Node* rootRight = root->right;
    root->right = rootRight->left;
    rootRight->left = root;
    return rootRight;
}

Node* leftBalance(Node* root, bool &taller){
    Node* leftTree = root->left;
    if (leftTree->balance == -1){
        root = rightRotate(root);
        root->balance = 0;
        root->right->balance = 0;
        taller = false;
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
        root->left = leftRotate(root->left);
        root = rightRotate(root);
        root->balance = 0;
        taller = false;
    }
    return root;
}


Node* rightBalance(Node* root, bool &taller){
    Node* rightTree = root->right;
    if (rightTree->balance == 1){
        root = leftRotate(root);
        root->balance = 0;
        root->left->balance = 0;
        taller = false;
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
        root->right = rightRotate(root->right);
        root = leftRotate(root);
        root->balance = 0;
        taller = false;
    }
    return root;
}

Node* insertNode(Node* root, int data, bool &taller){
    if (root == NULL){
        taller  = true;
        return new Node(data);
    }
    else {
        if (root->data > data){
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
        else {
            root->right = insertNode(root->right, data, taller);
            if (root->balance == 0){
                root->balance = 1;
            }
            else if (root->balance == -1){
                root->balance = 0;
                taller = false;
            }
            else{
                root = rightBalance(root, taller);
            }
        }
    }
    return root;
}

Node* minNode(Node* root){
    Node* tmp = root;
    while (tmp != NULL && tmp->right != NULL){
        tmp = tmp->right;
    }
    return tmp;
}

Node* deleteRightBalance(Node* root, bool &shorter){
    if (root->balance == -1){
        root->balance = 0;
    }
    else if (root->balance == 0){
        root->balance = 1;
        shorter = false;
    }
    else {
        Node* rightTree = root->right;
        if (rightTree->balance == 1){
            root->balance = 0;
            rightTree->balance = 0;
            root = leftRotate(root);
        }
        else if (rightTree->balance == 0){
            root->balance = 1;
            rightTree->balance = -1;
            shorter = false;
            root = leftRotate(root);
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
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
    }
    return root;
}

Node* deleteLeftBalance(Node* root, bool &shorter){
    if (root->balance == 1){
        root->balance = 0;
    }
    else if (root->balance == 0){
        root->balance = -1;
        shorter = false;
    }
    else {
        Node* leftTree = root->left;
        if (leftTree->balance == -1){
            root->balance = 0;
            leftTree->balance = 0;
            root = rightRotate(root);
        }
        else if (leftTree->balance == 0){
            root->balance = -1;
            leftTree->balance = 1;
            shorter = false;
            root = rightRotate(root);
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
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
    }
    return root;
}


Node* deleteNode(Node* root, int data, bool &shorter){
    if (root == NULL){
        shorter = false;
        return root;
    }
    if (root->data > data){
        root->left = deleteNode(root->left, data, shorter);
        if (shorter){
            root = deleteRightBalance(root, shorter);
        }
    }
    else if (root->data < data){
        root->right = deleteNode(root->right, data, shorter);
        if (shorter){
            root = deleteLeftBalance(root, shorter);
        }
    }
    else {
        if (root->right == NULL){
            Node* tmp = root->left;
            delete root;
            shorter = true;
            return tmp;
        }
        else if (root->left == NULL){
            Node* tmp = root->right;
            delete root;
            shorter = true;
            return tmp;
        }
        else {
            Node* xoa = minNode(root->left);
            root->data = xoa->data;
            root->left = deleteNode(root->left, xoa->data, shorter);
            if (shorter){
                root = deleteRightBalance(root, shorter);
            }
        }
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
    for (int i = 1; i <= n; i++){
        int tmp; cin >> tmp;
        bool taller = false;
        root = insertNode(root, tmp, taller);
    }
    preOrder(root);
}   