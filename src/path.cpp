#include "path.hpp"
using a_star::Path;

#include <cmath>

#include <queue>
using std::priority_queue;

Path::Path(Graph *graph, Node *start, Node *goal) {
	priority_queue<Priority_Node, vector<Priority_Node>, Priority_Node_Comparator> frontier;
	Priority_Node pn;
	pn.node = start;
	pn.priority = 0;
	frontier.push(pn);
	map<unsigned long, unsigned long> came_from;
	came_from[start->getId()] = start->getId();
	map<unsigned long, float> cost_so_far;
	cost_so_far[start->getId()] = 0;
	
	bool found = false;
	while(!frontier.empty()) {
		Priority_Node current = frontier.top();
		if(*(current.node) == *goal) {
			found = true;
			break;
		}
		for(Node *next : graph->get_neighbors(current.node->getId())) {
			Node::Cross_t cross_t = next->get_crossable();
			if(cross_t == Node::Cross_t::NOT_CROSSABLE || (*(current.node) == *start && cross_t == Node::Cross_t::TEMP_NOT_CROSSABLE)) {
				continue;
			}
			float new_cost = cost_so_far[current.node->getId()] + graph->get_cost(current.node->getId(), next->getId());
			if(cost_so_far.find(next->getId()) == cost_so_far.end() || new_cost < cost_so_far[next->getId()]) {
				cost_so_far[next->getId()] = new_cost;
				Priority_Node pn;
				pn.node = next;
				pn.priority = new_cost + heuristic(next, goal);
				frontier.push(pn);
				came_from[next->getId()] = current.node->getId();
			}
		}
		frontier.pop();
	}
	if(found) {
		auto it = came_from.find(goal->getId());
		this->path.push_front(goal);
		while(it != came_from.end() && it->second != start->getId()) {
			this->path.push_front(graph->getNode(it->second));
			it = came_from.find(it->second);
		}
	}
}

Path::~Path() {
	
}

vector<Node *> Path::get() const {
	vector<Node *> res;
	for(auto it=this->path.begin(); it!=this->path.end(); ++it) {
		res.push_back(*it);
	}
	return res;
}

float Path::heuristic(Node *a, Node *b) {
	return abs(a->getX() - b->getX()) + abs(a->getY() - b->getY());
}

Path::Priority_Node_Comparator::Priority_Node_Comparator(bool reverse) {
	this->reverse = reverse;
}

bool Path::Priority_Node_Comparator::operator() (const Priority_Node& lhs, const Priority_Node&rhs) const {
	return (this->reverse ? lhs.priority>rhs.priority : lhs.priority<rhs.priority);
}
