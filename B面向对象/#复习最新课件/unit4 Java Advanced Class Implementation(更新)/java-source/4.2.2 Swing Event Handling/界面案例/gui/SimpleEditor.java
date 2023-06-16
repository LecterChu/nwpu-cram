package book.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JToolBar;
import javax.swing.JTree;
import javax.swing.Timer;
import javax.swing.border.BevelBorder;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.filechooser.FileFilter;
import javax.swing.text.BadLocationException;
import javax.swing.tree.DefaultMutableTreeNode;
/**
 * 一个简单的文本编辑器，能够编辑html、java、cpp、txt文件，
 * 并支持java的编译与运行
 */
public class SimpleEditor extends JFrame {

	/********菜单栏、菜单和菜单项*********/
	JMenuBar menuBar = new JMenuBar();
	JMenu fileMenu = new JMenu("File");
	JMenu optionMenu = new JMenu("Option");
	JMenu advanceMenu = new JMenu("Advance");
	JMenu helpMenu = new JMenu("Help");
	JMenu editMenu = new JMenu("Edit");
	JMenuItem newMenuItem = new JMenuItem("new");
	JMenuItem openMenuItem = new JMenuItem("Open");
	JMenuItem saveMenuItem = new JMenuItem("Save");
	JMenuItem exitMenuItem = new JMenuItem("exit");
	JMenuItem findMenuItem = new JMenuItem("Find");
	JMenuItem findNextMenuItem = new JMenuItem("Find Next");
	JMenuItem replaceMenuItem = new JMenuItem("Replace");
	JMenuItem compileMenuItem = new JMenuItem("Compile");
	JMenuItem buildMenuItem = new JMenuItem("Build");
	JMenuItem stopFlashMenuItem = new JMenuItem("Stop Flash");
	JMenuItem startFlashMenuItem = new JMenuItem("Start Flash");
	JMenuItem helpMenuItem = new JMenuItem("Help");
	JMenuItem copyMenuItem = new JMenuItem("Copy");
	JMenuItem cutMenuItem = new JMenuItem("Cut");
	JMenuItem pasteMenuItem = new JMenuItem("Paste");

	
	/********文件内容的显示****/
	//用多个文本域存放多个文件内容，文本域放在JScrollPane里
	//而JScrollPane放在JTabbedPane中，这就是一个多页面的布局
	
	//多个文本域，每个文本域显示一个文件的内容
	JTextArea[] fileTextAreas = new JTextArea[10];
	//编译或者运行时的控制台信息
	JTextArea consoleTextArea = new JTextArea();
	JScrollPane[] fileScrollPanes = new JScrollPane[10];
	JScrollPane consoleScrollPane;
	//多个文本域放在不同tab里
	JTabbedPane fileTabbedPane = new JTabbedPane();
	
	/**********工具栏以及工具栏上的按钮**********/
	JToolBar toolBar = new JToolBar();
	JButton openButton = new JButton(new ImageIcon(loadImage("image/open.gif")));
	JButton newButton = new JButton(new ImageIcon(loadImage("image/new.gif")));
	JButton saveButton = new JButton(new ImageIcon(loadImage("image/save.gif")));
	JButton helpButton = new JButton(new ImageIcon(loadImage("image/help.gif")));
	JButton exitButton = new JButton(new ImageIcon(loadImage("image/close.gif")));
	JButton compileButton = new JButton(new ImageIcon(loadImage("image/compile.gif")));
	JButton buildButton = new JButton(new ImageIcon(loadImage("image/build.gif")));
	JButton copyButton = new JButton(new ImageIcon(loadImage("image/copy.gif")));
	JButton cutButton = new JButton(new ImageIcon(loadImage("image/cut.gif")));
	JButton pasteButton = new JButton(new ImageIcon(loadImage("image/paste.gif")));
	
	//该文本域显示当前光标在当前文本域中的行号
	JTextArea showLineNoTextArea = new JTextArea();
	//对话框窗体，程序中所有对话框都显示在该窗体中
	JFrame dialogFrame = new JFrame();

	/*****文件名以树型结构在左边显示*******/
	JTree tree;
	DefaultMutableTreeNode root;
	DefaultMutableTreeNode[] nodes = new DefaultMutableTreeNode[10];
	
	/*******组件之间的分隔栏******/
	JSplitPane leftRightSplitPane;
	JSplitPane lineNoConsoleSplitPane;
	JSplitPane treeFlashSplitPane;
	JSplitPane tabbedLineNoSplitPane;
	
	/**********文件选择、存储相关********/
	//文件过滤器
	Filter fileFilter = new Filter();
	//文件选择器
	FileChooser fileChooser = new FileChooser();
	// 文件读写控制，0表示文件选择器读文件，1文件选择器标示写文件
	int fileChooser_control = 0;
	FileWriter fileWriter;

