#ifndef FACE_
#define FACE_

#include <iostream>
#include <vector>

template <typename T>
class Face{

public:

	typedef typename T::HalfEdge _HalfEdge_;

	Face(){ std::cout << "Created a Face" << std::endl; }

	_HalfEdge_ * he;
	
private:

};

#endif