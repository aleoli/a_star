#define cols 3
#define rows 3

#include <iostream>

#include "a_star.hpp"

using std::cout;
using std::endl;

using namespace a_star;

int main(int argc, char *argv[]) {
	/*vector<Node *> nodes;
	vector<Link> links;
	
	int id=0;
	for(int a=0; a<rows; a++) {
		for(int b=0; b<cols; b++) {
			cout << id << "\t";
			Point p;
			p.y = a;
			p.x = b;
			nodes.push_back(new Node(id, 1, p));
			if(a>0) {
				Link l;
				l.from = id;
				l.to = id-rows;
				l.weight = 1;
				links.push_back(l);
			}
			if(b>0) {
				Link l;
				l.from = id;
				l.to = id-1;
				l.weight = 1;
				links.push_back(l);
			}
			id++;
		}
		cout << endl;
	}
	cout << endl;
	
	Graph graph(nodes, links);*/
	
	Graph graph("nodes.txt", "links.txt");
	
	while(true) {
		try {
			int id;
			cout << "Id start node: ";
			scanf("%d", &id);
			Node *start = graph.getNode(id);
			cout << "Id goal node: ";
			scanf("%d", &id);
			Node *goal = graph.getNode(id);
			
			Path path(&graph, start, goal);
			vector<Node *> p = path.get();
			
			cout << endl << "Path from " << start->to_string() << " to " << goal->to_string() << " lenght: " << p.size() << endl;
			for(auto it=p.begin(); it!=p.end(); ++it) {
				cout << (*it)->to_string() << endl;
			}
		} catch(std::exception &e) {
			cout << e.what() << endl;
		}
	}
	
	return 0;
}