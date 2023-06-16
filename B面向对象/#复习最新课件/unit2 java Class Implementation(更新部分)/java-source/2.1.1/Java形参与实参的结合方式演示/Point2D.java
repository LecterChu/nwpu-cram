
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
	public void setX(float newX){
		
		x=newX;
	}
	public void setY(float newY){
		
		y=newY;
	}
	public String toString(){
		return getX()+","+getY();
	}
	
}
