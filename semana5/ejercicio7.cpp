#include <cstdlib>
#include <gl/glut.h>
#include <cmath>

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint eje = 2;
float perspectiveX = 19, perspectiveY = 36, perspectiveZ = 0;
float ex, ey;
float ang = 0.0;

void esfera_movil(float trasladarX, float trasladarY) {
    glPushMatrix();
    glTranslatef(trasladarX, trasladarY, 0);
    glColor3f(.0, 1.0, 0.0);
    glutWireSphere(0.5, 50, 50);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Point of View
    GLfloat x, y;
    glRotatef(perspectiveX, 1, 0, 0);
    glRotatef(perspectiveY, 0, 1, 0);
    glRotatef(perspectiveZ, 0, 0, 1);

    glScalef(0.3, 0.3, 0.3);
    // glColor3f(0.0, 0.0, 1.0); // Puntos en negro

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 1.0); // Puntos en negro
    float arg = 2 * M_PI /1000;
    // a = 2 b = 3
    for (float sa = 0; sa < 2 * M_PI; sa += arg)
    {
        x = 5 * cos(sa);
        y = 3 * sin(sa);
        glVertex2f(x, y);
    }
    glEnd();

    ang += 0.002;
    if (ang > 360) ang -= 360.0;
    ex = 10.0 * sin(ang);
    ey = 6.0 * cos(ang);
    glPushMatrix();
    glScalef(0.5, 0.5,0.5);
    esfera_movil(ex, ey);
    glPopMatrix();
    glPushMatrix();
    esfera_movil(4,0);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

// Esta función controla el ángulo de rotación según el eje de giro
void girar_objeto_geometrico() {
    theta[eje] += 0.02;
    if (theta[eje] > 360) theta[eje] -= 360.0;

    display();
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'a':
            eje = 0;
            break;
        case 's':
            eje = 1;
            break;
        case 'd':
            eje = 2;
            break;
        case 'x':
            perspectiveX++;
            break;
        case 'y':
            perspectiveY++;
            break;
        case 'z':
            perspectiveZ++;
            break;
        case 'e':
            exit(0);
            break;
        default:
            break;
    }
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
                2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
                2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(800, 100);
    glutCreateWindow("Pendulo");
    glClearColor(0, 0, 0, 0); // Gris
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}