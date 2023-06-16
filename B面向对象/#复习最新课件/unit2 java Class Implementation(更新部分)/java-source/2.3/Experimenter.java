
public class Experimenter extends FacultyMember{


	private String degree;
	
	public Experimenter(String initialId, String initialName,String initialTele,String initialDegree){
		super(initialId, initialName,initialTele);
		degree = initialDegree;
	}
	public String getDegree(){
		
		return degree;
	}
	public String toString(){
		
		return super.toString()+" degree:"+degree;
	}
}
