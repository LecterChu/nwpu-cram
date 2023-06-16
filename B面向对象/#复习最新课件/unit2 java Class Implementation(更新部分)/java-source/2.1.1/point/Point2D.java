package point;
public class Point2D {
	
	private float x;
	private float y;
	
	public Point2D(float initialX, float initialY) {
		
		x = initialX;
		y = initialY;
	}
	
	public float getX() {
		
		return x;
	}
	
	public float getY() {
		
		return y;
	}	
	
	public static void main(String[] args) {
		
		Point2D pointOne = new Point2D(100.0f,200.0f);
		
		System.out.println("x = "+pointOne.getX()
												
				+"  y = "+pointOne.getY());
												

		
												
	}
}
