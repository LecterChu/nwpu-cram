#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

// 窗口尺寸
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

// 天体参数
const float SUN_RADIUS = 2.0f;
const float EARTH_RADIUS = 0.5f;
const float MOON_RADIUS = 0.15f;

// 轨道参数
const float EARTH_ORBIT_RADIUS = 8.0f;
const float MOON_ORBIT_RADIUS = 1.5f;

// 运行速度（角度/帧）
const float EARTH_SPEED = 0.5f;  // 地球绕太阳：12个月 = 360度
const float MOON_SPEED = 6.0f;   // 月球绕地球：1个月 = 360度
const float ROTATION_SPEED = 2.0f; // 自转速度

// 当前角度
float earthAngle = 0.0f;
float moonAngle = 0.0f;
float earthRotation = 0.0f;
float moonRotation = 0.0f;

// 光照控制
bool lightingEnabled = true;

// 字符串转换函数（替代std::to_string）
std::string toString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string toString(float value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

// 初始化函数
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // 设置太阳光源
    GLfloat sunLightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat sunLightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat sunLightDiffuse[] = { 1.0f, 0.8f, 0.5f, 1.0f };
    GLfloat sunLightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, sunLightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sunLightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunLightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunLightSpecular);

    // 设置全局环境光
    GLfloat globalAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
}

// 绘制太阳
void drawSun() {
    glPushMatrix();

    // 太阳材质 - 发光体
    GLfloat sunEmission[] = { 0.8f, 0.3f, 0.1f, 1.0f };
    GLfloat sunAmbient[] = { 0.8f, 0.3f, 0.1f, 1.0f };
    GLfloat sunDiffuse[] = { 1.0f, 0.4f, 0.1f, 1.0f };
    GLfloat sunSpecular[] = { 1.0f, 1.0f, 0.8f, 1.0f };

    glMaterialfv(GL_FRONT, GL_EMISSION, sunEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, sunAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sunDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sunSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    // 绘制太阳
    glColor3f(1.0f, 0.4f, 0.1f);
    glutSolidSphere(SUN_RADIUS, 50, 50);

    // 重置发射属性
    GLfloat noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();
}

// 绘制地球
void drawEarth() {
    glPushMatrix();

    // 计算地球位置
    float earthX = EARTH_ORBIT_RADIUS * cos(earthAngle * 3.14159f / 180.0f);
    float earthZ = EARTH_ORBIT_RADIUS * sin(earthAngle * 3.14159f / 180.0f);

    glTranslatef(earthX, 0.0f, earthZ);
    glRotatef(earthRotation, 0.0f, 1.0f, 0.0f); // 地球自转

    // 地球材质
    GLfloat earthAmbient[] = { 0.1f, 0.2f, 0.5f, 1.0f };
    GLfloat earthDiffuse[] = { 0.2f, 0.4f, 0.8f, 1.0f };
    GLfloat earthSpecular[] = { 0.5f, 0.5f, 1.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, earthAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earthDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earthSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0f);

    // 绘制地球
    glColor3f(0.2f, 0.4f, 0.8f);
    glutSolidSphere(EARTH_RADIUS, 30, 30);

    glPopMatrix();
}

// 绘制月球
void drawMoon() {
    glPushMatrix();

    // 先移动到地球位置
    float earthX = EARTH_ORBIT_RADIUS * cos(earthAngle * 3.14159f / 180.0f);
    float earthZ = EARTH_ORBIT_RADIUS * sin(earthAngle * 3.14159f / 180.0f);

    glTranslatef(earthX, 0.0f, earthZ);

    // 再计算月球相对地球的位置
    float moonX = MOON_ORBIT_RADIUS * cos(moonAngle * 3.14159f / 180.0f);
    float moonZ = MOON_ORBIT_RADIUS * sin(moonAngle * 3.14159f / 180.0f);

    glTranslatef(moonX, 0.0f, moonZ);
    glRotatef(moonRotation, 0.0f, 1.0f, 0.0f); // 月球自转

    // 月球材质
    GLfloat moonAmbient[] = { 0.4f, 0.4f, 0.2f, 1.0f };
    GLfloat moonDiffuse[] = { 0.6f, 0.6f, 0.3f, 1.0f };
    GLfloat moonSpecular[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, moonAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moonDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, moonSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

    // 绘制月球
    glColor3f(0.8f, 0.8f, 0.3f);
    glutSolidSphere(MOON_RADIUS, 20, 20);

    glPopMatrix();
}

// 绘制轨道
void drawOrbits() {
    glDisable(GL_LIGHTING);

    // 地球轨道
    glColor3f(0.3f, 0.3f, 0.6f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        float x = EARTH_ORBIT_RADIUS * cos(angle);
        float z = EARTH_ORBIT_RADIUS * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();

    // 月球轨道（在每个地球位置绘制）
    float earthX = EARTH_ORBIT_RADIUS * cos(earthAngle * 3.14159f / 180.0f);
    float earthZ = EARTH_ORBIT_RADIUS * sin(earthAngle * 3.14159f / 180.0f);

    glPushMatrix();
    glTranslatef(earthX, 0.0f, earthZ);

    glColor3f(0.6f, 0.6f, 0.3f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        float x = MOON_ORBIT_RADIUS * cos(angle);
        float z = MOON_ORBIT_RADIUS * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

// 显示信息
void displayInfo() {
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 显示文字信息
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, WINDOW_HEIGHT - 20);

    int earthMonth = static_cast<int>(earthAngle / 30);
    int moonCycle = static_cast<int>(moonAngle / 30);

    std::string info = "太阳系模拟 - 地球月份: " + toString(earthMonth) +
        "  月球周期: " + toString(moonCycle);

    for (size_t i = 0; i < info.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, info[i]);
    }

    // 显示控制说明
    glRasterPos2f(10, 30);
    std::string controls = "控制: ESC退出 | 空格键切换光照 | R重置";
    for (size_t i = 0; i < controls.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, controls[i]);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
}

// 显示函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 设置相机
    static float cameraAngle = 0.0f;
    cameraAngle += 0.2f;
    float camX = 15.0f * sin(cameraAngle * 0.01f);
    float camZ = 15.0f * cos(cameraAngle * 0.01f);

    gluLookAt(camX, 8.0f, camZ,    // 相机位置
        0.0f, 0.0f, 0.0f,    // 观察点
        0.0f, 1.0f, 0.0f);   // 上方向

    // 绘制场景
    drawOrbits();
    drawSun();
    drawEarth();
    drawMoon();
    displayInfo();

    glutSwapBuffers();
}

// 更新动画
void update(int value) {
    // 更新角度
    earthAngle += EARTH_SPEED;
    moonAngle += MOON_SPEED;
    earthRotation += ROTATION_SPEED;
    moonRotation += ROTATION_SPEED * 0.5f;

    // 保持角度在0-360度范围内
    if (earthAngle >= 360.0f) earthAngle -= 360.0f;
    if (moonAngle >= 360.0f) moonAngle -= 360.0f;
    if (earthRotation >= 360.0f) earthRotation -= 360.0f;
    if (moonRotation >= 360.0f) moonRotation -= 360.0f;

    // 更新太阳光源位置（虽然太阳在中心，但方向很重要）
    GLfloat sunLightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, sunLightPosition);

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 约60FPS
}

// reshape函数
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
}

