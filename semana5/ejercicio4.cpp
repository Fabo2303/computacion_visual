#include <cstdlib>
#include <gl/glut.h>
#include "figures.h"

GLint eje = 2;
int mainMenu, figure, color, background, lineWidth, schema;
int currentFigure = 1;
float red = 1, green = 0, blue = 0;
bool rectangular = false, polar = false, currentFigureInPolar = false;
bool tarjeta = false;
GLfloat scale = 0.5;

void cara()
{
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
}

void cubo()
{
    // Cara frontal (roja)
    //glColor3f(1.0, 0.0, 0.0);
    cara();

    // Cara trasera (verde)
    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0);
    //glColor3f(0.0, 1.0, 0.0);
    cara();
    glPopMatrix();

    // Cara derecha (azul)
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    //glColor3f(0.0, 0.0, 1.0);
    cara();
    glPopMatrix();

    // Cara izquierda (amarilla)
    glPushMatrix();
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    //glColor3f(1.0, 1.0, 0.0);
    cara();
    glPopMatrix();

    // Cara superior (magenta)
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    //glColor3f(1.0, 0.0, 1.0);
    cara();
    glPopMatrix();

    // Cara inferior (cian)
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    //glColor3f(0.0, 1.0, 1.0);
    cara();
    glPopMatrix();
}

void dibujarEjes()
{
    // Eje X (Rojo)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    // Eje Y (Verde)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    // Eje Z (Azul)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(red, green, blue);
    if(tarjeta){
        dibujarEjes();
    }
    switch (currentFigure) {
        case 1:
            cube();
            break;
        case 2:
            sphere();
            break;
        case 3:
            espiral_cuad();
            break;
        case 4:
            tetra();
            break;
        case 5:
            dodecaedro();
            break;
        case 6:
            icosaedro();
            break;
        default:
            cubo();
    }
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

void girar_objeto_geometrico() {
    theta[eje] += 0.1;
    if (theta[eje] > 360) theta[eje] -= 360.0;
    display();
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
        case 'f':
            exit(0);
    }
    glutPostRedisplay();
}

void menu_color(int value) {
    switch (value) {
        case 1:
            red = 1;
            green = 0;
            blue = 0;
            break;
        case 2:
            red = 0;
            green = 1;
            blue = 0;
            break;
        default:
            red = 0;
            green = 0;
            blue = 1;
    }
    glutPostRedisplay();
}

void menu_figure(int value) {
    if (value != 15) {
        currentFigure = value;
    }

    glutPostRedisplay();
}

void menu_background(int value) {
    switch (value) {
        case 1:
            glClearColor(1.0, 0.0, 0.0, 0.0);
            break;
        case 2:
            glClearColor(0.0, 1.0, 0.0, 0.0);
            break;
        case 3:
            glClearColor(0.0, 0.0, 1.0, 0.0);
            break;
        case 4:
            glClearColor(1.0, 0.0, 1.0, 0.0);
            break;
        default:
            glClearColor(1.0, 1.0, 1.0, 0.0);
    }
    glutPostRedisplay();
}

void menu_lineWidth(int value) {
    switch (value) {
        case 1:
            glLineWidth(1.0);
            break;
        case 2:
            glLineWidth(1.5);
            break;
        case 3:
            glLineWidth(2.0);
            break;
        default:
            glLineWidth(2.5);
    }
    glutPostRedisplay();
}

void menu_schema(int value) {
    if(value == 1){
        tarjeta = !tarjeta;
    }
    glutPostRedisplay();
}

void menuFunc(int value) {
    if (value == 100) exit(0);
}

void menu() {
    mainMenu = glutCreateMenu(menuFunc);
    figure = glutCreateMenu(menu_figure);
    glutAddMenuEntry("Cubo", 1);
    glutAddMenuEntry("sphere", 2);
    glutAddMenuEntry("espiral", 3);
    glutAddMenuEntry("tetraedro", 4);
    glutAddMenuEntry("dodecaedro", 5);
    glutAddMenuEntry("icosaedro", 6);
    glutAddMenuEntry("cubo colorido", 7);

    color = glutCreateMenu(menu_color);
    glutAddMenuEntry("ROJO", 1);
    glutAddMenuEntry("VERDE", 2);
    glutAddMenuEntry("AZUL", 3);
    glutAddMenuEntry("Volver", 4);

    background = glutCreateMenu(menu_background);
    glutAddMenuEntry("ROJO", 1);
    glutAddMenuEntry("VERDE", 2);
    glutAddMenuEntry("AZUL", 3);
    glutAddMenuEntry("MORADO", 4);
    glutAddMenuEntry("BLANCO", 5);
    glutAddMenuEntry("Volver", 6);

    lineWidth = glutCreateMenu(menu_lineWidth);
    glutAddMenuEntry("1.0", 1);
    glutAddMenuEntry("1.5", 2);
    glutAddMenuEntry("2.0", 3);
    glutAddMenuEntry("2.5", 4);
    glutAddMenuEntry("Volver", 5);

    schema = glutCreateMenu(menu_schema);
    glutAddMenuEntry("Cartesiano", 1);
    glutAddMenuEntry("Polar", 2);

    glutSetMenu(mainMenu);
    glutAddSubMenu("Figura", figure);
    glutAddSubMenu("Color", color);
    glutAddSubMenu("Fondo", background);
    glutAddSubMenu("Grosor", lineWidth);
    glutAddSubMenu("Sistema", schema);
    glutAddMenuEntry("Salir", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Cubo Rotativo");
    menu();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}