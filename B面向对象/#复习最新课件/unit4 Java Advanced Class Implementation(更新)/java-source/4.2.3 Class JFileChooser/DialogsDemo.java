// Creating and using Dialog Boxes.

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

/**/
class MyDialog extends JDialog {
	
	public MyDialog(JFrame parent) {
	  	
		super(parent, "My dialog", true);
		    
		setLayout(new FlowLayout());
		
		JLabel labelOne = new JLabel("Hello!Here is my dialog");
		labelOne.setFont(new Font("Serif", Font.BOLD, 18));		
		   
		JButton ok = new JButton("OK");	
		ok.setFont(new Font("Serif", Font.BOLD, 20));
		ok.addActionListener(new ListenerOne());	
		
		add(labelOne);   
		add(ok);
				
		setSize(200,200);
	}
	
	class ListenerOne implements ActionListener {
	
		public void actionPerformed(ActionEvent e){
			
			dispose(); // Closes the dialog
		}
	}
}


public class DialogsDemo extends JPanel {
	
	private JButton b1;
	private MyDialog dlg;
	
	public static void main(String[] args) {
		   
		  JFrame frame = new JFrame("Dialog demo");
		  frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		  //当前的工作面板设置为窗体的内容面板
		  frame.setContentPane(new DialogsDemo());
		  frame.setSize(200,200);
		  frame.setVisible(true);
	}
	//编辑当前的工作面板
	public DialogsDemo() {
	  
		b1 = new JButton("Dialog Box button");
		b1.setFont(new Font("Serif", Font.BOLD, 20));
		b1.addActionListener(new ListenerTwo());
		
		add(b1); 
		
		dlg = new MyDialog(null);		
	}
	
	class ListenerTwo implements ActionListener {
		
		public void actionPerformed(ActionEvent e){
			
			dlg.setVisible(true);
			//JOptionPane.showMessageDialog(null,"75 is not a valid age under 70",
			//				"Error Message",
			//				JOptionPane.ERROR_MESSAGE);
		}
	}  	    
	
} ///:~