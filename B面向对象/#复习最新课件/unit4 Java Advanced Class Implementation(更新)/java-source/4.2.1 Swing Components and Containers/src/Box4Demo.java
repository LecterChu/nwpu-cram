import javax.swing.*;
import java.awt.*;

public class Box4Demo {
	
	public static void main(String[] args) {
		
		//instantiate a JFrame object.		
		JFrame theFrame = new JFrame("BoxLayout");
						
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//let's create and add  componentS.	
		
		Box bv = Box.createVerticalBox();
    		bv.add(new JButton("Top"));
    		bv.add(Box.createRigidArea(new Dimension(120, 90)));
    		bv.add(new JButton("Bottom"));
    		Box bh = Box.createHorizontalBox();
    		bh.add(new JButton("Left"));
    		bh.add(Box.createRigidArea(new Dimension(160, 80)));
    		bh.add(new JButton("Right"));
    		bv.add(bh);
    		theFrame.add(bv);
				
		// Adjust the size of the window
		theFrame.pack();
		
		//make the frame appear by invoking
		// its setVisible() method
		theFrame.setVisible(true);
		
	}
}