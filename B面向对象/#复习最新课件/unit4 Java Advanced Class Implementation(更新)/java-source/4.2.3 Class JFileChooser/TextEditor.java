import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;

/**
 * Demonstrates the class {@link JFileChooser}. This class extends
 * class {@link @JPanel}.
 *
 * @author author name
 * @version 1.0.0
 */
public class TextEditor extends JPanel {

	/* Line separator */
	private final static String NEW_LINE =
			System.getProperty("line.separator");

	/* Standard error stream */
	private static PrintWriter  stdErr =
			new PrintWriter(System.err, true);


	private JButton  openButton;
	private JButton  saveButton;
	private TextArea  textArea;

	private JFileChooser  fileChooser;

	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("TextEditor");

		frame.setContentPane(new TextEditor());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(400,400);
		frame.setVisible(true);
	}

	/**
	 * Creates a Graphical User Interface.
	 */
	public TextEditor() {

		setBackground(Color.white);

		// Create the components
		openButton = new JButton("Open");
		saveButton = new JButton("Save");
		openButton.setFont(new Font("Serif", Font.BOLD, 30));
		saveButton.setFont(new Font("Serif", Font.BOLD, 30));
		
		textArea = new TextArea();

		fileChooser = new JFileChooser();
		//fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

		// Register the listeners for the buttons
		openButton.addActionListener(new OpenButtonListener());
		saveButton.addActionListener(new SaveButtonListener());

		// Add components to the container
		setLayout(new BorderLayout());
		add(openButton, BorderLayout.NORTH);
		add(textArea, BorderLayout.CENTER);
		add(saveButton, BorderLayout.SOUTH);
	}

	/**
	 * This inner class handles button clicks for the Open button.
	 */
	class OpenButtonListener implements ActionListener {

		/**
		 * Opens a text file.
		 *
		 * @param event  the event object.
		 */
		public void actionPerformed(ActionEvent event)  {

			int result = fileChooser.showOpenDialog(null);

			if (result == JFileChooser.APPROVE_OPTION) {

				try {

					File file = fileChooser.getSelectedFile();
					BufferedReader  input =
							new BufferedReader(new FileReader(file));

					String  line = input.readLine();

					while (line != null)  {
						textArea.append(line + NEW_LINE);
						line = input.readLine();
					}
					input.close();
					
				} catch (IOException ioe) {
					stdErr.println(ioe.toString());
				}
			}
		}
	}

	/**
	 * This inner class handles button clicks for the Save button.
	 */
	class SaveButtonListener implements ActionListener {

		/**
		 * Saves a text file.
		 *
		 * @param event  the event object.
		 */
		public void actionPerformed(ActionEvent event) {

			int result = fileChooser.showSaveDialog(null);

			if (result == JFileChooser.APPROVE_OPTION) {

				try {

					File file = fileChooser.getSelectedFile();
					PrintWriter output =
							new PrintWriter(new FileWriter(file));

					output.print(textArea.getText());
					output.close();
					
				} catch (IOException ioe) {
					stdErr.println(ioe.toString());
				}
			}
		}
	}
}

