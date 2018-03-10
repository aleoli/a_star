#ifndef graph_hpp
#define graph_hpp

#include "a_star_dependencies.hpp"

#include "node.hpp"
using a_star::Node;

namespace a_star {
	
	class Graph {
	
	public:
		Graph(vector<Node *> nodes, vector<Link> links);
		Graph(string nodes, string links);
		~Graph();
		
		Node *getNode(int id) const;
		Node *getNode(float x, float y) const;
		float get_cost(int from, int to) const;
		vector<Node *> get_neighbors(int node_id);
		
	private:
		map<int, Node *> nodes;
	
	};
	
}

#endif