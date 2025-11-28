// Robot3D.cpp : OpenGL 机器人 + 桌子 + 茶壶 | freeglut | VS2022 控制台项目
#include <windows.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <cmath>

// ---------------- 全局相机参数 ----------------
float camDist = 12.0f;
float camAngleX = 15.0f;
float camAngleY = 30.0f;

// ---------------- 光源 ----------------
void initLight()
{
    GLfloat pos[] = { 5.0f, 10.0f, 5.0f, 0.0f };   // 定向光
    GLfloat white[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// ---------------- 绘制立方体 ----------------
void cube(float sx, float sy, float sz)
{
    glPushMatrix();
    glScalef(sx, sy, sz);
    glutSolidCube(1.0);
    glPopMatrix();
}

// ---------------- 绘制圆柱 ----------------
void cylinder(float radius, float height, int slices = 16)
{
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluCylinder(q, radius, radius, height, slices, 1);
    gluDeleteQuadric(q);
}

// ---------------- 机器人 ----------------
void drawRobot()
{
    // 身体
    glPushMatrix();
    glScalef(1.0f, 2.0f, 0.6f);
    glColor3f(0.7f, 0.7f, 0.7f);
    glutSolidCube(1.0);
    glPopMatrix();

    // 头部
    glPushMatrix();
    glTranslatef(0, 2.8f, 0);
    glColor3f(0.9f, 0.9f, 0.9f);
    glutSolidSphere(0.8, 32, 32);
    // 左眼
    glPushMatrix();
    glTranslatef(-0.3f, 0.2f, 0.7f);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 16, 16);
    glPopMatrix();
    // 右眼
    glPushMatrix();
    glTranslatef(0.3f, 0.2f, 0.7f);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 16, 16);
    glPopMatrix();
    // 鼻子
    glPushMatrix();
    glTranslatef(0, 0, 0.8f);
    glColor3f(1, 0.7f, 0.7f);
    glutSolidSphere(0.1, 16, 16);
    glPopMatrix();
    // 嘴（小圆柱）
    glPushMatrix();
    glTranslatef(0, -0.2f, 0.8f);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8f, 0, 0);
    cylinder(0.15, 0.3);
    glPopMatrix();
    glPopMatrix(); // head

    // 左臂
    glPushMatrix();
    glTranslatef(-1.2f, 0.5f, 0);
    glRotatef(90, 0, 0, 1);
    glColor3f(0.6f, 0.6f, 0.6f);
    cylinder(0.2, 1.5);
    glPopMatrix();
    // 右臂
    glPushMatrix();
    glTranslatef(1.2f, 0.5f, 0);
    glRotatef(-90, 0, 0, 1);
    glColor3f(0.6f, 0.6f, 0.6f);
    cylinder(0.2, 1.5);
    glPopMatrix();

    // 左腿
    glPushMatrix();
    glTranslatef(-0.4f, -1.8f, 0);
    glColor3f(0.6f, 0.6f, 0.6f);
    cylinder(0.25, 1.8);
    glPopMatrix();
    // 右腿
    glPushMatrix();
    glTranslatef(0.4f, -1.8f, 0);
    glColor3f(0.6f, 0.6f, 0.6f);
    cylinder(0.25, 1.8);
    glPopMatrix();
}

// ---------------- 桌子 + 茶壶 ----------------
void drawTableAndTeapot()
{
    // 桌面
    glPushMatrix();
    glTranslatef(3.0f, 0.75f, 0);
    glScalef(2.0f, 0.1f, 1.5f);
    glColor3f(0.55f, 0.27f, 0.07f);
    glutSolidCube(1.0);
    glPopMatrix();

    // 桌腿（4 根）
    for (int i = 0; i < 4; ++i)
    {
        glPushMatrix();
        glTranslatef(3.0f + (i & 1 ? 0.9f : -0.9f), 0, (i & 2 ? 0.7f : -0.7f));
        glColor3f(0.45f, 0.22f, 0.05f);
        cylinder(0.08f, 1.4f);
        glPopMatrix();
    }

    // 茶壶
    glPushMatrix();
    glTranslatef(3.0f, 1.5f, 0);
    glColor3f(0.9f, 0.75f, 0.15f);
    glutSolidTeapot(0.6);
    glPopMatrix();
}

// ---------------- 显示回调 ----------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // 相机
    gluLookAt(camDist * sin(camAngleY * 3.1416f / 180) * cos(camAngleX * 3.1416f / 180),
        camDist * sin(camAngleX * 3.1416f / 180),
        camDist * cos(camAngleY * 3.1416f / 180) * cos(camAngleX * 3.1416f / 180),
        0, 0, 0,
        0, 1, 0);

    drawRobot();
    drawTableAndTeapot();

    glutSwapBuffers();
}

// ---------------- 窗口 reshape ----------------
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// ---------------- 键盘漫游 ----------------
void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:  camAngleY -= 5; break;
    case GLUT_KEY_RIGHT: camAngleY += 5; break;
    case GLUT_KEY_UP:    camAngleX -= 5; break;
    case GLUT_KEY_DOWN:  camAngleX += 5; break;
    case GLUT_KEY_PAGE_UP:   camDist *= 0.9f; break;
    case GLUT_KEY_PAGE_DOWN: camDist *= 1.1f; break;
    }
    glutPostRedisplay();
}

// ---------------- main ----------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("实验四：OpenGL 3D 机器人与茶壶");
    initLight();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutMainLoop();
    return 0;
}