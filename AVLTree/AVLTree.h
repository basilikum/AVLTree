#pragma once
#include <string>
#include "AVLNode.h"

using namespace std;

template <class V, class T>
class AVLTree {
private:
	Node<V, T>* head;
	Node<V, T>* get_node(const V key) const;
	void remove_node(Node<V, T>* node);
	void rotateright(Node<V, T>* node);
	void rotateleft(Node<V, T>* node);
	void rotateleftright(Node<V, T>* node);
	void rotaterightleft(Node<V, T>* node);
	Node<V, T>* get_min(Node<V, T>* node);
	Node<V, T>* get_max(Node<V, T>* node);
	void balance(Node<V, T>* node);
	void switchparent(Node<V, T>* node, Node<V, T>* node2);
	void clear(Node<V, T>* node);
public:
	AVLTree();
	~AVLTree();
	void insert(const V key, const T* value);
	void remove(const V key);
	T* get(const V key) const;
	void print() const;
	void print(const Node<V, T>* node, string o) const;
};

#include "AVLTree.cpp"
