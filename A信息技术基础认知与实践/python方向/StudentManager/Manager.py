import SQLManager
from typing import List

def grade_to_gpa(grade:float)->float:
    if grade >= 95:
        return 4.1
    if grade >= 90:
        return 4.0
    elif grade >= 85:
        return 3.7
    elif grade >= 82:
        return 3.3
    elif grade >= 78:
        return 3.0
    elif grade >= 75:
        return 2.7
    elif grade >= 72:
        return 2.3
    elif grade >= 68:
        return 2.0
    elif grade >= 64:
        return 1.5
    elif grade >= 60:
        return 1.0
    else:
        return 0.0      

class Course:
    def __init__(self,cid:str="0",cname:str="",credit:float=0,grade:float=0):
        self.cid = cid
        self.cname = cname
        self.credit = credit
        self.grade = grade
    def __str__(self):
        return f"课程编号: {self.cid} 课程名称: {self.cname} 学分: {self.credit} GPA: {grade_to_gpa(self.grade)}\n"
class Student:
    def __init__(self,sql,sid:int=0,sname:str="",sgender:str="男",sage:int=18,classname:str="",courses:List[Course]=[]):
        self.sid = sid
        self.sname = sname
        self.sgender = sgender
        self.sage = sage
        self.classname = classname
        self.courses = courses.copy()
        self.sql = sql
    def __str__(self):
        course_str = "\n".join([str(course) for course in self.courses])
        return (
f"""姓名: {self.sname}
学号: {self.sid}
性别: {self.sgender}
年龄: {self.sage}
班级: {self.classname}
课程成绩:\n{course_str}"""
        )
    def __repr__(self):
        return self.__str__()
    def __eq__(self,other):
        return self.sid == other.sid
    def load_from_db(self,sid):
        self.sid = sid
        sql = f"select * from student where sid={sid}"
        result = self.sql.query(sql)
        if result:
            self.sname = result[0][1]
            self.sgender = result[0][2]
            self.sage = int(result[0][3])
            self.classname = result[0][4]
            # load courses
            sql = f"select * from course where sid={sid}"
            result = self.sql.query(sql)
            for row in result:
                course = Course(row[1],row[2],float(row[3]),float(row[4]))
                self.courses.append(course)
    def save_to_db(self):
        # 检查学生是否存在，如果存在则更新，否则插入
        sql = f"select * from student where sid={self.sid}"
        result = self.sql.query(sql)
        if result:
            self.update()
            return
        sql = f"insert into student values({self.sid},'{self.sname}','{self.sgender}',{self.sage},'{self.classname}')"
        self.sql.insert(sql)
        for course in self.courses:
            sql = f"insert into course values({self.sid},'{course.cid}','{course.cname}',{course.credit},{course.grade})"
            self.sql.insert(sql)
    def update(self):
        sql = f"update student set sname='{self.sname}',sgender='{self.sgender}',sage={self.sage},classname='{self.classname}' where sid={self.sid}"
        self.sql.update(sql)
        sql = f"delete from course where sid={self.sid}"
        self.sql.delete(sql)
        for course in self.courses:
            sql = f"insert into course values({self.sid},'{course.cid}','{course.cname}',{course.credit},{course.grade})"
            self.sql.insert(sql)

    def add_course(self,course):
        self.courses.append(course)
    def remove_course(self,course):
        self.courses.remove(course)
    def get_courses(self):
        return self.courses
    def get_gpa(self):
        # 加权平均GPA
        total_credit = 0
        total_gpa = 0
        for course in self.courses:
            total_credit += course.credit
            total_gpa += grade_to_gpa(course.grade) * course.credit
        if total_credit == 0:
            return 0    
        return total_gpa / total_credit
    def get_credit(self):
        # 总学分
        total_credit = 0
        for course in self.courses:
            total_credit += course.credit
        return total_credit
    def remove_course_by_name(self,cname:str):
        for course in self.courses:
            if course.cname == cname:
                self.courses.remove(course)
                return True
        return False
    def remove_course_by_id(self,cid:str):
        for course in self.courses:
            if course.cid == cid:
                self.courses.remove(course)
                return True
        return False
    def get_course_by_name(self,cname:str)->Course:
        for course in self.courses:
            if course.cname == cname:
                return course
        return None
    def get_course_by_id(self,cid:str)->Course:
        for course in self.courses:
            if course.cid == cid:
                return course
        return None

