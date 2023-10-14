#include "figures.h"
#include <GL/glut.h>
#include <cmath>
#define miLista 1

GLfloat theta[] = {0.0, 0.0, 0.0};

void espiral_cuad() {
    GLfloat  difRotacion, scale;
    for (int i = 0; i <= 22; i++) {
        scale = 1 - 0.045 * i;
        difRotacion = 4 * i;
        glPushMatrix();
        glTranslatef(0.0, 0.0, -2.0);
        glRotatef(theta[0], 1.0, 0.0, 0.0);
        glRotatef(theta[1], 0.0, 1.0, 0.0);
        glRotatef(theta[2] + difRotacion, 0.0, 0.0, 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(-scale, -scale, -scale);
        glVertex3f(scale, -scale, -scale);
        glVertex3f(scale, scale, -scale);
        glVertex3f(-scale, scale, -scale);
        glEnd();
        glPopMatrix();
    }
}

void sphere(){
    glPushMatrix();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

    //glColor3f(1.0, 0.0, 0.0); // Color rojo para el cubo de alambre
    glutWireSphere(1.0, 10, 10);
    //glutWireDodecahedron();
    //glutSolidCube(1.0);
    ////glColor3f(0.0, 0.0, 0.0);
    //glutWireCube(1.0); // Dibuja un cubo de alambre con un tamaño de 1.0
    glPopMatrix();
}

void cube(){
    glPushMatrix();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

    glutWireCube(1.0); // Dibuja un cubo de alambre con un tamaño de 1.0
    glPopMatrix();
}

void tetra(){
    glPushMatrix();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glutWireTetrahedron(); // Dibuja un cubo de alambre con un tamaño de 1.0
    glPopMatrix();
}

void dodecaedro(){
    glPushMatrix();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glutWireDodecahedron(); // Dibuja un cubo de alambre con un tamaño de 1.0
    glPopMatrix();
}

void icosaedro(){
    glPushMatrix();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glutWireIcosahedron(); // Dibuja un cubo de alambre con un tamaño de 1.0
    glPopMatrix();
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

