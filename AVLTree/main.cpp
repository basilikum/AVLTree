#include <iostream>
#include "AVLTree.h"

using namespace std;

class Item {
public:
	Item(int v, int k) : value(v), key(k) {};
	int value;
	int key;
};

int main() {
	AVLTree<int, Item> a;
	auto i1 = make_unique<Item>(1, 2);
	auto i2 = make_unique<Item>(1, 6);
	auto i3 = make_unique<Item>(1, 3);
	auto i4= make_unique<Item>(1, 9);
	a.insert(2, i1.get());
	a.print();
	a.insert(6, i2.get());
	a.print();
	a.insert(3, i3.get());
	a.print();
	a.insert(9, i4.get());
	a.print();
	a.insert(1, i4.get());
	a.print();
	a.insert(4, i4.get());
	a.print();
	a.insert(8, i4.get());
	a.print();
	a.insert(11, i4.get());
	a.remove(3);
	a.print();
	int zz;
	cin >> zz;
	return 0;
}