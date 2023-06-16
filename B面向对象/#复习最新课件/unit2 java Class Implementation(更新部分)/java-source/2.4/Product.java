
public class Product {

	private String name;
    private int quantity;
    private double price;
    
    public Product(String initialName,int initialQuantity, double InitialPrice){
    	
    	name = initialName;
    	quantity = initialQuantity;
    	price = InitialPrice;    	
    }
    
    public String getName(){
    	
    	return name;
    }
    
    public int getQuantity() {
    	
    	return quantity;
    }
    
    public double getPrice() {
    	
    	return price;
    }
	public String toString(){
		return "product: "+ name+"; "+quantity+";  "+price;
	}
    
}
