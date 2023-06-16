/**/
public class SimpleMobileFactory {
	public Static Mobile createMobile(String type){
		Mobile mobile =null;	
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
	    return mobile;
}


