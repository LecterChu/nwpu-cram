import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SwingApplication {
	private static String labelPrefix = "Number of button clicks: ";

	private int numClicks = 0; // 计数器，计算点击次数

	public Component createComponents() {
		final JLabel label = new JLabel(labelPrefix + "0 ");
		JButton button = new JButton("I'm a Swing button!");
		button.setMnemonic(KeyEvent.VK_I); // 设置按钮的热键为'I'
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				numClicks++;
				label.setText(labelPrefix + numClicks);
			}
		});
		label.setLabelFor(button);
		JPanel pane = new JPanel();
		pane.setBorder(BorderFactory.createEmptyBorder(30, 30, 10, 30));
		pane.setLayout(new GridLayout(0, 1)); // 单列多行
		pane.add(button);
		pane.add(label);
		return pane;
	}

	public static void main(String[] args) {
		try {
			UIManager.setLookAndFeel(UIManager
					.getCrossPlatformLookAndFeelClassName());
		} catch (Exception e) {
		}

		JFrame frame = new JFrame("SwingApplication");
		SwingApplication app = new SwingApplication();
		Component contents = app.createComponents();
		frame.getContentPane().add(contents, BorderLayout.CENTER);

		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		frame.pack();
		frame.setVisible(true);
	}
}
