import java.util.*;
public class Teacher extends FacultyMember{

	private String title;
	//private ArrayList<String> teachingCourses;
	
	public Teacher(String initialId, String initialName,String initialTele,String initialTitle){
		super(initialId, initialName,initialTele);
		title =  initialTitle;
				
	}
	public String getTitle(){
		return title;
	} 
    public String toString(){
		
		return super.toString()+" title:"+title;
	}
	
	
	
	
	
	
	
}
