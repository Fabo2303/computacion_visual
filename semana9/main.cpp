#include <cstdlib>
#include <gl/glut.h>
#include <cmath>
#define miLista 1

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint eje = 2;

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

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    //torus(20, 20);
    glPushMatrix();
        glCallList(miLista);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1, 1, 0);
        glCallList(miLista);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void girar_objeto_geometrico (){
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
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mi objeto bajo rotaciones");
    glClearColor(0.5, 0.5, 0.5, 1.0); // Gris

    torus(20, 20);

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}