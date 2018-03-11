#ifndef a_star_dependencies_hpp
#define a_star_dependencies_hpp

#include <iostream>
#include <vector>
#include <map>

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
		unsigned long to;
		float weight;
	} Connection;
	
	typedef struct {
		int from;
		int to;
		float weight;
	} Link;
    
    /*bool operator==(const Point& lhs, const Point& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    bool operator!=(const Point& lhs, const Point& rhs) {
        return !(lhs == rhs);
    }
    bool operator>(const Point& lhs, const Point& rhs) {
        if(lhs.x > rhs.x) {
            return true;
        }
        return lhs.y > rhs.y;
    }
    bool operator<(const Point& lhs, const Point& rhs) {
        if(rhs.x > lhs.x) {
            return true;
        }
        return rhs.y > lhs.y;
    }*/
	
	class Node;
	class Graph;
	class Path;
	
	class A_star_exception;
	
}

#endif
