/*!Begin Snippet:file*/
import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;

/**
 * Demonstrates the component {@link JLabel}. This class extends
 * class {@link @JPanel}.
 *
 * @author author name
 * @version 1.0.0
 */
public class JLabelDemo extends JPanel {

	private JLabel labelLeft;
	private JLabel labelCenter;
	private JLabel labelRight;

	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("JLabelDemo");

		frame.add(new JLabelDemo());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();    // Adjust the size of the window
		frame.setVisible(true);
	}

	/**
	 * Creates three {@link JLabel} components .
	 */
	public JLabelDemo() {

		setLayout(new GridLayout(1, 3));
		setBackground(Color.white);

		ImageIcon icon = new ImageIcon("picture/bananas.jpg",
		 	"an image with bananas");

		// Create the components
		labelLeft = new JLabel("Hello", icon,JLabel.CENTER);
		labelCenter = new JLabel("Hello",JLabel.CENTER);
		labelRight = new JLabel(icon);

		// Set the position of the text, relative to the icon
		//labelLeft.setVerticalTextPosition(JLabel.BOTTOM);
		//labelLeft.setHorizontalTextPosition(JLabel.CENTER);
		//labelLeft.setFont(new Font("Serif", Font.BOLD, 20));
		labelLeft.setBorder(new TitledBorder("labelLeft"));

		//labelCenter.setFont(new Font("Serif", Font.BOLD, 30));
		labelCenter.setBorder(new TitledBorder("labelCenter"));
		
		labelRight.setBorder(new TitledBorder("labelRight"));

		// Add labels to the container
		add(labelLeft);
		add(labelCenter);
		add(labelRight);
	}
}
/*!End Snippet:file*/