#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int countDelete = 0;

class HuffNode
{
    public:
        virtual int getWeight() = 0;
        virtual int getHeight() = 0;
        virtual bool isLeaf() = 0;
};

class LeafNode : public HuffNode
{
    private:
        pair<char, int> ch;
        int wgt;
        int hgt;
    public:
        LeafNode() {}
        LeafNode(pair<char, int> c, int w, int h) {
            this->ch = c;
            this->wgt = w;
            this->hgt = h;
        }
        ~LeafNode() {}
        
        pair<char, int> getChar() {
            return this->ch;
        }
        int getWeight() override {
            return this->wgt;
        }
        int getHeight()  override {
            return this->hgt;
        }
        bool isLeaf() override {
            return true;
        }
};

class InternalNode : public HuffNode
{
    private:
        int wgt;
        int hgt;
        HuffNode *leftNode;
        HuffNode *rightNode;
    public:
        InternalNode() {}
        InternalNode(HuffNode *a, HuffNode *b) {
            this->wgt = a->getWeight() + b->getWeight();
            this->hgt = max(a->getHeight(), b->getHeight()) + 1;
            this->leftNode = a;
            this->rightNode = b;
        }
        ~InternalNode() {
            wgt = 0;
            delete this->leftNode; this->leftNode = nullptr; countDelete--;
            delete this->rightNode; this->rightNode = nullptr; countDelete--;
        }
        int getWeight() override {
            return this->wgt;
        }
        int getHeight() override {
            return this->hgt;
        }
        bool isLeaf() override {
            return false;
        }
        HuffNode*& getLeftNode() {
            return this->leftNode;
        }
        HuffNode*& getRightNode() {
            return this->rightNode;
        }
        void setLeftNode (HuffNode *a) {
            this->leftNode = a;
        }
        void setRightNode (HuffNode *b) {
            this->rightNode = b;
        }
        void setHeight (int h) {
            this->hgt = h;
        }
};

class HuffTree
{
    private:
        HuffNode *root;
    public:
        HuffTree() {} 
        HuffTree(pair<char, int> character, int weight, int height) {
            root = new LeafNode(character, weight, height); countDelete++;
        }
        HuffTree(HuffTree *a, HuffTree *b) {
            root = new InternalNode(a->root, b->root); countDelete++;
        }
        ~HuffTree() {}
        HuffNode*& getRoot() {
            return this->root;
        }

        void printHuffTree (HuffNode *root) const {
            if (root == nullptr) {
                return;
            }
            else if (root->isLeaf() == true) {
                LeafNode *leaf = dynamic_cast<LeafNode*>(root);
                cout << leaf->getWeight() << "(" << leaf->getChar().first << ")\t";
            }
            else {
                InternalNode *internal = dynamic_cast<InternalNode*>(root);
                cout << internal->getWeight() << "\t";
                printHuffTree(internal->getLeftNode());
                printHuffTree(internal->getRightNode());
            }
        }
        void clear(HuffNode *&root) {
            if (root == nullptr) {
                return;
            }

            // Xoa theo post order - do la quy tac
            if (root->isLeaf() == false) {
                InternalNode *internalNode = dynamic_cast<InternalNode*>(root);
                if (internalNode != nullptr) {
                    clear(internalNode->getLeftNode());
                    clear(internalNode->getRightNode());
                }
            }
            delete root; root = nullptr; countDelete--;
        }

};

struct compare
{
    bool operator() (HuffTree *a, HuffTree *b) {
        if (a->getRoot()->getWeight() > b->getRoot()->getWeight()) {
            return true;
        }
        else if (a->getRoot()->getWeight() == b->getRoot()->getWeight()) {
            if (a->getRoot()->isLeaf() == true && b->getRoot()->isLeaf() == true) {
                LeafNode *leafA = dynamic_cast<LeafNode*>(a->getRoot());
                LeafNode *leafB = dynamic_cast<LeafNode*>(b->getRoot());
                if (leafA && leafB) {
                    return leafA->getChar().second > leafB->getChar().second;
                }
            }
        }
        return false;
    }
};



