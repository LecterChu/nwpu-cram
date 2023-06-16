//display a JFrame

//First ,we'll import the Swing package,so that the Java 
//compiler will know what a JFrame is: 

import javax.swing.*;
import java.awt.*;

public class FlowLayoutDemo {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("BorderLayout");
		JPanel thePanel = new JPanel();
				
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		theFrame.add(thePanel);
		
		for(int i = 0; i < 20; i++){
			thePanel.add(new JButton("Button"+i));		
		}
				 
		theFrame.setSize(200,400);		
		//make the frame appear by invoking
		// its setVisible() method
		theFrame.setVisible(true);
		
	}
}