class CollegeStudentManager:
    # 学生管理类(学院)
    def __init__(self,sql,college:str=""):
        self.students:List[Student] = []
        self.sql = sql
        self.college = college
    def add(self,student:Student):
        # 添加学生
        for s in self.students:
            if s.sid == student.sid:
                # update
                s = student
                return
        self.students.append(student)
    def remove(self,student:Student)->bool:
        # 删除学生
        for i in range(len(self.students)):
            if self.students[i] == student:
                del self.students[i]
                return True
        return False
    def __str__(self):
        return self.college + "\n" + "\n".join(["- " + str(student) for student in self.students])
    def __repr__(self):
        return self.__str__()
    def sort(self):
        self.students.sort(key=lambda student:student.sid)
    def sort_by_age(self):
        self.students.sort(key=lambda student:student.sage)
    def sort_by_classname(self):
        self.students.sort(key=lambda student:student.classname)
    def sort_by_name(self):
        self.students.sort(key=lambda student:student.sname)
    def sort_by_gpa(self):
        self.students.sort(key=lambda student:student.get_gpa())
    def sort_by_credit(self):
        self.students.sort(key=lambda student:student.get_credit())
    def search(self,sid):
        for student in self.students:
            if student.sid == sid:
                return student
        return None
    def update(self,student:Student):
        for i in range(len(self.students)):
            if self.students[i] == student:
                self.students[i] = student
                return
        self.add(student)
    def get(self):
        return self.students
    def __iter__(self):
        return iter(self.students)
    def __next__(self):
        return next(self.students)
    def __getitem__(self,sid):
        for student in self.students:
            if student.sid == sid:
                return student
        return None
    def __len__(self):
        return len(self.students)
    def load_from_db(self):
        if not self.sql:
            raise ValueError("SQLManager is not set")
        # 从数据库加载学生信息
        # 读取学院下的所有学生的id，然后加载学生信息
        sql = f"select sid from college_students where classname='{self.college}'"
        result = self.sql.query(sql)
        for row in result:
            student = Student(self.sql)
            student.load_from_db(row[0])
            self.students.append(student)

        
    def save_to_db(self):
        if not self.sql:
            raise ValueError("SQLManager is not set")
        sql = f"delete from college where collegename='{self.college}'"
        self.sql.delete(sql)
        # 插入学院，然后在学院的子级插入所有学生id
        # 类似
        # collegename
        # - id1
        # - id2
        
        # 插入学院
        sql = f"insert into college values('{self.college}')"
        self.sql.insert(sql)
        sql = f"delete from college_students where classname='{self.college}'"
        self.sql.delete(sql)
        # 在学院条目下插入所有学生id
        for student in self.students:
            sql = f"insert into college_students values('{self.college}',{student.sid})"
            self.sql.insert(sql)
            student.save_to_db()

    def get_gpa(self):
        # 计算学院的平均GPA
        total_gpa = 0
        for student in self.students:
            total_gpa += student.get_gpa()
        if len(self.students) == 0:
            return 0
        return total_gpa / len(self.students)
    def get_credit(self):
        # 计算学院的平均学分
        total_credit = 0
        for student in self.students:
            total_credit += student.get_credit()
        if len(self.students) == 0:
            return 0
        return total_credit / len(self.students)
    def get_student_count(self):
        return len(self.students)
    def get_student(self,index):
        return self.students[index]
    def get_student_by_sid(self,sid:int)->Student:
        for student in self.students:
            if student.sid == sid:
                return student
        return None
    def get_student_by_name(self,name:str)->Student:
        for student in self.students:
            if student.sname == name:
                return student
        return None
    def get_student_by_classname(self,classname:str)->List[Student]:
        students = []
        for student in self.students:
            if student.classname == classname:
                students.append(student)
        return students
    def get_student_by_age(self,age:int)->List[Student]:
        students = []
        for student in self.students:
            if student.sage == age:
                students.append(student)
        return students
    def get_student_by_gpa(self,gpa:float)->List[Student]:
        students = []
        for student in self.students:
            if student.get_gpa() == gpa:
                students.append(student)
        return students
    def get_student_by_credit(self,credit:int)->List[Student]:
        students = []
        for student in self.students:
            if student.get_credit() == credit:
                students.append(student)
        return students
    def get_student_by_course(self,course:Course)->List[Student]:
        students = []
        for student in self.students:
            if course in student.get_courses():
                students.append(student)
        return students
    def get_student_by_course_name(self,cname:str)->List[Student]:
        students = []
        for student in self.students:
            for course in student.get_courses():
                if course.cname == cname:
                    students.append(student)
                    break
        return students
    def get_student_by_course_id(self,cid:int)->List[Student]:
        students = []
        for student in self.students:
            for course in student.get_courses():
                if course.cid == cid:
                    students.append(student)
                    break
        return students
    
    def get_student_credit_lower_than(self,credit:float)->List[Student]:
        students = []
        for student in self.students:
            if student.get_credit() < credit:
                students.append(student)
        return students

    def get_student_credit_higher_than(self,credit:float)->List[Student]:
        students = []
        for student in self.students:
            if student.get_credit() > credit:
                students.append(student)
        return students
    def remove_student_by_sid(self,sid:int)->bool:
        for i in range(len(self.students)):
            if self.students[i].sid == sid:
                del self.students[i]
                return True
        return False
    