	// tabbedPane中tab页的当前数量
	int tb = 1;
	int find_control = 0;
	//文本域的控制器，指向当前操作的文本域
	int textAreas_control = 0;
	//当前文本域中的文本
	String currentTextInTextArea;

	//标志文件是否为新建的，如果是新建的文件，为true
	boolean[] newFileFlags = new boolean[10];
	//存放打开文件所在的目录
	String[] directory = new String[10];
	
	/********查找替换相关****/
	//正在查找的字符串及其长度
	String findWord;
	int fingWordLength;
	//保存正在查找的字符串在文本域中的文本的位置
	int findIndex;
	//被替换的文本的长度
	int replaceLength = 0;
	
	/********用于显示Flash的控制器****/
	JLabel flashLabel = new JLabel(new ImageIcon(loadImage("image/Juggler0.gif")));
	Timer timer = new Timer(100, new Act_timer());
	int timerControl = 0;

	/********帮助相关****/
	Font font = new Font("Courier", Font.TRUETYPE_FONT, 14);
	JTextArea helpTextArea = new JTextArea();
	JFrame helpFrame = new JFrame("Help");
	
	//构造函数
	public SimpleEditor() {
		super("文本编辑器");
		
		//为窗体添加键盘事件处理器
		//下面这一行非常重要，表示窗体能够接受焦点。
		//如果没有这一句，按键盘会无效。
		this.setFocusable(true);
		this.addKeyListener(new MyKeyListener());
		
		//为窗体添加窗口事件处理器
		this.addWindowListener(new WindowListener());

		//初始化
		init();
		setLocation(200, 200);
		setVisible(true);
		pack();
		//初始时启动动画
		timer.start();
	}
	
