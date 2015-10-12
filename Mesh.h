#ifndef MESH_
#define MESH_

#include <iostream>
#include <vector>
#include <map>

#include "Face.h"
#include "HalfEdge.h"
#include "Vertex.h"

template <typename T>
class Mesh{

public:

	typedef Mesh<T> TraitMesh;
	typedef Face<TraitMesh> Face;
	typedef Vertex<TraitMesh> Vertex;
	typedef HalfEdge<TraitMesh> HalfEdge;

	Mesh(){ std::cout << "Created a mesh" << std::endl; }
	void AddFace(Face * face_){ faces.push_back(face_); }
	
	void AddVertex(Vertex * v_){

		vertices.push_back(v_);
	}

	bool VertexExist(Vertex * v_){

		for (Vertex * v : vertices){
			if (v->position == v_->position)
				return true;
		}

		return false;
	}

	void CreateFace(int v1, int v2, int v3){

		Face * new_face = new Face();

		edges[std::pair<int, int>(v1, v2)] = new HalfEdge();
		edges[std::pair<int, int>(v2, v3)] = new HalfEdge();
		edges[std::pair<int, int>(v3, v1)] = new HalfEdge();

		edges[std::pair<int, int>(v1, v2)]->vert = vertices[v2];
		edges[std::pair<int, int>(v2, v3)]->vert = vertices[v3];
		edges[std::pair<int, int>(v3, v1)]->vert = vertices[v1];

		edges[std::pair<int, int>(v1, v2)]->face = new_face;
		edges[std::pair<int, int>(v2, v3)]->face = new_face;
		edges[std::pair<int, int>(v3, v1)]->face = new_face;
		
		// It doesn't matter it changes a lot of times. It's only need to access the ooposite half-edge
		edges[std::pair<int, int>(v1, v2)]->next = edges[std::pair<int, int>(v2, v3)];
		edges[std::pair<int, int>(v2, v3)]->next = edges[std::pair<int, int>(v3, v1)];
		edges[std::pair<int, int>(v3, v1)]->next = edges[std::pair<int, int>(v1, v2)];

		edges[std::pair<int, int>(v1, v2)]->prev = edges[std::pair<int, int>(v3, v1)];
		edges[std::pair<int, int>(v2, v3)]->prev = edges[std::pair<int, int>(v1, v2)];
		edges[std::pair<int, int>(v3, v1)]->prev = edges[std::pair<int, int>(v2, v3)];

		new_face->he = edges[std::pair<int, int>(v1, v2)];

		if (edges.find(std::pair<int, int>(v2, v1)) != edges.end())
		{
			edges[std::pair<int, int>(v2, v1)]->opposite = edges[std::pair<int, int>(v1, v2)];
			edges[std::pair<int, int>(v1, v2)]->opposite = edges[std::pair<int, int>(v2, v1)];
		}

		if (edges.find(std::pair<int, int>(v3, v2)) != edges.end())
		{
			edges[std::pair<int, int>(v3, v2)]->opposite = edges[std::pair<int, int>(v2, v3)];
			edges[std::pair<int, int>(v2, v3)]->opposite = edges[std::pair<int, int>(v3, v2)];
		}

		if (edges.find(std::pair<int, int>(v1, v3)) != edges.end())
		{
			edges[std::pair<int, int>(v1, v3)]->opposite = edges[std::pair<int, int>(v3, v1)];
			edges[std::pair<int, int>(v3, v1)]->opposite = edges[std::pair<int, int>(v1, v3)];
		}

		this->faces.push_back(new_face);
	}

	void PrintFaces(){
		
		for(Face * f : faces){
			HalfEdge * end = f->he, * tmp;
			tmp = end;
			std::cout << "f ->  ";
			do{
				std::cout << "vert->id: " << tmp->vert->id << " ";	
				tmp = tmp->next;
			} while (tmp != end);
			std::cout << std::endl;
		}

	}

	Vertex * getVertex(int id){ return vertices[id]; }
	std::vector<Vertex *> * getVertices(){return &vertices;}
	std::vector <Face *> * getFaces(){return &faces; }
	std::vector<Vertex *> vertices;

private:
	std::map< std::pair<int, int>, HalfEdge* > edges;
	std::vector<Face *> faces;
	
};

#endif