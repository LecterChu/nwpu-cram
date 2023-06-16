/*!Begin Snippet:file*/
import java.io.*;

/**
 * This class models a watch that can be started and stopped at
 * will for exact timing.
 *
 * @author author name
 * @version  1.0.0
 * @see Device
 * @see System
 */
public class Stopwatch  implements Device {

	/** Represents the off state */
	public static final int  OFF = 0;

	/** Represents the on state */
	public static final int  ON = 1;

	/* Standard output stream */
	private static PrintWriter  stdOut =
		new  PrintWriter(System.out, true);

	/* State of this device */
	private int state;

	/* Stores the time when the device is turn on */
	private long startTime;
	
	private String name;

	/**
	 * Tests the class <code>Stopwatch</code>.
	 */
	public static void main (String[] args) {

		Device device = new Stopwatch("Stopwatch");

		device.turnOn();

		/* delay */
		for (int i = 0; i < 50000000; i++);

		device.turnOff();
	}

	/**
	 * Constructs a <code>Stopwatch</code> object.
	 * <p>
	 * The initial state of the stopwatch is off.
	 * </p>
	 */
	public Stopwatch (String initialName) {

		state = Stopwatch.OFF;
		startTime = 0;
		name = initialName;
	}

	/**
	 * Turns the stopwatch off and outputs how long the stopwatch
	 * was on.
	 */
	public void turnOff() {

		if (state == Stopwatch.OFF) {
			stdOut.println("The Stopwatch is off");
		} else {

			long rightNow  = System.currentTimeMillis();			
			stdOut.println("Time: " + (rightNow - startTime));
			stdOut.println("turn off the device:"+name);
			startTime = 0;
			state = Stopwatch.OFF;
		}
	}

	/**
	 * Turns the stopwatch on and takes note of the current time.
	 */
	public void turnOn() {

		startTime = System.currentTimeMillis();
		state = Stopwatch.ON;
		stdOut.println("turn on the device:"+name);
	}
}
/*!End Snippet:file*/