/*
 * Triangle.h
 *
 *  Created on: 2013-10-22
 *      Author: Administrator
 */
/*
	#ifndef 指示检测指定的预处理器变量是否未定义。
	如果预处理器变量未定义，那么跟在其后的所有指示都被处理，
	直到出现 #endif
	头文件应该含有保护符，即使这些头文件不会被其他头
       文件包含。编写头文件保护符并不困难，而且如果头文
      件被包含多次，它可以避免难以理解的编译错误。
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "point2D.h"
class Triangle {
   private:
		Point2D pointOne;
		Point2D pointTwo;
		Point2D pointThree;
   public:
		Triangle(Point2D initialPointOne, 
		          Point2D initialPointTwo,
		          Point2D initialPointThree);
	    Point2D getFirstPoint();
};
#endif /* TRIANGLE_H_ */
