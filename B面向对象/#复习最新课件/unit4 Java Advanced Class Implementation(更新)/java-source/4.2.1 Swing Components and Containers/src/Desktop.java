//file: Desktop.java
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class Desktop {
	public static void main(String[] args) {
		// create a JFrame to hold everything
		JFrame f = new JFrame("Desktop");
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				System.exit(0);
			}
		});
		f.setSize(300, 300);
		f.setLocation(200, 200);
		JDesktopPane desktop = new JDesktopPane();
		for (int i = 0; i < 5; i++) {
			JInternalFrame internal = new JInternalFrame("Frame " + i, true,
					true, true, true);
			internal.setSize(180, 180);
			internal.setLocation(i * 20, i * 20);
			internal.setVisible(true);
			desktop.add(internal);
		}
		f.setContentPane(desktop);
		f.setVisible(true);
	}
}