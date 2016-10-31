#pragma once
#include <memory>

using namespace std;

namespace AVL {

	template <typename V, class T>
	class Node {
	public:
		Node(Node<V, T>* p, T* v, V k);
		Node<V, T>* left;
		Node<V, T>* right;
		Node<V, T>* parent;
		T* value;
		V key;
		unsigned char height;
		char bfactor() const;
		void updateHeight();
	};
}