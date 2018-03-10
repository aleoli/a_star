#ifndef node_hpp
#define node_hpp

#include "a_star_dependencies.hpp"

namespace a_star {
	
	class Node {
	
	public:
		typedef enum {
			CROSSABLE, TEMP_NOT_CROSSABLE, NOT_CROSSABLE
		} Cross_t;
		
		Node(unsigned long id, float cost, Point position, Cross_t crossable = CROSSABLE);
		~Node();
		
		void add_neighbor(int node_id, float weight);
		vector<Connection> get_neighbors() const;
		
        unsigned long getId() const;
		
		float getCost() const;
		
		float getX() const;
		float getY() const;
		
		Cross_t get_crossable() const;
		void crossable(Cross_t new_val);
		
		string to_string() const;
		
		bool operator== (Node &n) const;
		bool operator!= (Node &n) const;
		
	private:
		unsigned long id;
		float cost;
		Point position;
		vector<Connection> neighbors;
		Cross_t _crossable;
		
	};
	
}

#endif
