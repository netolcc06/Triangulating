#include <iostream>
#include "Mesh.h"
#include "vec3.hpp"
#include "IOMesh.h"


int main(int argc, char * argv[]){

	Mesh<int> mesh;
	Mesh<int>::Face f1;
	// Counter-clock wise
	Mesh<int>::Vertex a1(glm::vec3(-1, 0, 0), 0), b1(glm::vec3(1, 0, 0), 1), c1(glm::vec3(0, 1, 0), 2), d1(glm::vec3(1, 1, 0), 3);//, a2, b2, c2, a3, b3, c3;
	Mesh<int>::Vertex a2(glm::vec3(1, 2, 0), 4), b2(glm::vec3(-1, 2, 0), 5);
	
	mesh.AddVertex(&a1); mesh.AddVertex(&b1); mesh.AddVertex(&c1); mesh.AddVertex(&d1); mesh.AddVertex(&a2); mesh.AddVertex(&b2);

	mesh.CreateFace(0, 1, 2);
	mesh.CreateFace(1, 3, 2);
	mesh.CreateFace(2, 3, 4);
	mesh.CreateFace(4, 5, 0);

	mesh.PrintFaces();

	
	IOMesh<Mesh<int>>::Write(&mesh, "C:\\Users\\netolcc06\\Desktop\\teste.obj");
	
	Mesh<int> * mydragon;

	mydragon = IOMesh<Mesh<int>>::Read("C:\\Users\\netolcc06\\Desktop\\dragon.obj");
	
	IOMesh<Mesh<int>>::Write(mydragon, "C:\\Users\\netolcc06\\Desktop\\mydragon.obj");
	
	std::cout << "numero de vert = " << mydragon->vertices.size() << std::endl;
	
	return 0;
}