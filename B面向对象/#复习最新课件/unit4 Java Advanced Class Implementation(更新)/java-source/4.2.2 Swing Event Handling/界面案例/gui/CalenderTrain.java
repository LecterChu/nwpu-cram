package book.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Date;
import java.util.GregorianCalendar;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
/**
 * 日历程序
 */
public class CalenderTrain extends JFrame implements ActionListener {
	//月份和年份的下拉列表框
	private JComboBox MonthBox = new JComboBox(); 
	private JComboBox YearBox = new JComboBox(); 
	//月份和年份的标签
	private JLabel YearLabel = new JLabel("年份: "); 
	private JLabel MonthLabel = new JLabel("月份: "); 
	//“确定”和“今天”两个按钮
	private JButton button_ok = new JButton("查 看"); 
	private JButton button_today = new JButton("今 天"); 
	
	//获取今天的日期、年份、月份
	private Date now_date = new Date(); 
	private int now_year = now_date.getYear() + 1900; 
	private int now_month = now_date.getMonth();
	//用否显示今天的日期
	private boolean todayFlag = false;
	
	//用一组按钮显示日期，一共7行7列，第一行为星期的名字
	private JButton[] button_day = new JButton[42];
	private final String[] week = {"日", "一", "二", "三", "四", "五", "六"};
	private JButton[] button_week = new JButton[7];
	//保存用户选择的年份
	private String year_int = null; 
	//保存用户选择的月份
	private int month_int; 

	/**
	 * 构造函数
	 */
	public CalenderTrain() {
		super();
		//设置标题
		this.setTitle("日 历"); 
		this.init();
		this.setLocation(500, 300);
		//面板的大小不能变化
		this.setResizable(false); 
		pack();
	}
	/**
	 * 初始化日历
	 */
	private void init(){
		Font font = new Font("Dialog", Font.BOLD, 14);
		YearLabel.setFont(font);
		MonthLabel.setFont(font);
		button_ok.setFont(font);
		button_today.setFont(font);
		//设定年份区间，为当前年份的过去10年到当前年份的未来20年，
		for (int i = now_year - 10; i <= now_year + 20; i++) {
			YearBox.addItem(i + "");
		}
		//	设定年份下拉列表为当前年份，当前月份处于第十项
		YearBox.setSelectedIndex(10); 
		//设定月份区间，12个月
		for (int i = 1; i < 13; i++) {
			MonthBox.addItem(i + "");
		}
		//	设定月份下拉列表为当前月份
		MonthBox.setSelectedIndex(now_month); 

		//放置下拉列表框和控制按钮的面板
		JPanel panel_ym = new JPanel(); 
		panel_ym.add(YearLabel); 
		panel_ym.add(YearBox); 
		panel_ym.add(MonthLabel); 
		panel_ym.add(MonthBox); 
		panel_ym.add(button_ok); 
		panel_ym.add(button_today); 
		//为2个按钮添加事件侦听器
		button_ok.addActionListener(this); 
		button_today.addActionListener(this); 
		
		//放置日期面板
		JPanel panel_day = new JPanel(); 
		//网格布局管理器，7行7列，网格之间水平和垂直方向上间隔均为5
		panel_day.setLayout(new GridLayout(7, 7, 3, 3));
		// 添加星期的名字，并放到画板里
		for (int i = 0; i < 7; i++) {
			button_week[i] = new JButton(" ");
			button_week[i].setText(week[i]);
			button_week[0].setForeground(Color.black);
			panel_day.add(button_week[i]);
		}
		button_week[0].setForeground(Color.red);
		button_week[6].setForeground(Color.red);
		// 添加日期，放到画板里
		for (int i = 0; i < 42; i++) {
			button_day[i] = new JButton(" ");
			panel_day.add(button_day[i]);
		}
		//显示当前年月的日期
		this.paintDay(); 
		
		 // 放置以上两个面板
		JPanel panel_main = new JPanel();
		// 边界布局管理器
		panel_main.setLayout(new BorderLayout()); 
		panel_main.add(panel_day, BorderLayout.SOUTH);
		panel_main.add(panel_ym, BorderLayout.NORTH);
		getContentPane().add(panel_main);
	}

