/*
 * Treap.h
 *
 *  Created on: 2011-11-28
 *      Author: morin
 */

#ifndef TREAP_H_
#define TREAP_H_

#include <climits>

#include "BinarySearchTree.h"

namespace ods {

template<class Node, class T> class Treap;

template<class Node, class T>
class TreapNode : public BSTNode<Node, T> {
protected:
	friend class Treap<Node,T>;
	int p;
};

template<class Node, class T>
class Treap : public BinarySearchTree<Node, T> {
protected:
	using BinaryTree<Node>::root;
	using BinaryTree<Node>::nil;
	using BinarySearchTree<Node,T>::null;
	using BinarySearchTree<Node,T>::n;
	void bubbleUp(Node *u);
	void trickleDown(Node *u);

	// Declare BST's virtual functions
	virtual Node *findLast(T x);
public:
	Treap();
	Treap(T null);
	virtual ~Treap();
	virtual bool add(T x);
	virtual bool remove(T x);
	virtual Treap<Node,T>* split(T x);
	virtual void absorb(Treap<Node,T> &t);

	// Declare BST's virtual functions
	virtual void splice(Node *u);
	virtual void rotateRight(Node *u);
	virtual void rotateLeft(Node *u);
};

template<class T>
class TreapNode1 : public TreapNode<TreapNode1<T>, T> { };

template<class T>
class Treap1 : public Treap<TreapNode1<T>, T> { };

template<class Node, class T>
Treap<Node, T>::Treap() {
	// nothing to do
}

template<class Node, class T>
Treap<Node, T>::Treap(T null) : BinarySearchTree<Node,T>(null) {
	// nothing to do
}

template<class Node, class T>
bool Treap<Node, T>::add(T x) {
	Node *u = new Node;
	u->x = x;
	u->p = rand();
	if (BinarySearchTree<Node,T>::add(u)) {
		bubbleUp(u);
		return true;
	}
	return false;
}

template<class Node, class T>
Treap<Node, T>::~Treap() {
	// nothing to do
}

template<class Node, class T>
void Treap<Node, T>::bubbleUp(Node *u) {
	while (u->parent != nil && u->parent->p > u->p) {
		if (u->parent->right == u) {
			rotateLeft(u->parent);
		} else {
			rotateRight(u->parent);
		}
	}
	if (u->parent == nil) {
		root = u;
	}
}

template<class Node, class T>
bool Treap<Node, T>::remove(T x) {
	Node *u = findLast(x);
	if (u != nil && compare(u->x, x) == 0) {
		trickleDown(u);
		splice(u);
		delete u;
		return true;
	}
	return false;
}


template<class Node, class T>
void Treap<Node, T>::trickleDown(Node *u) {
	while (u->left != nil || u->right != nil) {
		if (u->left == nil) {
			rotateLeft(u);
		} else if (u->right == nil) {
			rotateRight(u);
		} else if (u->left->p < u->right->p) {
			rotateRight(u);
		} else {
			rotateLeft(u);
		}
		if (root == u) {
			root = u->parent;
		}
	}
}

/**
 * Warning - you can not call size() on the original treap or the new treap
 * after calling this method
 */
template<class Node, class T>
Treap<Node,T>* Treap<Node, T>::split(T x) {
	Node* u = findLast(x);
	Node* s = new Node();
	if (u->right == nil) {
		u->right = s;
	} else {
		u = u->right;
		while (u->left != nil)
			u = u->left;
		u->left = s;
	}
	s->parent = u;
	s->p = INT_MIN;
	bubbleUp(s);
	this->root = s->right;
	if (this->root != nil) this->root->parent = nil;
	n = INT_MIN;
	Treap<Node,T> *ret = new Treap<Node,T>(null);
	ret->root = s->left;
	if (ret->root != nil) ret->root->parent = nil;
	n = INT_MIN;
	return ret;
}
/**
 * Absorb the elements of treap t, which should all be smaller than
 * all the elements in this
 * @param t
 * @return
 */
template<class Node, class T>
void Treap<Node,T>::absorb(Treap<Node,T> &t) {
	Node* s = new Node();
	s->right = this->root;
	if (this->root != nil) this->root->parent = s;
	s->left = t.root;
	if (t.root != nil) t.root->parent = s;
	this->root = s;
	t.root = nil;
	trickleDown(s);
	splice(s);
}

// Add declaration of BST's virtual functions
template<class Node, class T>
void Treap<Node,T>::splice(Node *u) {
    BinarySearchTree<Node, T>::splice(u);
}

template<class Node, class T>
void Treap<Node,T>::rotateRight(Node *u) {
    BinarySearchTree<Node, T>::rotateRight(u);
}

template<class Node, class T>
void Treap<Node,T>::rotateLeft(Node *u) {
    BinarySearchTree<Node, T>::rotateLeft(u);
}

template<class Node, class T>
Node* Treap<Node,T>::findLast(T x) {
    return BinarySearchTree<Node, T>::findLast(x);
}

} /* namespace ods */
#endif /* TREAP_H_ */
