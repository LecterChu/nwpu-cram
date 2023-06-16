
public class Official extends FacultyMember {
	
	private String jobPostion;
	
	public Official(String initialId, String initialName,String initialTele,String initialJP){
		super(initialId, initialName,initialTele);
		jobPostion = initialJP;
	}
	public String getJobPostion(){
		
		return jobPostion;
	}
	public String toString(){
		
		return super.toString()+" jobPostion:"+jobPostion;
	}

}
