/*
 * Triangle.cpp
 *
 *  Created on: 2013-10-22
 *      Author: Administrator
*/
#include <iostream>
#include "triangle.h"

  Triangle::Triangle(Point2D initialPointOne, 
                     Point2D initialPointTwo,
		             Point2D initialPointThree) {

		pointOne = initialPointOne;
		pointTwo = initialPointTwo;
		pointThree = initialPointThree;
	}

  Point2D Triangle::getFirstPoint() {

		return pointOne;
  }
