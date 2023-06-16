package book.gui.dragdrop;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.util.Hashtable;

import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListCellRenderer;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * 一个展示支持拖放的List的例子。 该例子主要演示如下几点： 
 * （1）JList的使用，根据数据模型自定义显示模型，即显示和数据分离。
 * （2）JList的项被选择时的事件处理，即ListSelectionListener的实现。
 * （3）JList实现拖放，文件拖放到JList中，JList中的项拖放到文件系统中。
 */
public class DragDropListDemo extends JFrame implements ListSelectionListener {
	/**
	 * 该例子包含两个组件，上面是一个文本框。下面是一个List列表， 
	 * 当用户单击列表中的项时，将会在文本框中显示该项的值。
	 */
	// 文本框
	private JTextField fileName;

	// 可拖放的List
	private DroppableList list;

	public DragDropListDemo() {
		super("DragDropListDemo");

		fileName = new JTextField(40);
		// 创建一个可拖放的List，并放入滚动板中
		list = new DroppableList();
		// 设置List中单元格的显示模型，也就是说，List的数据模型中项的值是"value"，
		// 但是通过设置显示模型，在显示List时，可能看到的是"new_value"。
		// 因为在List在显示数据模型里的值时，会调用ListCellRender的getListCellRendererComponent方法。
		// 这里自定义一个ListCellRender，名字叫CustomCellRenderer，
		// 并实现了getListCellRendererComponent方法。
		list.setCellRenderer(new CustomCellRenderer());
		// 设置List为单选，一次只能选择一项
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JScrollPane listScrollPane = new JScrollPane(list);

		// List的数据模型
		DefaultListModel listModel = (DefaultListModel) list.getModel();
		String dirName = new String("/");
		String filelist[] = new File(dirName).list();
		for (int i = 0; i < filelist.length; i++) {
			String thisFileSt = dirName + filelist[i];
			File thisFile = new File(thisFileSt);
			if (thisFile.isDirectory())
				continue;
			try {
				// 将单个文件的信息组成一项放在List的数据模型中。
				listModel.addElement(makeNode(thisFile.getName(), thisFile
						.toURL().toString(), thisFile.getAbsolutePath()));
			} catch (java.net.MalformedURLException e) {
			}
		}

		// 为List添加选择事件侦听器，类型为ListSelectionListener。
		// 当用户选择List中的一项时，会调用ListSelectionListener的valueChanged方法
		list.addListSelectionListener(this);
		if (listModel.size() > 0) {
			// 默认为选择第0项
			list.setSelectedIndex(0);
			String name = listModel.getElementAt(list.getSelectedIndex())
					.toString();
			fileName.setText(name);
		} else {
			list.setSelectedIndex(-1);
			fileName.setText("null");
		}

		JPanel buttonPane = new JPanel();
		buttonPane.add(fileName);
		Container contentPane = getContentPane();
		contentPane.add(listScrollPane, BorderLayout.CENTER);
		contentPane.add(buttonPane, BorderLayout.NORTH);
	}

	/**
	 * 实现 ListSelectionListener接口定义的方法。 当用户选择List中的项时，调用该方法
	 */
	public void valueChanged(ListSelectionEvent e) {
		// 如果此事件是多个更改事件之一，则getValueIsAdjusting返回 true
		if (e.getValueIsAdjusting() == false) {
			// 表明此事件是一个单个事件，即单击List中的项。
			// 将List中被选择的项的值显示在文本框中。
			fileName.setText("");
			if (list.getSelectedIndex() != -1) {
				String name = list.getSelectedValue().toString();
				fileName.setText(name);
			}
		}
	}

	/**
	 * 利用文件的信息建立一个节点，存放在List的数据模型中。节点类型为一个Hashtable
	 */
	private static Hashtable makeNode(String name, String url, String strPath) {
		Hashtable hashtable = new Hashtable();
		hashtable.put("name", name);
		hashtable.put("url", url);
		hashtable.put("path", strPath);
		return hashtable;
	}

	/**
	 * 内部类，定义了List单元格内容显示的格式。
	 */
	class CustomCellRenderer implements ListCellRenderer {
		DefaultListCellRenderer listCellRenderer = new DefaultListCellRenderer();

		/**
		 * 实现ListCellRenderer接口定义的getListCellRendererComponent方法。
		 */
		public Component getListCellRendererComponent(JList list, Object value,
				int index, boolean selected, boolean hasFocus) {
			// 利用默认的单元格内容显示格式，对于选中的项，用特殊颜色标示。
			listCellRenderer.getListCellRendererComponent(list, value, index,
					selected, hasFocus);
			// 用新的格式显示项的值
			listCellRenderer.setText(getValueString(value));
			return listCellRenderer;
		}

		/**
		 * 根据值获得显示字符串
		 */
		private String getValueString(Object value) {
			String returnString = "null";
			if (value != null) {
				if (value instanceof Hashtable) {
					Hashtable h = (Hashtable) value;
					String name = (String) h.get("name");
					String url = (String) h.get("url");
					// 显示Hashtable中键值对
					returnString = name + " ==> " + url;
				} else {
					returnString = "X: " + value.toString();
				}
			}
			return returnString;
		}
	}

	public static void main(String s[]) {
		JFrame frame = new DragDropListDemo();
		// 关闭窗口的另一种方式。与setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);等价
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		frame.pack();
		frame.setVisible(true);
	}
}
