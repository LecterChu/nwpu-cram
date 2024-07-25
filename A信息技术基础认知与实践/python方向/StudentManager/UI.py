from tkinter import *
from tkinter import messagebox
from tkinter import ttk
import Manager
import SQLManager
import json

class isNumber:
    def __init__(self):
        pass
    def __call__(self,s:str):
        if s=='':
            return True
        try:
            float(s)
            return True
        except:
            return False
    def applyVaildateForEntry(self,entry:Entry):
        vcmd = entry.register(self)
        entry.config(validate='key',validatecommand=(vcmd,'%P'))
class ManagerUI:
    pass

class StudentInfoUI:
    def __init__(self,student:Manager.Student,master:ManagerUI=None):
        self.master = master
        self.window = Toplevel()
        self.window.title('学生信息')
        self.window.resizable(width=True,height=True)
        self.window.transient()
        self.window.grab_set()

        self.student = student
        self.window.bind('<Configure>',self.resize)
        self.initUI()
        self.window.geometry('700x400')
        # 绑定关闭事件
        self.window.bind('<Destroy>',self.close)
        self.window.update()
        self.window.mainloop()

    def initUI(self):
        self.label = Label(self.window,text=f'学号:{self.student.sid}  姓名:{self.student.sname}  年龄:{self.student.sage}  班级:{self.student.classname}')
        self.label.pack()
        self.courses = ttk.Treeview(self.window)
        self.courses['columns'] = ('课程名','分数','学分','GPA')
        self.courses.column('课程名',width=100)
        self.courses.column('分数',width=50)
        self.courses.column('学分',width=50)
        self.courses.column('GPA',width=50)
        self.courses.pack()
        self.courses.bind('<Double-1>',self.modifyCourse)
        for course in self.student.courses:
            self.courses.insert('','end',values=(course.cname,course.grade,course.credit,Manager.grade_to_gpa(course.grade)),text=f"[课程代码]{course.cid}")

        # 右侧加入编辑按钮（添加课程、删除课程，修改课程）
        self.editFrame = Frame(self.window)
        self.editFrame.pack()
        self.addCourseButton = Button(self.editFrame,text='添加课程',command=self.addCourse)
        self.addCourseButton.pack(side=LEFT)
        self.deleteCourseButton = Button(self.editFrame,text='删除课程',command=self.deleteCourse)
        self.deleteCourseButton.pack(side=LEFT)
        self.modifyCourseButton = Button(self.editFrame,text='修改课程',command=self.modifyCourse)
        self.modifyCourseButton.pack(side=LEFT)
        self.modifyMainInfoButton = Button(self.editFrame,text='修改学生信息',command=self.modifyMainInfo)
        self.modifyMainInfoButton.pack(side=LEFT)

        width = self.window.winfo_width()
        height = self.window.winfo_height()
        self.label.config(height=1)
        self.label.place(x=0,y=0,width=width)
        self.courses.place(x=0,y=self.label.winfo_height(),width=width,height=height-self.label.winfo_height()*2)
        self.courses.heading('课程名',text='课程名')
        self.courses.heading('分数',text='分数')
        self.courses.heading('学分',text='学分')
        self.courses.heading('GPA',text='GPA')
        self.editFrame.place(x=0,y=height-self.label.winfo_height(),width=width,height=self.label.winfo_height())
        self.addCourseButton.place(x=0,y=0,width=width//4,height=self.label.winfo_height())
        self.deleteCourseButton.place(x=width//4,y=0,width=width//4,height=self.label.winfo_height())
        self.modifyCourseButton.place(x=(width//4)*2,y=0,width=width//4,height=self.label.winfo_height())
        self.modifyMainInfoButton.place(x=(width//4)*3,y=0,width=width//4,height=self.label.winfo_height())

        self.addCourseButton.update()
        self.deleteCourseButton.update()
        self.modifyCourseButton.update()
    def modifyMainInfo(self):
        self.modifyWindow = Toplevel(self.window)
        self.modifyWindow.title('修改学生信息')
        self.modifyWindow.geometry('300x200')
        self.modifyWindow.resizable(0,0)
        self.modifyWindow.transient(self.window)
        self.modifyWindow.grab_set()
        # 姓名
        self.nameLabel = Label(self.modifyWindow,text='姓名')
        self.nameLabel.pack()
        self.nameEntry = Entry(self.modifyWindow)
        self.nameEntry.insert(0,self.student.sname)
        self.nameEntry.pack()
        # 年龄
        self.ageLabel = Label(self.modifyWindow,text='年龄')
        self.ageLabel.pack()
        self.ageEntry = Entry(self.modifyWindow)
        self.ageEntry.insert(0,self.student.sage)
        isNumber().applyVaildateForEntry(self.ageEntry)
        self.ageEntry.pack()
        # 班级
        self.classLabel = Label(self.modifyWindow,text='班级')
        self.classLabel.pack()
        self.classEntry = Entry(self.modifyWindow)
        self.classEntry.insert(0,self.student.classname)
        self.classEntry.pack()
        # 确认按钮
        self.confirmButton = Button(self.modifyWindow,text='确认',command=self.confirmModifyMainInfo)
        self.confirmButton.pack()
    def confirmModifyMainInfo(self):
        name = self.nameEntry.get()
        age = self.ageEntry.get()
        classname = self.classEntry.get()
        if name == '' or age == '' or classname == '':
            messagebox.showinfo('提示','姓名、年龄、班级不能为空')
            return
        self.student.sname = name
        self.student.sage = int(age)
        self.student.classname = classname
        self.label.config(text=f'学号:{self.student.sid}  姓名:{self.student.sname}  年龄:{self.student.sage}  班级:{self.student.classname}')
        self.modifyWindow.destroy()
    def addCourse(self):
        self.addWindow = Toplevel(self.window)
        self.addWindow.title('添加课程')
        self.addWindow.geometry('300x200')
        self.addWindow.resizable(0,0)
        self.addWindow.transient(self.window)
        self.addWindow.grab_set()
        # 课程代码
        self.cidLabel = Label(self.addWindow,text='课程代码')
        self.cidLabel.pack()
        self.cidEntry = Entry(self.addWindow)
        self.cidEntry.pack()
        # 课程名
        self.cnameLabel = Label(self.addWindow,text='课程名')
        self.cnameLabel.pack()
        self.cnameEntry = Entry(self.addWindow)
        self.cnameEntry.pack()
        # 分数
        self.gradeLabel = Label(self.addWindow,text='分数')
        self.gradeLabel.pack()
        self.gradeEntry = Entry(self.addWindow)
        isNumber().applyVaildateForEntry(self.gradeEntry)
        self.gradeEntry.pack()
        # 学分
        self.creditLabel = Label(self.addWindow,text='学分')
        self.creditLabel.pack()
        self.creditEntry = Entry(self.addWindow)
        isNumber().applyVaildateForEntry(self.creditEntry)
        self.creditEntry.pack()
        # 确认按钮
        self.confirmButton = Button(self.addWindow,text='确认',command=self.confirmAddCourse)
        self.confirmButton.pack()
    def confirmAddCourse(self):
        cid = self.cidEntry.get()
        cname = self.cnameEntry.get()
        grade = self.gradeEntry.get()
        credit = self.creditEntry.get()
        if cname == '' or grade == '' or credit == '':
            messagebox.showinfo('提示','课程名、分数、学分不能为空')
            return
        self.student.add_course(Manager.Course(cid,cname,float(credit),float(grade)))
        self.addWindow.destroy()
        self.courses.insert('','end',values=(cname,grade,float(credit),Manager.grade_to_gpa(float(grade))),text=f"[课程代码]{cid}")
    def deleteCourse(self):
        if not messagebox.askokcancel('提示','确认删除课程?'):
            return
        if not self.courses.selection():
            return
        course = self.courses.item(self.courses.selection()[0])
        course = self.student.get_course_by_id(course['text'][6:])
        self.student.remove_course(course)
        self.courses.delete(self.courses.selection())

    def modifyCourse(self,event:Event=None):
        if not self.courses.selection():
            return
        course = self.courses.item(self.courses.selection()[0])
        course = self.student.get_course_by_id(course['text'][6:])
        self.modifyWindow = Toplevel(self.window)
        self.modifyWindow.title('修改课程')
        self.modifyWindow.geometry('300x200')
        self.modifyWindow.resizable(0,0)
        self.modifyWindow.transient(self.window)
        self.modifyWindow.grab_set()
        # 课程名
        self.cnameLabel = Label(self.modifyWindow,text='课程名')
        self.cnameLabel.pack()
        self.cnameEntry = Entry(self.modifyWindow)
        self.cnameEntry.insert(0,course.cname)
        self.cnameEntry.pack()
        # 分数
        self.gradeLabel = Label(self.modifyWindow,text='分数')
        self.gradeLabel.pack()
        self.gradeEntry = Entry(self.modifyWindow)
        self.gradeEntry.insert(0,course.grade)
        isNumber().applyVaildateForEntry(self.gradeEntry)
        self.gradeEntry.pack()
        # 学分
        self.creditLabel = Label(self.modifyWindow,text='学分')
        self.creditLabel.pack()
        self.creditEntry = Entry(self.modifyWindow)
        self.creditEntry.insert(0,course.credit)
        isNumber().applyVaildateForEntry(self.creditEntry)
        self.creditEntry.pack()
        # 确认按钮
        self.confirmButton = Button(self.modifyWindow,text='确认',command=lambda:self.confirmModifyCourse(course))
        self.confirmButton.pack()

    def confirmModifyCourse(self,course:Manager.Course):
        cname = self.cnameEntry.get()
        grade = self.gradeEntry.get()
        credit = self.creditEntry.get()
        if cname == '' or grade == '' or credit == '':
            messagebox.showinfo('提示','课程名、分数、学分不能为空')
            return
        course.cname = cname
        course.grade = float(grade)
        course.credit = float(credit)
        self.modifyWindow.destroy()
        self.courses.delete(self.courses.selection())
        self.courses.insert('','end',values=(cname,grade,float(credit),Manager.grade_to_gpa(float(grade))),text=f"[课程代码]{course.cid}")
        
    def resize(self,event:Event):
        if event.widget != self.window:
            return
        if event.width < 400 or event.height < 300:
            self.window.geometry('400x300')
            event.width = 400
            event.height = 300
        self.label.config(height=1)
        self.label.place(x=0,y=0,width=event.width)
        self.courses.place(x=0,y=self.label.winfo_height(),width=event.width,height=event.height-self.label.winfo_height()*2)
        self.courses.heading('课程名',text='课程名')
        self.courses.heading('分数',text='分数')
        self.courses.heading('学分',text='学分')
        self.courses.heading('GPA',text='GPA')
        self.editFrame.place(x=0,y=event.height-self.label.winfo_height(),width=event.width,height=self.label.winfo_height())
        self.addCourseButton.place(x=0,y=0,width=event.width//4,height=self.label.winfo_height())
        self.deleteCourseButton.place(x=event.width//4,y=0,width=event.width//4,height=self.label.winfo_height())
        self.modifyCourseButton.place(x=(event.width//4)*2,y=0,width=event.width//4,height=self.label.winfo_height())
        self.modifyMainInfoButton.place(x=(event.width//4)*3,y=0,width=event.width//4,height=self.label.winfo_height())
        self.addCourseButton.update()
        self.deleteCourseButton.update()
        self.modifyCourseButton.update()
    def close(self,event:Event):
        if event.widget != self.window:
            return
        if self.master:
            self.master.showStudents(None) 
            self.master.showStudentInfo(self.master.students.selection())
        
class ManagerUI:
    def __init__(self,config:dict):
        self.openNewDB(**config,init=True)
        self.window:Tk = Tk()
        self.window.title('学生管理系统')
        self.window.geometry('800x600')
        self.window.bind('<Configure>',self.resize)

        self.initUI()


        self.window.mainloop()
    def initUI(self):
        self.createMenu()
        
        # 文本左对齐
        self.label = Label(self.window,text="已连接到数据库:" + str(self.sql),anchor=W)
        self.label.pack(fill=X)

        # 分学院显示学生信息
        # 左侧为学院列表，右侧为学生信息
        self.frame = Frame(self.window)
        self.frame.pack()
        self.listbox = Listbox(self.frame)
        self.listbox.pack()
        self.listbox.bind('<<ListboxSelect>>',self.showStudents)
        def on_focus_out(evt):
            if self.listbox_select:
                self.listbox.selection_set(self.listbox_select)
        self.listbox.bind('<FocusOut>',on_focus_out)
        self.listbox.bind('<Double-1>',self.showCollegeInfo)
        self.students = ttk.Treeview(self.frame)
        # 设置列
        self.students['columns'] = ('学号','姓名')
        self.students.column('学号',width=100)
        self.students.column('姓名',width=100)
        self.students.bind('<<TreeviewSelect>>',self.showStudentInfo)
        self.students.bind('<Double-1>',self.doubleClickStudent)
        self.students.pack()
        def treeview_focus_out(evt):
            if self.students.selection():
                self.students.selection_set(self.students.selection())
        self.students.bind('<FocusOut>',treeview_focus_out)
        # 提供一个表格显示选中的学生信息
        # AGE | NAME | ID | COLLEGE
        # 然后下面显示该学生所有课程信息
        # 课程ID | 课程名 | 分数 | 学分 | GPA

        self.studentInfos = Frame(self.window)
        self.studentInfos.pack()
        self.studentInfo = ttk.Treeview(self.studentInfos)
        # 设置列
        self.studentInfo['columns'] = ('课程名','分数','学分','GPA')
        self.studentInfo.column('课程名',width=100)
        self.studentInfo.column('分数',width=50)
        self.studentInfo.column('学分',width=50)
        self.studentInfo.column('GPA',width=50)
        self.studentInfo.pack()

        self.studentMainInfo = Label(self.studentInfos,text='学生信息',anchor=SW)

        self.showColleges()
    def doubleClickStudent(self,event:Event):
        if not self.students.selection():
            return
        student = self.students.item(self.students.selection()[0])
        student = self.manager.get_student_by_sid(int(student['values'][0]))
        StudentInfoUI(student,self)
    def resize(self,event:Event):
        if event.widget != self.window:
            return
        if event.width < 800 or event.height < 600:
            self.window.geometry('800x600')
            event.width = 800
            event.height = 600
        self.label.config(height=1)
        self.label.place(x=0,y=event.height-self.label.winfo_height(),width=event.width)
        self.frame.place(x=0,y=0,width=event.width,height=event.height-self.label.winfo_height())
        self.listbox.place(x=0,y=0,width=event.width//3,height=event.height-self.label.winfo_height())
        self.students.place(x=event.width//3,y=0,width=event.width-(event.width//3),height=(event.height-self.label.winfo_height())//2)
        self.students.heading('学号',text='学号')
        self.students.heading('姓名',text='姓名')
        
        self.studentInfos.place(x=event.width//3,y=(event.height-self.label.winfo_height())//2,width=event.width-(event.width//3),height=(event.height-self.label.winfo_height())//2)
        self.studentMainInfo.config(height=2)
        self.studentMainInfo.place(x=0,y=0,width=event.width-(event.width//3))
        self.studentMainInfo.update()
        self.studentInfo.place(x=0,y=self.studentMainInfo.winfo_height(),width=self.studentInfos.winfo_width(),height=self.studentInfos.winfo_height()-self.studentMainInfo.winfo_height())
        self.studentInfo.heading('课程名',text='课程名')
        self.studentInfo.heading('分数',text='分数')
        self.studentInfo.heading('学分',text='学分')
        self.studentInfo.heading('GPA',text='GPA')
    def showStudentInfo(self,event:Event):
        if not self.students.selection():
            return
        student = self.students.item(self.students.selection()[0])
        student = self.manager.get_student_by_sid(int(student['values'][0]))
        self.studentMainInfo.config(text=f'学生信息  年龄:{student.sage}  总学分:{student.get_credit()}  GPA:{student.get_gpa()}')

        self.studentInfo.delete(*self.studentInfo.get_children())
        courses = student.courses
        for course in courses:
            self.studentInfo.insert('','end',values=(course.cname,course.grade,course.credit,Manager.grade_to_gpa(course.grade)),text=f"[课程代码]{course.cid}")
    def createMenu(self):
        self.menu = Menu(self.window)
        self.window.config(menu=self.menu)
        # 创建编辑菜单
        edit_menu = Menu(self.menu, tearoff=0)
        self.menu.add_cascade(label='编辑', menu=edit_menu)

        # 添加命令到编辑菜单，并分配快捷键
        edit_menu.add_command(label='连接到数据库', command=self.openNewDB, accelerator='Ctrl+O')
        edit_menu.add_command(label='保存到数据库', command=self.saveDB, accelerator='Ctrl+S')
        
        # ----
        edit_menu.add_separator()

        edit_menu.add_command(label='添加学生', command=self.addStudent, accelerator='Ctrl+A')
        edit_menu.add_command(label='删除学生', command=self.deleteStudent, accelerator='Ctrl+D')
        edit_menu.add_command(label='添加学院', command=self.addCollege, accelerator='Ctrl+Shift+A')
        edit_menu.add_command(label='删除学院', command=self.deleteCollege, accelerator='Ctrl+Shift+D')

        edit_menu.add_separator()
        edit_menu.add_command(label='移动学生', command=self.moveStudent, accelerator='Ctrl+M')
        

        # 绑定快捷键到相应的方法
        self.window.bind('<Control-o>', lambda event: self.openNewDB())
        self.window.bind('<Control-s>', lambda event: self.saveDB())
        self.window.bind('<Control-a>', lambda event: self.addStudent())
        self.window.bind('<Control-d>', lambda event: self.deleteStudent())
        self.window.bind('<Control-Shift-A>', lambda event: self.addCollege())
        self.window.bind('<Control-Shift-D>', lambda event: self.deleteCollege())
        self.window.bind('<Control-m>', lambda event: self.moveStudent())

        sort_menu = Menu(self.menu, tearoff=0)
        self.menu.add_cascade(label='排序', menu=sort_menu)
        sort_menu.add_command(label='对学院排序', command=self.manager.sort, accelerator='F1')
        sort_menu.add_command(label='按学号排序', command=self.sort_by_sid, accelerator='F2')
        sort_menu.add_command(label='按姓名排序', command=self.sort_by_name, accelerator='F3')
        sort_menu.add_command(label='按年龄排序', command=self.sort_by_age, accelerator='F4')
        sort_menu.add_command(label='按学分排序', command=self.sort_by_credit, accelerator='F5')
        sort_menu.add_command(label='按GPA排序', command=self.sort_by_gpa,accelerator='F6')
        sort_menu.add_command(label='按班级排序', command=self.sort_by_classname,accelerator='F7')

        # F1 - F7
        self.window.bind('<F1>', lambda event: self.manager.sort())
        self.window.bind('<F2>', lambda event: self.sort_by_sid())
        self.window.bind('<F3>', lambda event: self.sort_by_name())
        self.window.bind('<F4>', lambda event: self.sort_by_age())
        self.window.bind('<F5>', lambda event: self.sort_by_credit())
        self.window.bind('<F6>', lambda event: self.sort_by_gpa())
        self.window.bind('<F7>', lambda event: self.sort_by_classname())

    def sort_by_classname(self):
        if not self.listbox.curselection():
            messagebox.showinfo('提示','未选中学院')
            return
        college = self.listbox.get(self.listbox.curselection())
        self.manager[college].sort_by_classname()
        self.showStudents(None)
    def sort_by_age(self):
        if not self.listbox.curselection():
            messagebox.showinfo('提示','未选中学院')
            return
        college = self.listbox.get(self.listbox.curselection())
        self.manager[college].sort_by_age()
        self.showStudents(None)
    def sort_by_name(self):
        if not self.listbox.curselection():
            messagebox.showinfo('提示','未选中学院')
            return
        college = self.listbox.get(self.listbox.curselection())
        self.manager[college].sort_by_name()
        self.showStudents(None)        
    def sort_by_gpa(self):
        if not self.listbox.curselection():
            messagebox.showinfo('提示','未选中学院')
            return
        college = self.listbox.get(self.listbox.curselection())
        self.manager[college].sort_by_gpa()
        self.showStudents(None)
    def sort_by_credit(self):
        if not self.listbox.curselection():
            messagebox.showinfo('提示','未选中学院')
            return
        college = self.listbox.get(self.listbox.curselection())
        self.manager[college].sort_by_credit()
        self.showStudents(None)
    def sort_by_sid(self):
        if not self.listbox.curselection():
            messagebox.showinfo('提示','未选中学院')
            return
        college = self.listbox.get(self.listbox.curselection())
        self.manager[college].sort()
        self.showStudents(None)

    def addCollege(self):
        # 弹出一个新窗口，输入学院名称
        # 点击确认后调用Manager的方法
        self.addWindow = Toplevel(self.window)
        self.addWindow.title('添加学院')
        self.addWindow.geometry('300x100')
        self.addWindow.resizable(0,0)
        self.addWindow.transient(self.window)
        self.addWindow.grab_set()
        # 学院
        self.collegeLabel = Label(self.addWindow,text='学院')
        self.collegeLabel.pack()
        self.collegeEntry = Entry(self.addWindow)
        self.collegeEntry.pack()
        # 确认按钮
        self.confirmButton = Button(self.addWindow,text='确认',command=self.confirmAddCollege)
        self.confirmButton.pack()
    def confirmAddCollege(self):
        college = self.collegeEntry.get()
        if college in [college.college for college in self.manager.collages]:
            # 提示学院已存在
            messagebox.showinfo('提示','学院已存在')
            return
        if college == '':
            # 提示学院名称不能为空
            messagebox.showinfo('提示','学院名称不能为空')
            return
        self.manager.add(Manager.CollegeStudentManager(self.sql,college))
        self.addWindow.destroy()
        self.showColleges()
    def deleteCollege(self):
        self.deleteWindow = Toplevel(self.window)
        self.deleteWindow.title('删除学院')
        self.deleteWindow.geometry('400x100')  # 调整窗口大小以适应新布局
        self.deleteWindow.resizable(0,0)
        self.deleteWindow.transient(self.window)
        self.deleteWindow.grab_set()

        # 使用Frame增加布局的灵活性
        inputFrame = Frame(self.deleteWindow)
        inputFrame.pack(fill='x', padx=10, pady=10)

        # 学院标签和下拉选择框
        self.collegeLabel = Label(inputFrame, text='学院')
        self.collegeLabel.grid(row=0, column=0, sticky='e')
        self.collegeVar = StringVar()
        self.collegeVar.set('请选择学院')
        college_names = [college.college for college in self.manager.collages]
        self.collegeCombo = ttk.Combobox(inputFrame, textvariable=self.collegeVar, values=college_names)
        self.collegeCombo.grid(row=0, column=1, sticky='ew')

        # 确认按钮
        self.confirmButton = Button(self.deleteWindow, text='确认', command=self.confirmDeleteCollege)
        self.confirmButton.pack(pady=10)

        # 调整列的配置以使选择框能够扩展填充整个窗口宽度
        inputFrame.columnconfigure(1, weight=1)
    def confirmDeleteCollege(self):
        # 显示警告框，确认删除
        message = f'确认删除学院：{self.collegeVar.get()}?'
        if not messagebox.askokcancel('警告',message):
            return
        college = self.collegeVar.get()
        self.manager.remove_by_name(college)
        self.deleteWindow.destroy()
        self.showColleges()

    def showColleges(self):
        self.listbox.delete(0,END)
        colleges = self.manager.collages
        for college in colleges:
            self.listbox.insert(END,college.college)
    def showStudents(self,event):
        self.listbox_select = self.listbox.curselection()
        if not self.listbox.curselection():  # 检查是否有选项被选中
            return  # 如果没有选项被选中，直接返回，不执行后续操作
        self.students.delete(*self.students.get_children())
        college = self.listbox.get(self.listbox.curselection())
        students = self.manager[college].students
        for student in students:
            self.students.insert('','end',values=(student.sid,student.sname),text=student.classname)

    def addStudent(self):
        # 弹出一个新窗口，输入学生信息
        # 姓名、学号、学院
        # 点击确认后调用Manager的方法
        
        # 下面创建一个新窗口
        self.addWindow = Toplevel(self.window)
        self.addWindow.title('添加学生')
        self.addWindow.geometry('400x200')  # 调整窗口大小以适应新布局
        self.addWindow.resizable(0,0)
        self.addWindow.transient(self.window)
        self.addWindow.grab_set()

        # 使用Frame增加布局的灵活性
        inputFrame = Frame(self.addWindow)
        inputFrame.pack(padx=10, pady=10, fill='x', expand=True)

        # 姓名
        self.nameLabel = Label(inputFrame, text='姓名')
        self.nameLabel.grid(row=0, column=0, sticky='e')
        self.nameEntry = Entry(inputFrame)
        self.nameEntry.grid(row=0, column=1, sticky='ew')

        # 学号
        self.idLabel = Label(inputFrame, text='学号')
        self.idLabel.grid(row=1, column=0, sticky='e')
        self.idEntry = Entry(inputFrame)
        isNumber().applyVaildateForEntry(self.idEntry)
        self.idEntry.grid(row=1, column=1, sticky='ew')

        # 学院
        self.collegeLabel = Label(inputFrame, text='学院(留空添加到当前学院)')
        self.collegeLabel.grid(row=2, column=0, sticky='e')
        self.collegeEntry = Entry(inputFrame)
        self.collegeEntry.grid(row=2, column=1, sticky='ew')

        # 确认按钮
        self.confirmButton = Button(self.addWindow, text='确认', command=self.confirmAdd)
        self.confirmButton.pack(pady=10)

        # 调整列的配置以使编辑框能够扩展填充整个窗口宽度
        inputFrame.columnconfigure(1, weight=1)
    def confirmAdd(self):
        name = self.nameEntry.get()
        id = self.idEntry.get()
        college = self.collegeEntry.get()
        if name == '' or id == '':
            # 提示姓名和学号不能为空
            messagebox.showinfo('提示','姓名和学号不能为空')
            return
        if college == '':
            if not self.listbox.curselection():
                # 提示没有学院
                messagebox.showinfo('提示','未选中学院，学院不能为空')
                return
            college = self.listbox.get(self.listbox.curselection())
        if self.manager[college] == None:
            # 提示学院不存在
            messagebox.showinfo('提示','学院不存在')
            return
        self.manager[college].add(Manager.Student(self.sql,int(id),name))
        self.addWindow.destroy()
        self.showStudents(None)
    
    def deleteStudent(self):
        # 弹出一个新窗口，输入学号
        # 点击确认后调用Manager的方法
        self.deleteWindow = Toplevel(self.window)
        self.deleteWindow.title('删除学生')
        self.deleteWindow.geometry('300x100')
        self.deleteWindow.resizable(0,0)
        self.deleteWindow.transient(self.window)
        self.deleteWindow.grab_set()

        # 使用Frame增加布局的灵活性
        inputFrame = Frame(self.deleteWindow)
        inputFrame.pack(fill='x', padx=10, pady=10)

        # 学号
        self.idLabel = Label(inputFrame, text='学号')
        self.idLabel.grid(row=0, column=0, sticky='e')
        self.idEntry = Entry(inputFrame)
        isNumber().applyVaildateForEntry(self.idEntry)
        self.idEntry.grid(row=0, column=1)

        # 确认按钮
        self.confirmButton = Button(self.deleteWindow, text='确认', command=self.confirmDelete)
        self.confirmButton.pack(pady=10)
        inputFrame.columnconfigure(1, weight=1)
    def confirmDelete(self):
        id = self.idEntry.get()
        if not self.listbox.curselection():
            # 提示未选中学院
            messagebox.showinfo('提示','未选中学院')
            return
        college = self.listbox.get(self.listbox.curselection())
        if not self.manager[college].get_student_by_sid(int(id)):
            # 提示学生不存在
            messagebox.showinfo('提示','学生不存在')
            return
        self.manager[college].remove_student_by_sid(int(id))
        self.deleteWindow.destroy()
        self.showStudents(None)

    def openNewDB(self,host='localhost',port=3306,user='root',password='',database='',charset='utf8',init=False):
        # 询问是否保存当前数据库
        # 如果是，调用saveDB
        if init:
            self.host = host
            self.port = port
            self.user = user
            self.password = password
            self.database = database
            self.charset = charset

            # 直接连接到数据库
            try:
                self.sql = SQLManager.SQLManager(host=host,port=port,user=user,password=password,database=database,charset=charset)
                self.manager = Manager.SchoolStudentManager(self.sql)
                self.manager.load_from_db()
            except Exception as e:
                messagebox.showinfo('提示',f'连接失败:{str(e)}')
                self.manager = Manager.SchoolStudentManager(None)
                self.sql = None
                return
            return
        if messagebox.askyesno('提示','是否保存当前数据库'):
            self.saveDB()

        # 弹出一个新窗口，输入数据库信息
        # 点击确认后调用Manager的方法
        self.dbWindow = Toplevel(self.window)
        self.dbWindow.title('连接到数据库')
        self.dbWindow.geometry('300x200')
        self.dbWindow.resizable(0,0)
        self.dbWindow.transient(self.window)
        self.dbWindow.grab_set()
        # 使用Frame增加布局的灵活性
        inputFrame = Frame(self.dbWindow)
        inputFrame.pack(padx=10, pady=10)

        # 主机
        self.hostLabel = Label(inputFrame, text='主机')
        self.hostLabel.grid(row=0, column=0, sticky='e')
        self.hostEntry = Entry(inputFrame)
        self.hostEntry.insert(0, self.host)
        self.hostEntry.grid(row=0, column=1)

        # 用户名
        self.userLabel = Label(inputFrame, text='用户名')
        self.userLabel.grid(row=1, column=0, sticky='e')
        self.userEntry = Entry(inputFrame)
        self.userEntry.insert(0, self.user)
        self.userEntry.grid(row=1, column=1)

        # 密码
        self.passwordLabel = Label(inputFrame, text='密码')
        self.passwordLabel.grid(row=2, column=0, sticky='e')
        self.passwordEntry = Entry(inputFrame, show='*')
        self.passwordEntry.grid(row=2, column=1)

        # 数据库
        self.dbLabel = Label(inputFrame, text='数据库')
        self.dbLabel.grid(row=3, column=0, sticky='e')
        self.dbEntry = Entry(inputFrame)
        self.dbEntry.insert(0, self.database)
        self.dbEntry.grid(row=3, column=1)

        # 编码
        self.charsetLabel = Label(inputFrame, text='编码')
        self.charsetLabel.grid(row=4, column=0, sticky='e')
        self.charsetEntry = Entry(inputFrame)
        self.charsetEntry.insert(0, self.charset)
        self.charsetEntry.grid(row=4, column=1)

        # 确认按钮
        self.confirmButton = Button(self.dbWindow, text='确认', command=self.confirmNewDB)
        self.confirmButton.pack(pady=10)
    def confirmNewDB(self):
        host = self.hostEntry.get()
        user = self.userEntry.get()
        password = self.passwordEntry.get()
        db = self.dbEntry.get()
        charset = self.charsetEntry.get()
        try:
            self.sql = SQLManager.SQLManager(host=host,user=user,password=password,database=db,charset=charset)
        except Exception as e:
            messagebox.showinfo('提示',f'连接失败:{str(e)}')
            return
        self.label.config(text=f'已连接到数据库:{str(self.sql)}')
        self.manager = Manager.SchoolStudentManager(self.sql)
        self.manager.load_from_db()
        self.dbWindow.destroy()
        self.showColleges()
    def saveDB(self):
        self.label.config(text=f'正在保存到数据库:{str(self.sql)}')
        self.manager.save_to_db()
        self.label.config(text='保存成功')
    def showCollegeInfo(self,event):
        # 显示学院信息(学院名称、学生数量、平均年龄、平均学分、平均GPA)

        # 1. 获取当前选中的学院
        if not self.listbox.curselection():
            return
        college = self.listbox.get(self.listbox.curselection())
        college = self.manager[college]

        # 2. 计算学生数量、平均年龄、平均学分、平均GPA
        avg_age = 0
        avg_credit = 0
        avg_gpa = 0
        students = college.students
        if len(students) == 0:
            messagebox.showinfo('提示','学院没有学生')
            return
        for student in students:
            avg_age += student.sage
            avg_credit += student.get_credit()
            avg_gpa += student.get_gpa()
        avg_age /= len(students)
        avg_credit /= len(students)
        avg_gpa /= len(students)
        # 3. 显示学院信息
        messagebox.showinfo('学院信息',f'学院:{college.college}\n学生数量:{len(students)}\n平均年龄:{round(avg_age, 3)}\n平均学分:{round(avg_credit, 3)}\n平均GPA:{round(avg_gpa, 3)}')
    def moveStudent(self,event=None):
        # 弹出一个新窗口，输入学号和学院
        # 点击确认后调用Manager的方法
        self.moveWindow = Toplevel(self.window)
        self.moveWindow.title('移动学生')
        self.moveWindow.geometry('400x125')  # 调整窗口大小以适应新布局
        self.moveWindow.resizable(0,0)
        self.moveWindow.transient(self.window)
        self.moveWindow.grab_set()

        # 学号输入框和学院下拉选择框
        inputFrame = Frame(self.moveWindow)
        inputFrame.pack(fill='x', padx=10, pady=10)

        # 学号
        self.idLabel = Label(inputFrame, text='学号')
        self.idLabel.grid(row=0, column=0, sticky='e')
        self.idEntry = Entry(inputFrame)
        isNumber().applyVaildateForEntry(self.idEntry)
        self.idEntry.grid(row=0, column=1, sticky='ew')

        # 学院
        self.collegeLabel = Label(inputFrame, text='目标学院')
        self.collegeLabel.grid(row=1, column=0, sticky='e')
        self.collegeVar = StringVar()
        self.collegeVar.set('请选择学院')
        college_names = [college.college for college in self.manager.collages]
        self.collegeCombo = ttk.Combobox(inputFrame, textvariable=self.collegeVar, values=college_names)
        self.collegeCombo.grid(row=1, column=1, sticky='ew')

        # 确认按钮
        self.confirmButton = Button(self.moveWindow, text='确认', command=self.confirmMove)
        self.confirmButton.pack(pady=10)

        # 调整列的配置以使选择框能够扩展填充整个窗口宽度
        inputFrame.columnconfigure(1, weight=1)
    def confirmMove(self):
        id = self.idEntry.get()
        college = self.collegeVar.get()
        if not self.manager.get_student_by_sid(int(id)):
            # 提示学生不存在
            messagebox.showinfo('提示','学生不存在')
            return
        self.manager.move_student(int(id),college)
        self.moveWindow.destroy()
        self.showStudents(None)
        


if __name__ == '__main__':
    with open('config.json','r') as f:
        config = json.load(f)
    ManagerUI(config)
