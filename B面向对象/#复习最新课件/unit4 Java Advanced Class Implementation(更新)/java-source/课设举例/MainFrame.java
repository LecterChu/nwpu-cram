package stumanage;

import javax.swing.*;
import javax.swing.plaf.*;
import com.borland.dbswing.*;
import java.awt.*;
import com.borland.jbcl.layout.*;
import com.borland.dx.sql.dataset.*;
import com.borland.dx.dataset.*;
import java.awt.event.*;
import java.sql.*;
import javax.swing.border.*;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2003</p>
 * <p>Company: </p>
 * @author 
 * @version 1.0
 */

public class MainFrame
    extends JFrame {
  PaneLayout paneLayout1 = new PaneLayout();
  static JTabbedPane jTabbedPane1 = new JTabbedPane();
  static JPanel jPanel1 = new JPanel();
  static JPanel jPanel2 = new JPanel();
  static JPanel jPanel3 = new JPanel();
  static JPanel jPanel4 = new JPanel();
  static JPanel jPanel5 = new JPanel();
  BorderLayout borderLayout1 = new BorderLayout();
  JdbNavToolBar jdbNavToolBar1 = new JdbNavToolBar();
  BorderLayout borderLayout2 = new BorderLayout();
  Database database1 = new Database();
  JPanel jPanel6 = new JPanel();
  BorderLayout borderLayout3 = new BorderLayout();
  JPanel jPanel7 = new JPanel();
  FlowLayout flowLayout1 = new FlowLayout();
  JLabel jLabel1 = new JLabel();
  TableScrollPane tableScrollPane1 = new TableScrollPane();
  JdbTable jdbTable1 = new JdbTable();
  Column column10 = new Column();
  Column column12 = new Column();
  Column column13 = new Column();
  Font font1;
  BorderLayout borderLayout4 = new BorderLayout();
  JPanel jPanel9 = new JPanel();
  JLabel jLabel8 = new JLabel();
  JLabel jLabel9 = new JLabel();
  JLabel jLabel10 = new JLabel();
  JLabel jLabel11 = new JLabel();
  JdbNavToolBar jdbNavToolBar2 = new JdbNavToolBar();
  JPanel jPanel10 = new JPanel();
  JPanel jPanel11 = new JPanel();
  JPanel jPanel12 = new JPanel();
  BorderLayout borderLayout5 = new BorderLayout();
  JLabel jLabel12 = new JLabel();
  TableScrollPane tableScrollPane2 = new TableScrollPane();
  JdbTable jdbTable2 = new JdbTable();
  JLabel jLabel13 = new JLabel();
  TableScrollPane tableScrollPane3 = new TableScrollPane();
  BorderLayout borderLayout6 = new BorderLayout();
  JButton jButton3 = new JButton();
  JButton jButton4 = new JButton();
  XYLayout xYLayout1 = new XYLayout();
  Column column2 = new Column();
  Column column4 = new Column();
  Column column6 = new Column();
  Column column7 = new Column();
  JdbTable jdbTable3 = new JdbTable();
  JLabel jLabel14 = new JLabel();
  JLabel jLabel15 = new JLabel();
  JPanel jPanel13 = new JPanel();
  JLabel jLabel16 = new JLabel();
  JLabel jLabel17 = new JLabel();
  BorderLayout borderLayout7 = new BorderLayout();
  JPanel jPanel15 = new JPanel();
  TableScrollPane tableScrollPane4 = new TableScrollPane();
  JdbTable jdbTable4 = new JdbTable();
  ButtonGroup buttonGroup1 = new ButtonGroup();
  JdbNavField jdbNavField1 = new JdbNavField();
  JdbTextField jdbTextField9 = new JdbTextField();
  JdbTextField jdbTextField10 = new JdbTextField();
  Column column16 = new Column();
  Column column19 = new Column();
  JdbTextField jdbTextField11 = new JdbTextField();
  JdbNavField jdbNavField2 = new JdbNavField();
  JdbNavField jdbNavField3 = new JdbNavField();
  JdbTextField jdbTextField12 = new JdbTextField();
  JdbTextField jdbTextField13 = new JdbTextField();
  JdbTextField jdbTextField14 = new JdbTextField();
  Column column21 = new Column();
  Column column23 = new Column();
  Column column24 = new Column();
  BorderLayout borderLayout12 = new BorderLayout();
  static JPanel jPanel20 = new JPanel();
  BorderLayout borderLayout13 = new BorderLayout();
  JPanel jPanel21 = new JPanel();
  JPanel jPanel22 = new JPanel();
  XYLayout xYLayout2 = new XYLayout();
  JLabel jLabel21 = new JLabel();
  JLabel jLabel22 = new JLabel();
  JTextField jTextField1 = new JTextField();
  JLabel jLabel23 = new JLabel();
  JLabel jLabel24 = new JLabel();
  JLabel jLabel25 = new JLabel();
  JLabel jLabel26 = new JLabel();
  JLabel jLabel27 = new JLabel();
  JTextField jTextField2 = new JTextField();
  JTextField jTextField3 = new JTextField();
  JTextField jTextField4 = new JTextField();
  JTextField jTextField6 = new JTextField();
  JTextField jTextField7 = new JTextField();
  JButton jButton7 = new JButton();
  XYLayout xYLayout3 = new XYLayout();
  JLabel jLabel28 = new JLabel();
  JLabel jLabel29 = new JLabel();
  JLabel jLabel30 = new JLabel();
  JLabel jLabel31 = new JLabel();
  JLabel jLabel32 = new JLabel();
  JLabel jLabel33 = new JLabel();
  JLabel jLabel34 = new JLabel();
  JLabel jLabel35 = new JLabel();
  JTextField jTextField8 = new JTextField();
  JTextField jTextField9 = new JTextField();
  JTextField jTextField10 = new JTextField();
  JTextField jTextField11 = new JTextField();
  JTextField jTextField12 = new JTextField();
  JButton jButton8 = new JButton();
  QueryDataSet qSet_student_info = new QueryDataSet();
  Column column8 = new Column();
  Column column9 = new Column();
  Column column11 = new Column();
  Column column14 = new Column();
  Column column17 = new Column();
  Column column26 = new Column();
  Column column27 = new Column();
  QueryDataSet qSet_coursecode = new QueryDataSet();
  Column column1 = new Column();
  Column column3 = new Column();
  Column column5 = new Column();
  Column column28 = new Column();
  Column column29 = new Column();
  Column column30 = new Column();
  Column column18 = new Column();
  Column column31 = new Column();
  Column column32 = new Column();
  Column column33 = new Column();
  Column column15 = new Column();
  Column column35 = new Column();
  QueryDataSet qSet_course = new QueryDataSet();
  Column column34 = new Column();
  Column column36 = new Column();
  Column column37 = new Column();
  Column column38 = new Column();
  JButton jButton9 = new JButton();
  JTextArea jTextArea1 = new JTextArea();
  JPanel jPanel23 = new JPanel();
  XYLayout xYLayout4 = new XYLayout();
  JLabel jLabel36 = new JLabel();
  JLabel jLabel37 = new JLabel();
  JLabel jLabel38 = new JLabel();
  JLabel jLabel39 = new JLabel();
  JLabel jLabel40 = new JLabel();
  JLabel jLabel41 = new JLabel();
  JLabel jLabel42 = new JLabel();
  JTextField jTextField13 = new JTextField();
  JTextField jTextField14 = new JTextField();
  JTextField jTextField15 = new JTextField();
  JTextField jTextField16 = new JTextField();
  JTextField jTextField17 = new JTextField();
  JButton jButton10 = new JButton();
  TableScrollPane tableScrollPane5 = new TableScrollPane();
  JdbTable jdbTable5 = new JdbTable();
  JLabel jLabel2 = new JLabel();
  JdbNavField jdbNavField4 = new JdbNavField();
  JButton jButton1 = new JButton();
  QueryDataSet qSet_class = new QueryDataSet();
  Column column39 = new Column();
  Column column40 = new Column();
  Column column42 = new Column();
  Column column43 = new Column();
  Column column44 = new Column();
  XYLayout xYLayout5 = new XYLayout();
  TableScrollPane tableScrollPane6 = new TableScrollPane();
  JdbTable jdbTable6 = new JdbTable();
  QueryDataSet qSet_practice = new QueryDataSet();
  Column column45 = new Column();
  Column column46 = new Column();
  Column column47 = new Column();
  Column column48 = new Column();
  Column column49 = new Column();
  Column column50 = new Column();
  JPanel jPanel8 = new JPanel();
  XYLayout xYLayout6 = new XYLayout();
  JLabel jLabel3 = new JLabel();
  JLabel jLabel4 = new JLabel();
  JButton jButton2 = new JButton();
  TableScrollPane tableScrollPane7 = new TableScrollPane();
  JdbTable jdbTable7 = new JdbTable();
  Column column52 = new Column();
  Column column54 = new Column();
  JLabel jLabel5 = new JLabel();
  JLabel jLabel6 = new JLabel();
  JLabel jLabel7 = new JLabel();
  JButton jButton5 = new JButton();
  JdbNavField jdbNavField6 = new JdbNavField();
  JdbNavField jdbNavField7 = new JdbNavField();
  JdbNavField jdbNavField8 = new JdbNavField();
  QueryDataSet qSet_gcheck = new QueryDataSet();
  Column column20 = new Column();
  Column column22 = new Column();
  Column column25 = new Column();
  Column column56 = new Column();
  Column column57 = new Column();
  Column column58 = new Column();
  JLabel jLabel18 = new JLabel();
  JLabel jLabel19 = new JLabel();
  JLabel jLabel20 = new JLabel();
  JLabel jLabel43 = new JLabel();
  JLabel jLabel44 = new JLabel();
  JLabel jLabel45 = new JLabel();
  JTextField jTextField18 = new JTextField();
  JTextField jTextField19 = new JTextField();
  JTextField jTextField20 = new JTextField();
  JTextField jTextField21 = new JTextField();
  JTextField jTextField22 = new JTextField();
  JTextField jTextField23 = new JTextField();
  JButton jButton6 = new JButton();
  JButton jButton11 = new JButton();
  JButton jButton12 = new JButton();
  JButton jButton13 = new JButton();
  Column column51 = new Column();
  JdbTextField jdbTextField1 = new JdbTextField();
  JLabel jLabel46 = new JLabel();
  TableScrollPane tableScrollPane8 = new TableScrollPane();
  JdbTable jdbTable8 = new JdbTable();
  JLabel jLabel47 = new JLabel();
  JButton jButton14 = new JButton();
  JTextField jTextField24 = new JTextField();
  QueryDataSet qSet_fail = new QueryDataSet();
  Column column53 = new Column();
  Column column55 = new Column();
  Column column59 = new Column();
  Column column60 = new Column();
  Column column61 = new Column();
  JButton jButton15 = new JButton();
  TitledBorder titledBorder1;
  JLabel jLabel48 = new JLabel();
  JRadioButton jRadioButton1 = new JRadioButton();
  JRadioButton jRadioButton2 = new JRadioButton();
  JButton jButton16 = new JButton();
  JButton jButton17 = new JButton();
  JButton jButton18 = new JButton();
  JButton jButton19 = new JButton();
  JLabel jLabel50 = new JLabel();
  JLabel jLabel49 = new JLabel();
  JLabel jLabel51 = new JLabel();
  JLabel jLabel52 = new JLabel();
  JLabel jLabel53 = new JLabel();
  JLabel jLabel54 = new JLabel();
  JLabel jLabel55 = new JLabel();
  JdbStatusLabel jdbStatusLabel1 = new JdbStatusLabel();
  JdbTextField jdbTextField2 = new JdbTextField();

  public MainFrame() {
    try {
      jbInit();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception e) {
    }
    //System.out.println(new javax.swing.UIManager());

    Font f = new java.awt.Font("SansSerif", 0, 12);
    UIManager.put("Label.font", f);
    UIManager.put("Label.foreground", Color.black);
    UIManager.put("Button.font", f);
    UIManager.put("Menu.font", f);
    UIManager.put("MenuItem.font", f);
    UIManager.put("List.font", f);
    UIManager.put("CheckBox.font", f);
    UIManager.put("RadioButton.font", f);
    UIManager.put("ComboBox.font", f);
    UIManager.put("TextArea.font", f);
    UIManager.put("dbTextArea.font", f);
    UIManager.put("font", f);

    MainFrame mainFrame = new MainFrame();
    mainFrame.setFont(new java.awt.Font("SansSerif", 0, 12));
    mainFrame.pack();
    mainFrame.setLocation(150,100);
    mainFrame.setSize(600, 450);
    mainFrame.show();
  }

  private void jbInit() throws Exception {
    font1 = new java.awt.Font("SansSerif", 0, 12);
    titledBorder1 = new TitledBorder("");
    this.getContentPane().setLayout(paneLayout1);
    this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    this.setTitle("Student Management System");
    jPanel1.setLayout(borderLayout1);
    jRadioButton1.setSelected(true);
    jButton16.setFont(new java.awt.Font("SansSerif", 0, 11));
    jButton16.setForeground(Color.blue);
    jButton16.setText("退出系统");
    jButton16.addActionListener(new MainFrame_jButton16_actionAdapter(this));
    jButton17.setBackground(UIManager.getColor("Button.background"));
    jButton17.setFont(new java.awt.Font("SansSerif", 0, 11));
    jButton17.setForeground(Color.blue);
    jButton17.setText("退出系统");
    jButton17.addActionListener(new MainFrame_jButton17_actionAdapter(this));
    jButton18.setFont(new java.awt.Font("SansSerif", 0, 11));
    jButton18.setForeground(Color.blue);
    jButton18.setText("退出系统");
    jButton18.addActionListener(new MainFrame_jButton18_actionAdapter(this));
    jButton19.setFont(new java.awt.Font("SansSerif", 0, 11));
    jButton19.setForeground(Color.blue);
    jButton19.setText("退出系统");
    jButton19.addActionListener(new MainFrame_jButton19_actionAdapter(this));
    jdbNavField4.setColumns(0);
    column46.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column47.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column22.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column25.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    jLabel50.setFont(new java.awt.Font("Serif", 1, 15));
    jLabel50.setText("学生获奖信息表");
    jLabel49.setFont(new java.awt.Font("Serif", 1, 15));
    jLabel49.setText("学生实践信息表");
    jLabel51.setText("\"b××\"为基础课");
    jLabel52.setText("\"e××\"为专业课");
    jLabel53.setText("\"ssd\"为卡耐基课");
    jLabel54.setText("\"l××\"为实验课");
    jLabel55.setForeground(Color.red);
    jLabel55.setText("(请慎重填写班级代号，录入班级代号后将不能被删除)");
    jLabel36.setForeground(Color.black);
    jButton15.setFont(new java.awt.Font("SansSerif", 0, 11));
    jButton15.setForeground(Color.blue);
    jPanel1.setForeground(Color.pink);
    jPanel2.setForeground(Color.orange);
    jPanel3.setFont(new java.awt.Font("MS Sans Serif", 0, 11));
    jPanel3.setForeground(Color.cyan);
    jPanel4.setForeground(Color.green);
    jPanel20.setForeground(Color.magenta);
    jTabbedPane1.setToolTipText("");
    jTextField3.setEditable(false);
    jdbTable3.setCellSelectionEnabled(true);
    jdbTable3.setAutoSelection(true);
    tableScrollPane3.setAutoscrolls(false);
    tableScrollPane3.setBorder(BorderFactory.createLoweredBevelBorder());
    qSet_course.setSort(new com.borland.dx.dataset.SortDescriptor("", new String[] {"count_id"}, new boolean[] {false, }, null, 0));
    jdbStatusLabel1.setText("jdbStatusLabel1");
    jdbStatusLabel1.setFocusedDataSet(qSet_course);
    column34.setCalcType(com.borland.dx.dataset.CalcType.NO_CALC);
    column34.setCurrency(true);
    column34.setPrecision(-1);
    column34.setRowId(false);
    jdbTextField2.setText("jdbTextField2");
    jdbTextField2.setColumnName("count_id");
    jdbTextField2.setDataSet(qSet_course);
    buttonGroup1.add(jRadioButton1);
    buttonGroup1.add(jRadioButton2);
    jdbNavToolBar1.setDebugGraphicsOptions(0);
    jdbNavToolBar1.setAlignment(FlowLayout.CENTER);
    jdbNavToolBar1.setDataSet(qSet_student_info);
    jPanel5.setLayout(borderLayout2);
    database1.setConnection(new com.borland.dx.sql.dataset.ConnectionDescriptor(
        "jdbc:microsoft:sqlserver://localhost:1433;databaseName=student", "sa",
        "22114602", false, "com.microsoft.jdbc.sqlserver.SQLServerDriver"));
    database1.setTransactionIsolation(java.sql.Connection.
                                      TRANSACTION_READ_COMMITTED);
    database1.setDatabaseName("");
    jPanel6.setFont(new java.awt.Font("SansSerif", 0, 12));
    jPanel6.setMinimumSize(new Dimension(50, 100));
    jPanel6.setPreferredSize(new Dimension(50, 150));
    jPanel6.setLayout(borderLayout3);
    jPanel7.setFont(new java.awt.Font("SansSerif", 0, 12));
    jPanel7.setMinimumSize(new Dimension(100, 30));
    jPanel7.setPreferredSize(new Dimension(100, 40));
    jPanel7.setLayout(flowLayout1);
    jLabel1.setText("学号：");
    flowLayout1.setAlignment(FlowLayout.LEFT);
    jdbTable1.setFont(new java.awt.Font("SansSerif", 0, 12));
    jdbTable1.setAutoscrolls(true);
    jdbTable1.setDebugGraphicsOptions(0);
    jdbTable1.setToolTipText("");
    jdbTable1.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
    jdbTable1.setCellSelectionEnabled(true);
    jdbTable1.setDataSet(qSet_student_info);
    jTabbedPane1.setFont(new java.awt.Font("SansSerif", 0, 12));
    jTabbedPane1.setMinimumSize(new Dimension(500, 194));
    jTabbedPane1.setPreferredSize(new Dimension(500, 607));
    column10.setCaption("姓名");
    column10.setColumnName("student_birthday");
    column10.setDataType(com.borland.dx.dataset.Variant.STRING);
    column10.setPrecision(50);
    column10.setSchemaName("dbo");
    column10.setTableName("student_info");
    column10.setWidth(10);
    column10.setServerColumnName("student_birthday");
    column10.setSqlType(12);
    column12.setCaption("性别");
    column12.setColumnName("student_tel");
    column12.setDataType(com.borland.dx.dataset.Variant.STRING);
    column12.setPrecision(50);
    column12.setSchemaName("dbo");
    column12.setTableName("student_info");
    column12.setWidth(10);
    column12.setServerColumnName("student_tel");
    column12.setSqlType(12);
    column13.setCaption("联系电话");
    column13.setColumnName("student_name");
    column13.setDataType(com.borland.dx.dataset.Variant.STRING);
    column13.setPrecision(50);
    column13.setSchemaName("dbo");
    column13.setTableName("student_info");
    column13.setWidth(10);
    column13.setServerColumnName("student_name");
    column13.setSqlType(12);
    jPanel1.setFont(new java.awt.Font("SansSerif", 0, 12));
    jPanel1.setPreferredSize(new Dimension(472, 580));
    jPanel5.setFont(new java.awt.Font("SansSerif", 0, 12));
    tableScrollPane1.setFont(new java.awt.Font("SansSerif", 0, 12));
    tableScrollPane1.getViewport().setFont(new java.awt.Font("SansSerif", 0, 12));
    tableScrollPane1.setPreferredSize(new Dimension(300, 300));
    this.setFont(new java.awt.Font("SansSerif", 0, 12));
    jPanel2.setFont(new java.awt.Font("SansSerif", 0, 12));
    jPanel2.setLayout(borderLayout4);
    jLabel8.setText("学号：");
    jLabel9.setRequestFocusEnabled(true);
    jLabel9.setText("姓名: ");
    jLabel10.setText("班级: ");
    jLabel11.setText("性别: ");
    jdbNavToolBar2.setEnabled(false);
    jdbNavToolBar2.setAlignment(FlowLayout.CENTER);
    jdbNavToolBar2.setDataSet(qSet_coursecode);
    jPanel10.setMinimumSize(new Dimension(300, 10));
    jPanel10.setPreferredSize(new Dimension(300, 10));
    jPanel10.setLayout(borderLayout5);
    jLabel12.setText("学校设置可选课程信息");
    jPanel11.setMinimumSize(new Dimension(200, 10));
    jPanel11.setPreferredSize(new Dimension(200, 10));
    jPanel11.setLayout(borderLayout6);
    jLabel13.setText("个人已选课程信息");
    jButton3.setText("选课");
    jButton3.addActionListener(new MainFrame_jButton3_actionAdapter(this));
    jButton4.setText("退课");
    jButton4.addActionListener(new MainFrame_jButton4_actionAdapter(this));
    jPanel12.setLayout(xYLayout1);
    column2.setCaption("课程名称");
    column2.setColumnName("course_name");
    column2.setDataType(com.borland.dx.dataset.Variant.STRING);
    column2.setPrecision(50);
    column2.setPreferredOrdinal(1);
    column2.setSchemaName("dbo");
    column2.setTableName("student_coursecode");
    column2.setWidth(10);
    column2.setServerColumnName("course_name");
    column2.setSqlType(12);
    column4.setAlignment(com.borland.dx.text.Alignment.LEFT |
                         com.borland.dx.text.Alignment.MIDDLE);
    column4.setCaption("课程学分");
    column4.setColumnName("course_credit");
    column4.setDataType(com.borland.dx.dataset.Variant.DOUBLE);
    column4.setPreferredOrdinal(3);
    column4.setSchemaName("dbo");
    column4.setTableName("student_coursecode");
    column4.setWidth(10);
    column4.setServerColumnName("course_credit");
    column4.setSqlType(6);
    column6.setCaption("上课地点");
    column6.setColumnName("course_address");
    column6.setDataType(com.borland.dx.dataset.Variant.STRING);
    column6.setPrecision(50);
    column6.setSchemaName("dbo");
    column6.setTableName("student_coursecode");
    column6.setWidth(10);
    column6.setServerColumnName("course_address");
    column6.setSqlType(12);
    jdbTable2.setFont(new java.awt.Font("SansSerif", 0, 12));
    jdbTable2.setDataSet(qSet_coursecode);
    jdbTable2.setEditable(false);
    column7.setCaption("学生姓名");
    column7.setColumnName("course_name");
    column7.setDataType(com.borland.dx.dataset.Variant.STRING);
    column7.setPrecision(50);
    column7.setSchemaName("dbo");
    column7.setTableName("student_course");
    column7.setWidth(10);
    column7.setServerColumnName("course_name");
    column7.setSqlType(12);
    jLabel14.setText("学号：");
    jLabel15.setText("性别: ");
    jLabel16.setRequestFocusEnabled(true);
    jLabel16.setText("姓名: ");
    jLabel17.setText("班级: ");
    jPanel3.setLayout(borderLayout7);
    jPanel15.setMinimumSize(new Dimension(200, 100));
    jPanel15.setPreferredSize(new Dimension(200, 250));
    jPanel15.setLayout(xYLayout5);
    jPanel13.setPreferredSize(new Dimension(404, 40));
    jdbNavField1.setMinimumSize(new Dimension(100, 22));
    jdbNavField1.setPreferredSize(new Dimension(100, 22));
    jdbNavField1.setText("jdbNavField1");
    jdbNavField1.setColumnName("student_id");
    jdbNavField1.setDataSet(qSet_student_info);
    jdbNavField1.addActionListener(new MainFrame_jdbNavField1_actionAdapter(this));
    jdbTextField9.setEnabled(true);

    jdbTextField9.setPreferredSize(new Dimension(70, 22));
    jdbTextField9.setEditable(false);
    jdbTextField9.setText("jdbTextField9");
    jdbTextField9.setColumns(0);
    jdbTextField9.setColumnName("student_class");
    jdbTextField9.setDataSet(qSet_student_info);
    jdbTextField10.setEnabled(true);
    jdbTextField10.setDebugGraphicsOptions(0);
    jdbTextField10.setPreferredSize(new Dimension(50, 22));
    jdbTextField10.setEditable(false);
    jdbTextField10.setText("jdbTextField10");
    jdbTextField10.setColumnName("student_sex");
    jdbTextField10.setDataSet(qSet_student_info);
    column16.setColumnName("course_id");
    column16.setDataType(com.borland.dx.dataset.Variant.STRING);
    column16.setSchemaName("dbo");
    column16.setTableName("student_course");
    column16.setVisible(com.borland.jb.util.TriStateProperty.FALSE);
    column16.setServerColumnName("course_id");
    column16.setSqlType(4);
    column19.setCaption("所选课程编号");
    column19.setColumnName("course_no");
    column19.setDataType(com.borland.dx.dataset.Variant.STRING);
    column19.setSchemaName("dbo");
    column19.setTableName("student_course");
    column19.setServerColumnName("course_no");
    column19.setSqlType(4);
    jdbTextField11.setMinimumSize(new Dimension(70, 22));
    jdbTextField11.setPreferredSize(new Dimension(70, 22));
    jdbTextField11.setEditable(false);
    jdbTextField11.setText("jdbTextField11");
    jdbTextField11.setColumnName("student_name");
    jdbTextField11.setDataSet(qSet_student_info);
    jdbNavField2.setColumnName("student_id");
    jdbNavField2.setDataSet(qSet_student_info);
    jdbNavField2.setPreferredSize(new Dimension(70, 22));
    jdbNavField2.setMinimumSize(new Dimension(70, 22));
    jdbNavField3.setMinimumSize(new Dimension(70, 22));
    jdbNavField3.setPreferredSize(new Dimension(70, 22));
    jdbNavField3.setColumnName("student_id");
    jdbNavField3.setDataSet(qSet_student_info);
    jdbTextField12.setColumnName("student_name");
    jdbTextField12.setDataSet(qSet_student_info);
    jdbTextField12.setText("jdbTextField11");
    jdbTextField12.setEditable(false);
    jdbTextField12.setPreferredSize(new Dimension(70, 22));
    jdbTextField12.setMinimumSize(new Dimension(70, 22));
    jdbTextField13.setColumnName("student_class");
    jdbTextField13.setDataSet(qSet_student_info);
    jdbTextField13.setColumns(0);
    jdbTextField13.setText("jdbTextField9");
    jdbTextField13.setEditable(false);
    jdbTextField13.setPreferredSize(new Dimension(70, 22));
    jdbTextField13.setEnabled(true);
    jdbTextField13.setDebugGraphicsOptions(0);
    jdbTextField14.setColumnName("student_sex");
    jdbTextField14.setDataSet(qSet_student_info);
    jdbTextField14.setText("jdbTextField10");
    jdbTextField14.setEditable(false);
    jdbTextField14.setPreferredSize(new Dimension(50, 22));
    jdbTextField14.setEnabled(true);
    jdbTable4.setToolTipText("");
    jdbTable4.setDataSet(qSet_gcheck);
    column21.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column21.setCaption("获奖记录号");
    column21.setColumnName("gcheck_id");
    column21.setDataType(com.borland.dx.dataset.Variant.INT);
    column21.setRowId(true);
    column21.setSchemaName("dbo");
    column21.setTableName("student_gcheck");
    column21.setVisible(com.borland.jb.util.TriStateProperty.DEFAULT);
    column21.setWidth(10);
    column21.setServerColumnName("gcheck_id");
    column21.setSqlType(4);
    column23.setCaption("学生姓名");
    column23.setColumnName("gcheck_name");
    column23.setDataType(com.borland.dx.dataset.Variant.STRING);
    column23.setPrecision(10);
    column23.setSchemaName("dbo");
    column23.setTableName("student_gcheck");
    column23.setVisible(com.borland.jb.util.TriStateProperty.DEFAULT);
    column23.setWidth(10);
    column23.setServerColumnName("gcheck_name");
    column23.setSqlType(1);
    column24.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column24.setCaption("获奖名称");
    column24.setColumnName("gcheck_title");
    column24.setDataType(com.borland.dx.dataset.Variant.STRING);
    column24.setPrecision(50);
    column24.setSchemaName("dbo");
    column24.setTableName("student_gcheck");
    column24.setWidth(10);
    column24.setServerColumnName("gcheck_title");
    column24.setSqlType(12);
    jPanel3.addFocusListener(new MainFrame_jPanel3_focusAdapter(this));
    jPanel4.setLayout(borderLayout12);
    jPanel4.setDebugGraphicsOptions(0);
    jPanel4.setVerifyInputWhenFocusTarget(true);
    jPanel20.setLayout(borderLayout13);
    jPanel21.setMinimumSize(new Dimension(100, 160));
    jPanel21.setPreferredSize(new Dimension(100, 110));
    jPanel21.setLayout(xYLayout2);
    jPanel22.setMinimumSize(new Dimension(100, 200));
    jPanel22.setPreferredSize(new Dimension(100, 130));
    jPanel22.setLayout(xYLayout3);
    jLabel21.setFont(new java.awt.Font("DialogInput", 1, 13));
    jLabel21.setText("*学号：");
    jLabel22.setText("*姓名：");
    jLabel23.setText("*班级：");
    jLabel24.setText("联系电话：");
    jLabel25.setText("*性别：");
    jLabel26.setText("出生年月：");
    jLabel27.setRequestFocusEnabled(true);
    jLabel27.setText("地址：");
    jButton7.setText("新增/修改");
    jButton7.addActionListener(new MainFrame_jButton7_actionAdapter(this));
    jLabel28.setFont(new java.awt.Font("Dialog", 1, 12));
    jLabel28.setText("*课程代号：");
    jLabel29.setText("*学时：");
    jLabel30.setText("任课教师：");
    jLabel31.setText("*课程名称：");
    jLabel32.setText("*学分：");
    jLabel33.setText("上课信息：");
    jLabel34.setFont(new java.awt.Font("DialogInput", 1, 15));
    jLabel34.setMinimumSize(new Dimension(88, 16));
    jLabel34.setText("可选课程基本信息");
    jLabel35.setFont(new java.awt.Font("DialogInput", 1, 15));
    jLabel35.setText("学生个人基本信息");
    jButton8.setText("新增/修改");
    jButton8.addActionListener(new MainFrame_jButton8_actionAdapter(this));
    jTextField1.setText("");
    jTextField2.setText("");
    jTextField3.setText("");
    jTextField4.setText("");
    jTextField6.setText("");
    jTextField7.setText("");
    jTextField8.setText("");
    jTextField9.setText("");
    jTextField10.setText("");
    jTextField11.setText("");
    jTextField12.setText("");
    qSet_student_info.setAccumulateResults(false);
    qSet_student_info.close();
    qSet_student_info.setQuery(new com.borland.dx.sql.dataset.QueryDescriptor(
        database1, "SELECT student_info.student_id,student_info.student_name,student_info.student_class,student_info.stud" +
        "ent_tel,student_info.student_sex,student_info.student_birthday,student_info.student_address " +
        "FROM student.dbo.student_info", null, true, Load.ALL));
    column8.setAlignment(com.borland.dx.text.Alignment.CENTER |
                         com.borland.dx.text.Alignment.MIDDLE);
    column8.setCalcType(com.borland.dx.dataset.CalcType.NO_CALC);
    column8.setCaption("学号");
    column8.setColumnName("student_id");
    column8.setDataType(com.borland.dx.dataset.Variant.STRING);
    column8.setPreferredOrdinal(0);
    column8.setEditable(false);
    column8.setWidth(10);
    column8.setServerColumnName("student_id");
    column8.setSqlType(0);
    column9.setAlignment(com.borland.dx.text.Alignment.CENTER |
                         com.borland.dx.text.Alignment.MIDDLE);
    column9.setCaption("姓名");
    column9.setColumnName("student_name");
    column9.setDataType(com.borland.dx.dataset.Variant.STRING);
    column9.setPreferredOrdinal(1);
    column9.setWidth(8);
    column9.setServerColumnName("student_name");
    column9.setSqlType(0);
    column11.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column11.setCaption("班级");
    column11.setColumnName("student_class");
    column11.setDataType(com.borland.dx.dataset.Variant.STRING);
    column11.setPreferredOrdinal(2);
    column11.setWidth(8);
    column11.setServerColumnName("student_class");
    column11.setSqlType(0);
    column14.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column14.setCaption("姓别");
    column14.setColumnName("student_sex");
    column14.setDataType(com.borland.dx.dataset.Variant.STRING);
    column14.setPreferredOrdinal(3);
    column14.setWidth(5);
    column14.setServerColumnName("student_sex");
    column14.setSqlType(0);
    column17.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column17.setCaption("出生年月");
    column17.setColumnName("student_birthday");
    column17.setDataType(com.borland.dx.dataset.Variant.STRING);
    column17.setPreferredOrdinal( -1);
    column17.setWidth(10);
    column17.setServerColumnName("student_birthday");
    column17.setSqlType(0);
    column26.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column26.setCaption("联系电话");
    column26.setColumnName("student_tel");
    column26.setDataType(com.borland.dx.dataset.Variant.STRING);
    column26.setPreferredOrdinal( -1);
    column26.setWidth(10);
    column26.setServerColumnName("student_tel");
    column26.setSqlType(0);
    column27.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column27.setCaption("家庭住址");
    column27.setColumnName("student_address");
    column27.setDataType(com.borland.dx.dataset.Variant.STRING);
    column27.setPreferredOrdinal( -1);
    column27.setServerColumnName("student_address");
    column27.setSqlType(0);
    qSet_coursecode.setQuery(new com.borland.dx.sql.dataset.QueryDescriptor(
        database1, "SELECT student_coursecode.course_code,student_coursecode.course_name,student_coursecode.course_period" +
        ",student_coursecode.course_credit,student_coursecode.course_teacher,student_coursecode.course_address" +
        " FROM student.dbo.student_coursecode", null, true, Load.ALL));
    column1.setAlignment(com.borland.dx.text.Alignment.CENTER |
                         com.borland.dx.text.Alignment.MIDDLE);
    column1.setCaption("课程代码");
    column1.setColumnName("course_code");
    column1.setDataType(com.borland.dx.dataset.Variant.STRING);
    column1.setPrecision(10);
    column1.setPreferredOrdinal(0);
    column1.setEditable(false);
    column1.setSchemaName("dbo");
    column1.setTableName("student_coursecode");
    column1.setWidth(10);
    column1.setServerColumnName("course_code");
    column1.setSqlType(12);
    column3.setAlignment(com.borland.dx.text.Alignment.CENTER |
                         com.borland.dx.text.Alignment.MIDDLE);
    column3.setCaption("课程名称");
    column3.setColumnName("course_name");
    column3.setDataType(com.borland.dx.dataset.Variant.STRING);
    column3.setPrecision(50);
    column3.setPreferredOrdinal(1);
    column3.setSchemaName("dbo");
    column3.setTableName("student_coursecode");
    column3.setWidth(13);
    column3.setServerColumnName("course_name");
    column3.setSqlType(12);
    column5.setAlignment(com.borland.dx.text.Alignment.CENTER |
                         com.borland.dx.text.Alignment.MIDDLE);
    column5.setCaption("课程学时");
    column5.setColumnName("course_period");
    column5.setDataType(com.borland.dx.dataset.Variant.INT);
    column5.setSchemaName("dbo");
    column5.setTableName("student_coursecode");
    column5.setWidth(10);
    column5.setServerColumnName("course_period");
    column5.setSqlType(4);
    column28.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column28.setCaption("课程学分");
    column28.setColumnName("course_credit");
    column28.setDataType(com.borland.dx.dataset.Variant.DOUBLE);
    column28.setPreferredOrdinal(2);
    column28.setSchemaName("dbo");
    column28.setTableName("student_coursecode");
    column28.setWidth(10);
    column28.setServerColumnName("course_credit");
    column28.setSqlType(6);
    column29.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column29.setCaption("任课教师");
    column29.setColumnName("course_teacher");
    column29.setDataType(com.borland.dx.dataset.Variant.STRING);
    column29.setPrecision(50);
    column29.setSchemaName("dbo");
    column29.setTableName("student_coursecode");
    column29.setWidth(10);
    column29.setServerColumnName("course_teacher");
    column29.setSqlType(12);
    column30.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column30.setCaption("上课信息");
    column30.setColumnName("course_address");
    column30.setDataType(com.borland.dx.dataset.Variant.STRING);
    column30.setPrecision(50);
    column30.setSchemaName("dbo");
    column30.setTableName("student_coursecode");
    column30.setWidth(15);
    column30.setServerColumnName("course_address");
    column30.setSqlType(12);
    column18.setColumnName("course_no");
    column18.setDataType(com.borland.dx.dataset.Variant.STRING);
    column18.setPrecision(10);
    column18.setSchemaName("dbo");
    column18.setTableName("student_course");
    column18.setWidth(5);
    column18.setServerColumnName("course_no");
    column18.setSqlType(12);
    column31.setColumnName("course_name");
    column31.setDataType(com.borland.dx.dataset.Variant.STRING);
    column31.setPrecision(50);
    column31.setSchemaName("dbo");
    column31.setTableName("student_course");
    column31.setWidth(10);
    column31.setServerColumnName("course_name");
    column31.setSqlType(12);
    column32.setCalcType(com.borland.dx.dataset.CalcType.NO_CALC);
    column32.setCaption("学生学号");
    column32.setColumnName("course_id");
    column32.setDataType(com.borland.dx.dataset.Variant.STRING);
    column32.setPrecision(10);
    column32.setSchemaName("dbo");
    column32.setTableName("student_course");
    column32.setWidth(5);
    column32.setServerColumnName("course_id");
    column32.setSqlType(12);
    column33.setColumnName("NewColumn1");
    column33.setDataType(com.borland.dx.dataset.Variant.STRING);
    column33.setPreferredOrdinal(3);
    column33.setServerColumnName("NewColumn1");
    column33.setSqlType(0);
    column15.setCaption("课程代号");
    column15.setColumnName("course_no");
    column15.setDataType(com.borland.dx.dataset.Variant.STRING);
    column15.setPrecision(10);
    column15.setSchemaName("dbo");
    column15.setTableName("student_course");
    column15.setServerColumnName("course_no");
    column15.setSqlType(12);
    column35.setCaption("学生学号");
    column35.setColumnName("course_id");
    column35.setDataType(com.borland.dx.dataset.Variant.STRING);
    column35.setPrecision(10);
    column35.setSchemaName("dbo");
    column35.setTableName("student_course");
    column35.setServerColumnName("course_id");
    column35.setSqlType(12);
    qSet_course.setColumns(new Column[] {column35, column15});
    column34.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column34.setCaption("记录号");
    column34.setColumnName("count_id");
    column34.setDataType(com.borland.dx.dataset.Variant.INT);
    column34.setPreferredOrdinal(0);
    column34.setEditable(false);
    column34.setWidth(5);
    column34.setServerColumnName("count_id");
    column34.setSqlType(0);
    column36.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column36.setCaption("学生学号");
    column36.setColumnName("course_id");
    column36.setDataType(com.borland.dx.dataset.Variant.STRING);
    column36.setPreferredOrdinal(1);
    column36.setEditable(false);
    column36.setWidth(10);
    column36.setServerColumnName("course_id");
    column36.setSqlType(0);
    column37.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column37.setCaption("学生姓名");
    column37.setColumnName("course_name");
    column37.setDataType(com.borland.dx.dataset.Variant.STRING);
    column37.setPreferredOrdinal(2);
    column37.setEditable(false);
    column37.setWidth(10);
    column37.setServerColumnName("course_name");
    column37.setSqlType(0);
    column38.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column38.setCaption("课程代号");
    column38.setColumnName("course_no");
    column38.setDataType(com.borland.dx.dataset.Variant.STRING);
    column38.setPreferredOrdinal(3);
    column38.setEditable(false);
    column38.setWidth(10);
    column38.setServerColumnName("course_no");
    column38.setSqlType(0);
    qSet_course.setQuery(new com.borland.dx.sql.dataset.QueryDescriptor(
        database1, "SELECT student_course.count_id,student_course.course_id,student_course.course_name,student_course.cou" +
        "rse_no ,student_course.course_score FROM student.dbo.student_course", null, true,
        Load.ALL));
    jdbTable3.setFont(new java.awt.Font("SansSerif", 0, 12));
    jdbTable3.setDataSet(qSet_course);
    jButton9.setText("刷新");
    jButton9.addActionListener(new MainFrame_jButton9_actionAdapter(this));
    qSet_student_info.setColumns(new Column[] {column8, column9, column11,
                                 column14, column26, column17, column27});
    qSet_coursecode.setColumns(new Column[] {column1, column3, column28,
                               column5, column29, column30});
    jTextArea1.setText("");
    jTextArea1.setLineWrap(true);
    jPanel23.setLayout(xYLayout4);
    jLabel36.setFont(new java.awt.Font("DialogInput", 1, 15));
    jLabel36.setText("班级基本信息");
    jLabel37.setFont(new java.awt.Font("Dialog", 3, 11));
    jLabel37.setRequestFocusEnabled(true);
    jLabel37.setText("注：带“*”号的为必填项");
    jLabel38.setText("*班级代号：");
    jLabel39.setText("*班级名称:");
    jLabel40.setText("*所属学院：");
    jLabel41.setText("*班主任：");
    jLabel42.setText("辅导员：");
    jTextField15.setEditable(false);
    jTextField15.setText("软微学院");
    jButton10.setText("新增/修改");
    jButton10.addActionListener(new MainFrame_jButton10_actionAdapter(this));
    jTextField14.setText("");
    jTextField17.setText("");
    jTextField13.setText("");
    jTextField16.setText("");
    jLabel2.setText("班级代号：");
    jdbNavField4.setMinimumSize(new Dimension(100, 22));
    jdbNavField4.setPreferredSize(new Dimension(100, 22));
    jdbNavField4.setText("jdbNavField4");
    jdbNavField4.setColumnName("class_id");
    jdbNavField4.setDataSet(qSet_class);
    jdbNavField4.addActionListener(new MainFrame_jdbNavField4_actionAdapter(this));
    jButton1.setText("刷新信息");
    jButton1.addActionListener(new MainFrame_jButton1_actionAdapter(this));
    column39.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column39.setCaption("班级代号");
    column39.setColumnName("class_id");
    column39.setDataType(com.borland.dx.dataset.Variant.STRING);
    column39.setPreferredOrdinal(0);
    column39.setEditable(false);
    column39.setRowId(true);
    column39.setServerColumnName("class_id");
    column39.setSqlType(0);
    column40.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column40.setCaption("班级名称");
    column40.setColumnName("class_name");
    column40.setDataType(com.borland.dx.dataset.Variant.STRING);
    column40.setPreferredOrdinal(1);
    column40.setEditable(false);
    column40.setWidth(13);
    column40.setServerColumnName("class_name");
    column40.setSqlType(0);
    column42.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column42.setCaption("班主任");
    column42.setColumnName("class_teacher");
    column42.setDataType(com.borland.dx.dataset.Variant.STRING);
    column42.setPreferredOrdinal(3);
    column42.setEditable(false);
    column42.setWidth(10);
    column42.setServerColumnName("class_teacher");
    column42.setSqlType(0);
    column43.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column43.setCaption("辅导员");
    column43.setColumnName("class_assistant");
    column43.setDataType(com.borland.dx.dataset.Variant.STRING);
    column43.setPreferredOrdinal(4);
    column43.setEditable(false);
    column43.setWidth(10);
    column43.setServerColumnName("class_assistant");
    column43.setSqlType(0);
    column44.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column44.setCaption("所属学院");
    column44.setColumnName("class_dep");
    column44.setDataType(com.borland.dx.dataset.Variant.STRING);
    column44.setPreferredOrdinal(5);
    column44.setEditable(false);
    column44.setServerColumnName("class_dep");
    column44.setSqlType(0);
    qSet_class.setQuery(new com.borland.dx.sql.dataset.QueryDescriptor(database1, "Select student_class.class_id, student_class.class_name, \nstudent_class.class_teacher, " +
      "student_class.class_assistant, student_class.class_dep from student_class\n", null, true, Load.ALL));
    jdbTable5.setFont(new java.awt.Font("SansSerif", 0, 12));
    jdbTable5.setDataSet(qSet_class);
    jdbTable5.addMouseListener(new MainFrame_jdbTable5_mouseAdapter(this));
    column45.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column45.setCaption("实践记录号");
    column45.setColumnName("p_id");
    column45.setDataType(com.borland.dx.dataset.Variant.INT);
    column45.setPreferredOrdinal(0);
    column45.setWidth(10);
    column45.setServerColumnName("p_id");
    column45.setSqlType(0);
    column46.setCaption("学生学号");
    column46.setColumnName("p_no");
    column46.setDataType(com.borland.dx.dataset.Variant.STRING);
    column46.setPreferredOrdinal(1);
    column46.setVisible(com.borland.jb.util.TriStateProperty.DEFAULT);
    column46.setServerColumnName("p_no");
    column46.setSqlType(0);
    column47.setCaption("学生姓名");
    column47.setColumnName("p_name");
    column47.setDataType(com.borland.dx.dataset.Variant.STRING);
    column47.setPreferredOrdinal(2);
    column47.setVisible(com.borland.jb.util.TriStateProperty.DEFAULT);
    column47.setServerColumnName("p_name");
    column47.setSqlType(0);
    column48.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column48.setCaption("实践时间");
    column48.setColumnName("p_time");
    column48.setDataType(com.borland.dx.dataset.Variant.STRING);
    column48.setPreferredOrdinal(3);
    column48.setVisible(com.borland.jb.util.TriStateProperty.DEFAULT);
    column48.setWidth(10);
    column48.setServerColumnName("p_time");
    column48.setSqlType(0);
    column49.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column49.setCaption("实践地点");
    column49.setColumnName("p_title");
    column49.setDataType(com.borland.dx.dataset.Variant.STRING);
    column49.setPreferredOrdinal(4);
    column49.setVisible(com.borland.jb.util.TriStateProperty.DEFAULT);
    column49.setWidth(10);
    column49.setServerColumnName("p_title");
    column49.setSqlType(0);
    column50.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column50.setCaption("具体说明");
    column50.setColumnName("p_disc");
    column50.setDataType(com.borland.dx.dataset.Variant.STRING);
    column50.setPreferredOrdinal(5);
    column50.setWidth(25);
    column50.setServerColumnName("p_disc");
    column50.setSqlType(0);
    qSet_practice.setColumns(new Column[] {column45, column46, column47,
                             column48, column49, column50});
    qSet_practice.setQuery(new com.borland.dx.sql.dataset.QueryDescriptor(
        database1, "SELECT student_practice.p_id,student_practice.p_no,student_practice.p_name,student_practice.p_time,st" +
        "udent_practice.p_title,student_practice.p_disc FROM student.dbo.student_practice", null, true,
        Load.ALL));
    jdbTable6.setDataSet(qSet_practice);
    jPanel8.setMinimumSize(new Dimension(10, 160));
    jPanel8.setPreferredSize(new Dimension(10, 250));
    jPanel8.setLayout(xYLayout6);
    jLabel3.setFont(new java.awt.Font("SansSerif", 1, 11));
    jLabel3.setText("注：可以由学生学号、姓名或课程代号快速定位和查询成绩，录入或修改成绩后点击保存修改。");
    jLabel4.setText("记录号：");
    jButton2.setText("保存修改");
    jButton2.addActionListener(new MainFrame_jButton2_actionAdapter(this));
    column52.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column52.setCaption("学生学号");
    column52.setColumnName("course_id");
    column52.setDataType(com.borland.dx.dataset.Variant.STRING);
    column52.setPreferredOrdinal(1);
    column52.setEditable(false);
    column52.setWidth(10);
    column52.setServerColumnName("course_id");
    column52.setSqlType(0);
    column54.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column54.setCaption("课程代号");
    column54.setColumnName("course_no");
    column54.setDataType(com.borland.dx.dataset.Variant.STRING);
    column54.setPreferredOrdinal(3);
    column54.setEditable(false);
    column54.setWidth(10);
    column54.setServerColumnName("course_no");
    column54.setSqlType(0);
    jLabel5.setText("学生学号：");
    jLabel6.setText("学生姓名：");
    jLabel7.setText("课程代号：");
    jButton5.setText("刷新");
    jButton5.addActionListener(new MainFrame_jButton5_actionAdapter(this));
    jdbNavField6.setText("jdbNavField6");
    jdbNavField6.setColumnName("course_id");
    jdbNavField6.setDataSet(qSet_course);
    jdbNavField7.setText("jdbNavField7");
    jdbNavField7.setColumnName("course_name");
    jdbNavField7.setDataSet(qSet_course);
    jdbNavField8.setText("jdbNavField8");
    jdbNavField8.setColumnName("course_no");
    jdbNavField8.setDataSet(qSet_course);
    //qSet_jiangli.setColumns(new Column[] {column24, column23, column21});
    column20.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column20.setCaption("获奖记录号");
    column20.setColumnName("gcheck_id");
    column20.setDataType(com.borland.dx.dataset.Variant.INT);
    column20.setPreferredOrdinal(0);
    column20.setWidth(10);
    column20.setServerColumnName("gcheck_id");
    column20.setSqlType(0);
    column22.setCaption("学生学号");
    column22.setColumnName("gcheck_no");
    column22.setDataType(com.borland.dx.dataset.Variant.STRING);
    column22.setPreferredOrdinal(1);
    column22.setVisible(com.borland.jb.util.TriStateProperty.DEFAULT);
    column22.setServerColumnName("gcheck_no");
    column22.setSqlType(0);
    column25.setCaption("学生姓名");
    column25.setColumnName("gcheck_name");
    column25.setDataType(com.borland.dx.dataset.Variant.STRING);
    column25.setPreferredOrdinal(2);
    column25.setVisible(com.borland.jb.util.TriStateProperty.DEFAULT);
    column25.setServerColumnName("gcheck_name");
    column25.setSqlType(0);
    column56.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column56.setCaption("获奖时间");
    column56.setColumnName("gcheck_time");
    column56.setDataType(com.borland.dx.dataset.Variant.STRING);
    column56.setPreferredOrdinal(3);
    column56.setWidth(10);
    column56.setServerColumnName("gcheck_time");
    column56.setSqlType(0);
    column57.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column57.setCaption("获奖名称");
    column57.setColumnName("gcheck_title");
    column57.setDataType(com.borland.dx.dataset.Variant.STRING);
    column57.setPreferredOrdinal(4);
    column57.setWidth(10);
    column57.setServerColumnName("gcheck_title");
    column57.setSqlType(0);
    column58.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column58.setCaption("具体说明");
    column58.setColumnName("gcheck_disc");
    column58.setDataType(com.borland.dx.dataset.Variant.STRING);
    column58.setPreferredOrdinal(5);
    column58.setWidth(25);
    column58.setServerColumnName("gcheck_disc");
    column58.setSqlType(0);
    qSet_gcheck.setColumns(new Column[] {column20, column22, column25, column56,
                           column57, column58});
    qSet_gcheck.setQuery(new com.borland.dx.sql.dataset.QueryDescriptor(
        database1, "SELECT student_gcheck.gcheck_id,student_gcheck.gcheck_no,student_gcheck.gcheck_name,student_gcheck.gc" +
        "heck_time,student_gcheck.gcheck_title,student_gcheck.gcheck_disc " +
        "FROM student.dbo.student_gcheck", null, true, Load.ALL));
    jLabel18.setText("*获奖时间：");
    jLabel19.setText("*获奖名称：");
    jLabel20.setText("具体说明：");
    jLabel43.setText("*实践时间：");
    jLabel44.setText("*实践地点：");
    jLabel45.setText("具体说明：");
    jButton6.setText("新增/修改");
    jButton6.addActionListener(new MainFrame_jButton6_actionAdapter(this));
    jButton11.setText("删除记录");
    jButton11.addActionListener(new MainFrame_jButton11_actionAdapter(this));
    jButton12.setText("新增/修改");
    jButton12.addActionListener(new MainFrame_jButton12_actionAdapter(this));
    jTextField18.setText("");
    jTextField19.setText("");
    jTextField20.setText("");
    jTextField21.setText("");
    jTextField22.setText("");
    jTextField23.setText("");
    jButton13.setText("删除记录");
    jButton13.addActionListener(new MainFrame_jButton13_actionAdapter(this));
    column51.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column51.setCaption("成绩");
    column51.setColumnName("course_score");
    column51.setDataType(com.borland.dx.dataset.Variant.STRING);
    column51.setPreferredOrdinal(4);
    column51.setWidth(10);
    column51.setServerColumnName("NewColumn1");
    column51.setSqlType(0);
    qSet_course.setColumns(new Column[] {column34, column36, column37, column38,
                           column51});
    jdbTable7.setDataSet(qSet_course);
    jdbTextField1.setColumnName("course_score");
    jdbTextField1.setDataSet(qSet_course);
    jLabel46.setText("成绩：");
    jLabel47.setText("在此输入课程代号可以查询该门课程不及格的学生信息:");
    jButton14.setText("查询");
    jButton14.addActionListener(new MainFrame_jButton14_actionAdapter(this));
    jTextField24.setText("");
    column53.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column53.setCaption("记录号");
    column53.setColumnName("count_id");
    column53.setDataType(com.borland.dx.dataset.Variant.INT);
    column53.setPreferredOrdinal(0);
    column53.setWidth(5);
    column53.setServerColumnName("NewColumn1");
    column53.setSqlType(0);
    column55.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column55.setCaption("学生学号");
    column55.setColumnName("course_id");
    column55.setDataType(com.borland.dx.dataset.Variant.STRING);
    column55.setPreferredOrdinal(1);
    column55.setWidth(10);
    column55.setServerColumnName("course_id");
    column55.setSqlType(0);
    column59.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column59.setCaption("学生姓名");
    column59.setColumnName("course_name");
    column59.setDataType(com.borland.dx.dataset.Variant.STRING);
    column59.setPreferredOrdinal(2);
    column59.setWidth(10);
    column59.setServerColumnName("course_name");
    column59.setSqlType(0);
    column60.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column60.setCaption("成绩");
    column60.setColumnName("course_score");
    column60.setDataType(com.borland.dx.dataset.Variant.STRING);
    column60.setPreferredOrdinal(5);
    column60.setWidth(10);
    column60.setServerColumnName("course_score");
    column60.setSqlType(0);
    jdbTable8.setDataSet(qSet_fail);
    column61.setAlignment(com.borland.dx.text.Alignment.CENTER |
                          com.borland.dx.text.Alignment.MIDDLE);
    column61.setCaption("班级代号");
    column61.setColumnName("student_class");
    column61.setDataType(com.borland.dx.dataset.Variant.STRING);
    column61.setPreferredOrdinal(3);
    column61.setServerColumnName("student_class");
    column61.setSqlType(0);
    qSet_fail.setColumns(new Column[] {column53, column55, column59, column61,
                         column60});
    jButton15.setText("退出系统");
    jButton15.addActionListener(new MainFrame_jButton15_actionAdapter(this));
    jLabel48.setText("（班级代号请在基本信息界面中选择）");

    jRadioButton1.setText("男");
    jRadioButton2.setText("女");
    qSet_class.setColumns(new Column[] {column39, column40, column42, column43, column44});
    jPanel8.add(tableScrollPane7,    new XYConstraints(-2, 96, 399, 122));
    jPanel8.add(jLabel4, new XYConstraints(7, 27, 73, 24));
    jPanel8.add(jLabel6, new XYConstraints(179, 66, 73, 24));
    jPanel8.add(jdbNavField7, new XYConstraints(247, 65, 70, 26));
    jPanel8.add(jLabel5, new XYConstraints(178, 29, 73, 24));
    jPanel8.add(jdbNavField6, new XYConstraints(247, 29, 71, 24));
    jPanel8.add(jLabel7, new XYConstraints(7, 65, 73, 24));
    jPanel8.add(jdbNavField8, new XYConstraints(90, 67, 71, 25));
    tableScrollPane7.getViewport().add(jdbTable7, null);
    jTabbedPane1.add(jPanel1,    "基本信息管理");
    jPanel1.add(jPanel5, BorderLayout.CENTER);
    jPanel5.add(jdbNavToolBar1, BorderLayout.SOUTH);
    jPanel5.add(jPanel6, BorderLayout.NORTH);
    jPanel6.add(jPanel7, BorderLayout.NORTH);
    jPanel7.add(jLabel1, null);
    jTabbedPane1.add(jPanel2,   "选课信息管理");
    jTabbedPane1.add(jPanel3,   "其他信息管理");
    jPanel3.add(jPanel13, BorderLayout.NORTH);
    jPanel13.add(jLabel14, null);
    jPanel13.add(jdbNavField3, null);
    jPanel13.add(jLabel16, null);
    jPanel13.add(jdbTextField12, null);
    jPanel13.add(jLabel17, null);
    jPanel13.add(jdbTextField13, null);
    jPanel13.add(jLabel15, null);
    jPanel3.add(jPanel15, BorderLayout.CENTER);
    jTabbedPane1.add(jPanel4, "学生成绩管理");
    jTabbedPane1.add(jPanel20, "新信息录入");
    jPanel20.add(jPanel22, BorderLayout.SOUTH);
    jPanel22.add(jLabel34, new XYConstraints(2, 11, 160, 21));
    jPanel22.add(jTextField8, new XYConstraints(247, 11, 87, 28));
    jPanel22.add(jTextField11, new XYConstraints(442, 9, 86, 28));
    jPanel22.add(jLabel32, new XYConstraints(8, 47, 51, 28));
    jPanel22.add(jLabel29, new XYConstraints(9, 93, 51, 26));
    jPanel22.add(jButton8,   new XYConstraints(450, 99, 90, 28));
    jPanel22.add(jTextArea1, new XYConstraints(246, 48, 92, 77));
    jPanel22.add(jTextField10, new XYConstraints(443, 56, 85, 28));
    jPanel22.add(jLabel28, new XYConstraints(154, 9, 79, 26));
    jPanel22.add(jLabel31, new XYConstraints(365, 9, 68, 28));
    jPanel22.add(jLabel30, new XYConstraints(365, 60, 63, 24));
    jPanel22.add(jLabel33, new XYConstraints(166, 72, 62, 28));
    jPanel22.add(jTextField12, new XYConstraints(74, 48, 63, 25));
    jPanel22.add(jTextField9, new XYConstraints(73, 96, 64, 25));
    jPanel20.add(jPanel21, BorderLayout.NORTH);
    jPanel21.add(jLabel37, new XYConstraints(146, 5, 144, 24));
    jPanel21.add(jLabel36, new XYConstraints(1, 3, 120, 26));
    jPanel21.add(jLabel42,  new XYConstraints(192, 76, 60, 28));
    jPanel21.add(jTextField17,   new XYConstraints(274, 75, 71, 24));
    jPanel21.add(jLabel41, new XYConstraints(7, 74, 59, 28));
    jPanel21.add(jTextField16,   new XYConstraints(79, 76, 71, -1));
    jPanel21.add(jTextField14,   new XYConstraints(273, 44, 71, 23));
    jPanel21.add(jButton19, new XYConstraints(430, 2, 83, 27));
    jPanel21.add(jLabel38, new XYConstraints(5, 43, 70, 26));
    jPanel21.add(jTextField13,    new XYConstraints(80, 48, 71, 21));
    jPanel21.add(jTextField15,  new XYConstraints(452, 40, 71, 28));
    jPanel21.add(jLabel40, new XYConstraints(374, 40, -1, 28));
    jPanel21.add(jButton10,    new XYConstraints(451, 78, 89, 27));
    jPanel21.add(jLabel39, new XYConstraints(187, 43, 59, 26));
    jPanel21.add(jLabel55,            new XYConstraints(3, 24, 342, 26));
    jPanel20.add(jPanel23, BorderLayout.WEST);
    jPanel23.add(jLabel35, new XYConstraints(2, 1, -1, -1));
    jPanel2.add(jPanel9, BorderLayout.NORTH);
    jPanel9.add(jLabel8, null);
    jPanel9.add(jdbNavField2, null);
    jPanel9.add(jLabel9, null);
    jPanel9.add(jdbTextField11, null);
    jPanel9.add(jLabel10, null);
    jPanel9.add(jdbTextField9, null);
    jPanel9.add(jLabel11, null);
    jPanel9.add(jdbTextField10, null);
    jPanel9.add(jButton16, null);
    jPanel2.add(jdbNavToolBar2, BorderLayout.SOUTH);
    jPanel2.add(jPanel10, BorderLayout.WEST);
    jPanel10.add(jLabel12, BorderLayout.NORTH);
    jPanel10.add(tableScrollPane2, BorderLayout.CENTER);
    tableScrollPane2.getViewport().add(jdbTable2, null);
    jPanel2.add(jPanel11, BorderLayout.EAST);
    jPanel11.add(jLabel13, BorderLayout.NORTH);
    jPanel11.add(tableScrollPane3, BorderLayout.CENTER);
    tableScrollPane3.getViewport().add(jdbTable3, null);
    jPanel2.add(jPanel12, BorderLayout.CENTER);
    jPanel7.add(jdbNavField1, null);
    jPanel7.add(jLabel2, null);
    jPanel7.add(jdbNavField4, null);
    jPanel7.add(jButton1, null);
    jPanel7.add(jButton15, null);
    jPanel6.add(tableScrollPane5, BorderLayout.CENTER);
    jPanel5.add(tableScrollPane1, BorderLayout.CENTER);
    tableScrollPane1.getViewport().add(jdbTable1, null);
    tableScrollPane5.getViewport().add(jdbTable5, null);
    jPanel13.add(jdbTextField14, null);
    jPanel13.add(jButton17, null);
    jPanel12.add(jButton9, new XYConstraints(9, 20, 59, 30));
    jPanel12.add(jButton3, new XYConstraints(10, 62, -1, 31));
    jPanel12.add(jButton4, new XYConstraints(10, 107, 59, 33));
    jPanel12.add(jLabel51,  new XYConstraints(0, 162, 87, 19));
    jPanel12.add(jLabel53,     new XYConstraints(1, 212, 96, -1));
    jPanel12.add(jLabel52,  new XYConstraints(1, 188, 85, 18));
    jPanel12.add(jLabel54,  new XYConstraints(1, 234, 87, 20));
    jPanel4.add(jPanel8, BorderLayout.CENTER);
    jPanel15.add(tableScrollPane6, new XYConstraints( -2, 214, 541, 106));
    jPanel15.add(jTextField22,  new XYConstraints(202, 186, 94, 24));
    jPanel15.add(jLabel44, new XYConstraints(139, 187, 70, 23));
    jPanel15.add(jTextField21, new XYConstraints(62, 187, 66, 24));
    jPanel15.add(jLabel43, new XYConstraints(0, 188, 70, 23));
    jPanel15.add(tableScrollPane4,    new XYConstraints(-3, 54, 542, 96));
    jPanel15.add(jLabel18, new XYConstraints(0, 24, 75, 27));
    jPanel15.add(jLabel19, new XYConstraints(139, 27, 69, 23));
    jPanel15.add(jTextField18, new XYConstraints(65, 27, 67, 23));
    jPanel15.add(jTextField19,   new XYConstraints(201, 28, 98, 23));
    jPanel15.add(jButton12,      new XYConstraints(138, 159, 90, 24));
    jPanel15.add(jButton6,        new XYConstraints(136, 0, 90, -1));
    jPanel15.add(jTextField20,    new XYConstraints(373, 26, 167, 24));
    jPanel15.add(jLabel20,  new XYConstraints(312, 27, 69, 24));
    jPanel15.add(jLabel49, new XYConstraints(3, 155, 134, 20));
    jPanel15.add(jTextField23,    new XYConstraints(369, 186, 167, 24));
    jPanel15.add(jLabel45,    new XYConstraints(308, 187, 66, 23));
    jPanel15.add(jButton11,      new XYConstraints(248, 0, 84, -1));
    jPanel15.add(jButton13,    new XYConstraints(245, 158, 84, 26));
    jPanel15.add(jLabel50,  new XYConstraints(9, 0, 134, 18));
    tableScrollPane4.getViewport().add(jdbTable4, null);
    tableScrollPane6.getViewport().add(jdbTable6, null);
    jPanel8.add(tableScrollPane8,    new XYConstraints(-3, 251, 399, 120));
    jPanel8.add(jLabel47, new XYConstraints(175, 226, 297, 19));
    jPanel8.add(jLabel3,  new XYConstraints(4, 0, 546, 30));
    jPanel8.add(jButton18, new XYConstraints(453, 27, 83, 27));
    jPanel8.add(jButton5,  new XYConstraints(345, 29, 68, 27));
    jPanel8.add(jLabel46,      new XYConstraints(431, 95, 47, 27));
    jPanel8.add(jdbTextField1,  new XYConstraints(477, 95, 54, 26));
    jPanel8.add(jButton2,  new XYConstraints(443, 134, 89, 32));
    jPanel8.add(jTextField24, new XYConstraints(473, 224, 59, 25));
    jPanel8.add(jButton14, new XYConstraints(473, 269, 59, 26));
    jPanel8.add(jdbStatusLabel1,     new XYConstraints(397, 175, 172, 32));
    jPanel8.add(jdbTextField2,   new XYConstraints(90, 29, 70, 26));
    tableScrollPane8.getViewport().add(jdbTable8, null);
    jPanel23.add(jLabel24, new XYConstraints(6, 88, 69, 26));
    jPanel23.add(jTextField4, new XYConstraints(81, 87, 77, 25));
    jPanel23.add(jTextField7, new XYConstraints(245, 87, 167, 25));
    jPanel23.add(jLabel23, new XYConstraints(6, 51, 55, 26));
    jPanel23.add(jTextField3, new XYConstraints(81, 52, 75, 25));
    jPanel23.add(jLabel48, new XYConstraints(1, 27, 205, 25));
    jPanel23.add(jLabel25, new XYConstraints(186, 51, 55, 26));
    jPanel23.add(jLabel27, new XYConstraints(189, 87, 55, 26));
    jPanel23.add(jRadioButton1, new XYConstraints(246, 58, 45, 16));
    jPanel23.add(jLabel26, new XYConstraints(370, 52, -1, 26));
    jPanel23.add(jButton7,    new XYConstraints(450, 84, 89, 28));
    jPanel23.add(jTextField6, new XYConstraints(450, 50, 77, 25));
    jPanel23.add(jTextField1, new XYConstraints(273, 12, 77, 25));
    jPanel23.add(jLabel21, new XYConstraints(205, 16, 55, -1));
    jPanel23.add(jLabel22, new XYConstraints(375, 12, 55, 26));
    jPanel23.add(jTextField2, new XYConstraints(450, 13, 77, 25));
    jPanel23.add(jRadioButton2,  new XYConstraints(298, 59, 41, 14));
    this.getContentPane().add(jTabbedPane1,
                              new PaneConstraints("jTabbedPane1",
                                                  "jTabbedPane1",
                                                  PaneConstraints.ROOT, 0.5f));
  }

  void jButton1_actionPerformed(ActionEvent e) {
    qSet_student_info.refresh();
    qSet_class.refresh();
  }

  void jButton3_actionPerformed(ActionEvent e) {
    if (qSet_student_info.isEmpty()) {
      return;
    }
    if (qSet_coursecode.isEmpty()) {
      return;
    }
    if (!qSet_coursecode.isOpen()) {
      qSet_coursecode.open();
    }
    if (!qSet_course.isOpen()) {
      qSet_course.open();
    }
    try {

      Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
      String url = "jdbc:microsoft:sqlserver://localhost:1433;" +
          "DatabaseName=student";
      Connection conn = DriverManager.getConnection(url, "sa", "22114602");
      Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,
                                            ResultSet.CONCUR_UPDATABLE);

      String SQL = "select * from student_course where course_id = '" +
          qSet_student_info.getString("student_id") + "' and course_no ='" +
          qSet_coursecode.getString("course_code") + "'";
      ResultSet rs = stmt.executeQuery(SQL); //查找该学生是否已经选过该课程
      if (rs.next()) {
        JOptionPane.showConfirmDialog(null, "该学生已经选过此门课程，不能重选！",
                                      "Student Management System"
                                      , JOptionPane.OK_CANCEL_OPTION,
                                      JOptionPane.WARNING_MESSAGE);

      } else{
       //先排序以免记录号出现重复
        qSet_course.setSort(new SortDescriptor(new String[]{"count_id"}));

        qSet_course.last();
        int i = qSet_course.getInt("count_id");

        qSet_course.insertRow(true);
        qSet_course.setInt("count_id", i + 1);
        qSet_course.setString("course_id",
                              qSet_student_info.getString("student_id"));
        qSet_course.setString("course_name",
                              qSet_student_info.getString("student_name"));
        qSet_course.setString("course_no",
                              qSet_coursecode.getString("course_code"));
        qSet_course.post();
        qSet_course.saveChanges(qSet_course);
        qSet_course.refresh();
      }

    }
    catch (Exception ex) {
      ex.toString();
    }
  }

  void jButton4_actionPerformed(ActionEvent e) {
    if (!qSet_course.isOpen()) {
      qSet_course.open();
    }
    if (qSet_course.isEmpty()) {
      return;
    }
    if (qSet_course.getString("course_score").equals("")) {

      qSet_course.deleteRow();
      qSet_course.saveChanges(qSet_course);
    }
    else {
      JOptionPane.showConfirmDialog(null, "该门课程已经被登录过成绩，不能删除该条选课记录！",
                                    "Student Management System"
                                    , JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.WARNING_MESSAGE);
      return;

    }

  }

  void qSet_course_filterRow(ReadRow row, RowFilterResponse response) {
    if (row.getString("course_id").equals(qSet_student_info.getString(
        "student_id"))) {
      response.add();
    }
    else {
      response.ignore();
    }
  }

  void jPanel2_focusGained(FocusEvent e) {
    qSet_course.refilter();
  }

  void qSet_student_info_navigated(NavigationEvent e) {
    qSet_course.refilter();
  }

  void jPanel3_focusGained(FocusEvent e) {

  }

  void jButton7_actionPerformed(ActionEvent e) {
    addStuInfo();
  }

  public void addStuInfo() {

    String id = jTextField1.getText();
    String name = jTextField2.getText();
    String classid = jTextField3.getText();
    String telnum = jTextField4.getText();
    String sex = null;
    String birthday = jTextField6.getText();
    String address = jTextField7.getText();
    if (jRadioButton1.isSelected()) {
      sex = "男";
    }
    if (jRadioButton2.isSelected()) {
      sex = "女";

    }
    if (id.equals("") || name.equals("") || classid.equals("") || sex.equals("")) {

      JOptionPane.showConfirmDialog(null, "必填项未完整输入或有错误，请重试！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.WARNING_MESSAGE);
      return;
    }

    if (jRadioButton1.isSelected()) {
      sex = "男";
    }
    if (jRadioButton2.isSelected()) {
      sex = "女";
    }

    if (omitspace(id).equals("") || omitspace(name).equals("") ||
       omitspace(classid).equals("") ) {

     JOptionPane.showConfirmDialog(null, "请不要单独输入空格作为必填项！",
                                   "Student Management System",
                                   JOptionPane.OK_CANCEL_OPTION,
                                   JOptionPane.WARNING_MESSAGE);
     return;
   }

    try {
      Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
      String url = "jdbc:microsoft:sqlserver://localhost:1433;" +
          "DatabaseName=student";
      Connection conn = DriverManager.getConnection(url, "sa", "22114602");
      Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,
                                            ResultSet.CONCUR_UPDATABLE);

      String SQL = "select * from student_info where Student_ID = '" +
          id + "'";
      ResultSet rs = stmt.executeQuery(SQL); //查找是否存在该学生的记录

      //如果已经存在该学生的记录则更新，如果不存在则插入新的记录
      if (rs.next()) {
        int i = JOptionPane.showConfirmDialog(null, "该学生记录已经存在，是否更新？",
                                              "Student Management System",
                                              JOptionPane.YES_NO_OPTION,
                                              JOptionPane.QUESTION_MESSAGE);
        if (i == 1 || i == 2) {
          return;
        }

        SQL = "update student_info set Student_Name='" + name +
            "',"
            + " Student_Class ='" + classid + "',"
            + " Student_Tel ='" + telnum + "',"
            + " Student_Sex ='" + sex + "',"
            + " Student_Birthday ='" + birthday + "',"
            + " Student_Address ='" + address + "'"
            + " where Student_ID = '" + id + "'";
        stmt.execute(SQL);
        JOptionPane.showConfirmDialog(null, "学生记录已经成功更新！",
                                      "Student Management System"
                                      , JOptionPane.OK_CANCEL_OPTION,
                                      JOptionPane.INFORMATION_MESSAGE);
      }
      else {
        SQL =
            "insert student_info(Student_ID,Student_Name,Student_Class, Student_Tel,Student_Sex,Student_Birthday,Student_Address) "
            + " values('" + id + "', '"
            + name + "','"
            + classid + "','"
            + telnum + "','"
            + sex + "','"
            + birthday + "','"
            + address + "')";
        stmt.execute(SQL);
        JOptionPane.showConfirmDialog(null, "新学生记录已经成功添加！",
                                      "Student Management System",
                                      JOptionPane.OK_CANCEL_OPTION,
                                      JOptionPane.INFORMATION_MESSAGE);
      }

      rs.close();
      stmt.close();
      conn.close();

      jTextField1.setText("");
       jTextField2.setText("");
       jTextField4.setText("");
       jTextField6.setText("");
       jTextField7.setText("");

    }
    catch (SQLException se) {
      se.printStackTrace();
    }
    catch (ClassNotFoundException ce) {
      ce.printStackTrace();
    }

  }

  void jButton8_actionPerformed(ActionEvent e) {
    addCourseCode();
  }

  public void addCourseCode() {

    if (jTextField8.getText().equals("") || jTextField11.getText().equals("") ||
        jTextField9.getText().equals("") || jTextField12.getText().equals("")) {

      JOptionPane.showConfirmDialog(null, "必填项未完整输入，请重试！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.WARNING_MESSAGE);
      return;
    }

    String code = jTextField8.getText();
    String name = jTextField11.getText();
    String period = jTextField9.getText();
    String credit = jTextField12.getText();
    String teacher = jTextField10.getText();
    String address = jTextArea1.getText();

    if (omitspace(code).equals("") || omitspace(name).equals("") ||
        omitspace(credit).equals("") || omitspace(period).equals("") ) {

      JOptionPane.showConfirmDialog(null, "请不要单独输入空格作为必填项！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.WARNING_MESSAGE);
      return;
    }


    if(!qSet_coursecode.isOpen()) {
      qSet_coursecode.isOpen();
    }
    try {
      Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
      String url = "jdbc:microsoft:sqlserver://localhost:1433;" +
          "DatabaseName=student";
      Connection conn = DriverManager.getConnection(url, "sa", "22114602");
      Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,
                                            ResultSet.CONCUR_UPDATABLE);

      String SQL = "select * from student_coursecode where Course_Code = '" +
          code + "'";
      ResultSet rs = stmt.executeQuery(SQL); //查找是否存在该课程的记录

      //如果已经存在该课程的记录则更新，如果不存在则插入新的记录

      if (rs.next()) {
        int i = JOptionPane.showConfirmDialog(null, "该课程记录已经存在，是否更新？",
                                              "Student Management System",
                                              JOptionPane.YES_NO_OPTION,
                                              JOptionPane.QUESTION_MESSAGE);
        if (i == 1 || i == 2) {
          return;
        }

        SQL = "update student_coursecode set Course_Name='" + name +
            "',"
            + " Course_period =" + Integer.parseInt(period) + ","
            + " Course_credit =" + Float.parseFloat(credit) + ","
            + " Course_teacher ='" + teacher + "',"
            + " Course_Address ='" + address + "'"
            + " where Course_Code = '" + code + "'";
        stmt.execute(SQL);
        JOptionPane.showConfirmDialog(null, "课程记录已经成功更新！",
                                      "Student Management System"
                                      , JOptionPane.OK_CANCEL_OPTION,
                                      JOptionPane.INFORMATION_MESSAGE);
      }
      else {
        SQL =
            "insert student_coursecode(Course_code,Course_Name,Course_period, Course_credit,Course_teacher,Course_Address) "
            + " values('" + code + "', '"
            + name + "',"
            + Integer.parseInt(period) + ","
            + Float.parseFloat(credit) + ",'"
            + teacher + "','"
            + address + "')";
        stmt.execute(SQL);
        JOptionPane.showConfirmDialog(null, "新课程记录已经成功添加！",
                                      "Student Management System",
                                      JOptionPane.OK_CANCEL_OPTION,
                                      JOptionPane.INFORMATION_MESSAGE);
      }

      rs.close();
      stmt.close();
      conn.close();

      jTextField8.setText("");
      jTextField9.setText("");
      jTextField10.setText("");
      jTextField11.setText("");
      jTextField12.setText("");
      jTextArea1.setText("");
    }
    catch (SQLException se) {
      se.printStackTrace();
    }
    catch (ClassNotFoundException ce) {
      ce.printStackTrace();
    }

  }

  void jButton9_actionPerformed(ActionEvent e) {
    qSet_coursecode.refresh();

  }

  void jButton10_actionPerformed(ActionEvent e) {
    addClass();
  }

  public void addClass() {

    String id = jTextField13.getText();
    String name = jTextField14.getText();
    String dep = jTextField15.getText();
    String teacher = jTextField16.getText();
    String assistant = jTextField17.getText();

    if (id.equals("") || name.equals("") || teacher.equals("")) {

      JOptionPane.showConfirmDialog(null, "必填项未完整输入，请重试！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.WARNING_MESSAGE);
      return;
    }

    if (omitspace(id).equals("") || omitspace(name).equals("") ||
       omitspace(dep).equals("") ||
       omitspace(teacher).equals("") ) {

     JOptionPane.showConfirmDialog(null, "请不要单独输入空格作为必填项！",
                                   "Student Management System",
                                   JOptionPane.OK_CANCEL_OPTION,
                                   JOptionPane.WARNING_MESSAGE);
     return;
   }

    try {
      Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
      String url = "jdbc:microsoft:sqlserver://localhost:1433;" +
          "DatabaseName=student";
      Connection conn = DriverManager.getConnection(url, "sa", "22114602");
      Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,
                                            ResultSet.CONCUR_UPDATABLE);

      String SQL = "select * from student_class where Class_ID = '" +
          id + "'";
      ResultSet rs = stmt.executeQuery(SQL); //查找是否存在该班级的记录

      //如果已经存在该班级的记录则更新，如果不存在则插入新的记录
      if (rs.next()) {
        int i = JOptionPane.showConfirmDialog(null, "该班级记录已经存在，是否更新？",
                                              "Student Management System",
                                              JOptionPane.YES_NO_OPTION,
                                              JOptionPane.QUESTION_MESSAGE);
        if (i == 1 || i == 2) {
          return;
        }
        SQL = "update student_class set Class_Name='" + name +
            "',"
            + " Class_Dep ='" + dep + "',"
            + " Class_Teacher ='" + teacher + "',"
            + " Class_Assistant ='" + assistant + "'"
            + " where Class_ID = '" + id + "'";
        stmt.execute(SQL);
        JOptionPane.showConfirmDialog(null, "班级记录已经成功更新！",
                                      "Student Management System"
                                      , JOptionPane.OK_CANCEL_OPTION,
                                      JOptionPane.INFORMATION_MESSAGE);

      }
      else {
        SQL =
            "insert student_class(Class_ID,Class_Name,Class_Dep,Class_Teacher,Class_Assistant) "
            + " values('" + id + "', '"
            + name + "','"
            + dep + "','"
            + teacher + "','"
            + assistant + "')";
        stmt.execute(SQL);
        JOptionPane.showConfirmDialog(null, "新班级记录已经成功添加！",
                                      "Student Management System",
                                      JOptionPane.OK_CANCEL_OPTION,
                                      JOptionPane.INFORMATION_MESSAGE);
      }

      rs.close();
      stmt.close();
      conn.close();

      jTextField13.setText("");
       jTextField14.setText("");
       jTextField16.setText("");
       jTextField17.setText("");

    }
    catch (SQLException se) {
      se.printStackTrace();
    }
    catch (ClassNotFoundException ce) {
      ce.printStackTrace();
    }

  }

  void jdbNavField4_actionPerformed(ActionEvent e) {

  }

  void jdbNavField1_actionPerformed(ActionEvent e) {

  }

  void jButton5_actionPerformed(ActionEvent e) {

  }

  void jButton2_actionPerformed(ActionEvent e) {
    qSet_course.saveChanges();
  }

  void jButton6_actionPerformed(ActionEvent e) {
    if (qSet_student_info.isEmpty()) {
      return;
    }
    if (!qSet_gcheck.isOpen()) {
      qSet_gcheck.open();
    }
    if (jTextField19.getText().equals("") || jTextField18.getText().equals("")) {
      JOptionPane.showConfirmDialog(null, "获奖时间和获奖名称其中之一不能为空，请完整输入！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.WARNING_MESSAGE);
      return;

    }
    if (omitspace(jTextField18.getText()).equals("") ||
       omitspace(jTextField19.getText()).equals("") ) {

     JOptionPane.showConfirmDialog(null, "请不要单独输入空格作为必填项！",
                                   "Student Management System",
                                   JOptionPane.OK_CANCEL_OPTION,
                                   JOptionPane.WARNING_MESSAGE);
     return;
   }

    try {

      Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
      String url = "jdbc:microsoft:sqlserver://localhost:1433;" +
          "DatabaseName=student";
      Connection conn = DriverManager.getConnection(url, "sa", "22114602");
      Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,
                                            ResultSet.CONCUR_UPDATABLE);

      String SQL = "select * from student_gcheck where gcheck_no = '" +
          qSet_student_info.getString("student_id") +
          "' and gcheck_title = '" + jTextField19.getText() +
          "' and gcheck_time = '" + jTextField18.getText() + "'";
      ResultSet rs = stmt.executeQuery(SQL); //查询该条获奖记录是否已经存在

      if (rs.next()) {
        int i = JOptionPane.showConfirmDialog(null,
                                              "学号为： " +
                                              qSet_student_info.getString("student_id") +
                                              " 的学生已经存在一条获奖时间为：" +
                                              jTextField18.getText() +
                                              "，获奖名称为： " + jTextField19.getText() +
                                              " 的记录，您是否仍要继续添加该记录：",
                                              "Student Management System",
                                              JOptionPane.YES_NO_OPTION,
                                              JOptionPane.QUESTION_MESSAGE);
        if (i == 1 || i == 2) {
          return;
        }

      }
      qSet_gcheck.setSort(new SortDescriptor (new  String []{"gcheck_id"}));
      qSet_gcheck.last();
      int i = qSet_gcheck.getInt("gcheck_id");
      qSet_gcheck.insertRow(true);
      qSet_gcheck.setInt("gcheck_id", i + 1);
      qSet_gcheck.setString("gcheck_no",
                            qSet_student_info.getString("student_id"));
      qSet_gcheck.setString("gcheck_name",
                            qSet_student_info.getString("student_name"));
      qSet_gcheck.setString("gcheck_time",
                            jTextField18.getText());
      qSet_gcheck.setString("gcheck_title",
                            jTextField19.getText());
      qSet_gcheck.setString("gcheck_disc",
                            jTextField20.getText());
      qSet_gcheck.post();
      qSet_gcheck.saveChanges(qSet_gcheck);
      qSet_gcheck.refresh();
      JOptionPane.showConfirmDialog(null, "新获奖记录已经成功添加！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.INFORMATION_MESSAGE);
      jTextField18.setText("");
      jTextField19.setText("");
      jTextField20.setText("");

    }
    catch (Exception ex) {
      ex.toString();
    }

  }

  void jButton12_actionPerformed(ActionEvent e) {
    if (qSet_student_info.isEmpty()) {
      return;
    }
    if (!qSet_practice.isOpen()) {
      qSet_practice.open();
    }

    if (jTextField21.getText().equals("") || jTextField22.getText().equals("")) {
      JOptionPane.showConfirmDialog(null, "实践时间和实践地点其中之一不能为空，请完整输入！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.WARNING_MESSAGE);
      return;

    }

    if (omitspace(jTextField21.getText()).equals("") ||
       omitspace(jTextField22.getText()).equals("")  ) {

     JOptionPane.showConfirmDialog(null, "请不要单独输入空格作为必填项！",
                                   "Student Management System",
                                   JOptionPane.OK_CANCEL_OPTION,
                                   JOptionPane.WARNING_MESSAGE);
     return;
   }

    try {
      Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
      String url = "jdbc:microsoft:sqlserver://localhost:1433;" +
          "DatabaseName=student";
      Connection conn = DriverManager.getConnection(url, "sa", "22114602");
      Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,
                                            ResultSet.CONCUR_UPDATABLE);

      String SQL = "select * from student_practice where p_no = '" +
          qSet_student_info.getString("student_id") +
          "' and p_title = '" + jTextField22.getText() +
          "' and p_time = '" + jTextField21.getText() + "'";
      ResultSet rs = stmt.executeQuery(SQL); //查询该条获奖记录是否已经存在

      if (rs.next()) {
        int i = JOptionPane.showConfirmDialog(null,
                                              "学号为： " +
                                              qSet_student_info.getString("student_id") +
                                              " 的学生已经存在一条实践时间为：" +
                                              jTextField21.getText() +
                                              "，实践地点为： " + jTextField22.getText() +
                                              " 的记录，您是否仍要继续添加该记录：",
                                              "Student Management System",
                                              JOptionPane.YES_NO_OPTION,
                                              JOptionPane.QUESTION_MESSAGE);
        if (i == 1 || i == 2) {
          return;
        }

      }
      qSet_practice.setSort(new SortDescriptor (new  String []{"p_id"}));
      qSet_practice.last();
      int i = qSet_practice.getInt("p_id");
      qSet_practice.insertRow(true);
      qSet_practice.setInt("p_id", i + 1);
      qSet_practice.setString("p_no",
                              qSet_student_info.getString("student_id"));
      qSet_practice.setString("p_name",
                              qSet_student_info.getString("student_name"));
      qSet_practice.setString("p_time",
                              jTextField21.getText());
      qSet_practice.setString("p_title",
                              jTextField22.getText());
      qSet_practice.setString("p_disc",
                              jTextField23.getText());
      qSet_practice.post();
      qSet_practice.saveChanges(qSet_practice);
      qSet_practice.refresh();
      JOptionPane.showConfirmDialog(null, "新实践记录已经成功添加！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.INFORMATION_MESSAGE);
      jTextField21.setText("");
      jTextField22.setText("");
      jTextField23.setText("");

    }
    catch (Exception ex) {
      ex.toString();
    }

  }

  void jButton11_actionPerformed(ActionEvent e) {
    if (!qSet_gcheck.isOpen()) {
      qSet_gcheck.open();
    }
    if (qSet_gcheck.isEmpty()) {
      return;
    }

    qSet_gcheck.deleteRow();
    qSet_gcheck.saveChanges(qSet_gcheck);
    qSet_gcheck.refresh();
  }

  void jButton13_actionPerformed(ActionEvent e) {
    if (!qSet_practice.isOpen()) {
      qSet_practice.open();
    }
    if (qSet_practice.isEmpty()) {
      return;
    }

    qSet_practice.deleteRow();
    qSet_practice.saveChanges(qSet_practice);
    qSet_practice.refresh();

  }

  void jButton14_actionPerformed(ActionEvent e) {
    if (jTextField24.getText().equals("")) {
      JOptionPane.showConfirmDialog(null, "请填入课程代号！",
                                    "Student Management System",
                                    JOptionPane.OK_CANCEL_OPTION,
                                    JOptionPane.WARNING_MESSAGE);
      return;

    }
    if (omitspace(jTextField24.getText()).equals("") ) {

     JOptionPane.showConfirmDialog(null, "无法查询空格课程代号！",
                                   "Student Management System",
                                   JOptionPane.OK_CANCEL_OPTION,
                                   JOptionPane.WARNING_MESSAGE);
     return;
   }


    String sqlQuery = "Select count_id,course_id,course_name,student_class,course_score From student_course,student_info where course_no = '"
        + omitspace(jTextField24.getText() )+ "' and course_score >= '0' and course_score < '60' and student_course.course_id = student_info.student_id";
    qSet_fail.close();
    qSet_fail.setQuery(new QueryDescriptor(database1, sqlQuery));
    qSet_fail.open();
    qSet_fail.refilter();

  }
  public String omitspace(String s) {
      s = s.trim();
    return s;
  }

  void jdbTable5_mouseClicked(MouseEvent e) {
    jTextField3.setText(qSet_class.getString("class_id"));
  }

  void jButton15_actionPerformed(ActionEvent e) {
    System.exit(0);
  }

  void jButton16_actionPerformed(ActionEvent e) {
    System.exit(0);
  }

  void jButton17_actionPerformed(ActionEvent e) {
    System.exit(0);
  }

  void jButton18_actionPerformed(ActionEvent e) {
    System.exit(0);
  }

  void jButton19_actionPerformed(ActionEvent e) {
    System.exit(0);
  }

}

class MainFrame_jButton3_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton3_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton3_actionPerformed(e);
  }
}

