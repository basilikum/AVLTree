#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "AVLTree.h"


using namespace std;
using namespace AVL;

class Item {
public:
	Item(int v, int k) : value(v), key(k) {};
	int value;
	int key;
};

int main() {
	AVLTree<int, Item> a;
	auto i1 = make_unique<Item>(1, 2);
	a.insert(2, i1.get());
	return 0;
}