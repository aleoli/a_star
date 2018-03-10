#include "node.hpp"
using a_star::Node;
using a_star::Connection;

Node::Node(int id, float cost, Point position, Cross_t crossable) {
	this->id = id;
	this->cost = cost;
	this->position = position;
	this->_crossable = crossable;
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

string Node::to_string() const {
	return "id: "+std::to_string(this->id)+"\tx: "+std::to_string(this->position.x)+"\ty: "+std::to_string(this->position.y);
}

Node::Cross_t Node::get_crossable() const {
	return this->_crossable;
}

void Node::crossable(Cross_t new_val) {
	this->_crossable = new_val;
}

bool Node::operator== (Node &n) const {
	return (this->position.x == n.position.x && this->position.y == n.position.y);
}

bool Node::operator!= (Node &n) const {
	return !((*this)==n);
}
