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

#include "BinaryHeap.h"
#include "MeldableHeap.h"

using namespace mySTL;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

const unsigned RA=0x0001;   // random access
const unsigned FM=0x0002;   // front modifications

template<typename T>
void print(vector<T> &t) {
	cout << endl;
	for(int i=0; i<(int)t.size(); i++) {
		cout << t[i] << " ";
	} 
	cout << endl;
}
template<class Heap>
void heapTests(Heap &h, int n) {
//void heapTests(Heap &h2, int n, bool print_data=false) {
	clock_t start, stop;
	cout << "Adding " << n << " elements...";
	cout.flush();
	start = clock();
	vector<int> t;
	for (int i = 0; i < n; i++) {
		t.push_back(rand()%100);
		//h.add(rand()%100);
		h.add(t[i]);
	}
	if(n<40)
    	print(t);
	//BinaryHeap<int> h(t);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Removing " << n << " elements...";
	cout.flush();
	start = clock();

	t.clear();
	int p = h.remove();
    t.push_back(p);
	for (int i = 1; i < n; i++) {
		assert(h.size() == n-i);
		int q = h.remove();
    	t.push_back(q);
		assert(p <= q);
		p = q;
	}
	if(n<40)
		print(t);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}

int main(int argc, char **argv)
{
	int n = 1000000;
//	int n = 20;

	srand(0);

	{
		cout << endl << "BinaryHeap<int>:" << endl;
		BinaryHeap<int> h;
    	heapTests(h, n);
	}

	{
		cout << endl << "MeldableHeap<int>:" << endl;
		MeldableHeap<int> h;
		heapTests(h, n);
	}

	return 0;
}

