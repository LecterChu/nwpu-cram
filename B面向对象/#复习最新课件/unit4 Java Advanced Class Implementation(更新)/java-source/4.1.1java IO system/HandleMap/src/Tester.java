import com.cochef.mapgen.data.GPSLocation;
import com.cochef.mapgen.util.GPST;
import com.cochef.mapgen.util.GeometryCalcu;

/**
 * 
 */

/**
 * @author mcy
 *
 */
public class Tester {
	
	public static void main(String args[]) {
		GPSLocation gps = new GPSLocation(108.802929,34.259345);
		GPSLocation gps2 = new GPSLocation(108.850651,34.258777);
		System.out.println(gps.realDistance(gps2));
	}

}
