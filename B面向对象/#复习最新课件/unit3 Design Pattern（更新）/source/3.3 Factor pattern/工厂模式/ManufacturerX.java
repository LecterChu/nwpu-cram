
public class ManufacturerX extends Manufacture{
	
public Mobile createMobile(String type){
		if (type.equals("HTC")){
			mobile = new XHTC();
		}else if (type.equals("Motorola")){
			mobile = new XMotorola();
	    }
 }
}
