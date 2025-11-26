#include <GL/glut.h>
#include <math.h>

// 相机参数
float g_dist = 5.0f;   // 观察距离
float g_theta = 45.0f; // 方位角（度）
float g_phi = 30.0f;   // 仰角（度）

// 材质参数
GLfloat mat_diffuse[] = { 0.8f, 0.0f, 0.8f, 1.0f }; // 紫色漫反射
GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // 白色环境光强度 0.2
GLfloat mat_specular[] = { 0.5f, 0.0f, 0.5f, 1.0f }; // 品红镜面
GLfloat mat_shininess[] = { 50.0f };                    // 光泽度
GLfloat mat_emission[] = { 0.5f, 0.0f, 0.5f, 1.0f }; // 紫色自发光 0.5

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void setLights()
{
    // 红色方向光（右前上 30°）
    GLfloat red_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat red_pos[] = { 1.0f, 1.0f, 0.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, red_pos);

    // 蓝色方向光（左前上 45°）
    GLfloat blue_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat blue_pos[] = { -1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, blue_pos);

    // 黄色方向光（左前下 60°）
    GLfloat yellow_diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat yellow_pos[] = { -1.0f, -1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, yellow_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, yellow_pos);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 计算相机位置
    float thetaRad = g_theta * 3.1415926f / 180.0f;
    float phiRad = g_phi * 3.1415926f / 180.0f;
    float eyeX = g_dist * cosf(phiRad) * cosf(thetaRad);
    float eyeY = g_dist * sinf(phiRad);
    float eyeZ = g_dist * cosf(phiRad) * cosf(1.570796f - thetaRad);

    gluLookAt(eyeX, eyeY, eyeZ,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    setLights();

    // 设置材质
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    glutSolidTeapot(1.0);
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// 键盘控制
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w': g_dist += 0.5f; break;   // 远离
    case 's': g_dist -= 0.5f; if (g_dist < 1.0f) g_dist = 1.0f; break;
    case 'a': g_theta -= 5.0f; break;  // 左转
    case 'd': g_theta += 5.0f; break;  // 右转
    case 'q': g_phi += 5.0f; if (g_phi > 85.0f) g_phi = 85.0f; break; // 抬高
    case 'e': g_phi -= 5.0f; if (g_phi < -85.0f) g_phi = -85.0f; break; // 俯视
    case 27: exit(0); // ESC 退出
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL 茶壶材质与多光源实验 - 可调视角");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}