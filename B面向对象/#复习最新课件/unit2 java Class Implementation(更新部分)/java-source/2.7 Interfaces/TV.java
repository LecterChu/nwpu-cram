/*!Begin Snippet:file*/
import java.io.*;

/**
 * This class demonstrates the use of interface {@link Device}.
 *
 * @author author name
 * @version  1.0.0
 * @see Device
 */
public class TV  implements Device {

	/* Standard output stream */
	private static PrintWriter  stdOut =
		new  PrintWriter(System.out, true);

	/* The name of the device */
	private String  name;

	/**
	 * Tests the class <code>DeviceDemo</code>.
	 */
	public static void main (String[] args) {

		Device device = new TV("TV");

		device.turnOn();
		device.turnOff();
		System.out.println(device.toString());
	}

	/**
	 * Constructs a <code>DeviceDemo</code> object.
	 *
	 * @param name  the name of this device.
	 */
	public TV (String initialName) {

		name = initialName;
	}

	/**
	 * Turns the device off.
	 */
	public void turnOff() {

		stdOut.println("Turn off the device " + name);
	}

	/**
	 * Turns the device on.
	 */
	public void turnOn() {

		stdOut.println("Turn on the device " + name);
	}
	public String toString() {
		
		return "TV";
	}
}
/*!End Snippet:file*/