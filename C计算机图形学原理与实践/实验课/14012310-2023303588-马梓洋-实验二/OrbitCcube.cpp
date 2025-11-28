#include <GL/glut.h>
#include <cmath>
#include <iostream>

// 立方体参数
float cubeSize = 0.1f;  // 原始半径
float scaleFactor = 2.0f;  // 放大倍数
float rotationAngle = 60.0f;  // 旋转角度
float circleRadius = 0.5f;  // 圆周半径

// 初始化函数
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 黑色背景
    glEnable(GL_DEPTH_TEST);  // 启用深度测试

    std::cout << "立方体变换演示程序" << std::endl;
    std::cout << "原始半径: " << cubeSize << std::endl;
    std::cout << "放大倍数: " << scaleFactor << std::endl;
    std::cout << "旋转角度: " << rotationAngle << "度" << std::endl;
    std::cout << "圆周半径: " << circleRadius << std::endl;
}

// 绘制立方体函数
void drawCube() {
    // 设置立方体颜色为蓝色
    glColor3f(0.0f, 0.5f, 1.0f);

    // 开始绘制立方体
    glutSolidCube(cubeSize * 2 * scaleFactor);  // glutSolidCube的参数是边长

    // 绘制边框以便更好观察
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(cubeSize * 2 * scaleFactor * 1.01f);
}

// 显示函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 设置相机位置
    gluLookAt(0.0f, 0.0f, 2.0f,    // 相机位置
        0.0f, 0.0f, 0.0f,    // 观察点
        0.0f, 1.0f, 0.0f);   // 上方向

    // 应用变换：绕圆周旋转
    float angleRad = rotationAngle * 3.14 / 180.0f;
    float xPos = circleRadius * cos(angleRad);
    float yPos = circleRadius * sin(angleRad);

    // 先平移后旋转
    glTranslatef(xPos, yPos, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

    // 绘制立方体
    drawCube();

    // 绘制参考圆周
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14 / 180.0f;
        glVertex3f(circleRadius * cos(angle), circleRadius * sin(angle), 0.0f);
    }
    glEnd();

    // 绘制坐标轴
    glBegin(GL_LINES);
    // X轴 - 红色
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    // Y轴 - 绿色
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    // Z轴 - 蓝色
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();

    glutSwapBuffers();
}

// 窗口大小改变回调函数
void reshape(int width, int height) {
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

// 键盘输入处理
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:  // ESC键退出
        exit(0);
        break;
    case 'r':
    case 'R':
        rotationAngle += 10.0f;
        if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;
        std::cout << "当前旋转角度: " << rotationAngle << "度" << std::endl;
        glutPostRedisplay();
        break;
    case 's':
    case 'S':
        scaleFactor += 0.1f;
        std::cout << "当前放大倍数: " << scaleFactor << std::endl;
        glutPostRedisplay();
        break;
    }
}

// 特殊键处理（方向键）
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        rotationAngle -= 5.0f;
        if (rotationAngle < 0.0f) rotationAngle += 360.0f;
        break;
    case GLUT_KEY_RIGHT:
        rotationAngle += 5.0f;
        if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;
        break;
    case GLUT_KEY_UP:
        circleRadius += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        circleRadius -= 0.1f;
        if (circleRadius < 0.1f) circleRadius = 0.1f;
        break;
    }
    std::cout << "旋转角度: " << rotationAngle << "度, 圆周半径: " << circleRadius << std::endl;
    glutPostRedisplay();
}

// 打印使用说明
void printInstructions() {
    std::cout << "\n=== 控制说明 ===" << std::endl;
    std::cout << "ESC: 退出程序" << std::endl;
    std::cout << "R/r: 增加旋转角度" << std::endl;
    std::cout << "S/s: 增加放大倍数" << std::endl;
    std::cout << "方向键左/右: 调整旋转角度" << std::endl;
    std::cout << "方向键上/下: 调整圆周半径" << std::endl;
    std::cout << "================\n" << std::endl;
}

int main(int argc, char** argv) {
    // 初始化GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("立方体变换演示 - OpenGL");

    // 打印使用说明
    printInstructions();

    // 注册回调函数
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    // 进入主循环
    glutMainLoop();

    return 0;
}