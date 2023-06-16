//display a JFrame

//First ,we'll import the Swing package,so that the Java 
//compiler will know what a JFrame is:   

import javax.swing.*;
import java.awt.*;

public class GridLayoutDemo {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("BorderLayout");
						
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		
		GridLayout grid=new GridLayout(7,3);//24,3...4,3	
		theFrame.setLayout(grid);
		
		for (int i = 1; i <8; i++){
			for (int j =1; j<4; j++) {
				theFrame.add(new JButton("Row"+i+","+"Column"+j));			
			}
		}
				
		// Adjust the size of the window
		theFrame.pack();
		
		//make the frame appear by invoking 
		// its setVisible() method
		theFrame.setVisible(true);
		
	}
}