/*
 * vectorExample.cpp
 *
 *  Created on: 2013-10-25
 *      Author: Administrator
 */

/**
 * @author Administrator
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include "Point2D.h"
using namespace std;

void print(Point2D p){
		    cout<<"point"<<": "<<"x="<<p.getX()
				        <<" ,y="<<p.getY()<<endl;
}
int main(){

    vector<Point2D>   vect;
	vector<Point2D*>  vect1;
	vector<Point2D>    *vect2 = new   vector<Point2D>;
	vector<Point2D*>  *vect3 = new   vector<Point2D*>;
	vector<Point2D> vect4(3);

	vect.push_back(Point2D(100,2000));	
	vect.push_back(Point2D(100,4000));	
	vect.push_back(Point2D(100,6000));	
	vect1.push_back(new Point2D(100,200));
	vect1.push_back(new Point2D(300,400));
	vect1.push_back(new Point2D(500,600));
	vect2->push_back(Point2D(100,20));
	vect2->push_back(Point2D(100,40));
	vect2->push_back(Point2D(100,60));
	vect3->push_back(new Point2D(100,2));
	vect3->push_back(new Point2D(100,4));
	vect3->push_back(new Point2D(100,6));
   
	for(vector<Point2D*>::size_type i = 0; 
		    i != vect.size(); ++i){
                 cout<<"point"<<i<<": "<<"x="<< vect[i].getX()
	       <<" ,y="<<vect[i].getY()<<endl;
       }
	for(vector<Point2D*>::size_type i = 0;
        i != vect1.size(); ++i){
	   cout<<"vect["<<i<<"]:"<<vect1[i]->getX()
	     <<","<<vect1[i]->getY()<<endl;
	}
	for(vector<Point2D*>::size_type i = 0;
        i != (*vect2).size(); ++i){
	   cout<<"vect["<<i<<"]:"<<(*vect2)[i].getX()
	     <<","<<(*vect2)[i].getY()<<endl;
	}
	for(vector<Point2D*>::size_type i = 0;
        i != (*vect3).size(); ++i){
	   cout<<"vect["<<i<<"]:"<<(*vect3)[i]->getX()
	     <<","<<(*vect3)[i]->getY()<<endl;
	}
	for(vector<Point2D>::size_type i = 0;
        i != vect4.size(); ++i){
	   cout<<"vect["<<i<<"]:"<<vect4[i].getX()
	     <<","<<vect4[i].getY()<<endl;
		
	} /**/
	
	 /*
		for(vector<Point2D*>::reverse_iterator iter = vect1.rbegin();  
		       iter!= vect1.rend(); ++iter){
			     cout<<"point"<<": "<<"x="<<(*iter)->getX()
				        <<" ,y="<<(*iter)->getY()<<endl;
	    }*/
	
	  /*  	
		for(vector<Point2D*>::iterator iter = vect1.begin();  
		       iter!= vect1.end(); ++iter){
			   *iter = new Point2D(99,99);
	           cout<<"point"<<": "<<"x="<<(*iter)->getX()
				        <<" ,y="<<(*iter)->getY()<<endl;
	    }*/
		
		
		//for_each(vect4.begin(),vect4.end(),print);
		
		/*for(vector<Point2D>::const_iterator iter = vect1->begin();  
		       iter!= vect1->end(); ++iter){
	           cout<<"point"<<": "<<"x="<<(*iter).getX()
				        <<" ,y="<<(*iter).getY()<<endl;
	    }
		for(vector<Point2D*>::const_iterator iter = vect3->begin();  
		       iter!= vect3->end(); ++iter){
	           cout<<"point"<<": "<<"x="<<(*iter)->getX()
				        <<" ,y="<<(*iter)->getY()<<endl;
	    }
		delete vect1;
		delete vect2;
	*/
		
	

	return 0;
}
