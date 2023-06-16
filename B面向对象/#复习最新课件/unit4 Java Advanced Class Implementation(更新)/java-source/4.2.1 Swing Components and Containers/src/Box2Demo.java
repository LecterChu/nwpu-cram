import javax.swing.*;
import java.awt.*;

public class Box2Demo {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("BoxLayout");
						
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//let's create and add  componentS.	
		Box bv = Box.createVerticalBox();
	   	for(int i = 0; i < 5; i++) {
	      		bv.add(new JButton("" + i));
	      		bv.add(Box.createVerticalStrut(i*10));
	    	}
	    	
    		Box bh = Box.createHorizontalBox();
    		
    		for(int i = 0; i < 5; i++) {
      			bh.add(new JButton("" + i));
      			bh.add(Box.createHorizontalStrut(i*10));
    		}
    		
    		theFrame.add(BorderLayout.EAST, bv);
    		theFrame.add(BorderLayout.SOUTH, bh);
				
		// Adjust the size of the window
		theFrame.pack();
		
		//make the frame appear by invoking
		// its setVisible() method
		theFrame.setVisible(true);
		
	}
}