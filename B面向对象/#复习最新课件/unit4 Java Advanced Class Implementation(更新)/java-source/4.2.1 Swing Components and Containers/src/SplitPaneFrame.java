//file: SplitPaneFrame.java
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class SplitPaneFrame {
	public static void main(String[] args) {

		ImageIcon icon = new ImageIcon("picture/bananas.jpg",
	 	"an image with bananas");		
		
		// create a JFrame to hold everything
		JFrame f = new JFrame("SplitPaneFrame");
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				System.exit(0);
			}
		});
		f.setSize(300, 200);
		f.setLocation(200, 200);
		
		JLabel labelLeft = new JLabel("Hello", icon,JLabel.CENTER);
		JLabel labelRight = new JLabel(icon);
		
		JSplitPane split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
				new JScrollPane(labelLeft,
						JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
						JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED), labelRight);
		split.setDividerLocation(100);
		f.getContentPane().add(split);
		f.setVisible(true);
	}
}