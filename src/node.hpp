#ifndef node_hpp
#define node_hpp

#include "a_star_dependencies.hpp"

namespace a_star {
	
	class Node {
	
	public:
		Node(int id, float cost, Point position);
		~Node();
		
		void add_neighbor(Node node, float weight);
		vector<Connection> get_neighbors() const;
		
	private:
		int id;
		float cost;
		Point position;
		vector<Connection> neighbors;
		
	};
	
}

#endif