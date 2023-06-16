import java.awt.*;

import javax.swing.*;
import javax.swing.tree.*;

import java.util.*;
import javax.swing.event.*;

public class CompanyGUI extends JFrame {

	private Container contentPane; 
	
	private Employee boss;

	private Employee marketVP;

	private Employee prodVP;

	private Employee salesMgr;

	private Employee advMgr;

	private Employee prodMgr;

	private Employee shipMgr;
	
	private DefaultMutableTreeNode tBoss;
	
	private JTree tree;
	
	private JLabel cost;

	public static void main(String[] args) {

		JFrame frame = new CompanyGUI();

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(300, 400); // Adjust the size of the window
		frame.setVisible(true);
	}

	public CompanyGUI() {
		
		super("company_employee_tree");
		
		buildEmployeeTree();

		tBoss = new DefaultMutableTreeNode("CEO");

		addNodes(tBoss, boss);

		DefaultTreeModel model = new DefaultTreeModel(tBoss);

		tree = new JTree(model);
		tree.addTreeSelectionListener(new TreeLisoner());
		
		//JLabel costLabel = new JLabel("cost:");
		cost = new JLabel();
		
		JPanel panel = new JPanel();
		//panel.add(costLabel);
		panel.add(cost);
		
		Font fon = new Font("Serif", Font.BOLD, 15);
		//costLabel.setFont(fon);
		cost.setFont(fon);
		
		contentPane = getContentPane();		
		contentPane.add(new JScrollPane(tree));
		contentPane.add(panel,BorderLayout.SOUTH);

	}

	private void buildEmployeeTree() {

		boss = new Employee("CEO", 200000);
		boss.add(marketVP = new Employee("Marketing VP", 100000));
		boss.add(prodVP = new Employee("Production VP", 100000));

		marketVP.add(salesMgr = new Employee("Sales Mgr", 50000));
		marketVP.add(advMgr = new Employee("Advt Mgr", 50000));

		//add salesmen reporting to Sales Manager
		for (int i = 0; i < 5; i++) {
			salesMgr.add(new Employee("Sales " + new Integer(i).toString(),
					30000.0F + (float) (Math.random() - 0.5) * 10000));
		}

		advMgr.add(new Employee("Secy", 20000));
		prodVP.add(prodMgr = new Employee("Prod Mgr", 40000));
		prodVP.add(shipMgr = new Employee("Ship Mgr", 35000));

		//add manufacturing staff	
		for (int i = 0; i < 4; i++) {

			prodMgr.add(new Employee("Manuf " + new Integer(i).toString(),
					25000.0F + (float) (Math.random() - 0.5) * 5000));
		}
		//add shipping clerks
		for (int i = 0; i < 3; i++) {

			shipMgr.add(new Employee("ShipClrk " + new Integer(i).toString(),
					20000.0F + (float) (Math.random() - 0.5) * 5000));
		}

	}

	private void addNodes(DefaultMutableTreeNode pnode, Employee emp) {
		DefaultMutableTreeNode node;
		Iterator<Employee> iterator = emp.iterator();
		while (iterator.hasNext()) {
			Employee newEmp = (Employee) iterator.next();
			node = new DefaultMutableTreeNode(newEmp.getName());
			pnode.add(node);
			addNodes(node, newEmp);
		}
	}
	
	public class TreeLisoner implements TreeSelectionListener {
		
		public void valueChanged(TreeSelectionEvent evt) {
			// called when employee is selected in tree llist
			TreePath path = evt.getPath();
			String selectedTerm = path.getLastPathComponent().toString();
			
			// find that employee in the composite			
			Employee emp = boss.getChild(selectedTerm);
			
			// display sum of salaries of subordinates(if any)
			if (emp != null) {
				cost.setText(emp.getName() + ":  cost = " + new Float(emp.getSalaries()).toString());
			}
		}
	}
}