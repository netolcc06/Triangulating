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
		
		bool exist = false;
		for (Vertex * v : vertices){
			if (v->id == v->id){
				return;
			}
		}

		if (!exist)
			vertices.push_back(v_);
	}

	void CreateFace(Vertex * v1, Vertex * v2, Vertex * v3){

		Face * new_face = new Face();

		// Add the vertices
		this->AddVertex(v1); this->AddVertex(v2); this->AddVertex(v3);

		edges[std::pair<int, int>(v1->id, v2->id)] = new HalfEdge();
		edges[std::pair<int, int>(v2->id, v3->id)] = new HalfEdge();
		edges[std::pair<int, int>(v3->id, v1->id)] = new HalfEdge();

		edges[std::pair<int, int>(v1->id, v2->id)]->face = new_face;
		edges[std::pair<int, int>(v2->id, v3->id)]->face = new_face;
		edges[std::pair<int, int>(v3->id, v1->id)]->face = new_face;

		edges[std::pair<int, int>(v1->id, v2->id)] = new HalfEdge();
		edges[std::pair<int, int>(v2->id, v3->id)] = new HalfEdge();
		edges[std::pair<int, int>(v3->id, v1->id)] = new HalfEdge();
		
		// It doesn't matter it changes a lot of times. It's only need to access the ooposite half-edge
		edges[std::pair<int, int>(v1->id, v2->id)]->next = edges[std::pair<int, int>(v2->id, v3->id)];
		edges[std::pair<int, int>(v2->id, v3->id)]->next = edges[std::pair<int, int>(v3->id, v1->id)];
		edges[std::pair<int, int>(v3->id, v1->id)]->next = edges[std::pair<int, int>(v1->id, v2->id)];

		edges[std::pair<int, int>(v1->id, v2->id)]->prev = edges[std::pair<int, int>(v3->id, v1->id)];
		edges[std::pair<int, int>(v2->id, v3->id)]->prev = edges[std::pair<int, int>(v1->id, v2->id)];
		edges[std::pair<int, int>(v3->id, v1->id)]->prev = edges[std::pair<int, int>(v2->id, v3->id)];

		edges[std::pair<int, int>(v1->id, v2->id)]->vert = v2;
		edges[std::pair<int, int>(v2->id, v3->id)]->vert = v3;
		edges[std::pair<int, int>(v3->id, v1->id)]->vert = v1;

		new_face->he = edges[std::pair<int, int>(v1->id, v2->id)];

		if (edges.find(std::pair<int, int>(v2->id, v1->id)) != edges.end())
		{
			edges[std::pair<int, int>(v2->id, v1->id)]->opposite = edges[std::pair<int, int>(v1->id, v2->id)];
			edges[std::pair<int, int>(v1->id, v2->id)]->opposite = edges[std::pair<int, int>(v2->id, v1->id)];
		}

		if (edges.find(std::pair<int, int>(v3->id, v2->id)) != edges.end())
		{
			edges[std::pair<int, int>(v3->id, v2->id)]->opposite = edges[std::pair<int, int>(v2->id, v3->id)];
			edges[std::pair<int, int>(v2->id, v3->id)]->opposite = edges[std::pair<int, int>(v3->id, v2->id)];
		}

		if (edges.find(std::pair<int, int>(v1->id, v3->id)) != edges.end())
		{
			edges[std::pair<int, int>(v1->id, v3->id)]->opposite = edges[std::pair<int, int>(v3->id, v1->id)];
			edges[std::pair<int, int>(v3->id, v1->id)]->opposite = edges[std::pair<int, int>(v1->id, v3->id)];
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
private:
	std::map< std::pair<int, int>, HalfEdge* > edges;
	std::vector<Face *> faces;
	std::vector<Vertex *> vertices;
};

#endif