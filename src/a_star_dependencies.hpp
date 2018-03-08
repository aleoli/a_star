#ifndef a_star_dependencies_hpp
#define a_star_dependencies_hpp

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;

namespace a_star {
	
	typedef struct {
		float x;
		float y;
	} Point;
	
	typedef struct {
		int to;
		float weight;
	} Connection;
	
	typedef struct {
		int from;
		int to;
		float weight;
	} Link;
	
	class Node;
	class Graph;
	
}

#endif