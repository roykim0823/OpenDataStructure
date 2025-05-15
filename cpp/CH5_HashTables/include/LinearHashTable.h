#ifndef LINEARHASHTABLE_H_
#define LINEARHASHTABLE_H_
#include <climits>
#include <iostream>
#include <vector>
#include <memory>

namespace HKSTL {

template<class T>
class LinearHashTable {
protected:
	typedef std::vector<T*> hashTable;
	hashTable table;
	T* deleted;	// to identify a deleted node
	long n;	 // number of element
	int d;  // hash table size (1 << d)
	int z;	// an odd random number for hash code
	static const int w = 32; //sizeof(int)*8;
	
	void allocTable(int m);
	void resize();
	size_t hash(T x) {
		// Multiplicative hashing (based on modular arithmetic)
		// hash(x) = ( (z*x) mod 2^w) div 2^(w-d) )
		return ((unsigned)((unsigned)z * x)) >> (w-d);  	// z is odd number
	}

	int probe(hashTable &t, size_t idx) {
		size_t iter=0;
		while(t[idx] != nullptr && iter < t.size())
			idx = ( idx == t.size()-1 ) ? 0 : idx+1;
		return idx;
	}
	
	void print(hashTable &t) {
		for(int i=0; i< t.size(); i++) {
			if(t[i] != nullptr) 
				cout << *t[i] << " ";
		}
		cout << endl;
	}

public:
	LinearHashTable();
	virtual ~LinearHashTable();
	bool add(T x);
	bool remove(T x);
	int find(T x);
	int size() { return n; }
	void clear();
};

// TODO(khyunjin):  A copy-constructor for arrays would be useful here
template<class T>
void LinearHashTable<T>::resize() {
	hashTable newTable;
	newTable.resize(1<<d, nullptr);
	// std::cout << "resize hashTable to " << (1<<d) << std::endl;

	for (size_t i=0; i<table.size(); i++) {
		if(table[i] != nullptr && table[i] != deleted) {
			size_t idx = hash(*table[i]);
			idx = probe(newTable, idx);
			newTable[idx] = table[i];
			table[i]=nullptr;
		}
	}
	table = newTable;	// replace the hashTable
}

template<class T>
LinearHashTable<T>::LinearHashTable() {
	n = 0;	
	d = 10;  // 1M entries (default)
	z = rand() | 1;     // is a random odd integer
	deleted = new T(0);
	table.resize(1 << d, nullptr);
}

template<class T>
LinearHashTable<T>::~LinearHashTable() {
	delete deleted;
}

// Add takes a constant time without resizing
template<class T>
bool LinearHashTable<T>::add(T x) {
	if ((n<<1) > ( 1<< d ) && d<30) {	// max 50% occupancy
		d++;
		resize();
	}	
	size_t idx = hash(x);
	while(table[idx] != nullptr && table[idx] != deleted) {
			idx = ( idx == table.size()-1 ) ? 0 : idx+1;	// idx++
	}
	table[idx] = new T(x);
	n++;
	return true;
}

// O(n * hash(x)) time
template<class T>
bool LinearHashTable<T>::remove(T x) {
	
	int idx = find(x);
	if (idx==-1)  	// not found
		return false;
	
	delete table[idx];
	table[idx]=deleted; 	// differentiate the deleted node from nullptr
	n--;

  if( (n<<3) < (1<<d) && d>10) {
		d--;
		resize();
	}
	return true;
}

template<class T>
int LinearHashTable<T>::find(T x) {
	size_t idx = hash(x);
	assert(idx < table.size());
	//size_t iter=0;
	//while(table[idx] != nullptr && iter<=table.size()) {
	// nullptr means that there was no data access in the entry -> no further search required!!!
	while(table[idx] != nullptr) {   	// worst case is linear search but nullptr is search limiter
		if(table[idx] != deleted && *table[idx]==x) {
			//cout << iter << " " << idx << " " << x << " !!"<< endl;
			return idx;
		}
		idx = (idx == table.size()-1) ? 0 : idx+1;
	}
	//cout << iter << " " << idx << " " << x << endl;
	return -1;
}

template<class T>
void LinearHashTable<T>::clear() {
	n = 0;
	d = 10;
	z = rand() | 1;     // is a random odd integer
	hashTable newTable;
	newTable.resize(1<<d, nullptr);
	table = newTable;
}

}  // namespace HKSTL
#endif  // CHAINEDHASHTABLE_H_
