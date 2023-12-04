#include <bits/stdc++.h>
using namespace std;

int countDelete = 0;

class HuffNode {
public:
    virtual int getHeight() = 0;
    virtual int getWeight() = 0;
    virtual bool isLeaf() = 0;
};

class LeafNode : public HuffNode {
private:
    pair<char, int> symbol;
    int wgt;
    int hgt;
public:
    LeafNode(){}
    LeafNode(pair<char, int> s, int w, int h) : symbol(s), wgt(w), hgt(h) {}
    ~LeafNode(){}
    pair<char, int> getSymbol(){
        return this->symbol;
    }
    int getHeight() override {
        return this->hgt;
    }
    int getWeight() override {
        return this->wgt;
    }
    bool isLeaf() override {
        return true;
    }
};

class InternalNode : public HuffNode {
private:
    int wgt;
    int hgt;
    HuffNode* left;
    HuffNode* right;
public:
    InternalNode(){}
    InternalNode(HuffNode* a, HuffNode* b){
        this->wgt = a->getWeight() + b->getWeight();
        this->hgt = max(a->getHeight(), b->getHeight()) + 1;
        this->left = a;
        this->right = b;
    }
    ~InternalNode(){
        delete this->left; this->left = NULL; countDelete--;
        delete this->right; this->right = NULL; countDelete--;
    }
    int getHeight() override {
        return this->hgt;
    }
    void setHeight(int newHeight){
        this->hgt = newHeight;
    }
    int getWeight() override {
        return this->wgt;
    }
    bool isLeaf() override {
        return false;
    }
    HuffNode*& getLeft(){
        return this->left;
    }
    void setLeft(HuffNode* newNode){
        this->left = newNode;
    }
    HuffNode*& getRight(){
        return this->right;
    }
    void setRight(HuffNode* newNode){
        this->right = newNode;
    }
};

class HuffTree {
private:
    HuffNode* root;
public:
    HuffTree(){}
    HuffTree(pair<char, int> c, int w, int h){
        root = new LeafNode(c, w, h);
        countDelete++;
    }
    HuffTree(HuffTree* left, HuffTree* right){
        root = new InternalNode(left->root, right->root);
        countDelete++;
    }
    ~HuffTree(){}
    HuffNode*& getRoot(){
        return this->root;
    }
    void print(HuffNode* root){
        if (root == NULL) return;
        else if(root->isLeaf()){
            LeafNode* leaf = dynamic_cast<LeafNode*> (root);
            cout << leaf->getWeight() << "(" << leaf->getSymbol().first << ")" << "\t"; 
        }
        else {
            InternalNode* internal = dynamic_cast<InternalNode*> (root);
            cout << internal->getWeight() << "\t";
            print(internal->getLeft());
            print(internal->getRight());
        }
    }
    void clear(HuffNode*& root){
        if (root == NULL) return;
        if (!root->isLeaf()){
            InternalNode* internal = dynamic_cast<InternalNode*> (root);
            clear(internal->getLeft());
            clear(internal->getRight());
        }
        delete root; root = NULL;
        countDelete--;
    }
};

struct Compare {
    bool operator() (HuffTree *a, HuffTree *b) {
        if (a->getRoot()->getWeight() > b->getRoot()->getWeight()) {
            return true;
        }
        else if (a->getRoot()->getWeight() == b->getRoot()->getWeight()) {
            if (a->getRoot()->isLeaf() == true && b->getRoot()->isLeaf() == true) {
                LeafNode *leafA = dynamic_cast<LeafNode*>(a->getRoot());
                LeafNode *leafB = dynamic_cast<LeafNode*>(b->getRoot());
                if (leafA && leafB) {
                    return leafA->getSymbol().second > leafB->getSymbol().second;
                }
            }
        }
        return false;
    }
};

void print_queue(priority_queue<HuffTree*, vector<HuffTree*>, Compare> Q){
    while (!Q.empty()){
        HuffTree* top = Q.top(); Q.pop();
        LeafNode* leaf = dynamic_cast<LeafNode*> (top->getRoot());
        cout << leaf->getWeight() << "(" << leaf->getSymbol().first << ")" << "\t";
    }
}

void rotateLeft (HuffNode *&rt)
{
    InternalNode *root = dynamic_cast<InternalNode*>(rt);
    HuffNode *right = root->getRight();
    InternalNode *rightRoot = dynamic_cast<InternalNode*>(right);
    root->setHeight(max(root->getLeft()->getHeight(), rightRoot->getLeft()->getHeight()) + 1);
    rightRoot->setHeight(max(root->getHeight(), rightRoot->getRight()->getHeight()) + 1);
    root->setRight(rightRoot->getLeft());
    rightRoot->setLeft(rt);
    rt = right;
}

