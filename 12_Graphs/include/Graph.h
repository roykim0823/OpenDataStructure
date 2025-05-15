/*
 * Algorithms.h
 *
 *  Created on: 2011-11-30
 *      Author: morin
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "SLList.h"
#include "utils.h"
#include "array.h"

namespace ods {

// BFS -> shortest path
template<class Graph>
void bfs(Graph &g, int r) {
	bool *seen = new bool[g.nVertices()];	// auxiliary boolean array to check visted nodes
	SLList<int> q;
	q.add(r);								// Add starting node
	seen[r] = true;
	while (q.size() > 0) {
		int i = q.remove();
		ArrayStack<int> edges;
		g.outEdges(i, edges);				// Get i's outEdges
		for (int k = 0; k < edges.size(); k++) {
			int j = edges.get(k); 			// Get dest's node
			if (!seen[j]) {
				q.add(j);
				seen[j] = true;
			}
		}
	}
	delete[] seen;
}

enum { white, grey, black };	// white: never seen the vertex
								// grey: currently visting node
								// black: visted node (done)

template<class Graph>	// Recursive Version
void dfs(Graph &g, int i, char *c) {
	c[i] = grey;  			// currently visiting i
	ArrayStack<int> edges; 	 
	g.outEdges(i, edges);   // get the edges of i
	for (int k = 0; k < edges.size(); k++) {
		int j = edges.get(k);	// get dest's node
		if (c[j] == white) {
			c[j] = grey;
			dfs(g, j, c);
		}
	}
	c[i] = black; 			// done visiting i
}

template<class Graph>
void dfs(Graph &g, int r) {
	char *c = new char[g.nVertices()];
	dfs(g, r, c);
	delete[] c;
}

// DFS -> detect cycle using Stack
template<class Graph>	// Iterative Version
void dfs2(Graph &g, int r) {
	char *c = new char[g.nVertices()];
	SLList<int> s;
	s.push(r);
	while (s.size() > 0) {
		int i = s.pop();
		if (c[i] == white) {
			c[i] = grey;
			ArrayStack<int> edges;
			g.outEdges(i, edges);	// get dest's node
			for (int k = 0; k < edges.size(); k++)
				s.push(edges.get(k));	// push neighbors node
		}
	}
	delete[] c;
}

} /* namespace ods */

#endif /* GRAPH_H */
