#ifndef graph_hpp
#define graph_hpp

#include "a_star_dependencies.hpp"

#include "node.hpp"
using a_star::Node;

namespace a_star {
	
	class Graph {
	
	public:
        Graph();
		Graph(vector<Node *> nodes, vector<Link> links);
		Graph(string nodes, string links);
		~Graph();
		
        void addNode(Node *node);
        void addLink(Link link, bool also_back = true);
		Node *getNode(unsigned long id) const;
        Node *getNode(Point p) const;
		Node *getNode(float x, float y) const;
		float get_cost(unsigned long from, unsigned long to) const;
		vector<Node *> get_neighbors(unsigned long node_id);
		
	private:
        static void add_back_links(Graph *g, vector<Link> links);
        
		map<unsigned long, Node *> nodes;
        map<Point, Node *> nodes_p;
	
	};
	
}

#endif
