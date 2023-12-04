#include <bits/stdc++.h>
using namespace std;

static int MAXSIZE;

class JJK_RESTAURANT;
class Restaurant_Gojo;
class Restaurant_Sukuna;
class HuffmanTree;

class JJK_RESTAURANT {
private:

public:
	void LAPSE (string name){
		
		cout << name << endl;
	}
	void KOKUSEN (){
		cout << "Kokusen" << endl;
	}
	void KEITEIKEN (int num){
		cout << num << ' ' << num + 1 << endl;
	}
	void HAND (){
		cout << "Hand" << endl;
	}
	void LIMITLESS (int num){
		cout << num << ' ' << num + 1 << endl;
	}
	void CLEAVE (int num){
		cout << num << ' ' << num + 1 << endl;
	}
};

class Restaurant_Gojo {
	class BST;  // Dùng để tránh xung đột của Bảng Băm 
private:
	vector <BST> Bang_Bam;
public:
	Restaurant_Gojo() : Bang_Bam(MAXSIZE + 1){}
	void insertCustomer (int result){ // Thêm khách vào Bản Băm tại khu vực ID 
		int ID = result % MAXSIZE + 1;
		Bang_Bam[ID].insert(result);
	}
	void remove_kokusen(){
		for (int i = 1; i <= MAXSIZE; i++){
			Bang_Bam[i].remove();
		}
	}
	void print_Limitless(int num){
		if (num <= 0 || num > MAXSIZE) return;
		Bang_Bam[num].print();
	}
private:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASS BINARY SEARCH TREE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class BST {
		class Node;
	private:
		Node* root;
		queue<int> Order; // Để hàm KOKUSEN xóa theo FIFO
	public:
		BST(){
			this->root = NULL;
		}
		int size(){ // Số khách hàng = số Node = kích thước của hàng đợi theo thứ tự thời gian 
			return Order.size();
		}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HÀM THÊM KHÁCH HÀNG~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		Node* insert_Helper(Node* node, int res){ // Chèn trong BST trả về Root 
			if (node == NULL){
				Order.push(res);
				return new Node(res);
			}
			else if (node->data == res){ // Nếu như trùng res thì thêm vào cây con bên phải 
				Node* newNode = new Node(res);
				Order.push(res);
				newNode->right = node->right;
				node->right = newNode;
				return node; // return node
			}
			else if (node->data > res){
				node->left = insert_Helper(node->left, res);
			}
			else node->right = insert_Helper(node->right, res);
		}
		void insert(int result){ // Hàm void để thêm thông qua class BST cho đơn giản
			root = insert_Helper(root, result);
		}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HÀM XÓA GIÁN ĐIỆP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		Node* min_Node(Node* node){ // Tìm node nhỏ nhất của cây bên phải 
			Node* tmp = node;
			while (tmp != NULL && tmp->left != NULL){
				tmp = tmp->left;
			}
			return  tmp;
		}
		Node* remove_Helper(Node* node, int res){// Gojo đuổi gián điệp, khi có 2 result giống nhau thì đi từ trên xuống 
			if (node == NULL) return node; // thì khách vào sớm thì node đó sẽ ở trên nên vẫn đảm bảo xóa đúng 
			if (node->data > res){
				node->left = remove_Helper(node->left, res);
			}
			else if (node->data < res){
				node->right = remove_Helper(node->right, res);
			}
			else {
				if (node->left == NULL){
					Node* tmp = node->right;
					delete node;
					return tmp;
				}
				else if (node->right == NULL){
					Node* tmp = node->left;
					delete node;
					return tmp;
				}
				else {
					Node* xoa = min_Node(node->right); // Tìm node nhỏ nhất ở cây bên phải 
					node->data = xoa->data;
					node->right = remove_Helper(node->right, xoa->data);
				}
			}
			return node;
		}
		long long giai_thua(int n){ // Tính n! -> phục vuk cho việc tính tổ hợp 
			long long res = 1;
			for (int i = 1; i <= n; i++){
				res *= i;
			}
			return res;
		}
		long long To_Hop(int k, int n){ // Tính tổ hợp nhưng mà sẽ update sau để phù hợp với n lớn ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			return (giai_thua(n) / giai_thua(k) / giai_thua(n - k));
		}
		void preOrder(Node* node, vector<int> &v){ // -> Tạo 1 vector lưu preOrder của BST từ đó tính số Hoán vị 
			if (node == NULL) return;
			v.push_back(node->data);
			preOrder(node->left, v);
			preOrder(node->right, v);
		}
		int Count(vector<int> v){ // Tính Số Hoán vị mà Tạo được BST gốc 
			if (v.size() == 0 || v.size() == 1){
				return 1;
			}
			vector<int> n1, n2;
			int root = v[0];
			for (int i = 1; i < v.size(); i++){
				if (v[i] < root){
					n1.push_back(v[i]);
				}
				else n2.push_back(v[i]);
			}
			return To_Hop(n1.size(), n1.size() + n2.size()) * Count(n1) * Count(n2);  // Công thức 
		}
		void remove(){
			if (this->size() == 0 || this->size() == 1) return; // Cây rỗng hoặc cây chỉ có 1 node thì sẽ có 1 hoán vị đều skip 
			vector <int> v;
			preOrder(root, v);
			long long Y = Count(v);
			while (Y != 0 && !Order.empty()){
				int tmp = Order.front();
				Order.pop();
				root = remove_Helper(root, tmp);
				Y--;
			}
		}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HÀM IN THÔNG TIN KHÁCH~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		void print_Helper(Node* node){ // Limitless in theo trung thứ tự 
			if (node == NULL) return;
			print_Helper(node->left);
			cout << node->data << endl;
			print_Helper(node->right);
		}
		void print(){
			if (this->size() == 0) return;
			print_Helper(root);
		}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	private:
		class Node { // Class Node của BST 
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
};

class Restaurant_Sukuna {
	class Node;
private:
	vector <Node*> Heap;
	list <Node*> VGM;
private:
	bool compare(int pos1, int pos2){
		for (Node* x : VGM){
			if (x->ID == Heap[pos2]->ID){
				return true;
			}
			if (x->ID == Heap[pos1]->ID){
				return false;
			}
		}
		return false;
	}
	void reheapDown(int pos){
		int l = pos * 2 + 1;
		int r = pos * 2 + 2;
		int largest = pos;
		if (l < Heap.size() && Heap[largest]->size() > Heap[l]->size()){
			largest = l;
		}
		else if (l < Heap.size() && Heap[largest]->size() == Heap[l]->size()){
			if (compare(largest, l)){
				largest = l;
			}
		}
		if (r < Heap.size() && Heap[largest]->size() > Heap[r]->size()){
			largest = r;
		}
		else if (r < Heap.size() && Heap[largest]->size() == Heap[r]->size()){
			if (compare(largest, r)){
				largest = r;
			}
		}
		if (largest != pos){
			swap(Heap[largest], Heap[pos]);
			reheapDown(largest);
		}
	}
	void reheapUp(int pos){
		if (pos >= Heap.size() || pos < 0) return;
		int parent = (pos - 1) / 2;
		if (parent >= 0 && Heap[parent]->size() > Heap[pos]->size()){
			swap(Heap[parent],Heap[pos]);
			reheapUp(parent);
		}
		else if (parent >= 0 && Heap[parent]->size() == Heap[pos]->size()){
			if (compare(pos, parent)){
				swap(Heap[parent],Heap[pos]);
				reheapUp(parent);
			}
		}
	}
	void moveTop(Node * node){ // chuyển node bị thay đổi gần nhất lên đầu danh sách 
		bool check = false;
		for (Node* x : VGM){
			if (x->ID == node->ID){
				check = true;
				break;
			}
		}
		if (check == true) {
			VGM.remove(node);
		}
		VGM.push_front(node);
	}
	void removeNode(Node* node){
		VGM.remove(node);
	}
public:
	void insert_customer(int result){
		int ID = result % MAXSIZE + 1;
		int pos = -1;
		for (int i = 0; i < Heap.size(); i++){
			if (Heap[i]->ID == ID) {
				pos = i;
				break;
			}
		}
		if (pos == -1){
			Heap.push_back(new Node(ID));
			pos = Heap.size() - 1;
			Heap[pos]->insert(result);
			this->moveTop(Heap[pos]);
			this->reheapUp(pos);
		}
		else {
			Heap[pos]->insert(result);
			this->moveTop(Heap[pos]);
			this->reheapDown(pos);
		}
	}
	void remove_keiteiken(int num){
		if (Heap.size() <= 0) return;
		int number = num;
		while (Heap.size() != 0 && num != 0){
			Heap[0]->remove(number);
			if (Heap[0]->size() == 0){
				swap(Heap[0], Heap[Heap.size() - 1]);
				this->removeNode(Heap[Heap.size() - 1]);
				delete Heap[Heap.size() - 1];
				Heap.pop_back();
			}
			this->reheapDown(0);
			num--;
		}
	}
	void preOrder(int pos, int num){
		if (pos >= this->Heap.size()) return;
		this->Heap[pos]->print(num);
		preOrder(pos * 2 + 1, num);
		preOrder(pos * 2 + 2, num);
	}
	void print_cleave(int num){
		if (num <= 0) return;
		preOrder(0, num);
	}
private:
	class Node{
	private:
		int ID;
		list <int> danhsach;
		friend class Restaurant_Sukuna;
	public:
		Node(int x){ // Class Node của Min_heap trong đó Node sẽ có 1 danh sách kiểu list để lưu lại thông tin của khách cũng như thứ tự 
			ID = x;
		}
		int size(){
			return danhsach.size();
		}
		void insert(int result){
			danhsach.push_front(result);
		}
		void remove(int num){
			while (num != 0 && !danhsach.empty()){
				cout << danhsach.back() << "-" << ID << endl;
				danhsach.pop_back();
			}
		}
		void print(int num){
			for (list<int>::iterator it = danhsach.begin(); it != danhsach.end() && num > 0; it++, num--){
				cout << ID << "-" << *it << endl;
			}
		}
	};
};

class HuffNode { // Class HuffNode của cây 
public:
	virtual int getHeight() = 0;
	virtual int getWeight() = 0;
	virtual bool isLeaf() = 0;
};

class LeafNode : public HuffNode { // Node lá 
private:
	pair<char, int> symbol; // fisrt là kí tự, second là thứ tự vào 
	int wgt;
	int hgt;
public:
	LeafNode(){}
	LeafNode(pair<char, int> s, int w, int h){
		symbol = s;
		wgt = w;
		hgt = h;
	}
	~LeafNode(){}
	pair<char, int> getSymbol() {
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

class InternalNode : public HuffNode { //Node trung gian 
private:
	int wgt;
	int hgt;
	HuffNode* left;
	HuffNode* right;
public:
	InternalNode(){}
	InternalNode(HuffNode* a, HuffNode* b){
		this->wgt = a->getWeight() + b->getWeight();
		this->hgt = a->getHeight() + b->getHeight();
		this->left = a;
		this->right = b;
	}
	~InternalNode(){}
	int getHeight() override {
		return this->hgt;
	}
	int getWeight() override {
		return this->wgt;
	}
	bool isLeaf() override {
		return false;
	}
	HuffNode* getLeft(){
		return this->left;
	}
	HuffNode* getRight(){
		return this->right;
	}
	void setLeft(HuffNode* a){
		this->left = a;
	}
	void setRight(HuffNode* b){
		this->right = b;
	}
};

class HuffmanTree { // Cây Huffman 
private:
	HuffNode* root;
public:
	HuffmanTree(){}
	HuffmanTree(pair<char, int> c, int w, int h){
		root = new LeafNode(c, w, h);
	}
	HuffmanTree(HuffmanTree* a, HuffmanTree* b){
		root = new InternalNode(a->root, b->root);
	}
	~HuffmanTree(){}
	HuffNode* getRoot(){
		return this->root;
	}
};

struct Compare { // Hàm đê thực hiện như min heap trong priority queue 
	bool operator() (HuffmanTree* a, HuffmanTree* b){
		if (a->getRoot()->getWeight() != b->getRoot()->getWeight()){
			return a->getRoot()->getWeight() > b->getRoot()->getWeight();
		}
		LeafNode* leaf1 = dynamic_cast<LeafNode*>(a->getRoot());
		LeafNode* leaf2 = dynamic_cast<LeafNode*>(b->getRoot());
		return leaf1->getSymbol().second > leaf2->getSymbol().second;
	}
};



inline void simulate(string filename)
{
	JJK_RESTAURANT* Nha_hang_chung = NULL;
	ifstream ss(filename);
	if (ss.fail()) {
		cout << "ERROR: " << filename << endl;
		return;
	}
	string str, maxsize, name, num;
	while (ss >> str){
		if (str == "MAXSIZE"){
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
			Nha_hang_chung = new JJK_RESTAURANT();
		}
		else if (str == "LAPSE"){
			ss >> name;
			Nha_hang_chung->LAPSE(name);
		}
		else if (str == "KOKUSEN"){
			Nha_hang_chung->KOKUSEN();
		}
		else if (str == "KEITEIKEN"){
			ss >> num;
			Nha_hang_chung->KEITEIKEN(stoi(num));
		}
		else if (str == "HAND"){
			Nha_hang_chung->HAND();
		}
		else if (str == "LIMITLESS"){
			ss >> num;
			Nha_hang_chung->LIMITLESS(stoi(num));
		}
		else if (str == "CLEAVE"){
			ss >> num;
			Nha_hang_chung->CLEAVE(stoi(num));
		}
	}
	delete Nha_hang_chung;
	cout << "Nguyen Dang Cuong \n";
}