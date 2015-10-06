#ifndef VERTEX_
#define VERTEX_

#include <iostream>
#include <vector>
#include "vec3.hpp"

template <typename T>
class Vertex{

public:
	typedef typename T::HalfEdge _HalfEdge_;

	Vertex(glm::vec3 position_, int id_){ 
	
		he = new _HalfEdge_();
		this->position = position_;
		id = id_;
		std::cout << "Created a Face" << std::endl; }

	_HalfEdge_ * he;
	glm::vec3 position;
	int id;

private:

};

#endif