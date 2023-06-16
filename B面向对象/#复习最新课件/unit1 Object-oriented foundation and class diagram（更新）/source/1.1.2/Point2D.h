#ifndef POINT2D_H_
#define POINT2D_H_
class Point2D {
        private:
                 float x;
                 float y;
        public:
                  float getX();
                  float getY();
                  Point2D(float initialX=100, float initialY=100);
                  Point2D(const  Point2D& p);
};
#endif
