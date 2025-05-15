/*
 * main.cpp
 *
 *  Created on: 2011-11-23
 *      Author: morin
 */
#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>

#include <iostream>
using namespace std;

#include "ArrayDeque.h"

#include "BinaryTree.h"
#include "BinarySearchTree.h"
//#include "Treap.h"
//#include "ScapegoatTree.h"
//#include "RedBlackTree.h"
//#include "BTree.h"
//#include "BinaryHeap.h"

//#include "BinaryTrie.h"

using namespace ods;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

const unsigned RA=0x0001;   // random access
const unsigned FM=0x0002;   // front modifications

template<class Tree>
void btTests(Tree &t) {
	t.size();
	t.size2();
	t.height();
	t.bfTraverse();
	t.traverse();
	t.traverse2();
}

template <class SSet>
void ssetTests(SSet &ss, int n, unsigned flags) {
	clock_t start, stop;
	cout << "Adding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		ss.add(rand());
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Finding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		int z = rand();
		int y = ss.find(z);
		if (i % 300000 == 0) {
			cout << "[" << z << "=>" << y << "]";
		}
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Running binary tree tests...";
	cout.flush();
	start = clock();
	btTests(ss);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Removing " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		ss.remove(rand());
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Final size is " << ss.size() << endl;

	cout << "Clearing " << ss.size() << " elements...";
	cout.flush();
	start = clock();
	ss.clear();
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}

int main(int argc, char **argv)
{
	int n = 1000000;

	srand(0);


	{
		cout << endl << "BinaryTree:" << endl;
		BinaryTree<BTNode1> t;
		btTests(t);
	}


	{
		cout << endl << "BinarySearchTree<int>:" << endl;
		BinarySearchTree1<int> t;
		btTests(t);
		ssetTests(t, n, 0x0);
	}



	{
		BinarySearchTree<BSTNode1<int>,int> s;
		btTests(s);
		ssetTests(s, n, 0x0);
	}

	return 0;
}

