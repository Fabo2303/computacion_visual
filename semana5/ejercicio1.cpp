#include <cstdlib>
#include <gl/glut.h>

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint eje = 2;

void cubo()
{
    glPushMatrix();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

    glColor3f(1.0, 0.0, 0.0); // Color rojo para el cubo de alambre
    glutWireSphere(1.0, 10, 10);
    //glutWireDodecahedron();
    //glutSolidCube(1.0);
    //glColor3f(0.0, 0.0, 0.0);
    //glutWireCube(1.0); // Dibuja un cubo de alambre con un tamaño de 1.0
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
// composicion de rotaciones
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    cubo();
    glFlush();
// intercambiamos los buffers, el que se muestra y el que esta oculto
    glutSwapBuffers();
}
// esta función controla el angulo de rotación según el eje de giro
void girar_objeto_geometrico ()
{
    theta[eje] += 0.02;
    if(theta[eje]>360) theta[eje] -= 360.0;
    display();
}
void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla){
        case 'a' : eje = 0; break;
        case 's' : eje = 1; break;
        case 'd' : eje = 2; break;
        case 'f' : exit(0) ; break;
    }
}
// control de ventana (recuerde el volumen de visualización)
// modifique dicho volumen según su conveniencia
void myReshape(int w, int h)
{
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mi objeto bajo rotaciones");
    glClearColor(0.5, 0.5, 0.5, 1.0); // Gris
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}