/*!Begin Snippet:file*/
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

/**
 * Demonstrates event-handling for radio buttons. This class extends
 * class {@link @JPanel}.
 *
 * @author author name
 * @version 1.0.0
 */
public class ButtonEventsDemo extends JPanel {

	private JRadioButton  buttonOne;
	private JRadioButton  buttonTwo;
	private JRadioButton  buttonThree;
	private JLabel  label;
	private JTextField text;
	private JButton buttonFour;
	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("ButtonEventsDemo1");

		frame.setContentPane(new ButtonEventsDemo());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);
	}

	/**
	 * Creates the components.
	 */
	public ButtonEventsDemo() {

		setBackground(Color.white);

		// Creates the components
		buttonOne = new JRadioButton("One", true);
		buttonTwo = new JRadioButton("Two");
		buttonThree = new JRadioButton("Three");
		buttonFour = new JButton("Enable Text Edit");			
		label = new JLabel(buttonOne.getText());
		
		label.setFont(new Font("Serif", Font.BOLD, 42));
		label.setHorizontalAlignment(JLabel.CENTER);
		
		text = new JTextField();
		text.setEditable(false);
		
		text.setFont(new Font("Serif", Font.BOLD, 42));
		text.setHorizontalAlignment(JLabel.CENTER);
				
		// Group the radio buttons
		/*
		ButtonGroup group = new ButtonGroup();
		group.add(buttonOne);
		group.add(buttonTwo);
		group.add(buttonThree);
        */
		// Change the buttons colors
		buttonOne.setBackground(Color.WHITE);
		buttonTwo.setBackground(Color.WHITE);
		buttonThree.setBackground(Color.WHITE);		
		buttonFour.setForeground(Color.RED);
		
		buttonOne.setFont(new Font("Serif", Font.BOLD, 30));
		buttonTwo.setFont(new Font("Serif", Font.BOLD, 30));
		buttonThree.setFont(new Font("Serif", Font.BOLD, 30));
		buttonFour.setFont(new Font("Serif", Font.BOLD, 30));
		
		// Add the radio buttons to a panel
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(3, 1));
		panel.add(buttonOne);
		panel.add(buttonTwo);
		panel.add(buttonThree);
		 
		// Create the layout
		setLayout(new BorderLayout());
		add(panel, BorderLayout.WEST);
		add(label, BorderLayout.SOUTH);		
		add(text,BorderLayout.CENTER);	
		add(buttonFour,BorderLayout.NORTH);
			
		panel.setBorder(BorderFactory.createEtchedBorder());
		label.setBorder(BorderFactory.createLoweredBevelBorder());
		text.setBorder(BorderFactory.createLoweredBevelBorder());
		
		// Register the listeners for the radio buttons.
		buttonOne.addActionListener(new ListenerOne());
		buttonTwo.addActionListener(new ListenerTwo());
		buttonThree.addActionListener(new ListenerThree());		
		buttonFour.addActionListener(new ListenerFour());
		text.addActionListener(new ListenerFive());
	}

	/**
	 * This inner class handles events associated with radio
	 * button "One".
	 */
	class ListenerOne implements ActionListener {

		/**
		 * Changes the text of the label.
		 *
		 * @param event  the event object.
		 */
		public void actionPerformed(ActionEvent event) {

			label.setText(buttonOne.getText());
			
		}
	}

	/**
	 * This inner class handles events associated with radio
	 * button "Two".
	 */
	class ListenerTwo implements ActionListener {

		/**
		 * Changes the text of the label.
		 *
		 * @param event  the event object.
		 */
		public void actionPerformed(ActionEvent event) {

			label.setText(buttonTwo.getText());
			
		}
	}

	/**
	 * This inner class handles events associated with radio
	 * button "Three".
	 */
	class ListenerThree implements ActionListener {

		/**
		 * Changes the text of the label.
		 *
		 * @param event  the event object.
		 */
		public void actionPerformed(ActionEvent event) {

			label.setText(buttonThree.getText());
			
		}
	}
	
	class ListenerFour implements ActionListener {

		/**
		 * Changes the editable of the text .
		 *
		 * @param event  the event object.
		 */
		public void actionPerformed(ActionEvent event) {

			if (text.isEditable()) {
				text.setEditable(false);
			} else {
				text.setEditable(true);
			}			
		}
	}
	
	class ListenerFive implements ActionListener {

		/**
		 * Changes the text of the label.
		 *
		 * @param event  the event object.
		 */
		public void actionPerformed(ActionEvent event) {

			label.setText(text.getText());
		}
	}
	
}
/*!End Snippet:file*/


