#include <GL/glut.h>
#include <stdio.h>

// 全局变量
static int window;
static int menu_id;
static int value = 0;

// 初始化函数
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); // 设置背景颜色为黑色
    glShadeModel(GL_FLAT); // 设置着色模式
}

// 显示函数
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区
    glLoadIdentity(); // 重置当前矩阵

    // 设置观察点
    gluLookAt(0.0, 0.0, 5.0,  // 观察点位置
        0.0, 0.0, 0.0,  // 观察目标位置
        0.0, 1.0, 0.0); // 向上向量

    // 根据当前选择的图形进行绘制
    switch (value) {
    case 1:
        // 绘制红色球体
        glColor3f(1.0, 0.0, 0.0);
        glutWireSphere(1.0, 20, 20);
        break;
    case 2:
        // 绘制绿色圆锥
        glColor3f(0.0, 1.0, 0.0);
        glutWireCone(1.0, 2.0, 20, 20);
        break;
    case 3:
        // 绘制蓝色立方体
        glColor3f(0.0, 0.0, 1.0);
        glutWireCube(2.0);
        break;
    case 4:
        // 绘制紫色茶壶
        glColor3f(1.0, 0.0, 1.0);
        glutWireTeapot(1.0);
        break;
    case 5:
        // 绘制黄色实线（车道线）
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(-2.0, 0.0, 0.0);
        glVertex3f(2.0, 0.0, 0.0);
        glEnd();

        // 绘制白色虚线（两侧）
        glColor3f(1.0, 1.0, 1.0);
        glEnable(GL_LINE_STIPPLE); // 启用虚线模式
        glLineStipple(1, 0x00FF); // 设置虚线模式

        // 上方虚线
        glBegin(GL_LINES);
        glVertex3f(-2.0, 0.5, 0.0);
        glVertex3f(2.0, 0.5, 0.0);
        glEnd();

        // 下方虚线
        glBegin(GL_LINES);
        glVertex3f(-2.0, -0.5, 0.0);
        glVertex3f(2.0, -0.5, 0.0);
        glEnd();

        glDisable(GL_LINE_STIPPLE); // 禁用虚线模式
        break;
    default:
        break;
    }

    glFlush(); // 刷新缓冲区
}

// 重塑函数
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 设置视口
    glMatrixMode(GL_PROJECTION); // 设置投影矩阵
    glLoadIdentity(); // 重置投影矩阵
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // 设置透视投影
    glMatrixMode(GL_MODELVIEW); // 设置模型视图矩阵
}

// 键盘处理函数
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        value = 1;
        glutPostRedisplay(); // 标记需要重新显示
        break;
    case '2':
        value = 2;
        glutPostRedisplay();
        break;
    case '3':
        value = 3;
        glutPostRedisplay();
        break;
    case 27: // ESC键
        glutDestroyWindow(window); // 销毁窗口
        exit(0);
        break;
    default:
        break;
    }
}

// 鼠标处理函数
void mouse(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            value = 4; // 鼠标左键按下时绘制茶壶
            glutPostRedisplay();
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            value = 5; // 鼠标右键按下时绘制车道线
            glutPostRedisplay();
        }
        break;
    default:
        break;
    }
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv); // 初始化GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 设置显示模式
    glutInitWindowSize(500, 500); // 设置窗口大小
    glutInitWindowPosition(100, 100); // 设置窗口位置
    window = glutCreateWindow("三维图形交互程序"); // 创建窗口

    init(); // 初始化

    // 注册回调函数
    glutDisplayFunc(display); // 注册显示回调函数
    glutReshapeFunc(reshape); // 注册重塑回调函数
    glutKeyboardFunc(keyboard); // 注册键盘回调函数
    glutMouseFunc(mouse); // 注册鼠标回调函数

    glutMainLoop(); // 进入主循环
    return 0;
}