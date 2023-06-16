//Calculator.java
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class Calculator extends JPanel {
	//Components are treated as attributes,so that
	//they will be visible to all of the methods of the class.
	//use description names for components where possible;
	//it makes your job easier later on !
	private JPanel leftPanel;
	private JPanel centerPanel;
	private JPanel buttonPanel;
	private JTextField input1TextField;
	private JTextField input2TextField;
	private JLabel answerLabel;
	private JButton plusButton;
	private JButton minusButton;
	 
	
	public static void main(String[] args) {
		
		JFrame frame = new JFrame("Simple Calculator");			
		// we want to use a WindowListener to terminate the 
		// application when the user closes the window.
		//frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		/* 
		  frame.addWindowListener(new WindowAdapter(){
		  	
		  	public void windowClosing(WindowEvent e) {
				
				System.exit(0);
			}
		  });	
		  */
		/*
		class WindowListenerOne extends WindowAdapter {
			
			public void windowClosing(WindowEvent e) {
				
				System.exit(0);
			}
		}
		WindowListenerOne w = new WindowListenerOne();
			
		frame.addWindowListener(w);	
		*/
		frame.setContentPane(new Calculator());		
		frame.setSize(600,200);		
		frame.setVisible(true);	
	}
	//Constructor.
	public Calculator(){
		
		setLayout(new BorderLayout());	
		
		Font font = new Font("Serif", Font.BOLD, 30);	
		
		leftPanel = new JPanel();
		leftPanel.setLayout(new GridLayout(3,1));
		
		JLabel inputOne = new JLabel("Input 1:  ");
		JLabel inputTwo = new JLabel("Input 2:  ");
		JLabel Answer = new JLabel("Answer:  ");
		
		inputOne.setFont(font);
		inputTwo.setFont(font);
		Answer.setFont(font);
		
		leftPanel.add(inputOne);
		leftPanel.add(inputTwo);
		leftPanel.add(Answer);		
		add(leftPanel,BorderLayout.WEST);
		
	
		centerPanel = new JPanel();
		centerPanel.setLayout(new GridLayout(3,1));		
		input1TextField = new JTextField(10);
		input2TextField = new JTextField(10);
		answerLabel = new JLabel();
		
		input1TextField.setFont(font);
		input2TextField.setFont(font);
		answerLabel.setFont(font);
		
		centerPanel.add(input1TextField);
		centerPanel.add(input2TextField);
		centerPanel.add(answerLabel);
		
		add(centerPanel,BorderLayout.CENTER);
		
		buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridLayout(2,1));
		
		plusButton = new JButton("+");
		minusButton = new JButton("-");
		
		plusButton.setFont(font);
		minusButton.setFont(font);
		
		buttonPanel.add(plusButton);
		buttonPanel.add(minusButton);
		
		add(buttonPanel,BorderLayout.EAST);
		
		//add behaviors!  
		ListenerOne listner = new ListenerOne();
		plusButton.addActionListener(listner);
		minusButton.addActionListener(listner);		
	}
	
	class ListenerOne implements ActionListener {
		
			public void actionPerformed(ActionEvent e){
			
				try{
					double d1 = 
					  new Double(input1TextField.getText()).doubleValue();
					double d2 = 
					  new Double(input2TextField.getText()).doubleValue();
					  
					if (e.getSource() == plusButton) {
						answerLabel.setText(""+(d1+d2));	
					} else {
						answerLabel.setText(""+(d1-d2));
					}
				} catch (NumberFormatException nfe){
					
					answerLabel.setText(nfe.getMessage());
				}
			}
	}
}
