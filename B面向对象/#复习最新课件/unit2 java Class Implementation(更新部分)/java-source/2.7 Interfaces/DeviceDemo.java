import  java.io.*;

/**
 * This class demonstrates the use of the container classes.
 *
 * @author mcy
 * @version 1.0.0 
 */
public class DeviceDemo {

	private static PrintWriter  stdOut =
		new PrintWriter(System.out, true);
		
	public static Device randDevice() {		
		
		switch((int)(Math.random() * 3)) {
			default:
			case 0: return new TV("TV");
			case 1: return new LightBulb("LightBulb");
			case 2: return new Stopwatch("Stopwatch");
	  	}
	}	
	 
	/**
	 * Demonstrates the use of polymorphism in the container
	 * classes.
	 *
	 * @param args  not used.
	 */
	public static void  main(String[]  args) {

		Device[] device = new Device[8];
		
		for (int index=0; index<8; index++){
			device[index] = DeviceDemo.randDevice();
		}
		
		for (int index=0; index<8; index++){
			device[index].turnOn();
			for (int i = 0; i < 50000000; i++);		
			device[index].turnOff();
		}
		
	}
}