void rotateLeft (HuffNode *&rt)
{
    if (rt->isLeaf() == true) {
        return;
    }
    else {
        InternalNode *root = dynamic_cast<InternalNode*>(rt);
        HuffNode *right = root->getRightNode();
        if (right->isLeaf() == true) {
            root->setRightNode(nullptr);
            right = new InternalNode(rt, nullptr);
            rt = right;
        }
        else {
            InternalNode *rightRoot = dynamic_cast<InternalNode*>(right);
            root->setHeight(max(root->getLeftNode()->getHeight(), rightRoot->getLeftNode()->getHeight()) + 1);
            rightRoot->setHeight(max(root->getHeight(), rightRoot->getRightNode()->getHeight()) + 1);
            root->setRightNode(rightRoot->getLeftNode());
            rightRoot->setLeftNode(rt);
            rt = right;
        }
    }
}

void rotateRight(HuffNode *&rt)
{
    if (rt->isLeaf() == true) {
        return;
    }
    else {
        InternalNode *root = dynamic_cast<InternalNode*>(rt);
        HuffNode *left = root->getLeftNode();
        if (left->isLeaf() == true) {
            root->setLeftNode(nullptr);
            left = new InternalNode(nullptr, rt);
            rt = left;
        }
        else {
            InternalNode *leftRoot = dynamic_cast<InternalNode*>(left);
            root->setHeight(max(root->getRightNode()->getHeight(), leftRoot->getRightNode()->getHeight()) + 1);
            leftRoot->setHeight(max(root->getHeight(), leftRoot->getLeftNode()->getHeight()) + 1);
            root->setLeftNode(leftRoot->getRightNode());
            leftRoot->setRightNode(rt);
            rt = left;
        }
    }
}

void leftBalance (HuffNode *&rt)
{
    InternalNode *root = dynamic_cast<InternalNode*>(rt);
    if (root == nullptr) {
        cout << "Loi leftBalance" << endl;
        return;
    }
    else {
        HuffNode *&left = root->getLeftNode();
        if (left->isLeaf() == true) {
            cout << "Loi leftBalance 1" << endl;
            return;
        }
        else {
            InternalNode *leftRoot = dynamic_cast<InternalNode*>(left);
            int difference = leftRoot->getLeftNode()->getHeight() - leftRoot->getRightNode()->getHeight();
            if (difference > 0) {
                rotateRight(rt);
            }
            else {
                rotateLeft(left);
                rotateRight(rt);
            }
        }
    }
}

void rightBalance (HuffNode *&rt)
{
    InternalNode *root = dynamic_cast<InternalNode*>(rt);
    if (root == nullptr) {
        cout << "Loi rightBalance" << endl;
        return;
    }
    else {
        HuffNode *&right = root->getRightNode();
        if (right->isLeaf() == true) {
            cout << "Loi rightBalance 1" << endl;
            return;
        }
        else {
            InternalNode *rightRoot = dynamic_cast<InternalNode*>(right);
            int difference = rightRoot->getLeftNode()->getHeight() - rightRoot->getRightNode()->getHeight();
            if (difference > 0) {
                rotateRight(right);
                rotateLeft(rt);
            }
            else {
                rotateLeft(rt);
            }
        }
    }
}

