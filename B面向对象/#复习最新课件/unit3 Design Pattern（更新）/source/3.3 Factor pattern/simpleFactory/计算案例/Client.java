	public class Client {   
	  
	    public static void main(String[] args) {   
	        Operation operation = OperationFactory.createOperation('*');   
	        operation.setNumberA(12);   
	        operation.setNumberB(6);   
	        System.out.println(operation.operate());   
	    }   
	}  
