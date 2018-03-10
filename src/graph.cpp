#include "graph.hpp"
using a_star::Graph;

using std::pair;

#include "a_star_exception.hpp"
using a_star::A_star_exception;

#include <fstream>
using std::ifstream;

Graph::Graph(vector<Node *> nodes, vector<Link> links) {
	for(auto it=nodes.begin(); it!=nodes.end(); ++it) {
		this->nodes.insert(pair<int, Node *>((*it)->getId(), *it));
	}
	for(auto it=links.begin(); it!=links.end(); ++it) {
		auto it2 = this->nodes.find(it->from);
		if(it2 == this->nodes.end()) {
			throw A_star_exception("Node not found for id "+std::to_string(it->from));
		}
		it2->second->add_neighbor(it->to, it->weight);
		auto it3 = this->nodes.find(it->to);
		if(it3 == this->nodes.end()) {
			throw A_star_exception("Node not found for id "+std::to_string(it->to));
		}
		it3->second->add_neighbor(it->from, it->weight);
	}
}

Graph::Graph(string nodes, string links) {
	ifstream f(nodes);
	int id;
	float cost;
	float x, y;
	while(f >> id >> cost >> x >> y) {
		Point p;
		p.x = x;
		p.y = y;
		this->nodes.insert(pair<int, Node *>(id, new Node(id, cost, p)));
	}
	f.close();
	
	ifstream f2(links);
	int from, to;
	float weight;
	while(f2 >> from >> to >> weight) {
		auto it = this->nodes.find(from);
		if(it == this->nodes.end()) {
			throw A_star_exception("Node not found for id "+std::to_string(from));
		}
		it->second->add_neighbor(to, weight);
		auto it2 = this->nodes.find(to);
		if(it2 == this->nodes.end()) {
			throw A_star_exception("Node not found for id "+std::to_string(to));
		}
		it2->second->add_neighbor(from, weight);
	}
	f2.close();
}

Graph::~Graph() {
	for(auto it=this->nodes.begin(); it!=this->nodes.end(); ++it) {
		delete it->second;
	}
}

Node *Graph::getNode(int id) const {
	auto it = this->nodes.find(id);
	if(it == this->nodes.end()) {
		throw A_star_exception("Node not found for id "+std::to_string(id));
	}
	return it->second;
}

Node *Graph::getNode(float x, float y) const {
	for(auto it=this->nodes.begin(); it!=this->nodes.end(); ++it) {
		if(it->second->getX() == x && it->second->getY() == y) {
			return it->second;
		}
	}
	throw A_star_exception("Node not found for (x: "+std::to_string(x)+", y: "+std::to_string(y)+")");
}

float Graph::get_cost(int from, int to) const {
	auto it = this->nodes.find(from);
	if(it == this->nodes.end()) {
		throw A_star_exception("Node not found for id "+std::to_string(from));
	}
	vector<Connection> conn = it->second->get_neighbors();
	for(auto it2=conn.begin(); it2!=conn.end(); ++it2) {
		if(it2->to == to) {
			return it2->weight;
		}
	}
	throw A_star_exception("Node "+std::to_string(from)+" is not connected to node "+std::to_string(to));
}

vector<Node *> Graph::get_neighbors(int node_id) {
	auto it = this->nodes.find(node_id);
	if(it == this->nodes.end()) {
		throw A_star_exception("Node not found for id "+std::to_string(node_id));
	}
	vector<Connection> conn = it->second->get_neighbors();
	vector<Node *> res;
	for(auto it2=conn.begin(); it2!=conn.end(); ++it2) {
		auto it3 = this->nodes.find(it2->to);
		if(it3 == this->nodes.end()) {
			throw A_star_exception("Node not found for id "+std::to_string(it2->to));
		}
		res.push_back(it3->second);
	}
	return res;
}