class MainFrame_jButton4_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton4_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton4_actionPerformed(e);
  }
}

class MainFrame_jPanel3_focusAdapter
    extends java.awt.event.FocusAdapter {
  MainFrame adaptee;

  MainFrame_jPanel3_focusAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void focusGained(FocusEvent e) {
    adaptee.jPanel3_focusGained(e);
  }
}

class MainFrame_jButton7_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton7_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton7_actionPerformed(e);
  }
}

class MainFrame_jButton8_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton8_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton8_actionPerformed(e);
  }
}

class MainFrame_jButton9_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton9_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton9_actionPerformed(e);
  }
}

class MainFrame_jButton10_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton10_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton10_actionPerformed(e);
  }
}

class MainFrame_jdbNavField4_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jdbNavField4_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jdbNavField4_actionPerformed(e);
  }
}

class MainFrame_jdbNavField1_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jdbNavField1_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jdbNavField1_actionPerformed(e);
  }
}

class MainFrame_jButton1_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton1_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton1_actionPerformed(e);
  }
}

class MainFrame_jButton5_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton5_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton5_actionPerformed(e);
  }
}

class MainFrame_jButton2_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton2_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton2_actionPerformed(e);
  }
}

class MainFrame_jButton6_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton6_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton6_actionPerformed(e);
  }
}

