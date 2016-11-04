#include <iostream>
#include "AVLTree.h"

using namespace std;

class Item {
public:
	Item(int v, int k) : value(v), key(k) {};
	~Item() {
		cout << "DEL " << key << endl;
	}
	int value;
	int key;
};

int main() {
	auto a = new AVLTree<int, unique_ptr<Item>>();
	a->insert(2, make_unique<Item>(1, 2));
	a->print();
	a->insert(6, make_unique<Item>(1, 6));
	a->print();
	a->insert(3, make_unique<Item>(1, 3));
	a->print();
	a->insert(9, make_unique<Item>(1, 9));
	a->print();
	a->insert(1, make_unique<Item>(1, 1));
	a->print();
	a->insert(4, make_unique<Item>(1, 4));
	a->print();
	a->insert(8, make_unique<Item>(1, 8));
	a->print();
	a->insert(11, make_unique<Item>(1, 11));
	a->print();
	a->remove(3);
	a->print();
	a->remove(9);
	a->print();
	a->remove(1);
	a->print();
	a->remove(2);
	a->print();
	a->remove(6);
	a->print();
	a->remove(8);
	a->print();
	delete a;
	int zz;
	cin >> zz;
	return 0;
}