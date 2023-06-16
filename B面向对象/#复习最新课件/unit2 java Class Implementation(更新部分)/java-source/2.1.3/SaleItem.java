public class SaleItem {	
	
	private String isbn;
	private int unitsSold;
	private double revenue; 
	
	public SaleItem(String initialIsbn, 
			int initialUnitsSold, double initialRevenue ){		
		
		isbn = initialIsbn;
		unitsSold = initialUnitsSold;
		revenue = initialRevenue;		
	}	
	public String getIsbn(){		
		return isbn;
	}	
	public int getUnitsSold(){		
		return unitsSold;
	}
                public double getRevenue(){
		return revenue;
	}    
	public double avg_price() 	{
	    if (unitsSold!=0) 
	        return revenue/unitsSold;
	    else
	        return 0;
	}
}
