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

#include "AdjacencyMatrix.h"
#include "AdjacencyLists.h"
#include "Graph.h"

using namespace ods;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

const unsigned RA=0x0001;   // random access
const unsigned FM=0x0002;   // front modifications

template<class Graph1, class Graph2>
void graphCmp(Graph1 &g1, Graph2 &g2) {
	int n = g1.nVertices();
	assert(n == g2.nVertices());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			assert(g1.hasEdge(i,j) == g2.hasEdge(i,j));
		}
	}
	for (int i = 0; i < n; i++) {
		int j;
		ArrayStack<int> l1, l2;
		g1.outEdges(i, l1);
		g2.outEdges(i, l2);
		for (int i = 0; i < l1.size(); i++) {
			for (j = 0; j < l2.size(); j++)
				if (l1.get(i) == l2.get(j)) break;
			assert(j < l2.size());
		}
		for (int i = 0; i < l2.size(); i++) {
			for (j = 0; j < l1.size(); j++)
				if (l2.get(i) == l1.get(j)) break;
			assert(j < l2.size());
		}
	}
}

template<class Graph1, class Graph2>
void graphTests(Graph1 &g1, Graph2 &g2) {
	int n = g1.nVertices();
	for (int k = 0; k < 50*n*n; k++) {
		int i = rand() % n;
		int j = rand() % n;
		if (i != j) {
			if (g1.hasEdge(i,j)) {
				g1.removeEdge(i,j);
				g2.removeEdge(i,j);
			} else {
				g1.addEdge(i,j);
				g2.addEdge(i,j);
			}
		}
		graphCmp(g1, g2);
	}
}

int main(int argc, char **argv)
{
	srand(0);

   	int n = 20;
   	cout << endl << "Graph Tests" << endl;
   	AdjacencyMatrix am(n);
   	AdjacencyLists al(n);
   	graphTests(am, al);
   	bfs(al, 0);
   	dfs(al, 0);
   	dfs2(al, 0);

	return 0;
}

