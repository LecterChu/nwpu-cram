import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 * @author author name
 * @version 1.0.0
 */
public class JPanelName extends JPanel {

	//要布局的组件
	private JLabel labelLeft;
	private JLabel labelCenter;
	private JLabel labelRight;
        ...
	/**
	 * Creates a window.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {
		
		//设置窗体的标题
		JFrame frame = new JFrame("title");
		
		//frame.setContentPane(new JPanelName());
		frame.add(new JPanelName());
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();    // Adjust the size of the window
		frame.setVisible(true);
	}

	/**
	 * Creates three {@link JLabel} components .
	 */
	public JPanelName() {
		//在当前面版上布局各种组件以显示在窗体上
		setLayout(...);
		setBackground(...);
		add(...);	
	}
}
/*!End Snippet:file*/