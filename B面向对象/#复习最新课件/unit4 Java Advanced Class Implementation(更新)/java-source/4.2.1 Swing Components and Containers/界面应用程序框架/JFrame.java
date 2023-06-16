
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 * @author author name
 * @version 1.0.0
 */

public class JFrameName extends JFrame {
	
	//声明一个容器变量指向窗体的内容嵌版
	private Container contentPane;
	
	//要布局的组件
	private JPanel buttonPanel;
	private JTextField input1TextField;	
	...
	
	public static void main(String[] args) {
		
		//创建一个窗体并显示
		JFrame frame = new JFrameName();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(300, 400); // Adjust the size of the window
		frame.setVisible(true);		
	}
	//Constructor.
	public JFrameName(){
		//设置窗体的标题
		super("title");
			
		this.setSize(250,100);
		
		//在当前窗体上布局各种组件并显示	
		this.setLayout(...);
		this.add(...);
	}		
}
