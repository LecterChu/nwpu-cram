/*!Begin Snippet:file*/
import java.awt.*;
import javax.swing.*;

/**
 * Demonstrates the component {@link JButton}. This class extends
 * class {@link @JPanel}.
 *
 * @author author name
 * @version 1.0.0
 */
public class JButtonDemo extends JPanel {

	private JButton buttonUp;
	private JButton buttonDown;
	private ImageIcon imageUp;
	private ImageIcon imageDown;

	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("JButtonDemo");

		frame.add(new JButtonDemo());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();    // Adjust the size of the window
		frame.setVisible(true);
	}

	/**
	 * Creates two {@link JButton} components.
	 */
	public JButtonDemo() {

		setLayout(new GridLayout(2, 1));
		setBackground(Color.white);

		imageUp = new ImageIcon("picture/bananas.gif",
			"up arrow");
		imageDown= new ImageIcon("picture/bananasdown.gif",
			"down arrow");

		// Create the components
		buttonUp = new JButton("Up", imageUp);
		buttonDown = new JButton("Down", imageDown);

		// Set the position of the text, relative to the icon
		buttonUp.setVerticalTextPosition(AbstractButton.CENTER);
		buttonUp.setHorizontalTextPosition(AbstractButton.LEFT);
		buttonDown.setVerticalTextPosition(AbstractButton.CENTER);
		buttonDown.setHorizontalTextPosition(AbstractButton.LEFT);

		// Set the color of buttons
		buttonUp.setBackground(new Color(0, 100, 0));
		buttonDown.setBackground(new Color(0, 100, 0));
		buttonUp.setForeground(Color.RED);
		buttonDown.setForeground(Color.WHITE);

		// Disable the Down button
		//buttonDown.setEnabled(false);

		// Add buttons to the container
		add(buttonUp);
		add(buttonDown);
	}
}
/*!End Snippet:file*/