	private void init(){
		
		/*******初始化文本域、目录、树节点*********/
		for (int i = 0; i < 10; i++) {
			nodes[i] = new DefaultMutableTreeNode("File" + (i + 1));
			newFileFlags[i] = true;
			fileTextAreas[i] = new JTextArea();
			// 设置文本域中文本的字体
			fileTextAreas[i].setFont(font);
			// 为文本域的插入光标设置颜色
			fileTextAreas[i].setCaretColor(Color.yellow);
			// 设置文本域的背景和前景颜色
			fileTextAreas[i].setBackground(new Color(70, 80, 91));
			fileTextAreas[i].setForeground(Color.pink);
			// 为文本域插入光标设置事件处理器
			fileTextAreas[i].addCaretListener(new CaretLis_lineNo());
			// 为文本域键盘设置事件处理器
			fileTextAreas[i].addKeyListener(new MyKeyListener());
			directory[i] = new String("/");
			fileScrollPanes[i] = new JScrollPane(fileTextAreas[i],
					JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
					JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		}
		root = new DefaultMutableTreeNode("正在编辑的文件");
		root.add(nodes[0]);
		tree = new JTree(root);
		tree.setEditable(false);
		tree.setForeground(new Color(200, 150, 10));
		tree.setBackground(new Color(70, 80, 91));
		
		//初始化控制台文本域
		consoleTextArea.setFont(font);
		consoleScrollPane = new JScrollPane(consoleTextArea, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
				JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		consoleTextArea.setForeground(new Color(200, 150, 10));
		consoleTextArea.setBackground(new Color(70, 80, 91));
		consoleTextArea.addMouseListener(new MouseListener_console());
		
		//初始化显示当前光标行数的文本域
		showLineNoTextArea.setEnabled(false);
		showLineNoTextArea.setFont(font);
		showLineNoTextArea.setBackground(new Color(70, 80, 91));
		showLineNoTextArea.setDisabledTextColor(Color.yellow);

		/**************初始化菜单*************/
		//初始化菜单项
		newMenuItem.addActionListener(new Act_NewFile());
		openMenuItem.addActionListener(new Act_OpenFile());
		saveMenuItem.addActionListener(new Act_SaveFile());
		exitMenuItem.addActionListener(new Act_ExitEditor());
		findMenuItem.addActionListener(new Act_Find());
		findNextMenuItem.addActionListener(new Act_FindNext());
		replaceMenuItem.addActionListener(new Act_Replace());
		compileMenuItem.addActionListener(new Act_Compile());
		buildMenuItem.addActionListener(new Act_Build());
		helpMenuItem.addActionListener(new Act_Help());
		copyMenuItem.addActionListener(new Act_Copy());
		cutMenuItem.addActionListener(new Act_Cut());
		pasteMenuItem.addActionListener(new Act_Paste());
		stopFlashMenuItem.addActionListener(new Act_StopFlash());
		startFlashMenuItem.addActionListener(new Act_StartFlash());
		startFlashMenuItem.setEnabled(false);
		//初始化菜单
		fileMenu.add(newMenuItem);
		fileMenu.add(openMenuItem);
		fileMenu.add(saveMenuItem);
		fileMenu.add(exitMenuItem);
		optionMenu.add(findMenuItem);
		optionMenu.add(findNextMenuItem);
		optionMenu.add(replaceMenuItem);
		advanceMenu.add(compileMenuItem);
		advanceMenu.add(buildMenuItem);
		advanceMenu.addSeparator();
		advanceMenu.add(stopFlashMenuItem);
		advanceMenu.add(startFlashMenuItem);
		helpMenu.add(helpMenuItem);
		editMenu.add(copyMenuItem);
		editMenu.add(cutMenuItem);
		editMenu.add(pasteMenuItem);
		//初始化菜单栏
		menuBar.add(fileMenu);
		menuBar.add(optionMenu);
		menuBar.add(advanceMenu);
		menuBar.add(editMenu);
		menuBar.add(helpMenu);
		//将菜单栏添加到窗体中
		setJMenuBar(menuBar);
		
		/***********初始化工具栏以及按钮**********/
		//初始化按钮
		newButton.addActionListener(new Act_NewFile());
		openButton.addActionListener(new Act_OpenFile());
		saveButton.addActionListener(new Act_SaveFile());
		exitButton.addActionListener(new Act_ExitEditor());
		compileButton.addActionListener(new Act_Compile());
		buildButton.addActionListener(new Act_Build());
		helpButton.addActionListener(new Act_Help());
		copyButton.addActionListener(new Act_Copy());
		cutButton.addActionListener(new Act_Cut());
		pasteButton.addActionListener(new Act_Paste());
		// 为工具栏设置提示信息，当鼠标在工具栏按钮上停留一段时间时，会显示提示信息
		newButton.setToolTipText("New");
		openButton.setToolTipText("Open");
		saveButton.setToolTipText("Save");
		exitButton.setToolTipText("Exit");
		helpButton.setToolTipText("Help");
		compileButton.setToolTipText("Compile");
		buildButton.setToolTipText("Build");
		copyButton.setToolTipText("Copy");
		cutButton.setToolTipText("Cut");
		pasteButton.setToolTipText("Paste");
		newButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		openButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		saveButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		exitButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		helpButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		compileButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		buildButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		cutButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		copyButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		pasteButton.setBorder(new BevelBorder(BevelBorder.RAISED));
		//初始化工具栏
		toolBar.add(newButton);
		toolBar.add(openButton);
		toolBar.add(saveButton);
		toolBar.add(copyButton);
		toolBar.add(cutButton);
		toolBar.add(pasteButton);
		toolBar.add(compileButton);
		toolBar.add(buildButton);
		toolBar.add(exitButton);
		toolBar.add(helpButton);

		/********初始化tab页面板和组件间的分隔栏*********/
		fileTabbedPane.addTab("File1", fileScrollPanes[0]);
		fileTabbedPane.addChangeListener(new Act_ChangeTab());
		//文件目录树和Flash之间的分隔栏
		treeFlashSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, true, flashLabel, tree);
		//文件文本域面板与指示光标所在行文本域面板之间的分隔栏
		tabbedLineNoSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, true, fileTabbedPane, showLineNoTextArea);
		//右边上2个面板与控制台面板的分隔栏
		lineNoConsoleSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, true, tabbedLineNoSplitPane,
				consoleScrollPane);
		//左边大面板与右边大面板之间的分隔栏
		leftRightSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, true, treeFlashSplitPane,
				lineNoConsoleSplitPane);
		// 设置分隔栏两边面板显示的宽度，如果分割条是左右分割，则参数表示分割条的横坐标
		// 如果分割条是上下分割，则参数表示分割条的纵坐标
		leftRightSplitPane.setDividerLocation(150);
		tabbedLineNoSplitPane.setDividerLocation(460);
		lineNoConsoleSplitPane.setDividerLocation(500);
		treeFlashSplitPane.setDividerLocation(120);
		
		//初始化帮助
		initHelp();
		
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add(toolBar, BorderLayout.NORTH);
		getContentPane().add(leftRightSplitPane);
	}
	
	/**
	 * 初始化帮助信息
	 */
	private void initHelp(){
		//帮助信息主要显示菜单的快捷方式
		
		// field存放JTable的表头信息，即表的标题
		String[] field = { "MenuItem", "ShortCut Key" };
		// data存放JTable的数据。
		Object[][] data = { { "     New           ", "    Ctrl+N    " },
				{ "    Open          ", "    F12       " },
				{ "    Save          ", "    Ctrl+S    " },
				{ "    Exit          ", "    Ctrl+X    " },
				{ "    Find          ", "    Alt       " },
				{ "    Find Next     ", "    F3        " },
				{ "    Compile       ", "    F9        " },
				{ "    Build         ", "    F5        " },
				{ "    Copy          ", "    Ctrl+C    " },
				{ "    Cut           ", "    Ctrl+X    " },
				{ "    Paste         ", "    Ctrl+Y    " },
				{ "    Help          ", "    Ctrl+H    " }, };
		// 用表头和数据构造一个表
		JTable help_Table = new JTable(data, field);
		help_Table.setFont(font);
		//不可编辑帮助信息表
		help_Table.setEnabled(false);
		// 为表和文本域设置背景和前景颜色
		helpTextArea.setFont(new Font("Courier", Font.TRUETYPE_FONT, 16));
		helpFrame.getContentPane().setLayout(new BorderLayout());
		help_Table.setForeground(Color.pink);
		helpTextArea.setForeground(Color.pink);
		help_Table.setBackground(new Color(70, 80, 91));
		help_Table.setSelectionBackground(new Color(70, 80, 91));
		helpTextArea.setBackground(new Color(70, 80, 91));
		helpTextArea.setText(" If you want to use this software with all functions,\n" 
						+ "     You must do the things following:\n" 
						+ "     1: install jdk_1.3 or Higher than it ;\n" 
						+ "     2: set your classpath and path correctly;\n" 
						+ "     3: if you want to use the compile and build functions,\n" 
						+ "       you should save your edited File in the save directory\n" 
						+ "       with  this software.\n ");
		// 将文本域和表加到窗体中
		helpFrame.getContentPane().add(
				new JScrollPane(help_Table,
						JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
						JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED), BorderLayout.CENTER);
		helpFrame.getContentPane().add(
				new JScrollPane(helpTextArea,
						JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
						JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED), BorderLayout.NORTH);
	}
	
	// 退出编辑器
	private void exitEditor(){
		// 弹出一个选择确认对话框，请求确认退出
		if ((JOptionPane.showConfirmDialog(this, "你确定文本编辑器？", "退出",
				JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)){
			// 如果选择YES，则退出。
			//dispose方法用于释放资源
			//释放由此 Window、其子组件及其拥有的所有子组件所使用的所有本机屏幕资源。
			//即这些 Component 的资源将被破坏，它们使用的所有内存都将返回到操作系统，并将它们标记为不可显示。
			//通过随后对 pack 或 show 的调用重新构造本机资源，可以再次显示 Window 及其子组件。
			//重新创建的 Window 及其子组件的状态在移除 Window 的点上与这些对象的状态将是一样的（不考虑这些操作之间的其他更改）。 
			dispose();
			System.exit(0);
		}
	}
	/**
	 * 键盘事件处理器
	 */
	public class MyKeyListener extends KeyAdapter {
		// 覆盖父类的keyPressed方法，处理键被按下时的事件。
		public void keyPressed(KeyEvent e) {
			// 按F12打开文件
			if (e.getKeyCode() == KeyEvent.VK_F12){
				(new Act_OpenFile()).actionPerformed(null);
			}
			// 按Ctrl加S键保存文件
			else if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_S){
				(new Act_SaveFile()).actionPerformed(null);
			}
			// 按Alt键查找
			else if (e.isAltDown()){
				(new Act_Find()).actionPerformed(null);
			}
			// 按F3查找下一个
			else if (e.getKeyCode() == KeyEvent.VK_F3){
				(new Act_FindNext()).actionPerformed(null);
			}
			// 按F4替换
			else if (e.getKeyCode() == KeyEvent.VK_F4){
				(new Act_Replace()).actionPerformed(null);
			}
			// 按Ctrl加N新建文件
			else if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_N){
				(new Act_NewFile()).actionPerformed(null);
			}
			// 按Ctrl加E退出编辑器
			else if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_E){
				(new Act_ExitEditor()).actionPerformed(null);
			}
			// 按F5运行Java程序
			else if (e.getKeyCode() == KeyEvent.VK_F5){
				(new Act_Build()).actionPerformed(null);
			}
			// 按F9编译Java源代码
			else if (e.getKeyCode() == KeyEvent.VK_F9){
				(new Act_Compile()).actionPerformed(null);
			}
			// 按Ctrl加H显示帮助
			else if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_H){
				(new Act_Help()).actionPerformed(null);
			}
		}
	}
	/**
	 * 窗口事件侦听器
	 */
	public class WindowListener extends WindowAdapter {
		// 处理关闭窗口事件
		public void windowClosing(WindowEvent e) {
			exitEditor();
		}
	}
	/**
	 * 文件选择器
	 */
	class FileChooser extends JFileChooser {
		public FileChooser() {
			//文件选择器默认位置为当前文件夹
			super("./");
		}
		/**
		 * 提交选择
		 */
		public void approveSelection() {
			String filename = null;
			//fileChooser_control == 0表示现在是打开文件，需要读
			if (fileChooser_control == 0) {
				//打开文件时，在左边的树中添加一个节点
				root.add(nodes[tb]);
				remove(tree);
				tree = new JTree(root);
				tree.setBackground(new Color(70, 80, 91));
				treeFlashSplitPane.setRightComponent(tree);
				treeFlashSplitPane.setDividerLocation(120);
				// 新建一个tab页，用于装新打开的文件
				fileTabbedPane.addTab("File" + (tb + 1), fileScrollPanes[tb]);
				fileTabbedPane.setSelectedIndex(tb);
				//将当前文本域设置到新打开的文件上
				textAreas_control = tb;
				tb++;
				
				//获取待打开的文件名
				filename = fileChooser.getSelectedFile().getName();
				//获取待打开的文件所在的目录，将目录保存至数组，这样在保存文件的时候，能够将文件名保存到目录中
				directory[textAreas_control] = fileChooser.getCurrentDirectory().toString();
				fileTextAreas[textAreas_control].setText(null);
				try {
					//将文件内容显示到文本域中
					String str;
					BufferedReader breader = new BufferedReader(new FileReader(
							directory[textAreas_control] + "/" + filename));
					while (true) {
						str = breader.readLine();
						if (str == null) {
							break;
						}
						fileTextAreas[textAreas_control].append(str + '\n');
					}
				} catch (Exception e_open) {
					JOptionPane
							.showMessageDialog(dialogFrame.getContentPane(), "读取发生错误");
				}
				
			} else if (fileChooser_control == 1) {
				//	fileChooser_control == 1表示现在是保存新文件，需要写
				filename = fileChooser.getSelectedFile().getName();
				directory[textAreas_control] = fileChooser.getCurrentDirectory().toString();
				try {
					//将文本域中的内容写到文件中
					fileWriter = new FileWriter(directory[textAreas_control] + "/"
							+ filename);
					fileWriter.write(fileTextAreas[textAreas_control].getText());
					fileWriter.close();
				} catch (Exception e_save) {
					JOptionPane
							.showMessageDialog(dialogFrame.getContentPane(), "读取发生错误");
				}

			}
			
			//关闭对话框
			dialogFrame.dispose();
			
			//更新文件目录树中的名字
			root.remove(nodes[textAreas_control]);
			nodes[textAreas_control] = new DefaultMutableTreeNode(filename);
			root.add(nodes[textAreas_control]);
			//将当前显示的树删除、显示新的树
			remove(tree);
			tree = new JTree(root);
			tree.setBackground(new Color(70, 80, 91));
			treeFlashSplitPane.setRightComponent(tree);
			treeFlashSplitPane.setDividerLocation(120);
			//将tab页的标题改为文件名
			fileTabbedPane.setTitleAt(textAreas_control, filename);
			//无论是打开、还是保存，这个文件不是已经新建的，所以置为false
			newFileFlags[textAreas_control] = false;
		}
		/**
		 * 取消选择
		 */
		public void cancelSelection() {
			dialogFrame.dispose();
		}
	}

	/**
	 * 文件过滤器，只支持编辑".java,*.html,*.txt,*.cpp"文件
	 */
	class Filter extends FileFilter {
		// 覆盖FileFilter的accept方法
		public boolean accept(File file1) {
			return (file1.getName().endsWith(".java") || file1.isDirectory()
					|| file1.getName().endsWith(".html")
					|| file1.getName().endsWith(".txt") || file1.getName()
					.endsWith(".cpp"));
		}

		public String getDescription() {
			return (".java,*.html,*.txt,*.cpp");
		}
	}

	/**
	 * 用于侦听文本组件插入符的位置更改的侦听器
	 * 获取当前光标在文件中的行号
	 */
	class CaretLis_lineNo implements CaretListener {
		public void caretUpdate(CaretEvent e) {
			try {
				showLineNoTextArea.setText("          Cursor at the "
						+ (fileTextAreas[textAreas_control]
								.getLineOfOffset(fileTextAreas[textAreas_control]
										.getCaretPosition()) + 1)
						+ " line in the file of "
						+ fileTabbedPane.getTitleAt(textAreas_control));
			} catch (BadLocationException eB) {
				System.out.println("IO Wrong");
			}
		}
	}

	/**
	 * 控制台文本域中鼠标事件的侦听器
	 * 当控制台中有错误信息时，表明Java源文件编译有问题，定位到出错的行号。
	 */
	class MouseListener_console extends MouseAdapter {
		public void mouseClicked(MouseEvent e) {
			// 获取光标在控制台文本域中的位置
			int off_err = consoleTextArea.getCaretPosition();
			int line_no = 0;
			try {
				// 根据光标位置，定位它在控制台文本域中的行
				int index = -1;
				int line_err = consoleTextArea.getLineOfOffset(off_err - 1);
				// 获取光标所在行的起始字符在文本域中的位置
				int start_err = consoleTextArea.getLineStartOffset(line_err);
				// 获取光标所在行的起始位置到光标位置之间文本，即错误信息
				String err_str = consoleTextArea.getText(start_err, off_err - start_err);
				// 高亮显示错误信息
				consoleTextArea.select(start_err, off_err);
				// 分析错误信息中是否有编译器指出的Java源文件行号，这里假定最多10000行源程序
				for (line_no = 0; line_no < 10000; line_no++) {
					index = err_str.indexOf(":" + line_no + ":");
					if (index > 0) {
						break;
					}
				}
				// 如果能够分析出Java源文件的行号，则在文件文本域中高亮显示。
				if (index != -1) {
					fileTextAreas[textAreas_control].requestFocus();
					fileTextAreas[textAreas_control].select(fileTextAreas[textAreas_control]
							.getLineStartOffset(line_no - 1), fileTextAreas[textAreas_control]
							.getLineEndOffset(line_no - 1));
				}
			} catch (BadLocationException eB) {
				System.out.println("IO Wrong");
			}
		}
	}
	/**
	 * 切换tab页事件
	 */
	class Act_ChangeTab implements ChangeListener {
		public void stateChanged(ChangeEvent e) {
			// 切换tab页时，更新textAreas_control的值。
			textAreas_control = fileTabbedPane.getSelectedIndex();
		}
	}
	/**
	 * 新建文件事件
	 */
	class Act_NewFile implements ActionListener {
		public void actionPerformed(ActionEvent e_ji0) {
			//建立新文件时，更新树和tab页。
			root.add(nodes[tb]);
			remove(tree);
			tree = new JTree(root);
			tree.setBackground(new Color(70, 80, 91));
			treeFlashSplitPane.setRightComponent(tree);
			treeFlashSplitPane.setDividerLocation(120);
			fileTabbedPane.addTab("File" + (tb + 1), fileScrollPanes[tb]);
			fileTabbedPane.setSelectedIndex(tb);
			textAreas_control = tb;
			tb++;
		}
	}
	/**
	 * 打开文件事件
	 */
	class Act_OpenFile implements ActionListener {
		public void actionPerformed(ActionEvent e_ji1) {
			//打开已有文件
			//将文件选择器置为打开文件状态
			fileChooser_control = 0;
			fileChooser.setApproveButtonText("打开");
			fileChooser.addChoosableFileFilter(fileFilter);
			dialogFrame.getContentPane().add(fileChooser);
			dialogFrame.setSize(550, 350);
			dialogFrame.setTitle("请选择要打开的文件!");
			dialogFrame.setVisible(true);
			fileTextAreas[textAreas_control].setCaretPosition(0);
		}
	}
	/**
	 * 保存文件事件
	 */
	class Act_SaveFile implements ActionListener {
		public void actionPerformed(ActionEvent e_ji2) {
			System.out.println("Act_SaveFile" + textAreas_control);
			if (newFileFlags[textAreas_control]) {
				//对于新建的文件，需要指定文件存储路径，因此调用了文件选择起存储文件
				//将文件选择器置为保存文件状态
				fileChooser_control = 1;
				fileChooser.setApproveButtonText("保存");
				fileChooser.addChoosableFileFilter(fileFilter);
				dialogFrame.getContentPane().add(fileChooser);
				dialogFrame.setTitle("请输入文件名!");
				dialogFrame.setSize(550, 350);
				dialogFrame.setVisible(true);

			} else {
				try {
					//对于已经存在的文件，直接保存
					//写文件，将当前文本域中文本写入到文件。
					fileWriter = new FileWriter(directory[textAreas_control] + "/"
							+ fileTabbedPane.getTitleAt(textAreas_control));
					fileWriter.write(fileTextAreas[textAreas_control].getText());
					fileWriter.close();
				} catch (Exception e_save) {
					JOptionPane.showMessageDialog(null, "读取发生错误");
				}
			}
		}
	}

	/**
	 * 退出编辑器事件
	 */
	class Act_ExitEditor implements ActionListener {
		public void actionPerformed(ActionEvent e_ji3) {
			//退出编辑器
			exitEditor();
		}
	}
	/**
	 * 查找事件
	 */
	class Act_Find implements ActionListener {
		public void actionPerformed(ActionEvent e_ji4) {
			//查找对话框
			findWord = JOptionPane
					.showInputDialog("请输入查找内容");
			if (findWord == null) {
				JOptionPane.showMessageDialog(null, "查找失败！");
			} else {
				//根据查找内容在当前文本域中进行匹配
				fingWordLength = findWord.length();
				currentTextInTextArea = fileTextAreas[textAreas_control].getText();
				findIndex = currentTextInTextArea.indexOf(findWord);
				if (findIndex < 0){
					JOptionPane.showMessageDialog(null,
							"   查找内容不存在  ");
				}  else {
					//如果找到了，则将鼠标键盘焦点放在当前文本域中，并将匹配字符串标示出来
					fileTextAreas[textAreas_control].requestFocus();
					fileTextAreas[textAreas_control].select(findIndex, findIndex + fingWordLength);
				}
			}
		}
	}
	/**
	 * 查找下一个事件
	 */
	class Act_FindNext implements ActionListener {
		public void actionPerformed(ActionEvent e_ji4_next) {
			//查找下一个匹配的字符串
			currentTextInTextArea = fileTextAreas[textAreas_control].getText();
			findIndex = currentTextInTextArea.indexOf(findWord, findIndex + 1);
			if (findIndex < 0) {
				JOptionPane.showMessageDialog(null,
						" 查找已经到达文件尾！ ");
			} else {
				fileTextAreas[textAreas_control].select(findIndex, findIndex + fingWordLength);
			}
		}
	}
	/**
	 * 替换事件
	 */
	class Act_Replace implements ActionListener {
		public void actionPerformed(ActionEvent e_ji5) {
			//替换对话框
			Object[] endButton1 = { "Replace", "Cancel" };
			String message1 = "确认替换？";
			currentTextInTextArea = fileTextAreas[textAreas_control].getText();
			
			//获取被替换的内容
			String seek_word = JOptionPane
					.showInputDialog("请输入查找内容");
			//获取替换后的内容
			String replace_word = JOptionPane
					.showInputDialog("请输入替换内容");
			//如果用户输入的查找内容不为null，则开始进行替换操作
			if (seek_word != null) {
				//获取查找内容的长度，也就是将来替换的长度
				replaceLength = seek_word.length();
				while (true) {
					//先获取当前文本域的文本，再进行查找
					currentTextInTextArea = fileTextAreas[textAreas_control].getText();
					findIndex = currentTextInTextArea.indexOf(seek_word, findIndex + replaceLength);
					if (findIndex < 0) {
						//文本中不存在查找内容
						JOptionPane.showMessageDialog(null,
								"查找已经到达文件尾！");
						break;
					} else {
						//查找成功，则标示出查找内容
						fileTextAreas[textAreas_control].requestFocus();
						fileTextAreas[textAreas_control].select(findIndex, findIndex + replaceLength);
						//替换确认
						JOptionPane end1 = new JOptionPane(message1,
								JOptionPane.WARNING_MESSAGE,
								JOptionPane.DEFAULT_OPTION, null, endButton1);
						JDialog endD1 = end1.createDialog(end1, "请选择");
						endD1.setVisible(true);
						Object push1 = end1.getValue();
						if (push1 == endButton1[0]){
							//如果用户选择替换，则将文本域中被标示的文字用replace替换
							fileTextAreas[textAreas_control].replaceSelection(replace_word);
						}
					}
				}
			}
		}
	}
	/**
	 * 编译compile事件
	 */
	class Act_Compile implements ActionListener {
		public void actionPerformed(ActionEvent e_ji6) {
			//compile一个java源文件
			//控制台信息
			consoleTextArea.setText(null);
			//目前只支持编译java类
			if ((fileTabbedPane.getTitleAt(textAreas_control)).indexOf(".java") > -1) {
				try {
					int count;
					byte input[] = new byte[256];
					String InputString;
					// 编译java源文件的命令"javac"
					String[] command = {
							"javac",
							directory[textAreas_control] + "/"
							+ fileTabbedPane.getTitleAt(textAreas_control) };
					//当前应用程序启动一个新进程，用于执行命令
					Process p = Runtime.getRuntime().exec(command);
					//读取执行命令时的错误输出
					BufferedInputStream bufin = new BufferedInputStream(p.getErrorStream());
					//这里仅仅读取前1024个字节
					bufin.mark(1024);
					count = bufin.read(input);
					if (count <= 0){
						//编译没有错误
						consoleTextArea.append("Compile to " + fileTabbedPane.getTitleAt(textAreas_control)
								+ " Success");
					} else {
						//编译失败
						InputString = new String(input, 0, count);
						consoleTextArea.append("Compile to " + fileTabbedPane.getTitleAt(textAreas_control)
								+ " Fail\n" + InputString);
					}
				} catch (IOException e) {
					System.err.println("IO error: " + e);
				}
			} else {
				consoleTextArea.append(fileTabbedPane.getTitleAt(textAreas_control)
						+ " is not a java File !\n Please Check it again!");
			}
		}
	}
	/**
	 * 运行build事件
	 */
	class Act_Build implements ActionListener {
		public void actionPerformed(ActionEvent e_ji7) {
			//build一个Java类
			consoleTextArea.setText(null);
			if ((fileTabbedPane.getTitleAt(textAreas_control)).indexOf(".java") > -1) {
				try {
					int count;
					byte input[] = new byte[256];
					String InputString;
					//获取java类的名字，去掉java源文件名的后五个字母".java"
					String class_name;
					int length = (fileTabbedPane.getTitleAt(textAreas_control)).length();
					class_name = (fileTabbedPane.getTitleAt(textAreas_control)).substring(0,
							length - 5);
					//运行java类的命令"java"
					String[] command = { "java", "-classpath",
							directory[textAreas_control], class_name };
					Process p = Runtime.getRuntime().exec(command);
					BufferedInputStream bufin = new BufferedInputStream(p
							.getErrorStream());
					bufin.mark(256);
					count = bufin.read(input);
					if (count <= 0){
						//运行没有错误
						consoleTextArea.append("Build to " + fileTabbedPane.getTitleAt(textAreas_control)
								+ " Success");
					} else {
						//运行有错误
						InputString = new String(input, 0, count);
						consoleTextArea.append("Builld to " + fileTabbedPane.getTitleAt(textAreas_control)
								+ " Fail\n" + InputString);
					}
				} catch (IOException e) {
					System.err.println("IO error: " + e);
				} catch (IndexOutOfBoundsException e2) {
					System.err.println("IO error: " + e2);
				}
			} else {
				consoleTextArea.append(fileTabbedPane.getTitleAt(textAreas_control)
						+ " is not a java File !\n Please Check it again!");
			}
		}
	}
	/**
	 * 显示帮助Help事件
	 */
	class Act_Help implements ActionListener {
		public void actionPerformed(ActionEvent e_ji9) {
			helpFrame.pack();
			helpFrame.setVisible(true);
			helpFrame.requestFocus();
			helpFrame.setLocation(200, 0);
		}
	}
	
	class Act_Copy implements ActionListener {
		public void actionPerformed(ActionEvent e_ji9) {
			//复制事件，直接调用JTextArea的copy方法
			fileTextAreas[textAreas_control].copy();
		}
	}

	class Act_Cut implements ActionListener {
		public void actionPerformed(ActionEvent e_ji10) {
			//剪贴事件，直接调用JTextArea的cut方法
			fileTextAreas[textAreas_control].cut();
		}
	}

	class Act_Paste implements ActionListener {
		public void actionPerformed(ActionEvent e_ji11) {
			//粘贴事件，直接调用JTextArea的paste方法
			fileTextAreas[textAreas_control].paste();
		}
	}

	/**
	 * 动画显示事件
	 */
	class Act_timer implements ActionListener {
		public void actionPerformed(ActionEvent e_time) {
			//Flash显示，一共就4个图片文件，按顺序显示
			if (timerControl > 4){
				timerControl = 0;
			}
			flashLabel.setIcon(new ImageIcon(loadImage("image/Juggler" + timerControl
					+ ".gif")));
			timerControl++;
		}
	}

	/**
	 * 停止动画事件
	 */
	class Act_StopFlash implements ActionListener {
		public void actionPerformed(ActionEvent E_stop) {
			//Flash控制。停止动画
			timer.stop();
			startFlashMenuItem.setEnabled(true);
			stopFlashMenuItem.setEnabled(false);
		}
	}

	/**
	 * 启动动画事件
	 */
	class Act_StartFlash implements ActionListener {
		public void actionPerformed(ActionEvent E_start) {
			//Flash控制。启动动画
			timer.start();
			startFlashMenuItem.setEnabled(false);
			stopFlashMenuItem.setEnabled(true);
		}
	}

	/**
	 * 从jar包中读取图片文件
	 * @param name
	 * @return	返回一个图片对象
	 */
	private java.awt.Image loadImage(String name) {
		try {
			java.net.URL url = getClass().getResource(name);
			//根据URL中内容新建一个图片文件
			return createImage((java.awt.image.ImageProducer) url.getContent());
		} catch (Exception ex) {
			return null;
		}
	}
	public static void main(String args[]) {
		new SimpleEditor();
	}
}
