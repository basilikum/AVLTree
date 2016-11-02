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
		}
		else {
			node->parent->right = node2;
			node2->parent = node->parent;
		}
	}
	else {
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
		cout << "BALANCE " << (int)bf << "/" << (int)node->height << endl;
		if (bf == -2) {
			if (node->left->bfactor() > 0) {
				cout << "LR" << endl;
				rotateleftright(node);
			} else {
				cout << "R" << endl;
				rotateright(node);
			}
		} else if (bf == 2) {
			if (node->right->bfactor() < 0) {
				cout << "RL" << endl;
				rotaterightleft(node);
			} else {
				cout << "L" << endl;
				rotateleft(node);
			}
		}
		node = node->parent;
	}
}

template <class V, class T>
void AVLTree<V, T>::insert(const V key, const T* value) {
	auto node = new Node<V, T>(nullptr, value, key);
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
void AVLTree<V, T>::remove_node(Node<V, T>* node) {
	if (!node) {
		return;
	}
	bool fromright = node->parent ? node->parent->right == node : false;
	if (!node->right) {
		if (node->left) {
			node->value = node->left->value;
			node->key = node->left->key;
			delete node->left;
			node->left = nullptr;
			balance(node);
		} else {
			if (fromright) {
				node->parent->right = nullptr;
			} else {
				node->parent->left = nullptr;
			}
			balance(node->parent);
			delete node;
		}
	} else {
		auto repln = get_min(node->right);
		n->value = repln->value;
		node->key = repln->key;
		remove(repln);
		balance(repln);
	}
	if (node->left && node->right) {
		auto repln = get_min(node->right);
		n->value = repln->value;
		node->key = repln->key;
		remove(repln);
		balance(repln);
	} else {
		
		if (node->left) {
			if (fromright) {
				if (node->parent) {
					node->parent->right = node->left;
				} else {
					head = node->left;
				}
			} else {
				if (node->parent) {
					node->parent->left = node->left;
				} else {
					head = node->left;
				}
			}
			node->left->parent = node->parent;
			node->left->updateHeight();
			//balance(node->left);
		} else if (node->right) {
			if (fromright) {
				if (node->parent) {
					node->parent->right = node->right;
				} else {
					head = node->right;
				}
			} else {
				if (node->parent) {
					node->parent->left = node->right;
				} else {
					head = node->right;
				}
			}
			node->right->parent = node->parent;
			node->right->updateHeight();
			//balance(node->right);
		} else if (node->parent) {
			if (fromright) {
				node->parent->right = nullptr;
			} else {
				node->parent->left = nullptr;
			}
			//balance(n->parent);
		} else {
			head = nullptr;
		}
		node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;
		delete node;
	}
}

template <class V, class T>
void AVLTree<V, T>::remove(const V key) {
	remove_node(get_node(key));
}

template <class V, class T>
Node<V, T>* AVLTree<V, T>::get_node(const V key) const {
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
T* AVLTree<V, T>::get(const V key) const {
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