void balanceProcess (HuffNode *&root)
{
    if (root->isLeaf() == true) {
        return;
    }
    else {
        InternalNode *internal = dynamic_cast<InternalNode*>(root);
        int difference = internal->getLeftNode()->getHeight() - internal->getRightNode()->getHeight();
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
}


HuffTree* buildHuff (priority_queue<HuffTree*, vector<HuffTree*>, compare> &forest)
{
    if (forest.size() <= 1) {
        return nullptr;
    }
    else {
        HuffTree *tmp1 = nullptr, *tmp2 = nullptr, *tmp3 = nullptr;
        while (forest.size() >= 2) {
            tmp1 = forest.top(); forest.pop();
            tmp2 = forest.top(); forest.pop();
            tmp3 = new HuffTree(tmp1, tmp2); countDelete++;
            balanceProcess(tmp3->getRoot());
            cout << "tmp3: " << tmp3->getRoot()->getWeight() << "-" << tmp3->getRoot()->getHeight() << "  print: ";
            tmp3->printHuffTree(tmp3->getRoot());
            cout << endl;
            forest.push(tmp3);
            delete tmp1; tmp1 = nullptr; countDelete--;
            delete tmp2; tmp2 = nullptr; countDelete--;
        }
        return tmp3;
    }
}

void printPriorityQueue (priority_queue<HuffTree*, vector<HuffTree*>, compare> pq)
{
    while (!pq.empty()) {
        HuffTree *top = pq.top(); pq.pop();
        if (top->getRoot()->isLeaf() == true) {
            LeafNode* leaf = dynamic_cast<LeafNode*>(top->getRoot());
            if (top != nullptr) {
                cout << leaf->getWeight() << "(" << leaf->getChar().first << ")\t";
            }
            else {
                cout << "Loi 3" << endl;
            }
        }
        else {
            cout << top->getRoot()->getWeight() << "\t";
        }
    }
    cout << endl << endl;
}

void depthFirstSearch (HuffNode *root, vector<pair<char, string>> &res, string tmp)
{
    if (root == nullptr) {
        return;
    }
    if (root->isLeaf() == true) {
        LeafNode *leaf = dynamic_cast<LeafNode*>(root);
        if (leaf != nullptr) {
            res.push_back({leaf->getChar().first, tmp});
        }
    }
    else {
        InternalNode *internal= dynamic_cast<InternalNode*>(root);
        if (internal != nullptr) {
            depthFirstSearch(internal->getLeftNode(), res, tmp + "0");
            depthFirstSearch(internal->getRightNode(), res, tmp + "1");
        }
    }
}

vector<pair<char, string>> encodeCharacter (HuffTree *hufftree)
{
    vector<pair<char, string>> res;
    depthFirstSearch(hufftree->getRoot(), res, "");
    return res;
}

string encodeString (vector<pair<char, string>> &encode, string &input)
{
    string res;
    for (char &i : input) {
        vector<pair<char, string>>::iterator it = find_if(encode.begin(), encode.end(), [i] (const pair<char, string> &a)->bool {return i == a.first;});
        if (it != encode.end()) {
            res += it->second;
        }
        else {
            cout << "Thieu ki tu trong vector encode roi!" << endl;
            return "";
        }
    }
    return res;
}



int main()
{
    // char: ki tu // int: so thu tu xuat hien, cang lon thi vao cang tre, cang nho thi vao cang som
    vector<pair<char, int>> letters = {{'C', 0}, {'D', 1}, {'E', 2}, {'K', 3}, {'L', 4}, {'M', 5}, {'U', 6}, {'Z', 7}};
    vector<int> frequencies = {32, 42, 120, 7, 42, 24, 37, 2};

    priority_queue<HuffTree*, vector<HuffTree*>, compare> forest;
    for (int i = 0; i < 8; i++) {
        HuffTree *newNode = new HuffTree(letters[i], frequencies[i], 0); countDelete++;
        forest.push(newNode);
    }
    cout << endl << "Priority Queue before buidHuff: <front .... rear> ------------------------------------------------------------" << endl;
    cout << "\t";
    printPriorityQueue(forest);
    cout << endl;


    HuffTree *huff_tree = buildHuff(forest);
    cout << "Print_PreOrdered of Huffman tree: < N L R > ------------------------------------------------------------------" << endl;
    cout << "\t";
    huff_tree->printHuffTree(huff_tree->getRoot());
    cout << endl << endl;

    cout << "Priority Queue after buidHuff: <front .... rear> -------------------------------------------------------------" << endl;
    cout << "\t";
    printPriorityQueue(forest);

    vector<pair<char, string>> encode = encodeCharacter(huff_tree);
    cout << "Encode character: --------------------------------------------------------------------------------------------" << endl;
    for (pair<char, string> &i : encode) {
        cout << "\t" << i.first << "-" << i.second << endl;
    } cout << endl;

    string encode_string = "MUCK";
    cout << "Encode string: " << encode_string << " has the form: ----------------------------------------------------------------------------" << endl;
    cout << "\t" << encodeString(encode, encode_string);
    cout << endl << endl;

    // huff_tree->clear(huff_tree->getRoot());
    // delete huff_tree; countDelete--;

    if (countDelete == 0) {
        cout << "Clear Success!!" << endl;
    }
}