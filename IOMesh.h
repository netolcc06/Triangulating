#ifndef IOMesh_
#define IOMesh_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "vec3.hpp"
#include "Mesh.h"


template <typename T>
class IOMesh{

public:

	typedef typename T::Vertex _Vertex_;
	typedef typename T::Face _Face_;
	typedef typename T::HalfEdge _HalfEdge_;

	IOMesh(){}
	static void Write(T * mesh, std::string path ){
		
		std::ofstream file_out;
		file_out.open(path);

		for (_Vertex_ * v : *(mesh->getVertices())){
			file_out << "v" << " " << v->position.x << " " << v->position.y << " " << v->position.z <<std::endl;
		}

		for (_Face_ * f : *(mesh->getFaces())){
			
			_HalfEdge_ * end = f->he, *tmp;
			tmp = end;
			file_out << "f ";

			do{
				file_out << tmp->vert->id + 1<< " ";
				tmp = tmp->next;
			} while (tmp != end);

			file_out << std::endl;
		}

		file_out.close();
	}

	static T * Read(std::string path){
	
		std::ifstream in_file(path);
		std::string line, op;
		std::stringstream linestream;
		glm::vec3 tmp_position;
		_Vertex_ * tmp_vert;

		T * mesh = new T();

		int count = 0;
		while (std::getline(in_file, line))
		{
			linestream << line;
			linestream >> op;

			if (op == "v"){

				tmp_vert = new _Vertex_();
				linestream >> tmp_vert->position.x >> tmp_vert->position.y >> tmp_vert->position.z;			
				tmp_vert->id = count;
				mesh->AddVertex(tmp_vert);
				count++;
				linestream.clear();
			}
			else if (op == "f"){
				int v0, v1, v2;
				linestream >> v0 >> v1 >> v2;
				mesh->CreateFace(mesh->getVertex(v0-1)->id, mesh->getVertex(v1-1)->id, mesh->getVertex(v2-1)->id);
			}
		}

		return mesh;
	}


private:
};


#endif