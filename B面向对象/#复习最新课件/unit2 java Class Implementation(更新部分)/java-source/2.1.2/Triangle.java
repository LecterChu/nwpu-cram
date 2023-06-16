import Point1.*;
public class Triangle {
	
	private Point2D pointOne;
	private Point2D pointTwo;
	private Point2D pointThree;
	//private Point2D[] points;
	
	public Triangle(Point2D initialPointOne, Point2D initialPointTwo, 
		Point2D initialPointThree) {
		
		pointOne = initialPointOne;
		pointTwo = initialPointTwo;
		pointThree = initialPointThree;	
	}
	
	public void setTriPoint(Point2D newPointOne, Point2D newPointTwo, 
		Point2D newPointThree) { 
		
		pointOne = newPointOne;
		pointTwo = newPointTwo;
		pointThree = newPointThree;	
	}
	public void printTriPoint() {
		
		System.out.println("the three Point2D of this triangle: \n"+"(" + pointOne.getX()+ ","+ pointOne.getY()+")"+
				"\n(" + pointTwo.getX()+ ","+ pointTwo.getY()+")"+
				"\n(" + pointThree.getX()+ ","+ pointThree.getY()+")");
	}
	
	public double perimeter(){
		
		double triSideOne = Math.hypot(pointOne.getX() - pointTwo.getX(),
				pointOne.getY() - pointTwo.getY());
		double triSideOneTwo = Math.hypot(pointTwo.getX() - pointThree.getX(),
				pointTwo.getY() - pointThree.getY());
		double triSideOneThree = Math.hypot(pointOne.getX() - pointThree.getX(),
				pointOne.getY() - pointThree.getY());
		return triSideOne + triSideOneTwo + triSideOneThree;
	}
	
	public static void main(String[] arg) {
		
		Triangle triangle = new Triangle(new Point2D(1,1),
					new Point2D(2,2), new Point2D(3,3));
		triangle.printTriPoint();
		System.out.println("the perimeter of this triangle:\n" + triangle.perimeter());
	
	}
}