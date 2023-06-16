  
	  
public abstract class Operation {   
        double numberA=0;   
	    double numberB=0;   
	       
	    
	  
	    public void setNumberA(double numberA) {   
	        this.numberA = numberA;   
	    }  
	    
	    public void setNumberB(double numberB) {   
	        this.numberB = numberB;   
		} 
	    
	    public double getNumberA() {   
	        return numberA;   
	    } 
	    public double getNumberB() {   
	        return numberB;   
	    }	    
	  
	    public abstract double operate();   
	}  
