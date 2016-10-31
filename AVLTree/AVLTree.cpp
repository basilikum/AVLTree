#pragma once
#include <memory>
#include "AVLNode.h"
#include "AVLTree.h"

using namespace std;
using namespace AVL;

template <typename V, class T>
AVLTree<V, T>::AVLTree() : head(nullptr) {}

template <typename V, class T>
AVLTree<V, T>::~AVLTree() {
	clear(head);
}

template <typename V, class T>
void AVLTree<V, T>::clear(Node<V, T>* node) {
	if (!node) {
		return;
	}
	clear(node->left);
	clear(node->right);
	delete node;
}

template <typename V, class T>
void AVLTree<V, T>::rotateleft(Node<V, T>* node) {
	auto hl = node->left;
	auto hlr = hl->right;
	switchParent(node, hl);
	hl->right = node;
	node->parent = hl;
	node->left = hlr;
	hlr->parent = node;
	node->updateHeight();
	hl->updateHeight();
}

template <typename V, class T>
void AVLTree<V, T>::rotateright(Node<V, T>* node) {
	auto hr = node->right;
	auto hrl = hr->left;
	switchParent(node, hr);
	hr->left = node;
	node->parent = hr;
	node->right = hrl;
	hrl->parent = node;
	node->updateHeight();
	hr->updateHeight();
}

template <typename V, class T>
void AVLTree<V, T>::rotateleftright(Node<V, T>* node) {
	auto hl = node->left;
	auto hlr = hl->right;
	auto hlrr = hlr->right;
	auto hlrl = hlr->left;
	switchParent(node, hlr);
	hlr->left = hl;
	hl->parent = hlr;
	hlr->right = node;
	node->parent = hlr;
	node->left = hlrr;
	hlrr->parent = node;
	hl->right = hlrl;
	hlrl->parent = hl;
	node->updateHeight();
	hl->updateHeight();
	hlr->updateHeight();
}

template <typename V, class T>
void AVLTree<V, T>::rotaterightleft(Node<V, T>* node) {
	auto hr = node->right;
	auto hrl = hr->left;
	auto hrll = hrl->left;
	auto hrlr = hrl->right;
	switchParent(node, hrl);
	hrl->right = hr;
	hr->parent = hrl;
	hrl->left = node;
	node->parent = hrl;
	node->right = hrll;
	hrll->parent = node;
	hr->left = hrlr;
	hrlr->parent = hr;
	node->updateHeight();
	hr->updateHeight();
	hrl->updateHeight();
}

template <typename V, class T>
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
		head.parent = nullptr;
	}
}

template <typename V, class T>
Node<V, T>* AVLTree<V, T>::get_min(Node<V, T>* node) {
	while (true) {
		if (!node->left) {
			return node;
		}
		node = node->left;
	}
}

template <typename V, class T>
Node<V, T>* AVLTree<V, T>::get_max(Node<V, T>* node) {
	while (true) {
		if (!node->right) {
			return node;
		}
		node = node->right;
	}
}

template <typename V, class T>
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

template <typename V, class T>
void AVLTree<V, T>::insert(const V key, const T* value) {
	node = new Node<V, T>(nullptr, value, key);
	if (!head) {
		head = node;
		return;
	}
	auto n = head;
	while (true) {
		if (n->key < key) {
			if (!n->right) {
				n->right = node;
				node.parent = n;
				break;
			} else {
				n = n->right;
			}
		} else {
			if (!n->left) {
				n->left = node;
				node.parent = n;
				break;
			}
			else {
				n = n->left;
			}
		}
	}
	balance(node);
}

template <typename V, class T>
void AVLTree<V, T>::remove(const V key) {
	auto n = head;
	bool fromright = false;
	while (n) {
		if (n->key == key) {
			if (n->left && n->right) {
				if (fromright) {
					auto repln = get_min(n);
					repln->parent->left = nullptr;
					if (n->parent) {
						n->parent->right = repln;
					}
					repln->parent = n->parent;
					repln->left = n->left;
					repln->right = n->right;
					balance(repln);
				} else {
					auto repln = get_max(n);
					repln->parent->right = nullptr;
					if (n->parent) {
						n->parent->left = repln;
					}
					repln->parent = n->parent;
					repln->left = n->left;
					repln->right = n->right;
					balance(repln);
				}
			} else if (n->left) {
				if (fromright) {
					if (n->parent) {
						n->parent->right = n->left;
					}
					n->left->parent = n->parent;
				} else {
					if (n->parent) {
						n->parent->left = n->left;
					}
					n->left->parent = n->parent;
				}
				balance(n->left);
			} else if (n->right) {
				if (fromright) {
					if (n->parent) {
						n->parent->right = n->right;
					}
					n->right->parent = n->parent;
				} else {
					if (n->parent) {
						n->parent->left = n->right;
					}
					n->right->parent = n->parent;
				}
				balance(n->right);
			} else if (n->parent) {
				if (fromright) {
					n->parent->right = nullptr;
				} else {
					n->parent->left = nullptr;
				}
				balance(n->parent);
			}
			n->left = nullptr;
			n->right = nullptr;
			n->parent = nullptr;
			delete n;
			break;
		} else if (n->key < key) {
			n = n->right;
			fromright = true;
		} else {
			n = n->left;
			fromright = false;
		}
	}
}

template <typename V, class T>
T* AVLTree<V, T>::get(const V key) const {
	auto n = head;
	while (n) {
		if (n->key == key) {
			return n->value;
			break;
		} else if (n->key < key) {
			n = n->right;
		} else {
			n = n->left;
		}
	}
	return nullptr;
}

