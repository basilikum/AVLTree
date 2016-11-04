#pragma once
#include <memory>
#include "AVLNode.h"

#ifndef AVLNODE_IMPL__
#define AVLNODE_IMPL__

using namespace std;

template <class V, class T>
Node<V, T>::Node(Node<V, T>* p, T v, V k) : left(nullptr), right(nullptr), parent(p), value(move(v)), key(k) {}

template <typename V, class T>
char Node<V, T>::bfactor() const {
	return (right ? right->height : 0) - (left ? left->height : 0);
}

template <typename V, class T>
void Node<V, T>::updateHeight() {
	unsigned char hl = (left ? left->height : 0);
	unsigned char hr = (right ? right->height : 0);
	height = (hl > hr ? hl : hr) + 1;
}

#endif