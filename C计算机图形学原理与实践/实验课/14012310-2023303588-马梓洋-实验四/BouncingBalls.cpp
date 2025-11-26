#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float BOX_SIZE = 8.0f;
const float BALL_RADIUS = 0.4f;

struct Ball {
    float x, y, z;
    float vx, vy, vz;
    float r, g, b;
};

Ball balls[2];
bool showLights = true;

void initBalls() {
    srand(time(NULL));

    // 小球1 - 红色
    balls[0].x = -1.5f;
    balls[0].y = 0.0f;
    balls[0].z = 0.0f;
    balls[0].vx = 0.04f;
    balls[0].vy = 0.03f;
    balls[0].vz = 0.02f;
    balls[0].r = 1.0f;
    balls[0].g = 0.0f;
    balls[0].b = 0.0f;

    // 小球2 - 蓝色
    balls[1].x = 1.5f;
    balls[1].y = 0.0f;
    balls[1].z = 0.0f;
    balls[1].vx = -0.03f;
    balls[1].vy = 0.04f;
    balls[1].vz = -0.025f;
    balls[1].r = 0.0f;
    balls[1].g = 0.0f;
    balls[1].b = 1.0f;
}

void init() {
    glEnable(GL_DEPTH_TEST);

    // 基本光照设置
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // 环境光
    GLfloat global_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    initBalls();
}

void drawBox() {
    float halfSize = BOX_SIZE / 2;

    glColor3f(0.3f, 0.3f, 0.5f);

    glBegin(GL_QUADS);

    // 前面 - 蓝色
    glColor3f(0.2f, 0.2f, 0.6f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-halfSize, -halfSize, halfSize);
    glVertex3f(halfSize, -halfSize, halfSize);
    glVertex3f(halfSize, halfSize, halfSize);
    glVertex3f(-halfSize, halfSize, halfSize);

    // 后面 - 深蓝色
    glColor3f(0.1f, 0.1f, 0.4f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, halfSize, -halfSize);
    glVertex3f(halfSize, halfSize, -halfSize);
    glVertex3f(halfSize, -halfSize, -halfSize);

    // 左面 - 青色
    glColor3f(0.2f, 0.5f, 0.5f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, halfSize);
    glVertex3f(-halfSize, halfSize, halfSize);
    glVertex3f(-halfSize, halfSize, -halfSize);

    // 右面 - 紫色
    glColor3f(0.5f, 0.2f, 0.5f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(halfSize, -halfSize, -halfSize);
    glVertex3f(halfSize, halfSize, -halfSize);
    glVertex3f(halfSize, halfSize, halfSize);
    glVertex3f(halfSize, -halfSize, halfSize);

    // 顶面 - 绿色
    glColor3f(0.2f, 0.6f, 0.2f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-halfSize, halfSize, -halfSize);
    glVertex3f(-halfSize, halfSize, halfSize);
    glVertex3f(halfSize, halfSize, halfSize);
    glVertex3f(halfSize, halfSize, -halfSize);

    // 底面 - 深绿色
    glColor3f(0.1f, 0.4f, 0.1f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(halfSize, -halfSize, -halfSize);
    glVertex3f(halfSize, -halfSize, halfSize);
    glVertex3f(-halfSize, -halfSize, halfSize);

    glEnd();
}

void drawBall(const Ball& ball, int lightId) {
    glPushMatrix();
    glTranslatef(ball.x, ball.y, ball.z);

    // 设置光源
    if (showLights) {
        GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat light_diffuse[] = { ball.r, ball.g, ball.b, 1.0f };
        GLfloat light_ambient[] = { ball.r * 0.3f, ball.g * 0.3f, ball.b * 0.3f, 1.0f };
        GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glLightfv(lightId, GL_POSITION, light_position);
        glLightfv(lightId, GL_DIFFUSE, light_diffuse);
        glLightfv(lightId, GL_AMBIENT, light_ambient);
        glLightfv(lightId, GL_SPECULAR, light_specular);

        // 设置衰减让光源更明显
        glLightf(lightId, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(lightId, GL_LINEAR_ATTENUATION, 0.1f);
        glLightf(lightId, GL_QUADRATIC_ATTENUATION, 0.01f);
    }

    // 绘制小球 - 先不用光照，确保可见
    glDisable(GL_LIGHTING);
    glColor3f(ball.r, ball.g, ball.b);
    glutSolidSphere(BALL_RADIUS, 32, 32);

    // 绘制一个更大的半透明光晕
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(ball.r, ball.g, ball.b, 0.3f);
    glutSolidSphere(BALL_RADIUS * 1.5, 32, 32);
    glDisable(GL_BLEND);

    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void updateBalls() {
    float halfBox = BOX_SIZE / 2 - BALL_RADIUS;

    for (int i = 0; i < 2; i++) {
        Ball& ball = balls[i];

        ball.x += ball.vx;
        ball.y += ball.vy;
        ball.z += ball.vz;

        // 碰撞检测
        if (ball.x > halfBox || ball.x < -halfBox) {
            ball.vx = -ball.vx;
            ball.x = (ball.x > halfBox) ? halfBox : -halfBox;
        }
        if (ball.y > halfBox || ball.y < -halfBox) {
            ball.vy = -ball.vy;
            ball.y = (ball.y > halfBox) ? halfBox : -halfBox;
        }
        if (ball.z > halfBox || ball.z < -halfBox) {
            ball.vz = -ball.vz;
            ball.z = (ball.z > halfBox) ? halfBox : -halfBox;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 固定相机视角
    gluLookAt(10.0f, 8.0f, 10.0f,   // 相机位置
        0.0f, 0.0f, 0.0f,     // 观察点
        0.0f, 1.0f, 0.0f);    // 上方向

    // 更新小球位置
    updateBalls();

    // 绘制盒子
    drawBox();

    // 绘制小球
    drawBall(balls[0], GL_LIGHT0);
    drawBall(balls[1], GL_LIGHT1);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
}

void idle() {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC
        exit(0);
        break;
    case ' ': // 空格键切换光照
        showLights = !showLights;
        if (showLights) {
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
        }
        else {
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
        }
        break;
    case 'r': // 重置小球
    case 'R':
        initBalls();
        break;
    }
}

void printInstructions() {
    std::cout << "=== 弹跳小球程序控制说明 ===" << std::endl;
    std::cout << "ESC: 退出程序" << std::endl;
    std::cout << "空格键: 切换光照效果" << std::endl;
    std::cout << "R键: 重置小球位置" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "如果还看不到小球，请检查OpenGL安装" << std::endl;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("弹跳小球 - 移动光源演示");

    init();

    printInstructions();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}