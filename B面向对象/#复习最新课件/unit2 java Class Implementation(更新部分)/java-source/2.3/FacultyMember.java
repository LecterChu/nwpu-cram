
public class FacultyMember {
	
	private String identification;
	private String name;
	private String contactTelephone;

	public FacultyMember(String initialId, String initialName,String initialTele ){
		
		identification = initialId;
		name = initialName;
		contactTelephone = initialTele;
		
	}
	
	public String getIdentification(){
		return identification;
	}
	
	public String getName(){
		return name;
	}
	
	public String getContactTelephone(){
		return contactTelephone;
	}
	public String toString(){
		
		return "identification: "+identification+" name: "+name+
		 	" contactTelephone: "+contactTelephone;
	}
	public boolean equals(Object o){
		
		if (o instanceof FacultyMember){
			FacultyMember member = (FacultyMember)o;
			return this.identification.equals(member.getIdentification())&&
			       this.name.equals(member.getName())&& 
			       this.contactTelephone.equals(member.getContactTelephone());			
		} else {
			
			return false;
		}
		 
		
	}
	
	
	
	
	
	
}
