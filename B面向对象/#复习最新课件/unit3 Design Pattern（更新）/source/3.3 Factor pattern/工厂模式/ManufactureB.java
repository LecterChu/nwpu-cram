
public class ManufactureB extends Manufacture{
	
	public Mobile createMobile(String type){
		if(type.equals("apple")){
			mobile = new BApple();
		}else if (type.equals("SAMSUNG")){
			mobile = new BSamsung();
		}
   }
}
