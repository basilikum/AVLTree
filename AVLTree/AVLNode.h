#pragma once
#include <memory>

using namespace std;

template <class V, class T>
class Node {
public:
	Node(Node<V, T>* p, const T* v, V k);
	Node<V, T>* left;
	Node<V, T>* right;
	Node<V, T>* parent;
	const T* value;
	V key;
	unsigned char height;
	char bfactor() const;
	void updateHeight();
};

#include "AVLNode.cpp"
