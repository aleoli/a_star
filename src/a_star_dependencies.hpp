#ifndef a_star_dependencies_hpp
#define a_star_dependencies_hpp

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;

namespace a_star {
	
    typedef struct Point Point;
	struct Point {
		float x;
		float y;
        
        bool operator==(const Point& o) const {
            return abs(this->x - o.x)<0.1 && abs(this->y - o.y)<0.1;
        }
        bool operator!=(const Point& o) const {
            return !(*this == o);
        }
        bool operator>(const Point& o) const {
            return this->x > o.x || (this->x == o.x && this->y > o.y);
        }
        bool operator<(const Point& o) const {
            return this->x < o.x || (this->x == o.x && this->y < o.y);
        }
	};
	
	typedef struct {
		unsigned long to;
		float weight;
	} Connection;
	
	typedef struct {
		int from;
		int to;
		float weight;
	} Link;
	
	class Node;
	class Graph;
	class Path;
	
	class A_star_exception;
	
}

#endif
