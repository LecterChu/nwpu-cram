/*!Begin Snippet:file*/
import java.awt.*;/*!Begin Snippet:file*/
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

/**
 * Demonstrates event-handling for lists and buttons. This class
 * extends class {@link @JPanel}.
 *
 * @author author name
 * @version One.0.0
 */
public class FruitListDemo extends JPanel {

	private JList  fruitList;
	private JButton  resetButton;
	private JTextArea resultTextArea;

	private Vector<String> vector;

	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("FruitListDemo");

		frame.setContentPane(new FruitListDemo());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);
	}

	/**
	 * Create a Graphical User Interface.
	 */
	public FruitListDemo() {

		setBackground(Color.white);
		Font font = new Font("Serif", Font.BOLD, 30);	
		setupVector();

		// Create the components
		fruitList = new JList(vector);
		resultTextArea = new JTextArea(6, 15);
		resetButton = new JButton("Reset Fruit List");
		
		fruitList.setFont(font);
		resultTextArea.setFont(font);
		resetButton.setFont(font);
		
		// Customize the component properties
		fruitList.setVisibleRowCount(4);
		fruitList.setSelectionMode(
					ListSelectionModel.SINGLE_SELECTION);
		//fruitList.setSelectionMode(
		//			ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		//fruitList.setSelectionMode(
		//			ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);			
		
		JPanel listPanel = new JPanel();
		listPanel.setBackground(Color.white);
		listPanel.add(
			new JScrollPane(fruitList,
					JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
					JScrollPane.HORIZONTAL_SCROLLBAR_NEVER));

		JPanel textAreaPanel = new JPanel();
		textAreaPanel.setBackground(Color.white);
		textAreaPanel.add(
			new JScrollPane(resultTextArea,
					JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
					JScrollPane.HORIZONTAL_SCROLLBAR_NEVER));

		setLayout(new BorderLayout());
		add(listPanel, BorderLayout.NORTH);
		add(resetButton, BorderLayout.CENTER);
		add(textAreaPanel, BorderLayout.SOUTH);
		// Register a listener for the list component
		fruitList.addListSelectionListener(new FruitListListener());
		
		// Register a listener for the button component
		resetButton.addActionListener(new ResetButtonListener());
	}

	/*
	 * Initializes the vector.
	 */
	private void setupVector() {

		vector = new Vector<String>();

		vector.add("Orange");
		vector.add("Pear");
		vector.add("Apple");
		vector.add("Pineapple");
		vector.add("Peach");
		vector.add("Grapefruit");
		vector.add("Lemon");
		vector.add("Grape");
		vector.add("Banana");
		vector.add("Tangerine");
	}

	/**
	 * This inner class handles list-selection events.
	 */
	class FruitListListener implements ListSelectionListener {

		/**
		 * Moves the selected element from the list to the text area.
		 *
		 * @param event  the event object.
		 */
		public void valueChanged(ListSelectionEvent event) {
			/**/
			int index = fruitList.getSelectedIndex();

			if (! fruitList.getValueIsAdjusting() && index != -1) {
				resultTextArea.append(fruitList.getSelectedValue()
				                      + "\n");
				vector.removeElementAt(index);
				fruitList.setListData(vector);
			}
			
			/*				
			if (! fruitList.getValueIsAdjusting()){
				Object[] items = fruitList.getSelectedValues();
				for(int i = 0; i < items.length; i++){
					resultTextArea.append(items[i]+"\n");
					vector.remove(items[i]);
			}
			fruitList.setListData(vector);				
			}
			
			*/
			
			
			
		}
	}

	/**
	 * This inner class handles button events.
	 */
	class ResetButtonListener implements ActionListener {

		/**
		 * Restores the list to its original state.
		 *
		 * @param event  the event object.
		 */
		public void actionPerformed(ActionEvent event) {

			setupVector();
			fruitList.setListData(vector);
			resultTextArea.setText("");
		}
	}	
}
/*!End Snippet:file*/