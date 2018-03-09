#ifndef a_star_exception_hpp
#define a_star_exception_hpp

#include "a_star_dependencies.hpp"

#include <exception>

namespace a_star {
	
	class A_star_exception : public std::exception {
	
	public:
		A_star_exception(string msg) : std::exception() {
			this->msg = string(msg);
		}
		
		virtual ~A_star_exception() throw() {
			
		}
		
		virtual const char* what() const throw() {
			return this->msg.c_str();
		}
		
	private:
		string msg;
	
	};
	
}

#endif