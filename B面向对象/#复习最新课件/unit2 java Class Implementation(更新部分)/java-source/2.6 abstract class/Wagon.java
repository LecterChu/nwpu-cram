/*!Begin Snippet:file*/
/**
 * This class models a wagon container.
 *
 * @author author name
 * @version 1.0.0
 * @see Container
 */
public class  Wagon  extends  Container  {

	/* The width of the wagon */
	private double  width;

	/* The height of the wagon */
	private double  height;

	/* The length of the wagon */
	private double  length;

	/**
	 * Constructs a <code>Wagon</code> object.
	 *
	 * @param initialWidth  the width of this wagon.
	 * @param initialHeight  the height of this wagon.
	 * @param initialLength  the length of this wagon.
	 */
	 public Wagon(double initialWidth,
		double initialHeight,
		double initialLength) {

	 	width = initialWidth;
	 	height = initialHeight;
	 	length = initialLength;
	 }

	/**
	 * Overrides {@link Container#computeVolume()}.
	 * <p>
	 * Computes the volume of this wagon.
	 * </p>
	 *
	 * @return the volume of this wagon.
	 */
	public double  computeVolume() {

		return width * height * length;
	}
	
	public String toString(){
		
		return "Wagon.computeVolume():";
	}
}
/*!End Snippet:file*/