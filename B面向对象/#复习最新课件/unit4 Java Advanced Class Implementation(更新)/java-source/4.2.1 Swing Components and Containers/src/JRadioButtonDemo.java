/*!Begin Snippet:file*/
import java.awt.*;
import javax.swing.*;

/**
 * Demonstrates the component {@link JRadioButton}. This class extends
 * class {@link @JPanel}.
 *
 * @author author name
 * @version 1.0.0
 */
public class JRadioButtonDemo extends JPanel {

	private JRadioButton  buttonOne;
	private JRadioButton  buttonTwo;
	private JRadioButton  buttonThree;

	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("JRadioButtonDemo");

		frame.add(new JRadioButtonDemo());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();    // Adjust the size of the window
		frame.setVisible(true);
	}

	/**
	 * Creates three {@link JRadioButton} components.
	 */
	public JRadioButtonDemo() {

		setLayout(new GridLayout(1, 3));
		setBackground(Color.white);
		
		Font fon = new Font("Serif", Font.BOLD, 30);
		
		// Create the radio buttons
		buttonOne = new JRadioButton("One", true);
		buttonTwo = new JRadioButton("Two",true);
		buttonThree = new JRadioButton("Three");

		/*
		// Group the radio buttons
		ButtonGroup group = new ButtonGroup();
		group.add(buttonOne);
		group.add(buttonTwo);
		group.add(buttonThree);
		*/
		
		//set the radio buttons font		
		buttonOne.setFont(fon);
		buttonTwo.setFont(fon);
		buttonThree.setFont(fon);
		
		// Change the radio buttons colors
		buttonOne.setBackground(Color.white);
		buttonTwo.setBackground(Color.white);
		buttonThree.setBackground(Color.white);

		// Add radio buttons to the container
		add(buttonOne);
		add(buttonTwo);
		add(buttonThree);
	}
}
/*!End Snippet:file*/