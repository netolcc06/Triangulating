#include <iostream>
#include "Mesh.h"
#include "vec3.hpp"

int main(int argc, char * argv[]){

	Mesh<int> mesh;
	Mesh<int>::Face f1;
	// Counter-clock wise
	Mesh<int>::Vertex a1(glm::vec3(-1, 0, 0), 0), b1(glm::vec3(1, 0, 0), 1), c1(glm::vec3(0, 1, 0), 2), d1(glm::vec3(1, 1, 0), 3);//, a2, b2, c2, a3, b3, c3;
	
	mesh.CreateFace(&a1, &b1, &c1);
	mesh.CreateFace(&b1, &c1, &d1);

	mesh.PrintFaces();

	return 0;
}