#include <iostream>
#include "Triangle.h"
using std::cout;
using std::endl;
  int main(){
      Point2D *pointOne= new Point2D(30,30);
      cout<<"x and y of pointOne are "<<pointOne->getX()
                          <<" and "<<pointOne->getY()
						  <<"  address: "<<pointOne<<endl;
      Point2D *pointTwo = pointOne;//赋值
      cout<<"x and y of pointTwo are "<<pointTwo->getX()
                          <<" and "<<pointTwo->getY()
						  <<"  address:  "<<pointTwo<<endl;
	  delete pointOne;
/**/
      
	  //演示两个对象的赋值      
      /*
      Point2D pointOne(30,30), pointTwo;
      cout<<"x and y of pointOne are "<<pointOne.getX()
                          <<" and "<<pointOne.getY()
						  <<"  address: "<<&pointOne<<endl;
      cout<<"x and y of pointTwo are "<<pointTwo.getX()
                          <<" and "<<pointTwo.getY()
						  <<"  address:  "<<&pointTwo<<endl;
      pointTwo = pointOne;//赋值
      cout<<"x and y of pointTwo are "<<pointTwo.getX()
                          <<" and "<<pointTwo.getY()
						  <<"  address:  "<<&pointTwo<<endl;
	*/
	
	 
      /*Point2D pointOne(30,30);
	  Point2D pointThree(pointOne);//复制构造函数自动调用的第一种情况
      Point2D pointFour = pointOne;//复制构造函数自动调用的第一种情况
      cout<<"x and y of pointOne are "<<pointOne.getX()
                          <<" and "<<pointOne.getY()
						  <<"  address: "<<&pointOne<<endl;
      cout<<"x and y of pointTwo are "<<pointThree.getX()
                          <<" and "<<pointThree.getY()
						  <<"  address:  "<<&pointThree<<endl;
	  cout<<"x and y of pointTwo are "<<pointFour.getX()
                          <<" and "<<pointFour.getY()
						  <<"  address:  "<<&pointFour<<endl;
*/
	
     /*  Point2D p1(1,1);
      Point2D p2(2,2);
	  Triangle triangle = Triangle(p1,p2, Point2D(3,3));//复制构造函数自动调用的第二种情况
	  cout<<"stopping" <<endl;
	 Point2D pointFive;
	  pointFive = triangle.getFirstPoint();//复制构造函数自动调用的第三种情况
	  cout<<"the first point of this triangle:\n" 
	              <<pointFive.getX()<<endl;
	  */
      return 0;
  }
