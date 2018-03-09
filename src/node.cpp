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

void Node::add_neighbor(int node_id, float weight) {
	Connection con;
	con.to = node_id;
	con.weight = weight;
	this->neighbors.push_back(con);
}

int Node::getId() const {
	return this->id;
}

float Node::getX() const {
	return this->position.x;
}

float Node::getY() const {
	return this->position.y;
}

bool Node::operator== (Node &n) const {
	return (this->position.x == n.position.x && this->position.y == n.position.y);
}