	/**
	 * 显示当前年月的日期
	 */
	private void paintDay() {
		if (todayFlag) {
			//要求显示今天的日历
			year_int = now_year + "";
			month_int = now_month;
		} else {
			//否则，从下拉框中获取用户选择的年月
			year_int = YearBox.getSelectedItem().toString();
			month_int = MonthBox.getSelectedIndex();//被选的序号
		}
		//	获得年份值	
		int year_sel = Integer.parseInt(year_int) - 1900; 
		 // 构造该月的第一天
		Date firstDay = new Date(year_sel, month_int, 1);
		//	创建一个Calendar实例
		GregorianCalendar cal = new GregorianCalendar(); 
		cal.setTime(firstDay);
		int days = 0; //存放某个月份的天数
		int day_week = 0; // 存放某个月的第一天是星期几的数值
		
		//判断是几月份,根据它来设定day的值 其中二月份要判断是否是闰年
		if (month_int == 0 || month_int == 2 || month_int == 4
				|| month_int == 6 || month_int == 7 || month_int == 9
				|| month_int == 11) {
			days = 31;
		} else if (month_int == 3 || month_int == 5 || month_int == 8
				|| month_int == 10) {
			days = 30;
		} else {
			//二月，如果是闰年，则有29天，否则有28天
			if (cal.isLeapYear(year_sel)) {
				days = 29;
			} else {
				days = 28;
			}
		}
		//getDay方法获取该天是星期几
		day_week = firstDay.getDay();
		int count = 1;
		/*
		 * 绘制按钮。在这里首先要根据选定的月份的第一天是星期几来确定绘制按钮的起始位置 
		 * 其中day_week就是我们要绘制的起始位置，对于那些没有数值可以显示的按钮要置空。
		 */
		for (int i = day_week; i < day_week + days; count++, i++) {
			if (i % 7 == 0 || i == 6 || i == 13 || i == 20 || i == 27
					|| i == 34 || i == 41) {
				//如果是边界上的按钮，文字用红色，以标示周末
				if (i == day_week + now_date.getDate() - 1) {
					// 将跟今天一样的日期用蓝色标示
					button_day[i].setForeground(Color.blue);
					button_day[i].setText(count + "");
				} else {
					//其他边界上的按钮中的文字用红色
					button_day[i].setForeground(Color.red);
					button_day[i].setText(count + "");
				}

			} else {
				if (i == day_week + now_date.getDate() - 1) {
					button_day[i].setForeground(Color.blue);
					button_day[i].setText(count + "");
				} else {
					//一般位置的按钮上的文字用黑色标示
					button_day[i].setForeground(Color.black);
					button_day[i].setText(count + "");
				}
			}
		}
		// 对于没有日期数值显示的按钮进行置空处理
		if (day_week == 0) {
			//如果第一天是周日，则将后面的按钮上的文字都设为空
			for (int i = days; i < 42; i++) {
				button_day[i].setText(" ");
			}
		} else {
			// 如果第一天不是周日，则将第一天前面的按钮置空
			for (int i = 0; i < day_week; i++) {
				button_day[i].setText(" ");
			} // 最后一天后面的按钮置空
			for (int i = day_week + days; i < 42; i++) {
				button_day[i].setText(" ");
			}
		}
	}

	/**
	 * 处理事件
	 */
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == button_ok) {
			//	如果点击确定按钮就调用setDay()重新方法绘制按钮
			todayFlag = false;
			this.paintDay(); 
		} else if (e.getSource() == button_today) {
			//  如果点击今天按钮，得到今天的日期 
			todayFlag = true;
			YearBox.setSelectedIndex(10);
			MonthBox.setSelectedIndex(now_month);
			this.paintDay(); 
		}
	}

	public static void main(String[] args) {
		CalenderTrain ct = new CalenderTrain();
		ct.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ct.setVisible(true);
		//ct.show();
//		ct.addWindowListener(new WindowAdapter(){
//			public void windowClosing(WindowEvent e){
//				System.exit(1);
//				
//			}
//		});
	}
}
