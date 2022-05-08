#include <iostream>
using namespace std;

struct List {
	string key;
	int value;
	List* next;
};
List* head;
List* tail;
class RBTree {
private:

	struct Node {
		string data;
		int value;
		Node* parent;
		Node* left;
		Node* right;
		bool isRed; // true - Red, false - Black
	};
	Node* root;
	Node* NIL;


	void clearHelper(Node* root)
	{
		if (root != NIL)
		{
			clearHelper(root->left);
			clearHelper(root->right);
			delete root;
		}
	}

	bool searchTreeHelper(Node* node, string key) {
		if (node == NIL || key == node->data) {
			if (node == NIL) {
				cout << "The tree does not contain key " << key << endl;
				return false;
			}
			else {
				cout << "The tree does contain " << key << ". Its value is " << node->value << endl;
				return true;
			}
		}
		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	void recoveryDelete(Node* sec) {
		Node* brother;
		while (sec != root && sec->isRed == false) {
			if (sec == sec->parent->left) {
				brother = sec->parent->right;
				if (brother->isRed == true) {
					brother->isRed = false;
					sec->parent->isRed = true;
					leftRotate(sec->parent);
					brother = sec->parent->right;
				}

				if (brother->left->isRed == false && brother->right->isRed == false) {
					brother->isRed = true;
					sec = sec->parent;
				}
				else {
					if (brother->right->isRed == false) {
						brother->left->isRed = false;
						brother->isRed = true;
						rightRotate(brother);
						brother = sec->parent->right;
					}
					brother->isRed = sec->parent->isRed;
					sec->parent->isRed = false;
					brother->right->isRed = false;
					leftRotate(sec->parent);
					sec = root;
				}
			}
			else {
				brother = sec->parent->left;
				if (brother->isRed == true) {
					brother->isRed = false;
					sec->parent->isRed = true;
					rightRotate(sec->parent);
					brother = sec->parent->left;
				}

				if (brother->left->isRed == false && brother->right->isRed == false) {
					brother->isRed = true;
					sec = sec->parent;
				}
				else {
					if (brother->left->isRed == false) {
						brother->right->isRed = false;
						brother->isRed = true;
						leftRotate(brother);
						brother = sec->parent->left;
					}
					brother->isRed = sec->parent->isRed;
					sec->parent->isRed = false;
					brother->left->isRed = false;
					rightRotate(sec->parent);
					sec = root;
				}
			}
		}
		sec->isRed = false;
	}
	void replacing(Node* first, Node* sec) {
		if (first->parent == nullptr) {
			root = sec;
		}
		else if (first == first->parent->left) {
			first->parent->left = sec;
		}
		else {
			first->parent->right = sec;
		}
		sec->parent = first->parent;
	}

	void recoveryInsert(Node* key) {
		Node* uncle;
		while (key->parent->isRed == true) {
			if (key->parent == key->parent->parent->right) {
				uncle = key->parent->parent->left; // uncle
				if (uncle->isRed == true) {
					uncle->isRed = false;
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					key = key->parent->parent;
				}
				else {
					if (key == key->parent->left) {
						key = key->parent;
						rightRotate(key);
					}
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					leftRotate(key->parent->parent);
				}
			}
			else {
				uncle = key->parent->parent->right;

				if (uncle->isRed == true) {
					uncle->isRed = false;
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					key = key->parent->parent;
				}
				else {
					if (key == key->parent->right) {
						key = key->parent;
						leftRotate(key);
					}
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					rightRotate(key->parent->parent);
				}
			}
			if (key == root) {
				break;
			}
		}
		root->isRed = false;
	}
	Node* max(Node* node) {
		while (node->right != NIL) {
			node = node->right;
		}
		return node;
	}
	Node* min(Node* node) {
		while (node->left != NIL) {
			node = node->left;
		}
		return node;
	}

public:
	RBTree() {
		NIL = new Node;
		NIL->isRed = false;
		NIL->left = nullptr;
		NIL->right = nullptr;
		root = NIL;
	}

	int get_size;
	int getSize()
	{
		return get_size;
	}

	bool isEmpty()
	{
		if (get_size != 0)
		{
			return 0;
		}
		else return 1;
	}


	bool find(string k) {
		return searchTreeHelper(this->root, k);
	}
	void leftRotate(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != NIL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	void rightRotate(Node* x) {
		Node* y = x->left;
		x->left = y->right;
		if (y->right != NIL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insert(string key, int value) {
		// Binary Search Insertion
		Node* node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->value = value;
		node->left = NIL;
		node->right = NIL;
		node->isRed = true;


		Node* items_parent = nullptr;
		Node* item = this->root;

		while (item != NIL) {
			items_parent = item;

			if (node->data < item->data) {
				item = item->left;
			}
			else {
				item = item->right;
			}
		}

		node->parent = items_parent;
		if (items_parent == nullptr) {
			root = node;
		}
		else if (node->data < items_parent->data) {
			items_parent->left = node;
		}
		else {
			items_parent->right = node;
		}
		if (node->value == root->value)
		{
			List* get = new List;
			get_size = 0;
			get_size++;
			get->value = value;
			get->key = key;
			get->next = NULL;
			head = tail = get;
		}
		else {
			List* get = head;
			while (get->next != NULL)
			{
				get = get->next;
			}
			List* newGet = new List;
			newGet->key = key;
			newGet->value = value;
			newGet->next = NULL;
			tail = newGet;
			get->next = newGet;
			get_size++;
		}


		// if new node is a root node, return
		if (node->parent == nullptr) {
			node->isRed = false;
			return;
		}

		// if the grandparent is null, return
		if (node->parent->parent == nullptr) {
			return;
		}

		recoveryInsert(node);

	}

	Node* getRoot() {
		return this->root;
	}

	void remove(string data) {

		Node* node = root;

		Node* cur = NIL;
		Node* sec;  Node* first;
		bool found = false;
		while (node != NIL) {
			if (node->data == data) {
				cur = node;
				found = true;
			}
			if (node->data <= data) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}
		get_size--;

		if (found == false && node == NIL) {
			throw "There's no key like that";
			return;
		}
		List* get = head;
		while (get->key != data)
		{
			get = get->next;
		}
		if (get == head)
		{
			head = get->next;
			get->key = "";
			get->value = NULL;
			get = NULL;
			delete(get);
		}
		else
		{
			if (get == tail)
			{
				get = head;
				while (get->next->key != tail->key)
				{
					get = get->next;
				}
				tail = get;
				tail->next = NULL;
			}
			else
			{
				List* deleteGet = get;
				get = head;
				while (get->next->key != data)
				{
					get = get->next;
				}
				get->next = deleteGet->next;
				deleteGet->key = "";
				deleteGet->value = NULL;
				deleteGet = NULL;
				delete(deleteGet);
			}
		}
		first = cur;
		bool instead_original_color = first->isRed;
		if (cur->left == NIL) {
			sec = cur->right;
			replacing(cur, cur->right);
		}
		else if (cur->right == NIL) {
			sec = cur->left;
			replacing(cur, cur->left);
		}
		else {
			first = min(cur->right);
			instead_original_color = first->isRed;
			sec = first->right;
			if (first->parent == cur) {
				sec->parent = first;
			}
			else {
				replacing(first, first->right);
				first->right = cur->right;
				first->right->parent = first;
			}

			replacing(cur, first);
			first->left = cur->left;
			first->left->parent = first;
			first->isRed = cur->isRed;
		}
		delete cur;
		if (instead_original_color == false) {
			recoveryDelete(sec);
		}
	}

	List* printGetKeys()
	{
		List* get = head;
		while (get != tail->next)
		{
			cout << get->key << " ";
			get = get->next;
		}
		cout << endl;
		return get;
	}
	List* printGetValues()
	{
		List* get = head;

		while (get != tail->next)
		{
			cout << get->value << " ";
			get = get->next;
		}
		cout << endl;
		return get;
	}

	void clear()
	{
		if (root != NIL) {
			clearHelper(this->root);
			this->root = NIL;
		}
		else
		{
			try {
				if (root == NIL)
					throw "The tree is empty";
			}
			catch (const char* msg)
			{
				cout << msg << endl;

			}
		}
	}

};


int main() {
	RBTree tree;
	tree.insert("G", 36);
	tree.insert("B", 25);
	tree.insert("D", 9);
	tree.insert("C", 16);
	tree.insert("J", 26);
	tree.insert("E", 36);
	tree.insert("A", 49);
	tree.insert("F", 64);
	tree.insert("H", 81);
	tree.insert("I", 100);
	cout << "The list of keys:" << endl;
	cout << tree.printGetKeys();
	cout << "The list of values:" << endl;
	tree.printGetValues();
	cout << "Now let's remove key J" << endl;
	tree.remove("J");
	cout << "The list of keys:" << endl;
	tree.printGetKeys();
	cout << "The list of values:" << endl;
	tree.printGetValues();
	cout << "Let's look for key J" << endl;
	tree.find("J");
	cout << "clear the map" << endl;
	tree.clear();

	return 0;
}
