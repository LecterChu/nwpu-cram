/*!Begin Snippet:file*/
import java.awt.*;
import javax.swing.*;

/**
 * Demonstrates the component {@link JTextField}. This class extends
 * class {@link @JPanel}.
 *
 * @author author name
 * @version 1.0.0
 */
public class JTextFieldDemo extends JPanel {

	private JLabel  labelCountry;
	private JLabel  labelCapital;
	private JTextField  textFieldCountry;
	private JTextField  textFieldCapital;

	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("JTextFieldDemo");

		frame.add(new JTextFieldDemo());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();    // Adjust the size of the window
		frame.setVisible(true);
	}

	/**
	 * Creates two {@link JLabel} components and two {@link JTextField}
	 * components.
	 */
	public JTextFieldDemo() {

		setLayout(new GridLayout(2, 1));
		setBackground(Color.white);
		Font fon = new Font("Serif", Font.BOLD, 30);
		
		// Create the components
		labelCountry = new JLabel("Country:");
		textFieldCountry = new JTextField("China", 10);
		labelCapital = new JLabel("Capital:");
		textFieldCapital = new JTextField("Bei jing", 10);
		
		labelCountry.setFont(fon);
		textFieldCountry.setFont(fon);
		labelCapital.setFont(fon);
		textFieldCapital.setFont(fon);

		//textFieldCountry.setEditable(false);
		
		// Change the colors of the text fields
		textFieldCapital.setBackground(new Color(150, 0, 0));
		textFieldCapital.setForeground(Color.white);

		// Define the text aligment
		textFieldCapital.setHorizontalAlignment(JTextField.CENTER);

		// Make the text field un-editable
		textFieldCapital.setEditable(false);

		// Add components to the container.
		JPanel panelCountry = new JPanel();
		
		panelCountry.setBackground(Color.white);
		panelCountry.add(labelCountry);
		panelCountry.add(textFieldCountry);
		add(panelCountry);

		JPanel panelCapital = new JPanel();

		panelCapital.setBackground(Color.white);
		panelCapital.add(labelCapital);
		panelCapital.add(textFieldCapital);
		add(panelCapital);
	}
}
/*!End Snippet:file*/