import javax.swing.*;
import java.awt.*;

public class Box3Demo {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("BoxLayout");
						
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//let's create and add  componentS.	
	
		Box bv = Box.createVerticalBox();
    		bv.add(new JLabel("Hello"));
    		bv.add(Box.createVerticalGlue());
    		bv.add(new JLabel("Applet"));
    		bv.add(Box.createVerticalGlue());
    		bv.add(new JLabel("World"));
    		
    		Box bh = Box.createHorizontalBox();
    		bh.add(new JLabel("Hello"));
    		bh.add(Box.createHorizontalGlue());
    		bh.add(new JLabel("Applet"));
    		bh.add(Box.createHorizontalGlue());
    		bh.add(new JLabel("World"));
    		bv.add(Box.createVerticalGlue());
    		
    		bv.add(bh);    		
    		bv.add(Box.createVerticalGlue());
    		
    		theFrame.add(bv);		
		// Adjust the size of the window
		theFrame.pack();
		
		//make the frame appear by invoking
		// its setVisible() method
		theFrame.setVisible(true);
		
	}
}