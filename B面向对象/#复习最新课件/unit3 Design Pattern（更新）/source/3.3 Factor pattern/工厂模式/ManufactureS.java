
public class ManufactureS extends Manufacture{
	
	public Mobile createMobile(String type){
		if (type.equals("ZTE")){
			mobile = new SZTE();
	    }else if (type.equals("HuaWei")){
			mobile = new SHuaWei();
	    }
 }
	
	
}
