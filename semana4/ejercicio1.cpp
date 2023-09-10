#include <GL/glut.h>
#include "polares.h"

void init();

void display();

void reshape(int, int);

void menu();

void menuFunc(int);

int mainMenu, figure, color, background, lineWidth, schema;
int currentFigure = 1;
float red = 0, green = 0, blue = 0;
bool rectangular = false, polar = false, currentFigureInPolar = false;

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
    if (value == 1) {
        if (polar) {
            polar = false;
        }
        rectangular = !rectangular;
    } else {
        if (rectangular) {
            rectangular = false;
        }
        polar = !polar;
    }
    currentFigureInPolar = polar;
    glutPostRedisplay();
}

void menuFunc(int value) {
    if (value == 100) exit(0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (currentFigureInPolar) {
        if (polar) {
            disk();
        }
    } else {
        if (rectangular) {
            drawAxes();
        }
    }
    glColor3f(red, green, blue);
    switch (currentFigure) {
        case 1:
            caracol();
            break;
        case 2:
            caracol_pascal();
            break;
        case 3:
            cardioide();
            break;
        case 4:
            circulo();
            break;
        case 5:
            cisoide_diocles();
            break;
        case 6:
            concoide_nicomenes();
            break;
        case 7:
            espiral();
            break;
        case 8:
            hiperbole();
            break;
        case 9:
            lemniscata();
            break;
        case 10:
            nefroide_freeth();
            break;
        case 11:
            parabola();
            break;
        case 12:
            rosal();
            break;
        case 13:
            rosa2();
            break;
        default:
            yinyan();
            break;
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

void menu() {
    mainMenu = glutCreateMenu(menuFunc);
    figure = glutCreateMenu(menu_figure);
    glutAddMenuEntry("Caracol", 1);
    glutAddMenuEntry("Caracol Pascal", 2);
    glutAddMenuEntry("Cardioide", 3);
    glutAddMenuEntry("Circulo", 4);
    glutAddMenuEntry("Cisoide Diocles", 5);
    glutAddMenuEntry("Concoides Nicomenes", 6);
    glutAddMenuEntry("Espiral", 7);
    glutAddMenuEntry("Hiperbole", 8);
    glutAddMenuEntry("Leminiscata", 9);
    glutAddMenuEntry("Nefroide Freeth", 10);
    glutAddMenuEntry("Parabola", 11);
    glutAddMenuEntry("Rosal 1", 12);
    glutAddMenuEntry("Rosal 2", 13);
    glutAddMenuEntry("Yin Yan", 14);
    glutAddMenuEntry("Volver", 15);

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

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(1.0);
    glShadeModel(GL_FLAT);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(1200, 100);
    glutCreateWindow("Menus Jerarquicos");
    init();
    menu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}