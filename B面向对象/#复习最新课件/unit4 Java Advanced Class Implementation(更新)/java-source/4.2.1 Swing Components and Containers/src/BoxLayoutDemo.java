
import javax.swing.*;
import java.awt.*;

public class BoxLayoutDemo {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("BoxLayout");
						
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//let's create and add  componentS.	
		
		GridLayout grid=new GridLayout(25,4);	
		
		JPanel jpv = new JPanel();
	        jpv.setLayout(new BoxLayout(jpv, BoxLayout.Y_AXIS));
	        
	    	for(int i = 0; i < 5; i++) {
	      		jpv.add(new JButton("" + i));
	      	}
	      	
	    	JPanel jph = new JPanel();	    	
	    	jph.setLayout(new BoxLayout(jph, BoxLayout.X_AXIS));
	    	
	    	for(int i = 0; i < 5; i++) {
	      		jph.add(new JButton("" + i));
	      	}
	    
	    	theFrame.add(BorderLayout.EAST, jpv);
	    	theFrame.add(BorderLayout.SOUTH, jph);
				
		// Adjust the size of the window
		theFrame.pack();
		
		//make the frame appear by invoking
		// its setVisible() method
		theFrame.setVisible(true);
		
	}
}