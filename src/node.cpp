#include "node.hpp"
using a_star::Node;
using a_star::Connection;

Node::Node(int id, float cost, Point position) {
	this->id = id;
	this->cost = cost;
	this->position = position;
}

Node::~Node() {
	
}

vector<Connection> Node::get_neighbors() const {
	return this->neighbors;
}

void Node::add_neighbor(Node node, float weight) {
	Connection con;
	con.id = node.id;
	con.weight = weight;
	this->neighbors.push_back(con);
}
