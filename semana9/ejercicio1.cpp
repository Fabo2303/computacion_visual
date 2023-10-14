#include <cstdlib>
#include <gl/glut.h>
#include <cmath>
#define miLista 99

GLint eje = 2;
int mainMenu, figure, color, background, lineWidth, position, tamanyo;
int currentFigure = 0;
bool rectangular = false, polar = false, currentFigureInPolar = false;
bool tarjeta = false;
GLfloat scaleX = 1, scaleY = 1, scaleZ = 1, colorB = 0, colorR = 1, colorG = 0, translateX = 0, translateY = 0, translateZ = 0;
GLfloat scale = 0.5;
GLfloat theta[] = {0.0, 0.0, 0.0};

void torus(int, int);
void dibujarTorus();
void borrarLista();

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
    for(int i = 1; i <= currentFigure; i++){
        glCallList(i);
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
            colorR = 1;
            colorG = 0;
            colorB = 0;
            break;
        case 2:
            colorR = 0;
            colorG = 1;
            colorB = 0;
            break;
        default:
            colorR = 0;
            colorG = 0;
            colorB = 1;
    }
    glutPostRedisplay();
}

void menu_figure(int value) {
    if(value!=2){
        currentFigure ++;
        dibujarTorus();
    }else{
        borrarLista();
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

void menu_position(int value) {
    switch(value){
        case 1: translateX += 0.1;
        case 2: translateY += 0.1;
        case 3: translateZ += 0.1;
        case 4: translateX -= 0.1;
        case 5: translateY -= 0.1;
        case 6: translateZ -= 0.1;
    }
    glutPostRedisplay();
}

void menu_tamanyo(int value){
    switch(value){
        case 1: scaleX += 0.1;
        case 2: scaleY += 0.1;
        case 3: scaleZ += 0.1;
        case 4: scaleX -= 0.1;
        case 5: scaleY -= 0.1;
        case 6: scaleZ -= 0.1;
    }
}

void menuFunc(int value) {
    if (value == 100) exit(0);
}

void menu() {
    mainMenu = glutCreateMenu(menuFunc);
    figure = glutCreateMenu(menu_figure);
    glutAddMenuEntry("Añadir", 1);
    glutAddMenuEntry("Quitar", 2);

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

    position = glutCreateMenu(menu_position);
    glutAddMenuEntry("++X", 1);
    glutAddMenuEntry("++Y", 2);
    glutAddMenuEntry("++Z", 3);
    glutAddMenuEntry("--X", 4);
    glutAddMenuEntry("--Y", 5);
    glutAddMenuEntry("--Z", 6);

    tamanyo = glutCreateMenu(menu_tamanyo);
    glutAddMenuEntry("++X", 1);
    glutAddMenuEntry("++Y", 2);
    glutAddMenuEntry("++Z", 3);
    glutAddMenuEntry("--X", 4);
    glutAddMenuEntry("--Y", 5);
    glutAddMenuEntry("--Z", 6);

    glutSetMenu(mainMenu);
    glutAddSubMenu("Figura", figure);
    glutAddSubMenu("Color", color);
    glutAddSubMenu("Fondo", background);
    glutAddSubMenu("Grosor", lineWidth);
    glutAddSubMenu("Posicion", position);
    glutAddSubMenu("Tamanyo", tamanyo);
    glutAddMenuEntry("Salir", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Cubo Rotativo");
    glClearColor(1, 1, 1, 0); 
    menu();
    torus(20, 20);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

void torus(int numc, int numt){
    int i, j, k;
    double s, t, x, y, z, twopi;
    twopi = 2 * M_PI;

    glNewList(miLista, GL_COMPILE);
    for(i = 0; i < numc; i++){
        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= numt; j++){
            for(k = 1; k >= 0; k--){
                s = (i + k)% numc + 0.5;
                t = j % numt;

                x = (1 + .1 * cos(s * twopi / numc)) * cos(t * twopi / numt);
                y = (1 + .1 * cos(s * twopi / numc)) * sin(t * twopi / numt);
                z = .1 * sin(s * twopi / numc);

                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }
    glEndList();
}

void borrarLista(){
    glDeleteLists(currentFigure, 1);
    currentFigure--;
}

void dibujarTorus(){
    glNewList(currentFigure, GL_COMPILE);
    glScalef(scaleX, scaleY, scaleZ);
    glTranslatef(translateX, translateY, translateZ);
    glColor3f(colorR, colorG, colorB);
    glCallList(miLista);
    glEndList();
}