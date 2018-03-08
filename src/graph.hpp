#ifndef graph_hpp
#define graph_hpp

#include "dependencies.hpp"

namespace a_star {
	
	class Graph {
	
	public:
		Graph(vector<Node *> nodes, vector<Link> links);
		~Graph();
		
	private:
		map<int, Node *> nodes;
	
	};
	
}

#endif