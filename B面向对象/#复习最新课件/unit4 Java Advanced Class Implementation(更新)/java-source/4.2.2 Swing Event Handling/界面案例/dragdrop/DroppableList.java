package book.gui.dragdrop;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.dnd.DnDConstants;
import java.awt.dnd.DragGestureEvent;
import java.awt.dnd.DragGestureListener;
import java.awt.dnd.DragSource;
import java.awt.dnd.DragSourceDragEvent;
import java.awt.dnd.DragSourceDropEvent;
import java.awt.dnd.DragSourceEvent;
import java.awt.dnd.DragSourceListener;
import java.awt.dnd.DropTarget;
import java.awt.dnd.DropTargetDragEvent;
import java.awt.dnd.DropTargetDropEvent;
import java.awt.dnd.DropTargetEvent;
import java.awt.dnd.DropTargetListener;
import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Vector;

import javax.swing.DefaultListModel;
import javax.swing.JList;

/**
 * 支持拖放的List：可以将文件拖放到List中，也可以把List中的项拖放到文件系统或者文本框中。
 * 支持拖放必须实现3个接口：DropTargetListener、DragSourceListener和DragGestureListener。
 * 当拖动List中的数据开始时，DragGestureListener定义的方法被调用。
 * 当拖动List中的数据过程中，DragSourceListener定义的方法被调用。
 * 当往List中放置数据时，DragSourceListener定义的方法被调用。
 */
