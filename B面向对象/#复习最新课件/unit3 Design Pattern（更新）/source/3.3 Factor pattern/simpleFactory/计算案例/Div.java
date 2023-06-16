	public class Div extends Operation {   
	  
	    
	    public double operate() {   
	       
	        	//java中浮点数运算中0作除数并不会出现异常，
	        	//正数除以0得正无穷，负数除以0得负无穷，0除以0得NaN
	        	//若是整形数运算则会抛出异常
	            return numberA/numberB;   
	         
	    }	     
}  
