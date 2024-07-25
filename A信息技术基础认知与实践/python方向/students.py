class Student:
    def __init__(self,sid=0,sname="",sgender="男",sage=18,classname=""):
        self.sid = sid
        self.sname = sname
        self.sgender = sgender
        self.sage = sage
        self.classname = classname
    def __str__(self):
        return (
f"""姓名: {self.sname}
学号: {self.sid}
性别: {self.sgender}
年龄: {self.sage}
班级: {self.classname}"""
        )
    def __repr__(self):
        return self.__str__()
    def __eq__(self,other):
        return self.sid == other.sid

class StudentManager:
    def __init__(self,*args):
        self.students = []
        if args:
            for student in args:
                self.students.append(student)
    def add(self,student):
        self.students.append(student)
    def remove(self,student):
        self.students.remove(student)
    def __str__(self):
        return "\n".join([str(student) for student in self.students])
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
    def search(self,sid):
        for student in self.students:
            if student.sid == sid:
                return student
        return None
    def update(self,student):
        for i in range(len(self.students)):
            if self.students[i] == student:
                self.students[i] = student
                break
    def get(self):
        return self.students
    def __iter__(self):
        return iter(self.students)
    def __next__(self):
        return next(self.students)
    def __getitem__(self,index):
        return self.students[index]
    def __len__(self):
        return len(self.students)
    def __contains__(self,student):
        return student in self.students
    def __add__(self,other):
        return StudentManager(*self.students,*other.students)
    def __sub__(self,other):
        return StudentManager(*[student for student in self.students if student not in other.students])
    def __and__(self,other):
        return StudentManager(*[student for student in self.students if student in other.students])
    def __or__(self,other):
        return StudentManager(*self.students,*[student for student in other.students if student not in self.students])
    

if __name__ =="__main__":
    m = StudentManager(
        Student(1,"张三","男",18,"软件1班"),
        Student(2,"李四","女",19,"软件2班"),
        Student(3,"王五","男",20,"软件3班"),
        Student(4,"赵六","女",21,"软件4班"),
    )
    print(m)
