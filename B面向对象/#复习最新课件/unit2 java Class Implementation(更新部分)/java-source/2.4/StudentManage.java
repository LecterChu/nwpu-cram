import java.util.ArrayList;
import java.util.Scanner;

/*
 * 学生管理系统
 */
public class StudentManage {
    public ArrayList<Student> students;
    public StudentManage(ArrayList<Student> students){
        this.students = students;
        if(this.students==null)this.students=new ArrayList<Student>();
    }
    public void addStudent(Student student){
        this.students.add(student);
    }
    public Student searchStudentByCode(String code){
        for(int i=0;i<this.students.size();i++){
            if(this.students.get(i).getCode().equals(code))return this.students.get(i);
        }
        return null;
    }
    public static Student readStudent(Scanner scanner){
        System.err.println("please input student info follow this format:name code sex age\n"+"sex: male or female");
        String infos = scanner.nextLine();
        String[] info = infos.split(" ");
        return new Student(info[0],info[1],info[2],Integer.parseInt(info[3]));
    }
    public static String readCode(Scanner scanner){
        System.err.println("please input the student's code you want to search");
        return scanner.nextLine();
    }
    public static void main(String[] args) {
        StudentManage studentManage = new StudentManage(null);
        Scanner scanner = new Scanner(System.in);
        String menu = "please select num to opt:\n"
                + "1. exit\n"
                + "2. add one new Student\n"
                + "3. search one Student by code\n";
        System.err.println(menu);
        int code = Integer.parseInt(scanner.nextLine());
        while(code!=1){
            switch (code){
                case 2:
                    studentManage.addStudent(readStudent(scanner));
                    System.err.println("add successful");
                    break;
                case 3:;
                    Student student = studentManage.searchStudentByCode(readCode(scanner));
                    System.err.println(student);
            }
            System.err.println(menu);
            code = Integer.parseInt(scanner.nextLine());
        }
    }
}
class Student{
    private String name;
    private String code;
    private String sex;
    private int age;
    public Student(String name,String code,String sex,int age){
        this.name = name;
        this.code = code;
        this.sex = sex;
        this.age = age;
    }

    public String getCode() {
        return code;
    }
    public void setCode(String code) {
        this.code = code;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getSex() {
        return this.sex;
    }
    public void setSex(String sex) {
        this.sex = sex;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", code='" + code + '\'' +
                ", sex='" + sex + '\'' +
                ", age=" + age +
                '}';
    }
}