class SchoolStudentManager:
    def __init__(self,sql):
        self.sql = sql
        self.collages:List[CollegeStudentManager] = []
    def add(self,collage):
        for c in self.collages:
            if c.college == collage.college:
                return
        self.collages.append(collage)
    def remove(self,collage):
        for i in range(len(self.collages)):
            if self.collages[i] == collage:
                del self.collages[i]
                return
    def remove_by_name(self,college:str)->bool:
        for i in range(len(self.collages)):
            if self.collages[i].college == college:
                del self.collages[i]
                return True
        return False
    def remove_by_sid(self,sid:int)->bool:
        for collage in self.collages:
            for i in range(len(collage.students)):
                if collage.students[i].sid == sid:
                    del collage.students[i]
                    return True
        return False
    def __str__(self):
        return "\n".join([str(collage) for collage in self.collages])
    def __repr__(self):
        return self.__str__()
    def sort(self):
        self.collages.sort(key=lambda collage:collage.college)
    def search(self,college:str)->CollegeStudentManager:
        for collage in self.collages:
            if collage.college == college:
                return collage
        # 如果不存在则创建
        collage = CollegeStudentManager(self.sql,college)
        self.add(collage)
        return collage
    def update(self,collage:CollegeStudentManager):
        for i in range(len(self.collages)):
            if self.collages[i] == collage:
                self.collages[i] = collage
                break
    def get(self):
        return self.collages
    def __iter__(self):
        return iter(self.collages)
    def __next__(self):
        return next(self.collages)
    def __getitem__(self,college:str):
        for collage in self.collages:
            if collage.college == college:
                return collage
        return None
    def __len__(self):
        return len(self.collages)
    def load_from_db(self):
        if not self.sql:
            raise ValueError("SQLManager is not set")
        # 先检索是否存在college表和student表，如果不存在则创建
        sql = "show tables"
        result = self.sql.query(sql)
        if ('college',) not in result:
            sql = "create table college(collegename varchar(255) primary key)"
            self.sql.update(sql)
        if ('college_students',) not in result:
            sql = "create table college_students(classname varchar(255),sid int)"
            self.sql.update(sql)
        if ('student',) not in result:
            sql = "create table student(sid int primary key,sname varchar(255),sgender varchar(255),sage int,classname varchar(255))"
            self.sql.update(sql)
        if ('course',) not in result:
            sql = "create table course(sid int,cid varchar(255),cname varchar(255),credit float,grade float)"
            self.sql.update(sql)
        # 从数据库加载学生信息
        # 读取学院下的所有学生的id，然后加载学生信息
        sql = f"select collegename from college"
        result = self.sql.query(sql)
        for row in result:
            college = CollegeStudentManager(self.sql,row[0])
            college.load_from_db()
            self.collages.append(college)
    def save_to_db(self):
        if not self.sql:
            raise ValueError("SQLManager is not set")
        for collage in self.collages:
            collage.save_to_db()
    def get_student_by_sid(self,sid:int)->Student:
        for collage in self.collages:
            student = collage.get_student_by_sid(sid)
            if student:
                return student
        return None
    def get_student_by_name(self,name:str)->Student:
        for collage in self.collages:
            student = collage.get_student_by_name(name)
            if student:
                return student
        return None
    def get_student_by_classname(self,classname:str)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_by_classname(classname)
        return students
    def get_student_by_age(self,age:int)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_by_age(age)
        return students
    def get_student_by_gpa(self,gpa:float)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_by_gpa(gpa)
        return students
    def get_student_by_credit(self,credit:int)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_by_credit(credit)
        return students
    def get_student_by_course(self,course:Course)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_by_course(course)
        return students
    def get_student_by_course_name(self,cname:str)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_by_course_name(cname)
        return students
    def get_student_by_course_id(self,cid:int)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_by_course_id(cid)
        return students
    def get_student_credit_lower_than(self,credit:float)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_credit_lower_than(credit)
        return students
    def get_student_credit_higher_than(self,credit:float)->List[Student]:
        students = []
        for collage in self.collages:
            students += collage.get_student_credit_higher_than(credit)
        return students
    def get_student_collage(self,college:str)->List[Student]:
        for collage in self.collages:
            if collage.college == college:
                return collage.get()
        return []
    def get_students(self):
        students = []
        for collage in self.collages:
            students += collage.get()
        return students
    def move_student(self,sid:int,to_college:str):
        for collage in self.collages:
            student = collage.get_student_by_sid(sid)
            if student:
                collage.remove_student_by_sid(sid)
                to_collage = self.search(to_college)
                to_collage.add(student)
                return True
        return False





