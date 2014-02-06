/*
 * Square.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Hassam
 */

#ifndef SQUARE_H_
#define SQUARE_H_
#include "iostream"
#include "Node.h"
class Square:public Node{
public:
 Square();
 std::string name;
 glm::vec3 Loc;
 void translate(glm::vec3 v);
 bool initialize();
 void draw();
  ~Square();
 void cleanup();


};



#endif /* SQUARE_H_ */
