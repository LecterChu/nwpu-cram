//display a JFrame

//First ,we'll import the Swing package,so that the Java 
//compiler will know what a JFrame is: 

import javax.swing.*;
import java.awt.*;

public class BorderLayoutDemo {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("BorderLayout");		
		
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//let's create and add  componentS.	
		BorderLayout layout = new BorderLayout();	
		theFrame.setLayout(layout);
		//theFrame.add(new JButton("WEST"));
		//theFrame.add(new JButton("NORTH"));
		//theFrame.add(new JButton("EAST"));
		//theFrame.add(new JButton("CENTER"));
		//theFrame.add(new JButton("SOUTH"));
		
		theFrame.add(new JButton("WEST"),BorderLayout.WEST);
		theFrame.add(new JButton("NORTH"),BorderLayout.NORTH);
		theFrame.add(new JButton("EAST"),BorderLayout.EAST);
		theFrame.add(new JButton("CENTER"),BorderLayout.CENTER);
		theFrame.add(new JButton("SOUTH"),BorderLayout.SOUTH);
		//layout.setHgap(10);
		//layout.setVgap(10);		
		// Adjust the size of the window
		theFrame.setSize(400,400);
		Dimension frameSize = theFrame.getSize();
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		
		int centerX = screenSize.width/2;
		int centerY = screenSize.height/2;
		int halfWidth = frameSize.width/2;
		int halfHeight = frameSize.height/2;
		
		theFrame.setLocation(centerX-halfWidth,centerY-halfHeight);
		
		//make the frame appear by invoking
		// its setVisible() method
		theFrame.setVisible(true);
		
	}
}