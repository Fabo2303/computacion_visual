#include <cstdlib>
#include <gl/glut.h>
#include <cmath>
#define miLista 1
// torus ----  1
// cuerda ---- 2
// cubo  ----  3

GLfloat theta[] = {0.0, 0.0, 0.0};
int figuras_menu, color_menu, main_menu;
int figura_actual;
int colorR = 0, colorG = 0, colorB = 0;
GLint eje = 1;
GLfloat rot = 0;


//Radio de 0.7
void torus(int numc, int numt){
    int i, j, k;
    double s, t, x, y, z, twopi;
    twopi = 2 * M_PI;

    glNewList(miLista, GL_COMPILE);
    for(i = 0; i < numc; i++){
        glBegin(GL_LINE_LOOP);
        for(j = 0; j <= numt; j++){
            for(k = 1; k >= 0; k--){
                s = (i + k)% numc + 0.5;
                t = j % numt;

                x = (1 + .4 * cos(s * twopi / numc)) * cos(t * twopi / numt);
                y = (1 + .4 * cos(s * twopi / numc)) * sin(t * twopi / numt);
                z = .4 * sin(s * twopi / numc);

                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }
    glEndList();
}

void cube(int lado){
    glNewList(3, GL_COMPILE);
        glutSolidCube(lado);
        glLineWidth(1.5);
        glColor3f(1, 1, 1);
        glutWireCube(lado);
    glEndList();
}

void piramide(){
    glNewList(4, GL_COMPILE);
        glutSolidTetrahedron();
        glLineWidth(1.5);
        glColor3f(1, 1, 1);
        glutWireTetrahedron();
    glEndList();
}

void esfera(double radius, int slices, int stacks){
    glNewList(5, GL_COMPILE);
        glutSolidSphere(radius, slices, stacks);
        glLineWidth(1.5);
        glColor3f(1, 1, 1);
        glutWireSphere(radius, slices, stacks);
    glEndList();
}

void drawCircle(float radio, float start, float end, float h, float k){
    float x,y,ang;
    for (ang = start; ang < end; ang += 2 * M_PI/10000)
    {
        x = radio * cos(ang) + h;
        y = radio * sin(ang) + k;
        glVertex2f(x,y);
    }
}

void cuerda(){
    glNewList(2, GL_COMPILE);
    glPushMatrix();
        glLineWidth(3);
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(1, 0.29, 0);
        glVertex3f(-1, 0.71, 0);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glLineWidth(3);
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(1, -0.29, 0);
        glVertex3f(-1, -0.72, 0);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glLineWidth(3);
        glBegin(GL_LINE_STRIP);
        drawCircle(0.29,-M_PI/2, M_PI/2, 1, 0);
        drawCircle(0.715, M_PI/2, 3*M_PI/2, -1, 0);
        glEnd();
    glPopMatrix();
    glEndList();
}

void menuFiguras(int value){
    figura_actual = value;
}

void menuColores(int value){
    switch (value)
    {
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
}

void menuMain(int value){
    if(value == 100) 
        exit(0);
}

void menu(){
    main_menu = glutCreateMenu(menuMain);

    figuras_menu = glutCreateMenu(menuFiguras);
    glutAddMenuEntry("Torus", 1);
    glutAddMenuEntry("Cubo", 3);
    glutAddMenuEntry("Piramide", 4);
    glutAddMenuEntry("Esfera", 5);

    color_menu = glutCreateMenu(menuColores);
    glutAddMenuEntry("Rojo", 1);
    glutAddMenuEntry("Verde", 2);
    glutAddMenuEntry("Azul", 3);

    glutSetMenu(main_menu);
    glutAddSubMenu("Figura", figuras_menu);
    glutAddSubMenu("Color", color_menu);
    glutAddMenuEntry("Salir", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    glPushMatrix();
        glRotatef(rot,0.0,0.0,1.0);
        glColor3f(colorR, colorG, colorB);
        glCallList(figura_actual);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void girar_objeto_geometrico (){
    rot < 360 ? rot += 0.01 : rot -= 360;
    theta[eje] += 0.02;
    if(theta[eje]>360) theta[eje] -= 360.0;
    display();
}

void teclado(unsigned char tecla,int x,int y){
    switch(tecla){
        case 'a' : eje = 0; break;
        case 's' : eje = 1; break;
        case 'd' : eje = 2; break;
        case 'f' : exit(0) ; break;
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
    glutCreateWindow("Mi objeto bajo rotaciones");
    glClearColor(0.5, 0.5, 0.5, 1.0); // Gris
    torus(5, 2);
    cuerda();
    cube(1);
    piramide();
    esfera(1, 20, 20);
    menu();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}