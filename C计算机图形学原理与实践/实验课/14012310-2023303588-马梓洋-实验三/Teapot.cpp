#include <GL/glut.h>

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // 黑色背景
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

void setLights() {
    // 红色光源：正右上方30度
    GLfloat red_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat red_position[] = { 1.0, 1.0, 0.0, 0.0 }; // 方向光源
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, red_position);

    // 蓝色光源：左前上方45度
    GLfloat blue_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat blue_position[] = { -1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, blue_position);

    // 黄色光源：左前下方60度
    GLfloat yellow_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat yellow_position[] = { -1.0, -1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, yellow_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, yellow_position);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 设置相机位置
    gluLookAt(3.0, 3.0, 3.0,  // 眼睛位置
        0.0, 0.0, 0.0,  // 看向原点
        0.0, 1.0, 0.0); // 上方向

    setLights();

    // 设置材质（白色茶壶）
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // 渲染茶壶
    glutSolidTeapot(1.0);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL 茶壶三光源照射");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}