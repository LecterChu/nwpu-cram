/**/
public class Manufacturer {	
	Mobile orderMobile(String type){
		Mobile mobile;
		if(type.equals("apple")){
			mobile = new Apple();
		}else if (type.equals("SAMSUNG")){
			mobile = new Samsung();
		}else if (type.equals("HTC")){
			mobile = new HTC();
		}else if (type.equals("Motorola")){
			mobile = new Motorola();
	    }else if (type.equals("NOKIA")){
			mobile = new Nokia();
	    }else if (type.equals("ZTE")){
			mobile = new ZTE();
	    }else if (type.equals("HuaWei")){
			mobile = new HuaWei();
	    }else if (type.equals("K-touch")){
			mobile = new Ktouch();
	    }else if (type.equals("Lenovo")){
			mobile = new Lenovo();
	    }
		mobile.assembleMainboard();
		mobile.assembleSUBboard();
		mobile.assembleKeypad();
		mobile.assembleWholewidget();
		mobile.BurnSD();
		mobile.testing();
	}
}

public class Manufacturer {	
	SimpleMobileFactory factory;
	public Manufacturer(SimpleMobileFactory factory){
		this.factory = factory;
	}	
	Mobile orderMobile(String type){
		Mobile mobile;
		mobile = factory.createMobile(type);
		mobile.assembleMainboard();
		mobile.assembleSUBboard();
		mobile.assembleKeypad();
		mobile.assembleWholewidget();
		mobile.testing();
	}
}