if __name__ == "__main__":
    sql = SQLManager.SQLManager(database="school",user="root",password="Sin(1)=0")
    school = SchoolStudentManager(sql)
    school.load_from_db()
    print(school)
    # 添加学生
    student = Student(sql,1,"张三","男",18,"DL01")
    student.add_course(Course(1,"高等数学",4))
    student.add_course(Course(2,"大学英语",3))    
    school.search("计算机科学与技术").add(student)
    student = Student(sql,2,"李四","男",19,"DL02")
    student.add_course(Course(1,"离散数学",4))
    student.add_course(Course(2,"大学物理",3))
    school.search("计算机科学与技术").add(student)
    student = Student(sql,3,"王五","女",20,"PHC12")
    student.add_course(Course(1,"高等数学",4))
    student.add_course(Course(2,"理论力学",3))
    school.search("物理学").add(student)
    student = Student(sql,4,"赵六","女",21,"DL02")
    student.add_course(Course(1,"高等数学",4))
    student.add_course(Course(2,"大学英语",3))
    school.search("计算机科学与技术").add(student)
    student = Student(sql,5,"钱七","男",22,"DL03")
    student.add_course(Course(1,"高等数学",4))
    student.add_course(Course(2,"大学英语",3))
    school.search("计算机科学与技术").add(student)
    # 保存到数据库
    school.save_to_db()
    print(school)
    # 删除学生
    student = school.search("计算机科学与技术").get_student_by_sid(5)
    school.search("计算机科学与技术").remove(student)
    # 保存到数据库
    school.save_to_db()
    print(school)
    # 更新学生信息
    student = school.search("计算机科学与技术").get_student_by_sid(4)
    student.sname = "赵六六"
    student.update()
    # 保存到数据库
    school.save_to_db()
    print(school)
    # 查询学生信息
    student = school.search("计算机科学与技术").get_student_by_sid(2)
    print(student)
    # 查询学院平均GPA
    print(school.search("计算机科学与技术").get_gpa())
    # 查询学院平均学分
    print(school.search("计算机科学与技术").get_credit())
    # 查询学生人数
    print(school.search("计算机科学与技术").get_student_count())
    # 查询学生
    
