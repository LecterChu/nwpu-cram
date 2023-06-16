/*!Begin Snippet:file*/
import java.util.*;
import java.awt.*;
import javax.swing.*;

/**
 * Demonstrates the component {@link JList}. This class extends
 * class {@link @JPanel}.
 *
 * @author author name
 * @version 1.0.0
 */
public class JListDemo extends JPanel {

	private JList listOne;
	private JList listTwo;
	private JList listThree;

	private static final String[] fruitNames =
			{"Orange", "Pear", "Apple", "Pineapple", "Peach",
			 "Grapefruit", "Lemon", "Grape"};
	private Vector<String> vect;
	private DefaultListModel listItems;	

	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("JListDemo");

		frame.add(new JListDemo());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();    // Adjust the size of the window
		frame.setVisible(true);
	}

	/**
	 * Creates two {@link JList} components.
	 */
	public JListDemo() {

		setBackground(Color.white);
		Font fon = new Font("Serif", Font.BOLD, 30);
		
		//create vector
		vect = new Vector<String>();
		vect.add("Orange");
		vect.add("Pear");
		vect.add("Apple");
		vect.add("Pineapple");
		vect.add("Peach");
		vect.add("Grapefruit");
		vect.add("Lemon");
		vect.add("Grape");			
		
		//create ListModel		
		listItems= new DefaultListModel();	
		listItems.addElement("Orange");
		listItems.addElement("Pear");
		listItems.addElement("Apple");
		listItems.addElement("Pineapple");
		listItems.addElement("Peach");
		listItems.addElement("Grapefruit");
		listItems.addElement("Lemon");
		listItems.addElement("Grape");	
		
		// Create the components	
		listOne = new JList(fruitNames);
		listThree = new JList(listItems);
		listTwo = new JList(vect);
			
		// Customize the list properties
		listOne.setVisibleRowCount(5);
		listTwo.setVisibleRowCount(5);
		listThree.setVisibleRowCount(5);
		
		listOne.setSelectionMode(
			ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		listTwo.setSelectionMode(
			ListSelectionModel.SINGLE_SELECTION);
					
		//listOne.setFixedCellHeight(30);
		//listOne.setFixedCellWidth(100);
		
		//listTwo.setFixedCellHeight(3);
		//listTwo.setFixedCellWidth(100);
		
		//set the font of the lists
		listOne.setFont(fon);
		listTwo.setFont(fon);
		listThree.setFont(fon);
		
		// Change the colors of the lists
		listOne.setBackground(new Color(0, 0, 150));
		listTwo.setBackground(new Color(0, 150, 0));
		listThree.setBackground(new Color(150, 0, 0));
		listOne.setForeground(Color.white);
		listTwo.setForeground(Color.white);		
		listThree.setForeground(Color.white);
				
		add(listOne);
		add(listTwo);
		add(listThree);	
		
		// Add lists to the scrollbar containers		
		add(new JScrollPane(listOne,
			JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
			JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
		add(new JScrollPane(listTwo,
			JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
			JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
		add(new JScrollPane(listThree,
			JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
			JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
		/**/
				
	}
}
/*!End Snippet:file*/

