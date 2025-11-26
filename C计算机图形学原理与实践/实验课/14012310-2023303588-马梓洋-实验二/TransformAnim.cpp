#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 动画控制变量
float teapotRotation = 0.0f;    // 茶壶当前旋转角度
float teapotTranslation = 0.0f; // 茶壶当前平移距离
float sphereTranslation = 0.0f; // 球体当前平移距离

bool animationRunning = true;   // 动画是否运行
int animationSpeed = 50;        // 动画速度（毫秒）

// 替代to_string的函数
template<typename T>
std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// 初始化函数
void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // 深灰色背景
    glEnable(GL_DEPTH_TEST);  // 启用深度测试

    // 启用光照
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 设置光源位置
    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // 设置光源颜色
    GLfloat whiteLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    std::cout << "OpenGL 变换动画演示程序" << std::endl;
    std::cout << "紫色茶壶: 顺时针旋转60度，向右平移0.5" << std::endl;
    std::cout << "绿色圆球: 从原点向上平移0.2" << std::endl;
}

// 更新动画状态
void update(int value) {
    if (animationRunning) {
        // 更新茶壶旋转角度（顺时针旋转60度）
        if (teapotRotation > -60.0f) {
            teapotRotation -= 2.0f; // 每次减少2度
            if (teapotRotation < -60.0f) teapotRotation = -60.0f;
        }

        // 更新茶壶平移距离（向右平移0.5）
        if (teapotTranslation < 0.5f && teapotRotation <= -60.0f) {
            teapotTranslation += 0.02f; // 每次增加0.02
            if (teapotTranslation > 0.5f) teapotTranslation = 0.5f;
        }

        // 更新球体平移距离（向上平移0.2）
        if (sphereTranslation < 0.2f) {
            sphereTranslation += 0.01f; // 每次增加0.01
            if (sphereTranslation > 0.2f) sphereTranslation = 0.2f;
        }

        glutPostRedisplay();
    }

    // 设置定时器回调
    glutTimerFunc(animationSpeed, update, 0);
}

// 显示函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 设置相机位置
    gluLookAt(1.5f, 1.0f, 1.5f,    // 相机位置
        0.0f, 0.0f, 0.0f,    // 观察点
        0.0f, 1.0f, 0.0f);   // 上方向

    // 绘制坐标轴
    glDisable(GL_LIGHTING);
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

    // 显示当前变换状态
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(-0.9f, 0.9f, 0.0f);

    // 使用替代的toString函数
    std::string status = "茶壶旋转: " + toString(-teapotRotation) + "度, 平移: " +
        toString(teapotTranslation) + ", 球体平移: " +
        toString(sphereTranslation);

    for (size_t i = 0; i < status.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, status[i]);
    }

    glEnable(GL_LIGHTING);

    // 绘制紫色茶壶
    glPushMatrix();
    // 茶壶变换：先旋转后平移
    glTranslatef(teapotTranslation, 0.0f, 0.0f);  // 向右平移
    glRotatef(teapotRotation, 0.0f, 1.0f, 0.0f);  // 绕Y轴旋转

    // 设置紫色材质
    GLfloat purpleColor[] = { 0.6f, 0.2f, 0.8f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purpleColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    glutSolidTeapot(0.1);  // 绘制半径为0.1的茶壶
    glPopMatrix();

    // 绘制绿色圆球
    glPushMatrix();
    // 圆球变换：向上平移
    glTranslatef(0.0f, sphereTranslation, 0.0f);  // 向上平移

    // 设置绿色材质
    GLfloat greenColor[] = { 0.2f, 0.8f, 0.2f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, greenColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0f);

    glutSolidSphere(0.1, 20, 20);  // 绘制半径为0.1的球体
    glPopMatrix();

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
    case ' ':  // 空格键暂停/继续动画
        animationRunning = !animationRunning;
        break;
    case 'r':
    case 'R':  // 重置动画
        teapotRotation = 0.0f;
        teapotTranslation = 0.0f;
        sphereTranslation = 0.0f;
        break;
    case '+':  // 加快动画速度
        animationSpeed -= 10;
        if (animationSpeed < 10) animationSpeed = 10;
        std::cout << "动画速度: " << animationSpeed << "ms" << std::endl;
        break;
    case '-':  // 减慢动画速度
        animationSpeed += 10;
        std::cout << "动画速度: " << animationSpeed << "ms" << std::endl;
        break;
    }
}

// 打印使用说明
void printInstructions() {
    std::cout << "\n=== 程序说明 ===" << std::endl;
    std::cout << "紫色茶壶: 半径0.1，顺时针旋转60度，向右平移0.5" << std::endl;
    std::cout << "绿色圆球: 半径0.1，从原点向上平移0.2" << std::endl;
    std::cout << "红色: X轴，绿色: Y轴，蓝色: Z轴" << std::endl;
    std::cout << "\n=== 控制说明 ===" << std::endl;
    std::cout << "ESC: 退出程序" << std::endl;
    std::cout << "空格: 暂停/继续动画" << std::endl;
    std::cout << "R/r: 重置动画" << std::endl;
    std::cout << "+: 加快动画速度" << std::endl;
    std::cout << "-: 减慢动画速度" << std::endl;
    std::cout << "================\n" << std::endl;
}

int main(int argc, char** argv) {
    // 初始化GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL 变换动画演示 - 茶壶和球体");

    // 打印使用说明
    printInstructions();

    // 注册回调函数
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(animationSpeed, update, 0);

    // 进入主循环
    glutMainLoop();

    return 0;
}