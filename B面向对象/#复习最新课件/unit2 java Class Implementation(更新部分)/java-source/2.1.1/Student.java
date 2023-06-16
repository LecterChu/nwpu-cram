
import java.util.*;
public class Student {
	
        private String name;
        private Calendar birthday;
        public Student() {
        }
        public Student(String name, Calendar birthday){
        	this.name = name;
        	this.birthday = birthday;
        }
        public String getName() {
        	return this.name;
        }
        public void setName() {
        	this.name = name;
        }
    
        public Date getBirthday() {
        	return this.birthday.getTime();
                }  
        	public static void main(String[] args) {
        		Calendar c = new  GregorianCalendar();
        		c.set(2006,8,11);
        		
        		Student student= new Student("xixi",c);
        		System.out.println(student.getName()+"  "+student.getBirthday());
        		
        		
        		
        		
        	}


}