class MainFrame_jButton12_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton12_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton12_actionPerformed(e);
  }
}

class MainFrame_jButton11_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton11_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton11_actionPerformed(e);
  }
}

class MainFrame_jButton13_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton13_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton13_actionPerformed(e);
  }
}

class MainFrame_jButton14_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton14_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton14_actionPerformed(e);
  }
}

class MainFrame_jButton15_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton15_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton15_actionPerformed(e);
  }
}

class MainFrame_jdbTable5_mouseAdapter
    extends java.awt.event.MouseAdapter {
  MainFrame adaptee;

  MainFrame_jdbTable5_mouseAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void mouseClicked(MouseEvent e) {
    adaptee.jdbTable5_mouseClicked(e);
  }
}

class MainFrame_jButton16_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton16_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton16_actionPerformed(e);
  }
}

class MainFrame_jButton17_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton17_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton17_actionPerformed(e);
  }
}

class MainFrame_jButton18_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton18_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton18_actionPerformed(e);
  }
}

class MainFrame_jButton19_actionAdapter
    implements java.awt.event.ActionListener {
  MainFrame adaptee;

  MainFrame_jButton19_actionAdapter(MainFrame adaptee) {
    this.adaptee = adaptee;
  }

  public void actionPerformed(ActionEvent e) {
    adaptee.jButton19_actionPerformed(e);
  }
}
