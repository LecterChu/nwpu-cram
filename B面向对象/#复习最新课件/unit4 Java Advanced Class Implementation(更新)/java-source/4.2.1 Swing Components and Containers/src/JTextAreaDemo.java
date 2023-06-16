/*!Begin Snippet:file*/
import java.awt.*;
import javax.swing.*;

/**
 * Demonstrates the component {@link JTextArea}. This class extends
 * class {@link @JPanel}.
 *
 * @author author name
 * @version 1.0.0
 */
public class JTextAreaDemo extends JPanel {

	private JTextArea textAreaOne;
	private JTextArea textAreaTwo;

	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("JTextAreaDemo");

		frame.setContentPane(new JTextAreaDemo());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();    // Adjust the size of the window
		frame.setVisible(true);
	}

	/**
	 * Creates two {@link JTextArea} components.
	 */
	public JTextAreaDemo() {

		setBackground(Color.white);

		String text = "Line1\nLine2\nLine3\nLine4\nLine5\n"
			+ "Line6\nLine7\nLine8\nLine9\nLine10\n";
			
		Font fon = new Font("Serif", Font.BOLD, 30);
		
		// Create the components
		textAreaOne = new JTextArea(text, 5, 10);
		textAreaTwo = new JTextArea(text, 5, 10);
		
		textAreaOne.setFont(fon);
		textAreaTwo.setFont(fon);

		// Change the colors of the components
		textAreaOne.setBackground(new Color(0, 0, 150));
		textAreaTwo.setBackground(new Color(0, 150, 0));
		textAreaOne.setForeground(Color.white);
		textAreaTwo.setForeground(Color.white);

		// Make the text area un-editable
		textAreaTwo.setEditable(false);

		// Add text area components to the scrollbar container.
		/*
		add(new JScrollPane(textAreaOne,
			JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
			JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
		add(new JScrollPane(textAreaTwo,
			JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
			JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS));
		*/
		/**/	
		add(new JScrollPane(textAreaOne,
			JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
			JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
		add(new JScrollPane(textAreaTwo,
			JScrollPane.VERTICAL_SCROLLBAR_NEVER,
			JScrollPane.HORIZONTAL_SCROLLBAR_NEVER));
		
	}
}
/*!End Snippet:file*/