public class DroppableList extends JList implements DropTargetListener,
		DragSourceListener, DragGestureListener {
	// 拖放的目的地，即放置点，本List接收放置drop操作
	DropTarget dropTarget = new DropTarget(this, this);

	// 使用默认的拖放源
	DragSource dragSource = DragSource.getDefaultDragSource();

	public DroppableList() {
		// 初始化拖放源，第一个参数指定源对象，即本对象；第二个参数指定拖动支持的方式；
		// 第三个参数指定拖动发生时DragGestureListener的实现类，即本对象。
		dragSource.createDefaultDragGestureRecognizer(this,
				DnDConstants.ACTION_COPY_OR_MOVE, this);
		// 设置List的数据模型。
		DefaultListModel model = new DefaultListModel();
		setModel(model);
	}

	// 下面五个方法实现了DragSourceListener接口定义的方法，当拖动本对象的数据到其他地方时，调用这些方法。
	public void dragDropEnd(DragSourceDropEvent DragSourceDropEvent) {
		System.out
				.println("method: dragDropEnd(DragSourceDropEvent DragSourceDropEvent)");
	}

	public void dragEnter(DragSourceDragEvent DragSourceDragEvent) {
		System.out
				.println("method: dragEnter(DragSourceDragEvent DragSourceDragEvent)");
	}

	public void dragExit(DragSourceEvent DragSourceEvent) {
		System.out.println("method: dragExit(DragSourceEvent DragSourceEvent)");
	}

	public void dragOver(DragSourceDragEvent DragSourceDragEvent) {
		// System.out.println("method: dragOver(DragSourceDragEvent
		// DragSourceDragEvent) called!");
	}

	public void dropActionChanged(DragSourceDragEvent DragSourceDragEvent) {
		System.out
				.println("method: dropActionChanged(DragSourceDragEvent DragSourceDragEvent)");
	}

	// 下面5个方法实现了DropTargetListener接口定义的方法，当拖动东西放进本对象时，这些方法被调用。
	public void dragEnter(DropTargetDragEvent dropTargetDragEvent) {
		System.out
				.println("method: dragEnter(DropTargetDragEvent dropTargetDragEvent)");
		dropTargetDragEvent.acceptDrag(DnDConstants.ACTION_COPY_OR_MOVE);
	}

	public void dragExit(DropTargetEvent dropTargetEvent) {
		System.out.println("method: dragExit(DropTargetEvent dropTargetEvent)");
	}

	public void dragOver(DropTargetDragEvent dropTargetDragEvent) {
		// System.out.println("method: dragOver(DropTargetDragEvent
		// dropTargetDragEvent) called!");
	}

	public void dropActionChanged(DropTargetDragEvent dropTargetDragEvent) {
		System.out
				.println("method: dropActionChanged(DropTargetDragEvent dropTargetDragEvent)");
	}

	/**
	 * 当拖动系统中的文件放置drop到该List中时，调用此方法。
	 */
	public synchronized void drop(DropTargetDropEvent dropTargetDropEvent) {
		System.out
				.println("method: drop(DropTargetDropEvent dropTargetDropEvent)");
		try {
			// 获取传入的Transfer对象
			Transferable tr = dropTargetDropEvent.getTransferable();
			// 如果Transfer对象支持文件放置到java平台，则进行下一步处理
			if (tr.isDataFlavorSupported(DataFlavor.javaFileListFlavor)) {
				// 使用“拷贝、移动”方式接收放置操作。
				dropTargetDropEvent
						.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
				// 从Transfer中取数据，得到的是一个文件列表。即可以一次拖放多个文件
				java.util.List fileList = (java.util.List) tr
						.getTransferData(DataFlavor.javaFileListFlavor);
				Iterator iterator = fileList.iterator();
				while (iterator.hasNext()) {
					// 将拖放进来的文件的信息添加到List的数据模型中
					File file = (File) iterator.next();
					Hashtable hashtable = new Hashtable();
					hashtable.put("name", file.getName());
					hashtable.put("url", file.toURL().toString());
					hashtable.put("path", file.getAbsolutePath());
					((DefaultListModel) getModel()).addElement(hashtable);
				}
				// 放置操作成功结束
				dropTargetDropEvent.getDropTargetContext().dropComplete(true);
			} else {
				// Transferable对象不支持文件放置到java中，拒绝。
				System.err.println("Rejected");
				dropTargetDropEvent.rejectDrop();
			}
		} catch (IOException io) {
			io.printStackTrace();
			dropTargetDropEvent.rejectDrop();
		} catch (UnsupportedFlavorException ufe) {
			ufe.printStackTrace();
			dropTargetDropEvent.rejectDrop();
		}
	}

	/**
	 * 当从List中选择一项拖放到文件系统或者其他地方时，调用此方法。 这是DragGestureListener接口定义的方法。
	 */
	public void dragGestureRecognized(DragGestureEvent dragGestureEvent) {
		System.out
				.println("method: dragGestureRecognized(DragGestureEvent dragGestureEvent)");
		if (getSelectedIndex() == -1)
			return;
		// 获得被选择的项的数据。
		Object obj = getSelectedValue();
		if (obj == null) {
			// 如果没有选择列表中的项，则不能视为一个拖动，则蜂鸣。
			System.out.println("Nothing selected - beep");
			getToolkit().beep();
		} else {
			// 将List中被选择的项打包成一个Transfer对象
			Hashtable table = (Hashtable) obj;
			FileSelection transferable = new FileSelection(new File(
					(String) table.get("path")));
			// 开始拖放，第一个参数为拖放时的光标；第二个参数为被拖放的数据对象；第三个是拖放拖放源侦听器
			dragGestureEvent.startDrag(DragSource.DefaultCopyDrop,
					transferable, this);
		}
	}

	/**
	 * 内部类，定义了一个支持文件拖放的Transfer对象。 它继承Vector，表示它可以一次传送多个文件
	 */
	class FileSelection extends Vector implements Transferable {
		final static int FILE = 0;

		final static int STRING = 1;

		final static int PLAIN = 2;

		// 定义该Transfer能够传送的数据类型，包括文件、字符串和无格式的文本。
		DataFlavor flavors[] = { DataFlavor.javaFileListFlavor,
				DataFlavor.stringFlavor, DataFlavor.plainTextFlavor };

		public FileSelection(File file) {
			// 将文件保存
			addElement(file);
		}

		/* 返回该Transfer能够传递的数据类型 */
		public synchronized DataFlavor[] getTransferDataFlavors() {
			return flavors;
		}

		/* 判断该Transfer是否支持flavor数据类型的传送 */
		public boolean isDataFlavorSupported(DataFlavor flavor) {
			boolean b = false;
			b |= flavor.equals(flavors[FILE]);
			b |= flavor.equals(flavors[STRING]);
			b |= flavor.equals(flavors[PLAIN]);
			return (b);
		}

		/**
		 * 返回Transfer对象中封装的数据
		 */
		public synchronized Object getTransferData(DataFlavor flavor)
				throws UnsupportedFlavorException, IOException {
			if (flavor.equals(flavors[FILE])) {
				// 如果是要获取文件数据、则将自己返回，是一个文件的Vector。
				System.out.println("return flavors[FILE]");
				return this;
			} else if (flavor.equals(flavors[PLAIN])) {
				// 如果是要获取一个文本，则将第一个文件的文件内容的流的引用返回。
				System.out.println("return flavors[PLAIN]");
				return new StringReader(((File) elementAt(0)).getAbsolutePath());
			} else if (flavor.equals(flavors[STRING])) {
				// 如果是要获取一个字符串，则将第一个文件的文件路径名返回
				System.out.println("return flavors[STRING]");
				return ((File) elementAt(0)).getAbsolutePath();
			} else {
				throw new UnsupportedFlavorException(flavor);
			}
		}
	}

	/**
	 * 组件拖放的基本原理：
	 * （1）从List中拖动时，dragGestureRecognized方法将JList中被选择的项打包成一个Transferable对象。
	 * （2）放置数据到List中时，drop方法将Transferable对象中的数据放到List中。
	 */
}
