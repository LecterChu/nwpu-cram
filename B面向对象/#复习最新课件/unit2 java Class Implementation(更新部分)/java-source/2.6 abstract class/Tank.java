/*!Begin Snippet:file*/
/**
 * This class models a tank container.
 *
 * @author author name
 * @version 1.0.0
 * @see Container
 */
public class  Tank  extends  Container  {

	/* The radius of the tank */
	private double  radius;

	/* The length of the tank */
	private double  length;

	/**
	 * Constructs a <code>Tank</code> object
	 *
	 * @param initialRadius  the radius of this tank.
	 * @param initialLength  the length of this tank.
	 */
	 public Tank(double initialRadius,
		double initialLength) {

	 	radius = initialRadius;
	 	length = initialLength;
	 }

	/**
	 * Overrides {@link Container#computeVolume()}.
	 * <p>
	 * Computes the volume of this tank.
	 * </p>
	 *
	 * @return the volume of this tank.
	 */
	public double  computeVolume() {

		return Math.PI * radius * radius * length;
	}
	
	public String toString(){
		
		return "Tank.computeVolume():";
	}
}
/*!End Snippet:file*/