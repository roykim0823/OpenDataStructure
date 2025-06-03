#pragma once
#include <queue>
#include <stack>
#include "Graph.h"

template <typename T>  // T is UniGraph or DiGraph
class Traverse {
protected:
	std::vector<bool> marked;		// Mark node if a shorest path to this vertex is known
	std::vector<int> edgeTo;     	// last vertex on known path to this vertex
	std::vector<int> dfs_path;		// dfs_path only, alternative of edgeTo but simpler
	int source;             		// starting node
	T& graph;

public:
	Traverse(T& G, int s=0): graph(G) {
		marked.resize(graph.get_V());
		edgeTo.resize(graph.get_V());
		source = s;
	}

	// return true if there a path from s to v
	bool hasPathTo(int v) { return marked[v]; }

	std::stack<int> pathTo(int v) {	// return path from s to v; null if no such path
		std::stack<int> path;
		if(hasPathTo(v)==false) return path;
		for(int x=v; x !=source; x=edgeTo[x])
			path.push(x);
		path.push(source);
		return path;
	}

	void print_path() {
		for (int v=0; v < this->graph.get_V(); ++v) {
			if (hasPathTo(v)) {
				std::cout << source << " -> " << v << " : ";
				std::stack<int> path = pathTo(v);
				while(!path.empty()) {
					int node = path.top();
					if (node == source) std::cout << node;
					else std::cout << " - " << node;
					path.pop();
				}
				std::cout << std::endl;
			}
		}
	}
	void print_reachable() {
		for (int v=0; v < this->graph.get_V(); ++v) {
			if(marked[v]) {
				std::cout << v << " ";
			}
		}
		std::cout << std::endl;
	}

	std::vector<int> get_dfs_path() {
		return dfs_path;
	}
};


template <typename T>  // T is UniGraph or DiGraph
class BFS: public Traverse<T> {
public:
	BFS(T& G, int s=0): Traverse<T>(G, s) {
		bfs(s);
	}

private:
	void bfs(int s) {
        std::queue<int> q;
		q.push(s);	       	// Put it on the queue
		this->marked[s] = true; 	// Mark the source
		while(!q.empty()) {
			int v = q.front();	// remove next vertex from the queue
			q.pop();

			const std::vector<int>& temp = this->graph.adj(v);
			for(auto pos=temp.begin(); pos !=temp.end(); ++pos) {
				if(this->marked[*pos] == false) {	// For every unmarked (not visited) adjacent vertex,
					q.push(*pos);           		// Add it to the queue
					this->marked[*pos] = true;      // Mark it because path is known
					this->edgeTo[*pos] = v;    		// Save last edge on a shortest path
				}
			}
		}
	}
};

template <typename T>
class DFS: public Traverse<T> {

public:
	DFS(T& G, int s=0, bool iter=false): Traverse<T>(G, s) {
		if (iter) {
			dfs(s);
		} else {
			dfs_iter(s);
		}
	}

	DFS(T& G, std::vector<int> s, bool iter=false): Traverse<T>(G, s[0]) {
		if (iter) {
			for(int i=0; i<s.size(); ++i)
				dfs(s[i]);
		} else {
			for(int i=0; i<s.size(); ++i)
				dfs_iter(s[i]);
		}
	}

private:
	void dfs(int v) {  // Recursive
		this->marked[v] = true;
		this->dfs_path.push_back(v);
		const std::vector<int>& temp = this->graph.adj(v);
		for(auto pos=temp.begin(); pos !=temp.end(); ++pos)
		{
			if(this->marked[*pos]==false) {
				this->edgeTo[*pos]=v;
				dfs(*pos);
			}
		}
		this->dfs_path.pop_back();
	}

	void dfs_iter(int v) {
		std::stack<int> s;
		this->marked[v]=true;
		s.push(v);

		while(!s.empty()) {
			int v=s.top();
			s.pop();

			const std::vector<int>& temp = this->graph.adj(v);
			for(auto pos=temp.begin(); pos !=temp.end(); ++pos) {
				if(this->marked[*pos]==false) {
		    		this->edgeTo[*pos] = v;
					this->marked[*pos] = true;
					s.push(*pos);
				}
			}
		}
	}
};