/*!Begin Snippet:file*/
/**
 * This class models a point in the Cartesian plane.
 *
 * @author author name
 * @version 1.0.0
 */
package Point1;
public class Point2D  {

	/* Number of instances created */
	private static int numberOfInstances = 0;

	/* x coordinate of this point*/
	private int  x;

	/* y coordinate of this point*/
	private int  y;

	/**
	 * Creates a <code>Point2D</code> object and increments the
	 * number of instances.
	 *
	 * @param initialX  the x coordinate
	 * @param initialY  the y coordinate
	 */
	public Point2D(int  initialX, int  initialY)  {

		x = initialX;
		y = initialY;

		numberOfInstances++;
	}

	/**
	 * Returns the number of <code>Point2D</code> instances that
	 * have been created.
	 *
	 * @return the number of <code>Point2D</code> instances that
	 *         have been created.
	 */
	public static int  getNumberOfInstances()  {

		return numberOfInstances;
	}

	/**
	 * Returns the x coordinate of this point.
	 *
	 * @return the x coordinate of this point.
	 */
	public int  getX()  {

		return x;
	}

	/**
	 * Returns the y coordinate of this point.
	 *
	 * @return the y coordinate of this point.
	 */
	public int  getY()  {

		return y;
	}

	/**
	 * Modifies the x coordinate of this point.
	 *
	 * @param newX  the new x coordinate
	 */
	public void  setX(int  newX)  {

		x = newX;
	}

	/**
	 * Modifies the y coordinate of this point.
	 *
	 * @param newY  the new y coordinate
	 */
	public void  setY(int  newY)  {

		y = newY;
	}
	/**
	 * Test driver for class <code>Point2D</code>.
	 *
	 * @param args  not used
	 */
	public static void main(String[] args) {

		System.out.println("Instances after PointOne is created: " +
				Point2D.getNumberOfInstances());	
		
		System.out.println("Instances after PointOne is created: " +
				getNumberOfInstances());	
		
		Point2D pointOne = new Point2D(10, 100);

		System.out.println("x: " + pointOne.getX());
		System.out.println("y: " + pointOne.getY());
		System.out.println("Instances after PointOne is created: " +
			Point2D.getNumberOfInstances());		

		Point2D pointTwo = new Point2D(20, 200);
		
		System.out.println("x: " + pointTwo.getX());
		System.out.println("y: " + pointTwo.getY());
		System.out.println("Instances after PointTwo is created: " +
			Point2D.getNumberOfInstances());

		Point2D pointThree= new Point2D(30, 300);
		
		System.out.println("Instances after PointThree is created: " +
			Point2D.getNumberOfInstances());
	}
}
/*!End Snippet:file*/
