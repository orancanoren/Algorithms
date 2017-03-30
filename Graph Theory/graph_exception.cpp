#include "graph.h"
#include <iostream>
#define _DEBUG

GraphException::GraphException(char * msg) : msg(msg) {
#ifdef _DEBUG
	std:: cout << "GraphException constructor invoked" << std::endl;
#endif
}

const char * const GraphException::what() const {
	return msg;
}

GraphException::~GraphException() {
#ifdef _DEBUG
	std::cout << "GraphException destructor invoked" << std::endl;
#endif
}

