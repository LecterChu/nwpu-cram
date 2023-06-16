/*!Begin Snippet:file*/
import javax.swing.*;

/**
 * @author author name
 * @version 1.0.0
 */
import javax.swing.border.*;

public class ButtonGroups extends JPanel {

	static String[] ids = { "快", "乐", "每", 
	"一", "天"};
  
	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		JFrame frame = new JFrame("ButtonGroups");

		frame.add(new ButtonGroups());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(300,300);    // Adjust the size of the window
		frame.setVisible(true);
	}

	/**
	 * Creates three {@link JRadioButton} components.
	 */
	public ButtonGroups() {
		
		JPanel jp1 = new JPanel();
		JPanel jp2 = new JPanel();
		JPanel jp3 = new JPanel();
		JPanel jp4 = new JPanel();
		
		ButtonGroup bg1 = new ButtonGroup();
		ButtonGroup bg2 = new ButtonGroup();
		ButtonGroup bg3 = new ButtonGroup();
		ButtonGroup bg4 = new ButtonGroup();	
				
		jp1.setBorder(new TitledBorder("JButton"));
		jp2.setBorder(new TitledBorder("JToggleButton"));
		jp3.setBorder(new TitledBorder("JCheckBox"));
		jp4.setBorder(new TitledBorder("JRadioButton"));
		
		
		for(int i = 0;i <ids.length; i++){
			AbstractButton ab = new JButton(ids[i]);
			bg1.add(ab);
			jp1.add(ab);		
		}
		
		
		for(int i = 0;i <ids.length; i++){
			AbstractButton ab = new JToggleButton(ids[i]);
			bg2.add(ab);
			jp2.add(ab);		
		}
		
			
		for(int i = 0;i <ids.length; i++){
			AbstractButton ab = new JCheckBox(ids[i]);
			bg3.add(ab);
			jp3.add(ab);		
		}
		
		
		for(int i = 0;i <ids.length; i++){
			AbstractButton ab = new JRadioButton(ids[i]);
			bg4.add(ab);
			jp4.add(ab);		
		}
		  
			add(jp1);
    		add(jp2);
    		add(jp3);
    		add(jp4);
  
	}
}
/*!End Snippet:file*/