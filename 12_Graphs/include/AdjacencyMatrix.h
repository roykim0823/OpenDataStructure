/*
 * AdjacencyMatrix.h
 *
 *  Created on: 2012-01-13
 *      Author: morin
 */

#ifndef ADJACENCYMATRIX_H_
#define ADJACENCYMATRIX_H_

namespace ods {

class AdjacencyMatrix {
protected:
	int n;
	bool **a;
public:
	AdjacencyMatrix(int num) {
		n=num;
		a = new bool*[n];
		for(int i=0; i<n; i++) 
			a[i]= new bool[n];
		for(int i=0; i<n; i++) 
			for(int j=0; j<n; j++)
				a[i][j]=false;
	}

	virtual ~AdjacencyMatrix() {
		for(int i=0; i<n; i++) 
			delete [] a[i];
		delete [] a;
	}

	void addEdge(int i, int j) {
		a[i][j] = true;
	}

	void removeEdge(int i, int j) {
		a[i][j] = false;
	}

	bool hasEdge(int i, int j) {
		return a[i][j];
	}

	template<class List>
	void outEdges(int i, List &edges) {
		for (int j = 0; j < n; j++)
			if (a[i][j]) edges.add(j);
	}

	template<class List>
	void inEdges(int i, List &edges) {
		for (int j = 0; j < n; j++)
			if (a[j][i]) edges.add(j);
	}

	int nVertices() {
		return n;
	}
};

} /* namespace ods */
#endif /* ADJACENCYMATRIX_H_ */
