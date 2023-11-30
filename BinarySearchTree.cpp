#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node(int x){
        data = x;
        left = right = NULL;
    }
};

Node* inserNode(Node* root, int data){
    if (root == NULL){
        root = new Node(data);
        return root;
    }
    Node* tmp = root;
    while (tmp != NULL){
        if (tmp->data == data){
            Node* newNode = new Node(data);
            newNode->left = tmp->left;
            tmp->left = newNode;
            return root;
        }
        else if (tmp->data > data){
            if (tmp->left == NULL){
                tmp->left = new Node(data);
                return root;
            }
            tmp = tmp->left;
        }
        else {
            if (tmp->right == NULL){
                tmp->right = new Node(data);
                return root;
            }
            tmp = tmp->right;
        }
    }
}

Node* deleteNode(Node* root, int data){
    if (root == NULL) return root;
    Node* tmp = root;
    Node* cha = NULL;
    while (tmp != NULL && tmp->data != data){
        cha = tmp;
        if (tmp->data < data){
            tmp = tmp->right;
        }
        else tmp = tmp->left;
    }
    if (tmp == NULL) return root;
    if (tmp->left == NULL){
        if (tmp == root){
            root = tmp->right;
        }
        else if (tmp == cha->left){
            cha->left = tmp->right;
        }
        else cha->right = tmp->right;
        delete tmp;
    }
    else if (tmp->right == NULL){
        if (tmp == root){
            root = tmp->left;
        }
        else if (tmp == cha->left){
            cha->left = tmp->left;
        }
        else cha->right = tmp->left;
        delete tmp;
    }
    else {
        Node* xoa = tmp->right;
        cha = tmp;
        while (xoa != NULL && xoa->left != NULL){
            cha = xoa;
            xoa = xoa->left;
        }
        tmp->data = xoa->data;
        if (xoa == cha->left){
            cha->left = NULL;
        }
        else{
            cha->right = xoa->right;
        }
        delete xoa;
    }
    return root;
}

void inOrder(Node* root){
    if (root == NULL) return;
    inOrder(root->left);
    cout << root->data << ' ';
    inOrder(root->right);
}

void preOrder(Node* root){
    if (root == NULL) return;
    cout << root->data << ' ';
    inOrder(root->left);
    inOrder(root->right);
}

int getMin(Node* root){
    Node* tmp = root;
    while (tmp != NULL && tmp->left != NULL){
        tmp = tmp->left;
    }
    return tmp->data;
}

int getMax(Node* root){
    Node* tmp = root;
    while (tmp != NULL && tmp->right != NULL){
        tmp = tmp->right;
    }
    return tmp->data;
}

bool find(Node* root, int data){
    if (root == NULL) return false;
    Node* tmp = root;
    while (tmp != NULL){
        if (tmp->data == data){
            return true;
        }
        else if (tmp->data > data){
            tmp = tmp->left;
        }
        else tmp = tmp->right;
    }
    return false;
}

int sumok(Node* root, int l, int r){
    if (root == NULL) return 0;
    if (root->data >= l && root->data <= r){
        return root->data + sumok(root->left, l, r) + sumok(root->right, l, r);
    }
    return sumok(root->left, l, r) + sumok(root->right, l, r);
}

int inRange(Node* root, int l, int r){
    if (root == NULL) return 0;
    if (root->data >= l && root->data <= r){
        return 1 + inRange(root->left, l, r) + inRange(root->right, l, r);
    }
    return inRange(root->left, l, r) + inRange(root->right, l, r);
}

Node* subtreeWithRange(Node* root, int l, int h){
    if (root == NULL) return root;
    if (root->data < l){
        return subtreeWithRange(root->right, l , h);
    }
    else if (root->data > h){
        return subtreeWithRange(root->left, l , h);
    }
    else {
        root->left = subtreeWithRange(root->left, l , h);
        root->right = subtreeWithRange(root->right, l, h);
        return root;
    }
}

int singleChild(Node* root){
    if (root == NULL) return 0;
    if (root->left == NULL && root->right != NULL || root->left != NULL && root->right == NULL){
        return 1 + singleChild(root->left) + singleChild(root->right);;
    }
    return singleChild(root->left) + singleChild(root->right);
}

void levelAlterTraverse(Node* root){
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty() || !s2.empty()){
        while (!s1.empty()){
            Node* top = s1.top(); s1.pop();
            cout << top->data << ' ';
            if (top->left != NULL){
                s2.push(top->left);
            }
            if (top->right != NULL){
                s2.push(top->right);
            }
        }
        while (!s2.empty()){
            Node* top = s2.top(); s2.pop();
            cout << top->data << ' ';
            if (top->right != NULL){
                s1.push(top->right);
            }
            if (top->left != NULL){
                s1.push(top->left);
            }
        }
    }
}

Node* foo(Node* root, int & sum){
    if (root == NULL) return root;
    foo(root->right, sum);
    sum += root->data;;
    root->data = sum;
    foo(root->left, sum);
    return root;
}

int main(){
    Node* root = NULL;
    int n; cin >> n;
    for (int i = 1; i <= n; i++){
        int t; cin >> t;
        root = inserNode(root, t);
    }
    int sum = 0;
    root = foo(root, sum);
    inOrder(root);
}