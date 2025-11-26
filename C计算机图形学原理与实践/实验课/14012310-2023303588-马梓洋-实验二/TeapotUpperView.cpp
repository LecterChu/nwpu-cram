#include <GL/glut.h>
#include <iostream>

// 窗口尺寸
int windowWidth = 800;
int windowHeight = 600;

// 初始化函数
void init() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // 深灰色背景
    glEnable(GL_DEPTH_TEST);

    // 启用光照
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = { 0.0f, 2.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    GLfloat whiteLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    std::cout << "茶壶部分显示演示程序" << std::endl;
    std::cout << "将茶壶的上半部分显示在窗口的左下四分之一区域" << std::endl;
}

// 显示函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 设置茶壶材质
    GLfloat teapotColor[] = { 0.7f, 0.5f, 0.9f, 1.0f };  // 紫色
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, teapotColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    // 设置视口为整个窗口，用于绘制完整茶壶（参考）
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // 绘制完整茶壶（半透明，作为参考）
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLfloat transparentColor[] = { 0.7f, 0.5f, 0.9f, 0.3f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, transparentColor);
    glutSolidTeapot(1.0);
    glDisable(GL_BLEND);

    // 设置裁剪平面，只显示茶壶上半部分 (y >= 0)
    GLdouble clipPlane[] = { 0.0, 1.0, 0.0, 0.0 }; // 保留 y >= 0 的部分
    glClipPlane(GL_CLIP_PLANE0, clipPlane);
    glEnable(GL_CLIP_PLANE0);

    // 设置视口为左下四分之一区域
    int quarterWidth = windowWidth / 2;
    int quarterHeight = windowHeight / 2;
    glViewport(0, 0, quarterWidth, quarterHeight);

    // 设置投影矩阵 - 使用透视投影
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)quarterWidth / quarterHeight, 0.1f, 100.0f);

    // 设置模型视图矩阵 - 调整视角以显示茶壶上半部分
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // 调整相机位置，使茶壶上半部分在视口中居中
    gluLookAt(0.0f, 0.3f, 2.5f, 0.0f, 0.3f, 0.0f, 0.0f, 1.0f, 0.0f);

    // 绘制茶壶（只显示上半部分）
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, teapotColor);
    glutSolidTeapot(1.0);

    glDisable(GL_CLIP_PLANE0);

    // 绘制视口边框
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f); // 黄色边框
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

// 窗口大小改变回调函数
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    glutPostRedisplay();
}

// 键盘输入处理
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC键退出
        exit(0);
        break;
    case 'r':
    case 'R':
        glutPostRedisplay();
        break;
    case 'c':
    case 'C':
        // 切换是否显示完整茶壶作为参考
        static bool showFullTeapot = true;
        showFullTeapot = !showFullTeapot;
        if (!showFullTeapot) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 黑色背景
        }
        else {
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // 深灰色背景
        }
        glutPostRedisplay();
        break;
    }
}

// 打印使用说明
void printInstructions() {
    std::cout << "\n=== 程序说明 ===" << std::endl;
    std::cout << "将茶壶的上半部分显示在窗口的左下四分之一区域" << std::endl;
    std::cout << "完整茶壶以半透明方式显示作为参考" << std::endl;
    std::cout << "黄色边框标示了左下四分之一区域" << std::endl;
    std::cout << "\n=== 控制说明 ===" << std::endl;
    std::cout << "ESC: 退出程序" << std::endl;
    std::cout << "R/r: 重绘场景" << std::endl;
    std::cout << "C/c: 切换是否显示完整茶壶参考" << std::endl;
    std::cout << "================\n" << std::endl;
}

int main(int argc, char** argv) {
    // 初始化GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("茶壶上半部分显示演示 - OpenGL");

    // 打印使用说明
    printInstructions();

    // 注册回调函数
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // 进入主循环
    glutMainLoop();

    return 0;
}