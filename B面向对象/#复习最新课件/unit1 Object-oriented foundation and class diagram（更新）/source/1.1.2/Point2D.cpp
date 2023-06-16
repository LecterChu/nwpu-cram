  #include <iostream>
  #include "point2D.h"
  using std::cout;
  using std::endl;

  float Point2D::getX(){
      return x;
  }
  float Point2D::getY(){
	  return y;
  }

  Point2D::Point2D(float initialX, float initialY){

	  x = initialX;
	  y = initialY;
  }

  Point2D::Point2D(const  Point2D& p) {
      x = p.x;
      y = p.y;
      cout<<"执行了复制构造函数"<<endl;

  }


