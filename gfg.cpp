#include <bits/stdc++.h>

using namespace std;

class BST {
    class Node;
private:
    Node* root;
public:
    BST(){
        root = NULL;
    }
    Node* getRoot(){
        return this->root;
    }
    Node* insert_help(Node* node, int res){
        if (node == NULL) return new Node(res);
        if (node->data == res){
            Node* newNode = new Node(res);
            newNode->right = node->right;
            node->right = newNode;
            return node;
        }
        else if (node->data < res){
            node->right= insert_help(node->right, res);
        }
        else node->left = insert_help(node->left, res);
    }
    void insert(int result){
        root = insert_help(root, result);
    }
    void print(Node* node, vector<int> &v){
        if (node == NULL){
            return;
        }
        v.push_back(node->data);
        print(node->left, v);
        print(node->right, v);
    }
    void Post(Node* node){
        if (node == NULL){
            return;
        }
        Post(node->left);
        Post(node->right);
        cout << node->data << ' ';
    }
    int gt(int n){
        int res = 1;
        for (int i = 1; i <= n; i++){
            res *= i;
        }
        return res;
    }
    int to_hop(int k, int n){
        return ((gt(n) / gt(k)) / (gt(n - k)));
    }
    int Count(vector<int> v){
        if (v.size() == 0 || v.size() == 1) return 1;
        int top = v[0];
        vector<int> min, max;
        for (int i = 1; i < v.size(); i++){
            if (v[i] < top){
                min.push_back(v[i]);
            }
            else max.push_back(v[i]);
        }
        return to_hop(min.size(), min.size() + max.size()) * Count(min) * Count(max);
    }

private:
    class Node {
    private:
        int data;
        Node* left;
        Node* right;
        friend class BST;
    public:
        Node (int x){
            data = x;
            left = NULL;
            right = NULL;
        }
    };
};

int main(){
    BST* tree = new BST();
    vector <int> v;
    int n; cin >> n;
    for (int i = 0; i < n; i++){
        int c; cin >> c;
        tree->insert(c);
    }
    tree->print(tree->getRoot(), v);
    cout << "Post order :\n";
    tree->Post(tree->getRoot());
    cout << endl;
    for (int x : v){
        cout << x << " ";
    }
    cout << endl;
    cout << tree->Count(v);
}