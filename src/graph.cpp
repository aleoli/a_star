#include "graph.hpp"
using a_star::Graph;

Graph::Graph(vector<Node *> nodes, vector<Link> links) {
	for(auto it=nodes.begin(); it!=nodes.end(); ++it) {
		this->map.insert();
	}
}

Graph::~Graph() {
	for(auto it=this->nodes.begin(); it!=this->nodes.end(); ++it) {
		delete it->second;
	}
}
