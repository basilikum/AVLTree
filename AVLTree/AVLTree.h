#pragma once
#include <string>
#include <memory>
#include "AVLNode.h"

using namespace std;

template <class V, class T>
class AVLTree {
private:
	Node<V, T>* head;
	Node<V, T>* get_node(V key) const;
	void swap(Node<V, T>* node1, Node<V, T>* node2);
	void rotateright(Node<V, T>* node);
	void rotateleft(Node<V, T>* node);
	void rotateleftright(Node<V, T>* node);
	void rotaterightleft(Node<V, T>* node);
	Node<V, T>* get_min(Node<V, T>* node);
	Node<V, T>* get_max(Node<V, T>* node);
	void balance(Node<V, T>* node);
	void switchparent(Node<V, T>* node, Node<V, T>* node2);
	void clear(Node<V, T>* node);
	void print(const Node<V, T>* node, string o) const;
public:
	AVLTree();
	~AVLTree();
	void insert(V key, T value);
	void remove(V key);
	T get(V key) const;
	void print() const;
};

#include "AVLTree.cpp"
