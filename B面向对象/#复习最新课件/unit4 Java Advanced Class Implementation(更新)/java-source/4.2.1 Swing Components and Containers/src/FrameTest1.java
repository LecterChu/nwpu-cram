//display a JFrame

//First ,we'll import the Swing package,so that the Java 
//compiler will know what a JFrame is: 
import javax.swing.*;
import java.awt.*;
public class FrameTest1 {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("Hello!!!");		
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				
		//let's create and add a component.
		JLabel labelOne = new JLabel("  Happy new year!  ");	
		labelOne.setFont(new Font("Serif", Font.BOLD, 30));			
		//Container contentPane = theFrame.getContentPane();		
		//contentPane.add(labelOne);		
		theFrame.add(labelOne);		
		theFrame.setSize(300,200);	
		Dimension frameSize = theFrame.getSize();
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		
		int centerX = screenSize.width/2;
		int centerY = screenSize.height/2;
		int halfWidth = frameSize.width/2;
		int halfHeight = frameSize.height/2;
		
		theFrame.setLocation(centerX-halfWidth,centerY-halfHeight);
		// Adjust the size of the window
		//theFrame.pack();
		//make the frame appear by invoking
		// its setVisible() method
		theFrame.setVisible(true);
		
	}
}