
class Point2D {
        private:
                 float x;
                 float y;
        public:
                  float getX() const;
                  float getY()  const;
      //与ppt中构造函数演示相对应
      //1         Point2D(float, float);
      //2         Point2D(float initialX, float initialY):x(initialX),y(initialY){}
                 Point2D(float initialX=200, float initialY=200);//3
                 ~Point2D();

};
