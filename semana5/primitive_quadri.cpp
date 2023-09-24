#include <cstdlib>
#include <gl/glut.h>

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint eje = 2;

void base(float ladoX, float ladoY, float ladoZ){
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(ladoX/2, -ladoY/2, ladoZ/2);
    glVertex3f(ladoX/2, -ladoY/2, -ladoZ/2);
    glVertex3f(-ladoX/2, -ladoY/2, -ladoZ/2);
    glVertex3f(-ladoX/2, -ladoY/2, ladoZ/2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(ladoX/2, -ladoY/2, ladoZ/2);
    glVertex3f(ladoX/2, -ladoY/2, -ladoZ/2);
    glVertex3f(-ladoX/2, -ladoY/2, -ladoZ/2);
    glVertex3f(-ladoX/2, -ladoY/2, ladoZ/2);
    glEnd();
    glPopMatrix();
}

void frontal(float ladoX, float ladoY, float ladoZ) {
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-ladoX/2, -ladoY/2, ladoZ/2);
    glVertex3f(ladoX/2, -ladoY/2, ladoZ/2);
    glVertex3f(ladoX/2, ladoY/2, ladoZ/2);
    glVertex3f(-ladoX/2, ladoY/2, ladoZ/2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-ladoX/2, -ladoY/2, ladoZ/2);
    glVertex3f(ladoX/2, -ladoY/2, ladoZ/2);
    glVertex3f(ladoX/2, ladoY/2, ladoZ/2);
    glVertex3f(-ladoX/2, ladoY/2, ladoZ/2);
    glEnd();
    glPopMatrix();
}

void lateral(float ladoX, float ladoY, float ladoZ) {
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(ladoX / 2, -ladoY / 2, ladoZ / 2);
    glVertex3f(ladoX / 2, -ladoY / 2, -ladoZ / 2);
    glVertex3f(ladoX / 2, ladoY / 2, -ladoZ / 2);
    glVertex3f(ladoX / 2, ladoY / 2, ladoZ / 2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(ladoX / 2, -ladoY / 2, ladoZ / 2);
    glVertex3f(ladoX / 2, -ladoY / 2, -ladoZ / 2);
    glVertex3f(ladoX / 2, ladoY / 2, -ladoZ / 2);
    glVertex3f(ladoX / 2, ladoY / 2, ladoZ / 2);
    glEnd();
    glPopMatrix();
}

void draw3DQuadrilateral(float ladoX, float ladoY, float ladoZ) {
    glPushMatrix();
    base(ladoX, ladoY, ladoZ);
    glPopMatrix();
    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    base(ladoX, ladoY, ladoZ);
    glPopMatrix();
    glPushMatrix();
    lateral(ladoX, ladoY, ladoZ);
    glPopMatrix();
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    lateral(ladoX, ladoY, ladoZ);
    glPopMatrix();
    glPushMatrix();
    frontal(ladoX, ladoY, ladoZ);
    glPopMatrix();
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    frontal(ladoX, ladoY, ladoZ);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

    draw3DQuadrilateral(0.75, 1, 1.5);

    glFlush();
    glutSwapBuffers();
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat) h / (GLfloat) w, 1.5 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat) w / (GLfloat) h, 1.5 * (GLfloat) w / (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'a':
            theta[1] += 5.0;
            break;
        case 's':
            theta[0] += 5.0;
            break;
        case 'd':
            theta[2] += 5.0;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Cubo Rotativo");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glClearColor(0.5, 0.5, 0.5, 1.0); // Gris
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}