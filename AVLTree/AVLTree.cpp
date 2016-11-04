#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "AVLNode.h"
#include "AVLTree.h"

#ifndef AVLTREE_IMPL__
#define AVLTREE_IMPL__

using namespace std;

template <class V, class T>
AVLTree<V, T>::AVLTree() {}

template <class V, class T>
AVLTree<V, T>::~AVLTree() {
	clear(head);
}

template <class V, class T>
void AVLTree<V, T>::clear(Node<V, T>* node) {
	if (!node) {
		return;
	}
	clear(node->left);
	clear(node->right);
	delete node;
}

template <class V, class T>
void AVLTree<V, T>::rotateright(Node<V, T>* node) {
	auto hl = node->left;
	auto hlr = hl->right;
	switchparent(node, hl);
	hl->right = node;
	node->parent = hl;
	node->left = hlr;
	if (hlr) {
		hlr->parent = node;
	}
	node->updateHeight();
	hl->updateHeight();
}

template <class V, class T>
void AVLTree<V, T>::rotateleft(Node<V, T>* node) {
	auto hr = node->right;
	auto hrl = hr->left;
	switchparent(node, hr);
	hr->left = node;
	node->parent = hr;
	node->right = hrl;
	if (hrl) {
		hrl->parent = node;
	}
	node->updateHeight();
	hr->updateHeight();
}

template <class V, class T>
void AVLTree<V, T>::rotateleftright(Node<V, T>* node) {
	auto hl = node->left;
	auto hlr = hl->right;
	auto hlrr = hlr->right;
	auto hlrl = hlr->left;
	switchparent(node, hlr);
	hlr->left = hl;
	hl->parent = hlr;
	hlr->right = node;
	node->parent = hlr;
	node->left = hlrr;
	if (hlrr) {
		hlrr->parent = node;
	}
	hl->right = hlrl;
	if (hlrl) {
		hlrl->parent = hl;
	}
	node->updateHeight();
	hl->updateHeight();
	hlr->updateHeight();
}

template <class V, class T>
void AVLTree<V, T>::rotaterightleft(Node<V, T>* node) {
	auto hr = node->right;
	auto hrl = hr->left;
	auto hrll = hrl->left;
	auto hrlr = hrl->right;
	switchparent(node, hrl);
	hrl->right = hr;
	hr->parent = hrl;
	hrl->left = node;
	node->parent = hrl;
	node->right = hrll;
	if (hrll) {
		hrll->parent = node;
	}
	hr->left = hrlr;
	if (hrlr) {
		hrlr->parent = hr;
	}
	node->updateHeight();
	hr->updateHeight();
	hrl->updateHeight();
}

template <class V, class T>
void AVLTree<V, T>::switchparent(Node<V, T>* node, Node<V, T>* node2) {
	if (node->parent) {
		if (node->parent->left == node) {
			node->parent->left = node2;
			node2->parent = node->parent;
		} else {
			node->parent->right = node2;
			node2->parent = node->parent;
		}
	} else {
		head = node2;
		head->parent = nullptr;
	}
}

template <class V, class T>
Node<V, T>* AVLTree<V, T>::get_min(Node<V, T>* node) {
	while (true) {
		if (!node->left) {
			break;
		}
		node = node->left;
	}
	return node;
}

template <class V, class T>
Node<V, T>* AVLTree<V, T>::get_max(Node<V, T>* node) {
	while (true) {
		if (!node->right) {
			break;
		}
		node = node->right;
	}
	return node;
}

template <class V, class T>
void AVLTree<V, T>::balance(Node<V, T>* node) {
	while (node) {
		node->updateHeight();
		auto bf = node->bfactor();
		if (bf == -2) {
			if (node->left->bfactor() > 0) {
				rotateleftright(node);
			} else {
				rotateright(node);
			}
		} else if (bf == 2) {
			if (node->right->bfactor() < 0) {
				rotaterightleft(node);
			} else {
				rotateleft(node);
			}
		}
		node = node->parent;
	}
}

template <class V, class T>
void AVLTree<V, T>::insert(V key, T value) {
	auto node = new Node<V, T>(nullptr, move(value), key);
	if (!head) {
		head = node;
		return;
	}
	auto n = head;
	while (true) {
		if (n->key < key) {
			if (!n->right) {
				n->right = node;
				node->parent = n;
				break;
			} else {
				n = n->right;
			}
		} else {
			if (!n->left) {
				n->left = node;
				node->parent = n;
				break;
			}
			else {
				n = n->left;
			}
		}
	}
	balance(node);
}

template <class V, class T>
void AVLTree<V, T>::swap(Node<V, T>* node1, Node<V, T>* node2) {
	node1->value = move(node2->value);
	node1->key = node2->key;
}

template <class V, class T>
void AVLTree<V, T>::remove(V key) {
	auto node = get_node(key);
	if (!node) {
		return;
	}
	if (!node->right) {
		if (node->left) {
			swap(node, node->left);
			delete node->left;
			node->left = nullptr;
			balance(node);
		} else {
			auto p = node->parent;
			if (p->right == node) {
				p->right = nullptr;
			} else {
				p->left = nullptr;
			}
			delete node;
			balance(p);
		}
	} else {
		auto repln = get_min(node->right);
		swap(node, repln);
		if (repln->right) {
			swap(repln, repln->right);
			delete repln->right;
			repln->right = nullptr;
			balance(repln);
		} else {
			auto p = repln->parent;
			if (p->right == repln) {
				p->right = nullptr;
			} else {
				p->left = nullptr;
			}
			delete repln;
			balance(p);
		}
		
	}
}

template <class V, class T>
Node<V, T>* AVLTree<V, T>::get_node(V key) const {
	auto n = head;
	while (n) {
		if (n->key == key) {
			return n;
		} else if (n->key < key) {
			n = n->right;
		} else {
			n = n->left;
		}
	}
	return nullptr;
}

template <class V, class T>
T AVLTree<V, T>::get(V key) const {
	auto n = get_node(key);
	if (n) {
		return n->value;
	}
	return nullptr;
}

template <class V, class T>
void AVLTree<V, T>::print() const {
	print(head, "0");
	cout << "###########" << endl;
}

template <class V, class T>
void AVLTree<V, T>::print(const Node<V, T>* n, string o) const {
	if (!n) {
		return;
	}
	cout << n->key << ": " << o << endl;
	print(n->left, o + "l");
	print(n->right, o + "r");
}



#endif