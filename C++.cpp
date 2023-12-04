#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int data;
    Node(int x){
        data = x;
    }
};

int main(){
    list <Node*> VGM;
    VGM.push_back(new Node(1));
    VGM.push_back(new Node(2));
    VGM.push_back(new Node(3));
    VGM.push_back(new Node(4));
    VGM.push_back(new Node(5));
    Node* tmp = NULL;
    for (Node* x : VGM){
        if (x->data == 4){
            tmp = x;
            break;
        }
    }
    Node* it = find(VGM.begin(), VGM.end(), tmp);
    
}