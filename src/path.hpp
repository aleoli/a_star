#ifndef path_hpp
#define path_hpp

#include "a_star_dependencies.hpp"

#include "graph.hpp"
#include "node.hpp"

using a_star::Graph;
using a_star::Node;

namespace a_star {
	
	class Path {
		
	public:
		Path(Graph *graph, Node *start, Node *goal);
		~Path();
		
	private:
		static float heuristic(Node *a, Node *b);
		
		typedef struct {
			Node *node;
			float priority;
		} Priority_Node;
		
		class Priority_Node_Comparator {
			
		public:
			Priority_Node_Comparator(bool reverse=false);
			bool operator() (const Priority_Node& lhs, const Priority_Node&rhs) const;
			
		private:
			bool reverse;
			
		};
		
	};
	
}

#endif