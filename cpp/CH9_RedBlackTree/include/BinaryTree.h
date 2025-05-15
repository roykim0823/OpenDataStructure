#ifndef BINARYTREE_H_
#define BINARYTREE_H_
#include <iostream>
#include <vector>
#include <new>
#include <memory>

namespace HKSTL {

// Binary Tree Node
template<typename T>
struct BTNode {
	T data;
	BTNode *left;
	BTNode *right;
	BTNode *parent;  // for iterative version of traverse or size                
                   // without the parent field, list or stack is used to       
						       // keep track of the path from the current node to the root 
	BTNode() {
		data = T();
		left = right = parent = nullptr;
	}

	BTNode(T x) {
		data = x;
		left = right = parent = nullptr;
	}
};
		
template<typename T>
class BinaryTree {
protected:
	BTNode<T> *root;	
	virtual int size(BTNode<T> *u);  // from a node
	virtual int height(BTNode<T> *u);  // from a node
	virtual void traverse(BTNode<T> *u);  // from a node
public:
	BinaryTree(): root(nullptr) {}
	virtual ~BinaryTree();
	virtual int depth(BTNode<T> *u);
	virtual int size()  { return size(root); }	
	virtual int height()  { return height(root); }
	virtual void traverse()  { return traverse(root); }
	virtual int size_iter();    	// iterative version
	virtual void traverse_iter();  	// iterative version
	virtual void bfTraverse();
	virtual void clear();
};


template<typename T>
BinaryTree<T>::~BinaryTree() {
	clear();
}

template<typename T>
void BinaryTree<T>::clear() {      
	BTNode<T> *u = root, *prev = nullptr, *next = nullptr;

	while (u != nullptr) {
		if (prev == u->parent) {
			if (u->left != nullptr) next = u->left;
			else if (u->right != nullptr) next = u->right;
			else next = u->parent; 	// left
		} else if (prev == u->left) { 	// try to move left to right
			if (u->right != nullptr) next = u->right;
			else next = u->parent; 	// leaf
		} else { 	// prev == u->right
			// visit all children (already removed) -> leaf
			next = u->parent;
		}
		prev = u;
		if (next == u->parent)	// leaf
		{	
			delete u;
		}
		u = next;
	}
	root = nullptr;
}

// Depth of a node
template<typename T>
int BinaryTree<T>::depth(BTNode<T> *u) {
	int d = 0;
	while (u != root) {
		u = u->parent;
		d++;
	}
	return d;
}

// a size of a node, the number of nodes (Recursive)
template<typename T>
int BinaryTree<T>::size(BTNode<T> *u) {
	if (u == nullptr) return 0;
	return 1 + size(u->left) + size(u->right);
}

// a height of a node (Recursive)
template<typename T>
int BinaryTree<T>::height(BTNode<T> *u) {
	if (u == nullptr) return -1;
	return 1 + max(height(u->left), height(u->right));
}

// Traverse from a node (Recursive)
template<typename T>
void BinaryTree<T>::traverse(BTNode<T> *u) {
	if (u == nullptr) return;
	// cout << u->data << " "; 	// print values in preorder
	traverse(u->left);
	// cout << u->data << " "; 	// print values in inorder
	traverse(u->right);
	// cout << u->data << " "; 	// print values in postorder
}

// Traverse the tree (Iterative) -> Prevent stack overflow
// Left, Right, Parent: Post-Order
template<typename T>
void BinaryTree<T>::traverse_iter() {
	BTNode<T> *u = root, *prev = nullptr, *next = nullptr;
	while (u != nullptr) {
		if (prev == u->parent) {
			if (u->left != nullptr) next = u->left;
			else if (u->right != nullptr) next = u->right;
			else next = u->parent;
		} else if (prev == u->left) {
			if (u->right != nullptr) next = u->right;
			else next = u->parent;
		} else {
			next = u->parent;
		}
		prev = u;
		u = next;
	}
}


// Size the tree (Iterative): same as tranverse2() except for counting "n"
// Left, Right, Parent
template<typename T>
int BinaryTree<T>::size_iter() {
	BTNode<T> *u = root, *prev = nullptr, *next = nullptr;
   	int n = 0;
   	while (u != nullptr) {
   		if (prev == u->parent) {	// if we arrive at a node u from u.parent,
   			n++;	// count a node when it arrives from the parent node at the first time!
   			if (u->left != nullptr) next = u->left;			// first, tries to visit u.left
   			else if (u->right != nullptr) next = u->right;	// second, tries to visit u.right
   			else next = u->parent;                      // finally, move back to u.parent
   		} else if (prev == u->left) { // if we arrive at a node u from u.left,
   			if (u->right != nullptr) next = u->right;		// first, tries to visit u.right
   			else next = u->parent;                      // finally, move back to u.parent
   		} else {                   // if we arrives at a node from u.right, visit all children
   			next = u->parent;                     		// move back to u.parent 
   		} 
   		prev = u; u = next; 
   	}
   	return n;
}


// Breadth-first Traversal
template<typename T>
void BinaryTree<T>::bfTraverse() {
	std::vector<BTNode<T>*> q;
	if (root != nullptr) q.push_back(root);	// q.size() is just a parameter 
	while (q.size() > 0) {
		BTNode<T> *u = q[q.size()-1];
		if (u->left != nullptr) q.push_back(u->left);
		if (u->right != nullptr) q.push_back(u->right);
	}
}


}  // namespace HKSTL
#endif  // BINARYTREE_H_
