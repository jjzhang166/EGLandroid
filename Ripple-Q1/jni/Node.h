/*
 * Node.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Hassam
 */

#ifndef NODE_H_
#define NODE_H_
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Vertex{
public:
 float x,y,z;
 Vertex():x(0),y(0),z(0){};
 Vertex(float,float,float):x(0),y(0),z(0){};
 ~Vertex(){};

};
class Node{

public:

	glm::vec3 Loc;
	static bool INITD;
	virtual bool initialize()=0;
	virtual void draw()=0;


};



#endif /* NODE_H_ */
