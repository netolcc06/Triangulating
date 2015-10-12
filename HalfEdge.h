#ifndef HALFEDGE_
#define HALFEDGE_

#include <iostream>
#include <vector>

template <typename T>
class HalfEdge{

public:

	typedef typename T::HalfEdge _HalfEdge_;
	typedef typename T::Vertex _Vertex_;
	typedef typename T::Face _Face_;

	HalfEdge(){ 
		next = prev = opposite = NULL;
	}

	_Face_ * face;
	_Vertex_ * vert;
	_HalfEdge_ *next, *prev, *opposite;

private:
	
};

#endif