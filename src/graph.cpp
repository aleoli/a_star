#include "graph.hpp"
using a_star::Graph;

using std::pair;

#include "a_star_exception.hpp"
using a_star::A_star_exception;

using a_star::Point;

#include <fstream>
#include <thread>
using std::ifstream;
using std::thread;

Graph::Graph() {
    
}

Graph::Graph(vector<Node *> nodes, vector<Link> links) {
	for(auto it=nodes.begin(); it!=nodes.end(); ++it) {
        this->addNode(*it);
	}
	for(auto it=links.begin(); it!=links.end(); ++it) {
        this->addLink(*it, true);
	}
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
        this->addNode(new Node(id, cost, p));
	}
	f.close();
	
	ifstream f2(links);
	unsigned long from, to;
	float weight;
	while(f2 >> from >> to >> weight) {
        Link l;
        l.from = from;
        l.to = to;
        l.weight = weight;
        this->addLink(l, true);
	}
	f2.close();
}

Graph::~Graph() {
	for(auto it=this->nodes.begin(); it!=this->nodes.end(); ++it) {
		delete it->second;
	}
}

void Graph::addNode(Node *node) {
    this->nodes.insert(pair<unsigned long, Node *>(node->getId(), node));
    this->nodes_p.insert(pair<Point, Node *>(node->getPosition(), node));
}

void Graph::addLink(Link link, bool also_back) {
    auto it = this->nodes.find(link.from);
    if(it == this->nodes.end()) {
        throw A_star_exception("Node not found for id "+std::to_string(link.from));
    }
    it->second->add_neighbor(link.to, link.weight);
    if(also_back) {
        it = this->nodes.find(link.to);
        if(it == this->nodes.end()) {
            throw A_star_exception("Node not found for id "+std::to_string(link.to));
        }
        it->second->add_neighbor(link.from, link.weight);
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

Node *Graph::getNode(Point p) const {
    auto it = this->nodes_p.find(p);
    if(it == this->nodes_p.end()) {
        throw A_star_exception("Node not found for position (x: "+std::to_string(p.x)+", y: "+std::to_string(p.y)+")");
    }
    return it->second;
}

Node *Graph::getNode(float x, float y) const {
    Point p;
    p.x = x;
    p.y = y;
    return this->getNode(p);
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