// 键盘控制
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC键退出
        exit(0);
        break;
    case ' ': // 空格键切换光照
        lightingEnabled = !lightingEnabled;
        if (lightingEnabled) {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
        }
        else {
            glDisable(GL_LIGHTING);
        }
        break;
    case 'r': // R键重置
    case 'R':
        earthAngle = 0.0f;
        moonAngle = 0.0f;
        earthRotation = 0.0f;
        moonRotation = 0.0f;
        break;
    }
}

// 打印说明
void printInstructions() {
    std::cout << "=== 太阳系模拟程序 ===" << std::endl;
    std::cout << "模拟内容:" << std::endl;
    std::cout << "- 太阳: 红色发光体（中心）" << std::endl;
    std::cout << "- 地球: 蓝色，绕太阳公转（12个月/周）" << std::endl;
    std::cout << "- 月球: 黄色，绕地球公转（1个月/周）" << std::endl;
    std::cout << "- 所有天体都有自转" << std::endl;
    std::cout << "- 光照效果展示明暗面" << std::endl;
    std::cout << "控制说明:" << std::endl;
    std::cout << "- ESC: 退出程序" << std::endl;
    std::cout << "- 空格键: 切换光照效果" << std::endl;
    std::cout << "- R键: 重置模拟" << std::endl;
    std::cout << "====================" << std::endl;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("太阳系模拟 - 太阳地球月球运行关系");

    init();
    printInstructions();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}