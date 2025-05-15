#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <climits>
#include <cmath>
#include "utils.h"
#include "BinaryTree.h"

namespace HKSTL {

template<typename T>
class BinarySearchTree : public BinaryTree<T> {
protected:
	using BinaryTree<T>::root;
	//using BinaryTree<T>::clear();
	int n;
	virtual BTNode<T> *findLast(T x);
	virtual bool addChild(BTNode<T> *p, BTNode<T> *u);
	virtual void splice(BTNode<T> *u);
	virtual void remove(BTNode<T> *u);
	virtual void rotateRight(BTNode<T> *u);
	virtual void rotateLeft(BTNode<T> *u);
	virtual bool add(BTNode<T> *u);
public:
	BinarySearchTree(): n(0) {}
	virtual ~BinarySearchTree() {}
	virtual bool add(T x);
	virtual bool remove(T x);
	//virtual T find(T x);
	virtual bool find(T x);
	virtual int size();
	virtual void clear();
};

template<typename T>
bool BinarySearchTree<T>::find(T x) { 	// findEQ 
	BTNode<T> *w = root;
	while (w != nullptr) {
		int comp = compare(x, w->data);
		if 		(comp < 0) { w = w->left; 	} 
		else if (comp > 0) { w = w->right; 	} 
		else 			   { return true;	}
	}
	return false;
}

/*
// Return the smallest value of the tree that is greater than or equal to x
template<typename T>
T BinarySearchTree<T>::find(T x) {
	BTNode<T> *w = root, *z = nullptr;
	while (w != nullptr) {
		int comp = compare(x, w->data);
		if (comp < 0) {
			z = w;		// x < w->data, then return w->data that is smallest, but greater than x
			w = w->left;
		} else if (comp > 0) {
			//z = w;		// x > w->data, then return w->data that is largest, but less than x
			w = w->right;
		} else {
			return w->data;
		}
	}
	return z == nullptr ? T() : z->data;
}
*/

// -----------------------------------------------------------------------------
// Addition
// -----------------------------------------------------------------------------
template<typename T>
bool BinarySearchTree<T>::add(T x) {
	BTNode<T> *p = findLast(x); 	// a parent of the new node
	BTNode<T> *u = new BTNode<T>;
	u->data = x;
	return addChild(p, u);
}

template<typename T>
bool BinarySearchTree<T>::add(BTNode<T> *u) {
	BTNode<T> *p = findLast(u->data);
	return addChild(p, u);
}

template<typename T>
BTNode<T>* BinarySearchTree<T>::findLast(T x) {
	BTNode<T> *w = root, *prev = nullptr;
	while (w != nullptr) {
		prev = w;	// keep track of the previous node
		int comp = compare(x, w->data);
		if 		(comp < 0) 	{ w = w->left; 	}	 
		else if (comp > 0) 	{ w = w->right;	} 
		else 				{ return w;		}	
	}
	return prev;
}

template<typename T>
bool BinarySearchTree<T>::addChild(BTNode<T> *p, BTNode<T> *u) {
		if (p == nullptr) {
			root = u;              // inserting into empty tree
		} else {
			int comp = compare(u->data, p->data);
			// link from parent to child
			if 		(comp < 0) 	{ p->left = u;	} 
			else if (comp > 0) 	{ p->right = u;	} 
			else 				{ return false; }  // u.x is already in the tree
			u->parent = p;	// link from child to parent
		}
		n++;
		return true;
}

// -----------------------------------------------------------------------------
// Removal
// -----------------------------------------------------------------------------
template<typename T>
void BinarySearchTree< T>::splice(BTNode<T> *u) { 	// cut a node from a tree
	BTNode<T> *s, *p;
	
	// s will be 1. left child 2. right child 3. nullptr (if it is leaf)
	if (u->left != nullptr) {
		s = u->left;
	} else {
		s = u->right;
	}

	if (u == root) { 	
		root = s;
		p = nullptr;
	} else {
		p = u->parent;
		// link u's parent to u's child to unlink u
		if (p->left == u) { 	
			p->left = s;
		} else {
			p->right = s;     	
		}
	}
	// connect s->parent to its parent.
	if (s != nullptr) {	      		 
		s->parent = p;
	}
	n--;
}

// Complex one
// 1. If u is a leaf, then we can just detach u from its parent.
// 2. If u has only one child, then we can splice u from the tree by having u.parent adopt u's child
// 3. If u has two children. Replace the node from "its right child's smallest decedent". 
template<typename T>
void BinarySearchTree<T>::remove(BTNode<T> *u) {
	if (u->left == nullptr || u->right == nullptr) { 	// Case 1 or 2
		splice(u);
		delete u;
	} else {  // Case 3
		BTNode<T> *w = u->right;
		while (w->left != nullptr)	// search its right child's smallest decedent
			w = w->left;
		u->data = w->data;	// replace u's data with its right child's smallest decedent
		splice(w);          // detach w
		delete w;
	}
}

template<typename T>
bool BinarySearchTree<T>::remove(T x) {
	BTNode<T> *u = findLast(x);
	if (u != nullptr && compare(x, u->data) == 0) {
		remove(u);
		return true;
	}
	return false;
}

template<typename T> inline
int BinarySearchTree<T>::size() {
	return n;
}

template<typename T> inline
void BinarySearchTree<T>::clear() {
	BinaryTree<T>::clear();
	n = 0;
}

template<typename T>
void BinarySearchTree<T>::rotateLeft(BTNode<T> *u) {
	BTNode<T> *w = u->right;
	w->parent = u->parent;
	if (w->parent != nullptr) {
		if (w->parent->left == u) {
			w->parent->left = w;
		} else {
			w->parent->right = w;
		}
	}
	u->right = w->left;
	if (u->right != nullptr) {
		u->right->parent = u;
	}
	u->parent = w;
	w->left = u;
	if (u == root) { root = w; root->parent = nullptr; }
}

template<typename T>
void BinarySearchTree<T>::rotateRight(BTNode<T> *u) {
	BTNode<T> *w = u->left;
	w->parent = u->parent;
	if (w->parent != nullptr) {
		if (w->parent->left == u) {
			w->parent->left = w;
		} else {
			w->parent->right = w;
		}
	}
	u->left = w->right;
	if (u->left != nullptr) {
		u->left->parent = u;
	}
	u->parent = w;
	w->right = u;
	if (u == root) { root = w; root->parent = nullptr; }
}

}  // namespace HKSTL
#endif  // BINARYSEARCHTREE_H_
