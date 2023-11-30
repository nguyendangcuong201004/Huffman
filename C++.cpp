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

Node* leftRotate(Node* root){
	Node* rNode = root->right;
	root->right = rNode->left;
	rNode->left = root;
	return rNode;
}

Node* rightRotate(Node* root){
	Node* rNode = root->left;
	root->left = rNode->right;
	rNode->right = root;
	return rNode;
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
		if (leftTree->balance ==  1){
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
		taller = true;
		return new Node(data);
	}
	if (root->data > data){
		root->left = insertNode(root->left, data, taller);
		if (taller){
			if (root->balance == 1){
				root->balance = 0;
				taller = false;
			}
			else if (root->balance == 0){
				root->balance = -1;
			}
			else root = leftBalance(root, taller);
		}
	}
	else {
		root->right = insertNode(root->right, data, taller);
		if (taller){
			if (root->balance == -1){
				root->balance = 0;
				taller = false;
			}
			else if (root->balance == 0){
				root->balance = 1;
			}
			else root = rightBalance(root, taller);
		}
	}
	return root;
}

Node* min_Node(Node* root){
	if (root != NULL && root->right != NULL){
		root = root->right;
	}
	return root;
}

Node* rightDelete(Node* root, bool &shorter){
	if (root->balance == -1){
		root->balance = 0;
	}
	else if (root->balance = 0){
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
			
		}
	}
}

Node* deleteNode(Node* root, int data, bool &shorter){
	if (root == NULL){
		shorter = false;
		return root;
	}
	if (root->data > data){
		root->left = deleteNode(root->left, data, shorter);
		if (shorter){
			root = rightDelete(root, shorter);
		}
	}
	else if (root->data < data){
		root->right = deleteNode(root->right, data, shorter);
	}
	else {
		if (root->left == NULL){
			Node* tmp = root->right;
			delete root;
			shorter = true;
			return tmp;
		}
		else if (root->right == NULL){
			Node* tmp = root->left;
			delete root;
			shorter = true;
			return tmp;
		}
		else {
			Node* xoa = min_Node(root->left);
			root->data = xoa->data;
			root->left = deleteNode(root->left, xoa->data, shorter);
			if (shorter){
				root = rightDelete(root, shorter);
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
	for (int i = 0; i < n; i++){
		int tmp; cin >> tmp;
		bool taller = false;
		root = insertNode(root, tmp, taller);
	}
	preOrder(root);
}