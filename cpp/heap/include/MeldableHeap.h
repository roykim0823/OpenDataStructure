/*
 * MeldableHeap.h
 *
 *  Created on: 2011-11-30
 *      Author: morin
 */

#ifndef MELDABLEHEAP_H_
#define MELDABLEHEAP_H_

#include "../../binaryTrees/include/BinaryTree.h"

namespace mySTL {

template<typename T>
class MeldableHeap: public BinaryTree<T> {	
protected:
	using BinaryTree<T>::root;
	int n;
	static BTNode<T> *merge(BTNode<T> *h1, BTNode<T> *h2);
public:
	MeldableHeap(): n(0) {}
	virtual ~MeldableHeap() {}
	bool add(T x);
	T findMin()	{ root->data; }	// same as heap (but min_heap)
	T remove();
	void remove(BTNode<T> *u);
	int size() {
		return n;
	}
};

template<typename T>
BTNode<T>* MeldableHeap<T>::merge(BTNode<T> *h1, BTNode<T> *h2) {
	if (h1 == nullptr) return h2;
	if (h2 == nullptr) return h1;
	
	if (compare(h1->data, h2->data) > 0) return merge(h2, h1); // h1->x > h2->x
        
	// now we know h1->x <= h2->x
	if (rand() % 2) {
		h1->left = merge(h1->left, h2);
		if (h1->left != nullptr) 	h1->left->parent = h1;
	} else {
		h1->right = merge(h1->right, h2);
		if (h1->right != nullptr) 	h1->right->parent = h1;
	}
	return h1;
}

template<typename T>
bool MeldableHeap<T>::add(T x) {
	BTNode<T> *u = new BTNode<T>(x);
	
	root = merge(u, root);
	root->parent = nullptr;
	n++;
	return true;
}

template<typename T>
T MeldableHeap<T>::remove() {
	T x = root->data;
	BTNode<T> *tmp = root;
	root = merge(root->left, root->right);
	delete tmp;
	if (root != nullptr) root->parent = nullptr;
	n--;
	return x;
}

template<typename T>
void MeldableHeap<T>::remove(BTNode<T> *u) {
	if (u == root) {
		remove();
	} else {
		// unlink u from its parent
		if (u == u->parent->left) {
			u->parent->left = nullptr;	
		} else {
			u->parent->right = nullptr;
		}
		u->parent = nullptr;
		root = merge(root, u->left);
		root = merge(root, u->right);
		root->parent = nullptr;
		n--;
	}
}

} /* namespace ods */
#endif /* MELDABLEHEAP_H_ */
