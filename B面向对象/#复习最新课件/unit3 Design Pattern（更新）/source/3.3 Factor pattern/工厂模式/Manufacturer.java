
public abstract class Manufacturer {	
	
	public Mobile orderMobile(String type){
		Mobile mobile;
		mobile = createMobile(type);
		mobile.assembleMainboard();
		mobile.assembleSUBboard();
		mobile.assembleKeypad();
		mobile.assembleWholewidget();
		mobile.testing();
	}
	public abstract Mobile createMobile(String type);
	
}

