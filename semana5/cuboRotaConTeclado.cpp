#include <cstdlib>
#include <gl/glut.h>

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint eje = 2;

void cara()
{
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
}

void dibujarCubo()
{
    // Cara frontal (roja)
    glColor3f(1.0, 0.0, 0.0);
    cara();

    // Cara trasera (verde)
    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    cara();
    glPopMatrix();

    // Cara derecha (azul)
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    cara();
    glPopMatrix();

    // Cara izquierda (amarilla)
    glPushMatrix();
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 0.0);
    cara();
    glPopMatrix();

    // Cara superior (magenta)
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 1.0);
    cara();
    glPopMatrix();

    // Cara inferior (cian)
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    cara();
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

    dibujarCubo();

    glFlush();
    glutSwapBuffers();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cubo Rotativo");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
