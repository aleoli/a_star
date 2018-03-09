#include "path.hpp"
using a_star::Path;

#include <queue>
using std::priority_queue;

Path::Path(Graph *graph, Node *start, Node *goal) {
	priority_queue<Priority_Node, vector<Priority_Node>, Priority_Node_Comparator> frontier;
	Priority_Node pn;
	pn.node = start;
	pn.priority = 0;
	frontier.push(pn);
	map<Node *, Node *> came_from;
	came_from[start] = start;
	map<Node *, float> cost_so_far;
	cost_so_far[start] = 0;
	
	while(!frontier.empty()) {
		Priority_Node current = frontier.top();
		if(*(current.node) == *goal) {
			break;
		}
		for(Node *next : graph->get_neighbors(current.node->getId())) {
			float new_cost = cost_so_far[current.node] + graph->get_cost(current.node->getId(), next->getId());
			if(cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				Priority_Node pn;
				pn.node = next;
				pn.priority = new_cost + heuristic(next, goal);
				frontier.push(pn);
				came_from[next] = current.node;
			}
		}
		frontier.pop();
	}
}

Path::~Path() {
	
}

float Path::heuristic(Node *a, Node *b) {
	return std::abs(a->getX() - b->getX()) + std::abs(a->getY() - b->getY());
}

Path::Priority_Node_Comparator::Priority_Node_Comparator(bool reverse) {
	this->reverse = reverse;
}

bool Path::Priority_Node_Comparator::operator() (const Priority_Node& lhs, const Priority_Node&rhs) const {
	return (this->reverse ? lhs.priority>rhs.priority : lhs.priority<rhs.priority);
}
