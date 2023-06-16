
public class ICarnegieInfo  {

	private static  ICarnegieInfo singletonInstance;
	//1:static private ICarnegieInfo singletonInstance = new IcarnegieInfo();
	private String name;
	private String address;
	private String telephone;
	//2:static private number = 0;
	
	private ICarnegieInfo () {

		name = "iCarnegie, Inc";
		address = "4615 Forbes Avenue Pittsburgh, PA 15213-3796";
		telephone = "1.412.622.2150";
	}
	
	
	static public ICarnegieInfo getSingletonInstance() {

		if (singletonInstance == null) {
			singletonInstance = new ICarnegieInfo();
		}
		return singletonInstance;
	}	
	
	/*1:
	static public ICarnegieInfo getSingletonInstance() {

		return singletonInstance;
	}*/
	
	/*2:static public ICarnegieInfo getSingletonInstance() {

		if (number < 6) {
			singletonInstance = new ICarnegieInfo();
			number++;
		}

		return singletonInstance;
	}*/
	

	
	public String getName() {

		return name;
	}

	
	public String getAddress() {

		return address;
	}

	
	public String getTelephone() {

		return telephone;
	}
}