void rotateRight(HuffNode *&rt)
{
    InternalNode *root = dynamic_cast<InternalNode*>(rt);
    HuffNode *left = root->getLeft();
    InternalNode *leftRoot = dynamic_cast<InternalNode*>(left);
    root->setHeight(max(root->getRight()->getHeight(), leftRoot->getRight()->getHeight()) + 1);
    leftRoot->setHeight(max(root->getHeight(), leftRoot->getLeft()->getHeight()) + 1);
    root->setLeft(leftRoot->getRight());
    leftRoot->setRight(rt);
    rt = left;
}

void leftBalance (HuffNode *&rt)
{
    InternalNode *root = dynamic_cast<InternalNode*>(rt);
    HuffNode *&left = root->getLeft();
    InternalNode *leftRoot = dynamic_cast<InternalNode*>(left);
    int difference = leftRoot->getLeft()->getHeight() - leftRoot->getRight()->getHeight();
    if (difference > 0) {
        rotateRight(rt);
    }
    else {
        rotateLeft(left);
        rotateRight(rt);
    }
}

void rightBalance (HuffNode *&rt)
{
    InternalNode *root = dynamic_cast<InternalNode*>(rt);
    HuffNode *&right = root->getRight();
    InternalNode *rightRoot = dynamic_cast<InternalNode*>(right);
    int difference = rightRoot->getLeft()->getHeight() - rightRoot->getRight()->getHeight();
    if (difference > 0) {
        rotateRight(right);
        rotateLeft(rt);
    }
    else {
        rotateLeft(rt);
    }
}

void balanceProcess (HuffNode *&root)
{
    InternalNode *internal = dynamic_cast<InternalNode*>(root);
    int difference = internal->getLeft()->getHeight() - internal->getRight()->getHeight();
    if (abs(difference) <= 1) {
        return;
    } 
    else if (difference >= 2) {
        leftBalance(root);
    }
    else {
        rightBalance(root);
    }
    balanceProcess(root);
}

HuffTree* BuidHuff (priority_queue<HuffTree*, vector<HuffTree*>, Compare> Q){
    if (Q.size() <= 1) return NULL;
    HuffTree* tmp1 = NULL;
    HuffTree* tmp3 = NULL;
    HuffTree* tmp2 = NULL;
    while (Q.size() >= 2){
        tmp1 = Q.top(); Q.pop();
        tmp2 = Q.top(); Q.pop();
        tmp3 = new HuffTree(tmp1, tmp2); countDelete++;
        balanceProcess(tmp3->getRoot());
        tmp3->print(tmp3->getRoot());
        cout << endl;
        Q.push(tmp3);
        delete tmp1; tmp1 = NULL; countDelete--;
        delete tmp2; tmp2 = NULL; countDelete--;
    }
    return tmp3;
}

void dfs(HuffNode* root, map<char, string> &mp, string tmp){
    if (root == NULL) return;
    if (root->isLeaf()){
        LeafNode* leaf = dynamic_cast<LeafNode*> (root);
        mp[leaf->getSymbol().first] = tmp;
    }
    else {
        InternalNode* internal = dynamic_cast<InternalNode*> (root);
        dfs(internal->getLeft(), mp, tmp + "0");
        dfs(internal->getRight(), mp, tmp + "1");
    }
}

map<char, string> encode(HuffTree* huff_tree){
    map<char, string> mp;
    dfs(huff_tree->getRoot(), mp, "");
    return mp;
}

string decode(string d, map<char, string> mp){
    string res = "";
    for (char c : d){
        res += mp[c];
    }
    return res;
}

int main(){
    vector<pair<char, int>> v = {{'E', 3}, {'f', 4}, {'e', 8}, {'a', 16}, {'b', 16}};
    vector<int> order = {1, 2, 3, 4, 5};
    priority_queue<HuffTree*, vector<HuffTree*>, Compare> Q;
    for (int i = 0; i < 5; i++){
        Q.push(new HuffTree({v[i].first, order[i]}, v[i].second, 0)); countDelete++;
    }
    cout << "HANG DOI UU TIEN: \n";
    print_queue(Q);
    cout << endl << endl << "DUYET CAY:\n";
    HuffTree* huff_tree = BuidHuff(Q);
    huff_tree->print(huff_tree->getRoot());
    cout << endl;
    cout << endl;
    cout << "ENCODE: \n";
    map<char, string> mp = encode(huff_tree);
    for (auto it : mp){
        cout << it.first << ' ' << it.second << endl;
    }
    cout << endl << endl;
    cout << "MA HOA CUA CHUOI: LCZK\n";
    cout << decode("MUCK", mp);
    huff_tree->clear(huff_tree->getRoot());
    delete huff_tree; huff_tree = NULL;
    countDelete--;
    cout << endl;
    if(countDelete == 0){
        cout << "NO leak" << endl;
    }
}