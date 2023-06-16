package stumanage;

import javax.swing.*;
import java.awt.*;
import sun.awt.image.*;
import java.awt.event.*;
import com.borland.jbcl.layout.*;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2003</p>
 * <p>Company: </p>
 * @author 
 * @version 1.0
 */

public class WelcomeFrame
    extends JFrame {
  JPanel jPanel1 = new MyPanel();
  ImageIcon imageIcon1 = new ImageIcon("beautiful.jpg");
  JPanel jPanel2 = new JPanel();
  JButton jButton1 = new JButton();
  JButton jButton2 = new JButton();
  JButton jButton3 = new JButton();
  JButton jButton4 = new JButton();
  JButton jButton5 = new JButton();
  JButton jButton6 = new JButton();
  XYLayout xYLayout1 = new XYLayout();
  BorderLayout borderLayout1 = new BorderLayout();

  public WelcomeFrame() {
    try {
      jbInit();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    WelcomeFrame welcomeFrame = new WelcomeFrame();
    welcomeFrame.setLocation(150,100);
    welcomeFrame.pack();
    welcomeFrame.show();
  }

  private void jbInit() throws Exception {
    imageIcon1.setDescription("beautiful.jpg");
    imageIcon1.setImageObserver(this);
    jPanel1.setLayout(borderLayout1);
    jPanel1.setDebugGraphicsOptions(0);
    jPanel1.setMinimumSize(new Dimension(730, 550));
    jPanel1.setPreferredSize(new Dimension(730, 450));
    this.setDefaultCloseOperation(HIDE_ON_CLOSE);
    this.setLocale(java.util.Locale.getDefault());
    this.setResizable(true);
    this.setSize(new Dimension(754, 453));
    this.setState(Frame.NORMAL);
    this.setTitle("欢迎您使用本系统  ^_^");
    this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    jPanel2.setBackground(UIManager.getColor(
        "RadioButtonMenuItem.selectionBackground"));
    jPanel2.setForeground(Color.black);
    jPanel2.setMinimumSize(new Dimension(100, 200));
    jPanel2.setPreferredSize(new Dimension(130, 400));
    jPanel2.setLayout(xYLayout1);
    jButton1.setBackground(UIManager.getColor("Button.background"));
    jButton1.setFont(new java.awt.Font("Dialog", 1, 15));
    jButton1.setForeground(Color.black);
    jButton1.setToolTipText(" 个人信息管理");
    jButton1.setActionCommand(" 学生个人基本信息管理");
    jButton1.setText("学生基本信息管理");
    jButton1.addActionListener(new WelcomeFrame_jButton1_actionAdapter(this));
    jButton2.setFont(new java.awt.Font("Dialog", 1, 15));
    jButton2.setForeground(Color.black);
    jButton2.setToolTipText(" 选课信息管理");
    jButton2.setText(" 学生选课信息管理");
    jButton2.addActionListener(new WelcomeFrame_jButton2_actionAdapter(this));
    jButton3.setFont(new java.awt.Font("Dialog", 1, 15));
    jButton3.setForeground(Color.black);
    jButton3.setToolTipText("学生其他信息管理");
    jButton3.setText("学生其他信息管理");
    jButton3.addActionListener(new WelcomeFrame_jButton3_actionAdapter(this));
    jButton4.setFont(new java.awt.Font("Dialog", 1, 15));
    jButton4.setForeground(Color.black);
    jButton4.setToolTipText("学生成绩信息管理");
    jButton4.setText("学生成绩信息管理");
    jButton4.addActionListener(new WelcomeFrame_jButton4_actionAdapter(this));
    jButton5.setFont(new java.awt.Font("Dialog", 1, 15));
    jButton5.setForeground(Color.blue);
    jButton5.setToolTipText("退出系统");
    jButton5.setText("退出系统");
    jButton5.addActionListener(new WelcomeFrame_jButton5_actionAdapter(this));
    jButton6.setFont(new java.awt.Font("Dialog", 1, 15));
    jButton6.setForeground(Color.black);
    jButton6.setText("新信息录入");
    jButton6.addActionListener(new WelcomeFrame_jButton6_actionAdapter(this));
    jPanel2.add(jButton1,          new XYConstraints(-14, 99, -1, -1));
    jPanel2.add(jButton2,           new XYConstraints(-19, 146, 168, -1));
    jPanel2.add(jButton5, new XYConstraints(-6, 316, 140, -1));
    jPanel2.add(jButton6, new XYConstraints(-4, 273, 137, -1));
    jPanel2.add(jButton3,  new XYConstraints(-13, 189, -1, -1));
    jPanel2.add(jButton4,      new XYConstraints(-14, 233, 162, -1));
    this.getContentPane().add(jPanel1, BorderLayout.CENTER);
    jPanel1.add(jPanel2, BorderLayout.EAST);
  }

  class MyPanel
      extends JPanel {
    public void paintComponent(Graphics g) {
      super.paintComponent(g);
      imageIcon1.paintIcon(this, g, 0, 0);
    }

  }

  void jButton4_actionPerformed(ActionEvent e) {
    MainFrame.main(null);
    this.hide();
    MainFrame.jTabbedPane1.setSelectedComponent(MainFrame.jPanel4);
  }

  void jButton1_actionPerformed(ActionEvent e) {
    MainFrame.main(null);
    this.hide();
  }

  void jButton3_actionPerformed(ActionEvent e) {
    MainFrame.main(null);
    this.hide();
    MainFrame.jTabbedPane1.setSelectedComponent(MainFrame.jPanel3);

  }

  void jButton2_actionPerformed(ActionEvent e) {
    MainFrame.main(null);
    this.hide();
    MainFrame.jTabbedPane1.setSelectedComponent(MainFrame.jPanel2);
  }

  void jButton5_actionPerformed(ActionEvent e) {
    System.exit(0);
  }

  void jButton6_actionPerformed(ActionEvent e) {
    MainFrame.main(null);
    this.hide();
    MainFrame.jTabbedPane1.setSelectedComponent(MainFrame.jPanel20);

  }

}

class WelcomeFrame_jButton4_actionAdapter
    implements java.awt.event.ActionListener {
  WelcomeFrame adaptee;

  WelcomeFrame_jButton4_actionAdapter(WelcomeFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton4_actionPerformed(e);
  }
}

class WelcomeFrame_jButton1_actionAdapter
    implements java.awt.event.ActionListener {
  WelcomeFrame adaptee;

  WelcomeFrame_jButton1_actionAdapter(WelcomeFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton1_actionPerformed(e);
  }
}

class WelcomeFrame_jButton3_actionAdapter
    implements java.awt.event.ActionListener {
  WelcomeFrame adaptee;

  WelcomeFrame_jButton3_actionAdapter(WelcomeFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton3_actionPerformed(e);
  }
}

class WelcomeFrame_jButton2_actionAdapter
    implements java.awt.event.ActionListener {
  WelcomeFrame adaptee;

  WelcomeFrame_jButton2_actionAdapter(WelcomeFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton2_actionPerformed(e);
  }
}

class WelcomeFrame_jButton5_actionAdapter
    implements java.awt.event.ActionListener {
  WelcomeFrame adaptee;

  WelcomeFrame_jButton5_actionAdapter(WelcomeFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton5_actionPerformed(e);
  }
}

class WelcomeFrame_jButton6_actionAdapter
    implements java.awt.event.ActionListener {
  WelcomeFrame adaptee;

  WelcomeFrame_jButton6_actionAdapter(WelcomeFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton6_actionPerformed(e);
  }
}