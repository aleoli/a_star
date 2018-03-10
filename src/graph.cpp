#include "graph.hpp"
using a_star::Graph;

using std::pair;

#include "a_star_exception.hpp"
using a_star::A_star_exception;

#include <fstream>
#include <thread>
using std::ifstream;
using std::thread;

Graph::Graph(vector<Node *> nodes, vector<Link> links) {
	for(auto it=nodes.begin(); it!=nodes.end(); ++it) {
		this->nodes.insert(pair<int, Node *>((*it)->getId(), *it));
	}
    thread back_links(Graph::add_back_links, this, links);
	for(auto it=links.begin(); it!=links.end(); ++it) {
		auto it2 = this->nodes.find(it->from);
		if(it2 == this->nodes.end()) {
			throw A_star_exception("Node not found for id "+std::to_string(it->from));
		}
		it2->second->add_neighbor(it->to, it->weight);
	}
    back_links.join();
}

Graph::Graph(string nodes, string links) {
	ifstream f(nodes);
	unsigned long id;
	float cost;
	float x, y;
	while(f >> id >> cost >> x >> y) {
		Point p;
		p.x = x;
		p.y = y;
		this->nodes.insert(pair<unsigned long, Node *>(id, new Node(id, cost, p)));
	}
	f.close();
	
	ifstream f2(links);
	unsigned long from, to;
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

void Graph::add_back_links(Graph *g, vector<Link> links) {
    for(auto it=links.begin(); it!=links.end(); ++it) {
        auto it2 = g->nodes.find(it->to);
        if(it2 == g->nodes.end()) {
            throw A_star_exception("Node not found for id "+std::to_string(it->to));
        }
        it2->second->add_neighbor(it->from, it->weight);
    }
}

Node *Graph::getNode(unsigned long id) const {
	auto it = this->nodes.find(id);
	if(it == this->nodes.end()) {
		throw A_star_exception("Node not found for id "+std::to_string(id));
	}
	return it->second;
}

Node *Graph::getNode(float x, float y) const {
	for(auto it=this->nodes.begin(); it!=this->nodes.end(); ++it) {
		if(it->second->getX()-this->epsilon <= x && it->second->getX()+this->epsilon >= x && it->second->getY()-this->epsilon <= y && it->second->getY()+this->epsilon >= y) {
			return it->second;
		}
	}
	throw A_star_exception("Node not found for (x: "+std::to_string(x)+", y: "+std::to_string(y)+")");
}

float Graph::get_cost(unsigned long from, unsigned long to) const {
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

vector<Node *> Graph::get_neighbors(unsigned long node_id) {
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
