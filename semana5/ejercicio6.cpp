#include <cstdlib>
#include <gl/glut.h>
#include <cmath>
#include <iostream>

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint eje = 2;
float perspectiveX = 19, perspectiveY = 36, perspectiveZ = 0;
float dx1, dy1, dx2, dy2, dx, dy, dxc, dyc;
bool turno1 = true, turno2 = false; // turno de la esfera a moverse
float ang = 0;
int i = 0;
//float ex, ez, ang = 0;

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

void esfera() {
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 6, 2.375);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 6, -2.375);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glutWireSphere(1.0, 50, 50);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(1.0, 50, 50);
    glPopMatrix();
}

void esfera_movil(float trasladarX, float trasladarY, int dir){
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex3f(dir, 6, 2.375);
    glVertex3f(trasladarX, trasladarY, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex3f(dir, 6, -2.375);
    glVertex3f(trasladarX, trasladarY, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(trasladarX, trasladarY, 0);
    glColor3f(0.0, 0.0, 0.0);
    glutWireSphere(1.0, 50, 50);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(1.0, 50, 50);
    glPopMatrix();
}

void dibujarEjes() {
    float medida = 7.0;
    // Eje X (Rojo)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-medida, 0.0, 0.0);
    glVertex3f(medida, 0.0, 0.0);
    glEnd();

    // Eje Y (Verde)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -medida, 0.0);
    glVertex3f(0.0, medida, 0.0);
    glEnd();

    // Eje Z (Azul)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -medida);
    glVertex3f(0.0, 0.0, medida);
    glEnd();
}

void soportes(){
    glPushMatrix();
    glTranslatef(0, -2, 0);
    draw3DQuadrilateral(10, 1, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.75, 2.0, 2.25);
    draw3DQuadrilateral(0.5, 7, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.75, 2.0, -2.25);
    draw3DQuadrilateral(0.5, 7, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.75, 2.0, -2.25);
    draw3DQuadrilateral(0.5, 7, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.75, 2.0, 2.25);
    draw3DQuadrilateral(0.5, 7, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,5.75,-2.25);
    draw3DQuadrilateral(10, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,5.75,2.25);
    draw3DQuadrilateral(10, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.75,5.75,0);
    draw3DQuadrilateral(0.5, 0.5, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.75,5.75,0);
    draw3DQuadrilateral(0.5, 0.5, 5);
    glPopMatrix();
}

void pendulos(){

    glPushMatrix();
    esfera_movil(2, 0, 2);
    glPopMatrix();

    if(turno1){
        dx1 = dx; dy1 = dy;
    }else{
        dx1 = 0; dy1 = 0;
    }

    glPushMatrix();
    esfera_movil(4 + dx1,dy1, 4);
    glPopMatrix();

    glPushMatrix();
    esfera_movil(0,0,0);
    glPopMatrix();

    glPushMatrix();
    esfera_movil(-2, 0, -2);
    glPopMatrix();

    if(turno2){
        dx2 = dx; dy2 = dy;
    }else{
        dx2 = 0; dy2 = 0;
    }

    glPushMatrix();
    esfera_movil(-4 - dx2, dy2, -4);
    glPopMatrix();
}

void pendulos2(){
    if(turno1){
        dx1 = dx; dy1 = dy;
    }else{
        dx1 = 0; dy1 = 0;
    }
    glPushMatrix();
    esfera_movil(2 + dx1, dy1, 2);
    glPopMatrix();

    glPushMatrix();
    esfera_movil(4 + dx1,dy1, 4);
    glPopMatrix();

    glPushMatrix();
    esfera_movil(0,0,0);
    glPopMatrix();

    if(turno2){
        dx2 = dx; dy2 = dy;
    }else{
        dx2 = 0; dy2 = 0;
    }
    glPushMatrix();
    esfera_movil(-2 - dx2, dy2, -2);
    glPopMatrix();

    glPushMatrix();
    esfera_movil(-4 - dx2, dy2, -4);
    glPopMatrix();
}

void pendulos3(){
    if(turno1){
        dx1 = dx; dy1 = dy;
    }else{
        dx1 = 0; dy1 = 0;
    }
    glPushMatrix();
    esfera_movil(2 + dx1, dy1, 2);
    glPopMatrix();

    glPushMatrix();
    esfera_movil(4 + dx1,dy1, 4);
    glPopMatrix();

    if(turno1){
        dxc = dx; dyc = dy;
    }else if(turno2){
        dxc = -dx; dyc = dy;
    }

    glPushMatrix();
    esfera_movil(dxc,dyc,0);
    glPopMatrix();

    if(turno2){
        dx2 = dx; dy2 = dy;
    }else{
        dx2 = 0; dy2 = 0;
    }
    glPushMatrix();
    esfera_movil(-2 - dx2, dy2, -2);
    glPopMatrix();

    glPushMatrix();
    esfera_movil(-4 - dx2, dy2, -4);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();

    //Point of View
    // x = 19 Y = 36 Z = 0
    glRotatef(perspectiveX, 1, 0, 0);
    glRotatef(perspectiveY, 0, 1, 0);
    glRotatef(perspectiveZ, 0, 0, 1);

    glScalef(0.3, 0.3, 0.3);

    if(ang <= 0 && i == 1){
        turno1 = !turno1;
        turno2 = !turno2;
        i = 0;
    }
    i == 0 ? ang += M_PI/1000 : ang -= M_PI/1000;
    if(ang >= M_PI/6)  i = 1;
    dx = 7 * sin(ang);
    dy = 14 * sin(ang/2) * sin(ang/2);

    dibujarEjes();
    soportes();
    pendulos3();

    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}

// esta función controla el angulo de rotación según el eje de giro
void girar_objeto_geometrico() {
    theta[eje] += 0.02;
    if (theta[eje] > 360) theta[eje] -= 360.0;
    display();
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'a' :
            eje = 0;
            break;
        case 's' :
            eje = 1;
            break;
        case 'd' :
            eje = 2;
            break;
        case 'x' :
            perspectiveX++;
            break;
        case 'y' :
            perspectiveY++;
            break;
        case 'z' :
            perspectiveZ++;
            break;
        case 'e' :
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
    glClearColor(0.5, 0.5, 0.5, 1.0); // Gris
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}