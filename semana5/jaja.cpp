#include <cstdlib>
#include <gl/glut.h>

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint eje = 2;
//GLfloat scale = 0.5;

void cara(GLfloat difRotacion, GLfloat scale) {
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2] + difRotacion, 0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-scale, -scale, -scale);
    glVertex3f(scale, -scale, -scale);
    glVertex3f(scale, scale, -scale);
    glVertex3f(-scale, scale, -scale);
    glEnd();
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    for(int i = 0 ; i <= 22; i++){
        cara(4*i, 1 - 0.045*i);
    }
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

void girar_objeto_geometrico ()
{
    theta[eje] += 0.1;
    if(theta[eje]>360) theta[eje] -= 360.0;
    display();
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
        case 'f':
            exit(0);
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
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
