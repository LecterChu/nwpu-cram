//display a JFrame

//First ,we'll import the Swing package,so that the Java 
//compiler will know what a JFrame is: 

import javax.swing.*;
import java.awt.*;

public class FrameTest2 {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("Hello!!!");
		
		JPanel panelOne = new JPanel();
		JPanel panelTwo = new JPanel();
		
		JLabel labelOne = new JLabel("I am labelOne    ");
		JLabel labelTwo = new JLabel("I am labelTwo     ");
		JLabel labelThree = new JLabel("I am labelThree   ");
		
		Font fon = new Font("Serif", Font.BOLD, 30);
		labelOne.setFont(fon);
		labelTwo.setFont(fon);
		labelThree.setFont(fon);
		
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//let's create and add a component.	
		
		theFrame.add(panelOne);		
		theFrame.add(panelTwo);
		
		panelOne.add(labelOne);
		panelTwo.add(labelTwo);
		panelTwo.add(labelThree);
		/*
		panelOne.add(labelOne);
		panelOne.add(panelTwo);
		
		panelTwo.add(labelTwo);
		panelTwo.add(labelThree);
		
		*/			
		// Adjust the size of the window
		theFrame.pack();
		theFrame.setSize(300,200);	
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