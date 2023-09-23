#include <cstdlib>
#include <gl/glut.h>
#include <cmath>

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint eje = 2;
float perspectiveX = 0, perspectiveY = 0, perspectiveZ = 0;
float ex, ez, ang = 0;

void bolita(){
    glPushMatrix();
    glTranslatef(ex, 0, ez);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

    glColor3f(0.0, 0.0, 0.0);
    glutWireSphere(1.0, 20, 20);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

void dibujarEjes(){
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

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();

    //Point of View
    glRotatef(perspectiveX, 1, 0, 0);
    glRotatef(perspectiveY, 0, 1, 0);
    glRotatef(perspectiveZ, 0, 1, 0);

    glScalef(0.3,0.3,0.3);

    ang <= 360 ? ang += 0.0005 : ang -= 360;
    ex = 5.0 * sin(ang);
    ez = 5.0 * cos(ang);

    glBegin(GL_LINES);
        glColor3f(0, 0, 1);
        glVertex3f(ex,0,ez);
        glVertex3f(0,6,0);
    glEnd();
    dibujarEjes();
    bolita();
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}
// esta función controla el angulo de rotación según el eje de giro
void girar_objeto_geometrico(){
    theta[eje] += 0.02;
    if(theta[eje]>360) theta[eje] -= 360.0;
    display();
}

void teclado(unsigned char tecla,int x,int y){
    switch(tecla){
        case 'a' : eje = 0; break;
        case 's' : eje = 1; break;
        case 'd' : eje = 2; break;
        case 'x' : perspectiveX++; break;
        case 'y' : perspectiveY++; break;
        case 'z' : perspectiveZ++; break;
        case 'e' : exit(0) ; break;
        default: break;
    }
}

void myReshape(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w <=h)
        glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,
                2.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0*(GLfloat)w/(GLfloat)h,
                2.0*(GLfloat)w/(GLfloat)h, -2.0,2.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
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