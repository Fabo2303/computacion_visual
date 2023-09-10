#include <iostream>
#include <cmath>
#include <GL/glut.h>

void init();
void display();
void reshape(int, int);
void menu();
void menuFunc(int);

int mainMenu, figuras, sistema;
bool figuraEnPolar = false;
bool cartesiano = false, polar = false;

int figura = 1;

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0); // Color negro para los ejes
    glBegin(GL_LINES);

    // Eje X
    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);

    // Eje Y
    glVertex2f(0.0, -10.0);
    glVertex2f(0.0, 10.0);

    glEnd();
}

void diskete() {
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); // Define la vista en el plano XY
    GLUquadricObj *pt;
    pt = gluNewQuadric();
    gluQuadricDrawStyle(pt, GLU_LINE);
    glColor3f(1.0, 0.0, 0.0);
    gluDisk(pt, 0, 7, 20, 6);
}

void caracol() {
    GLfloat ang, r, x, y;
    glBegin(GL_LINE_STRIP);

    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        r = 2 + 4 * sin(ang);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }

    glEnd();
}

void caracol_pascal() {
    GLfloat ang, r, x, y;
    glBegin(GL_LINE_STRIP);

    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        r = 3 - 2 * sin(ang);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }

    glEnd();
}

// Otras funciones de dibujo...

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (figuraEnPolar) {
        if (polar) {
            diskete();
        }
    } else {
        if (cartesiano) {
            drawAxes();
        }
    }

    switch (figura) {
        case 1:
            caracol();
            break;
        case 2:
            caracol_pascal();
            break;
            // Resto de las figuras...
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void menu_sistema(int value) {
    if (value == 1) {
        if (polar) {
            polar = false;
        }
        cartesiano = !cartesiano;
    } else {
        if (cartesiano) {
            cartesiano = false;
        }
        polar = !polar;
    }

    figuraEnPolar = polar; // Actualiza el estado
    glutPostRedisplay();
}

void menuFunc(int value) {
    switch (value) {
        case 1:
            figura = 1;
            break;
        case 2:
            figura = 2;
            break;
            // Agrega casos para el resto de las figuras...
    }
    glutPostRedisplay();
}

void menu() {
    mainMenu = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Caracol", 1);
    glutAddMenuEntry("Caracol Pascal", 2);
    sistema = glutCreateMenu(menu_sistema);
    glutAddMenuEntry("Cartesiano", 1);
    glutAddMenuEntry("Polar", 2);
    glutSetMenu(mainMenu);
    glutAddSubMenu("Sistema", sistema);

    // Agrega entradas para el resto de las figuras...
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(1.0);
    glShadeModel(GL_FLAT);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(1200, 100);
    glutCreateWindow("Algoritmo Basico");
    init();
    menu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
