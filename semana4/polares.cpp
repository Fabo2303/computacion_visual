#include "polares.h"
#include <GL/glut.h>
#include <cmath>

void caracol() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);

    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        // a > 0, b > 0, a < b
        r = 2 + 4 * sin(ang);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void caracol_pascal() {
    GLfloat ang, r, x, y;
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        //Para que sea un caracol de pascal con hoyuelos
        // a>0, b>0, 1<a/b<2
        r = 3 - 2 * sin(ang);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}

void cardioide() {
    GLfloat ang, r, x, y;
    glBegin(GL_LINE_STRIP);

    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        // se cumplen las siguientes condiciones para que sea
        // un cardiode a>0, b>0 y a/b = 1.
        //probar cambiando por coseno y cambiando la suma por menos
        r = 3 - 3 * sin(ang);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}

void circulo() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        r = 4 * sin(ang); //El circulo se dibuja con el x
        //r = 4 * cos(ang); //El circulo se dibuja con el y
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void cisoide_diocles() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        //curva rosa polar
        r = 2 * sin(ang) * tan(ang);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void concoide_nicomenes() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        //concoide de nicomenes
        // r = 2 / sin(ang) + 3;
        // r = 2 / cos(ang) - 1;
        r = 1 / cos(ang) + 2;
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void espiral() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        r = ang;
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void drawHiperbole(int abcisas, int ordenadas) {
    for (float i = 0.5; i < 10; i += 0.4) {
        glVertex2f(abcisas * i, 0);
        glVertex2f(0, ordenadas * (10 - i));
    }
}

void hiperbole() {
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    glPointSize(2.0);
    glBegin(GL_LINES);


    drawHiperbole(1, 1);
    drawHiperbole(-1, 1);
    drawHiperbole(-1, -1);
    drawHiperbole(1, -1);

    glEnd();
    
    //glFlush();
}

void lemniscata() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        //Lemniscata
        // r² = a² * cos(2 * theta)
        r = sqrt(16 * sin(2 * ang));
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void nefroide_freeth() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 4 * M_PI; ang += arg) {
        //nefroide de freeth
        r = 2 + 4 * sin(ang / 2);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void parabola() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        //curva rosa polar
        r = 5 / (2 - 2 * sin(ang));
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void rosa2() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        //curva rosa polar
        r = 1 - 4 * sin(3 * ang);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void rosal() {
    GLfloat ang, r, x, y;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    //diskete();
    glBegin(GL_LINE_STRIP);


    float arg = 2 * M_PI / 1000;
    for (ang = 0; ang < 2 * M_PI; ang += arg) {
        // si hacemos que varie el coef del angulo aumentan
        // el numero de petalos,
        // Si se usa r = a * cos(n * theta), n par 2n petalos
        // En caso de r = a * sin(n * theta), n impar n petalos
        r = 6 * cos(2 * ang);
        //r = 6 * sin(3 * ang);
        x = r * cos(ang);
        y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
    
    //glFlush();
}

void drawCircle(float radius, float start, float end, float h, float k) {
    float x, y, ang;
    for (ang = start; ang < end; ang += 2 * M_PI / 10000) {
        x = radius * cos(ang) + h;
        y = radius * sin(ang) + k;
        glVertex2f(x, y);
    }
}

void yinyan() {
    GLfloat r = 8.0f;
    //glClear(GL_COLOR_BUFFER_BIT);
     // salva el estado actual de la matriz
    glPointSize(2.0);

    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0); // Puntos en negro
    drawCircle(r, M_PI / 2, 3 * M_PI / 2, 0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0); // Puntos en negro
    drawCircle(r, M_PI / 2, 3 * M_PI / 2, 0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(r, 3 * M_PI / 2, 5 * M_PI / 2, 0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(r / 2, 0.0f, 2 * M_PI, 0, r / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(r / 2, 0.0f, 2 * M_PI, 0, -r / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(r / 6, 0.0f, 2 * M_PI, 0, r / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(r / 6, 0.0f, 2 * M_PI, 0, -r / 2);
    glEnd();
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);

    glVertex2f(0.0, -10.0);
    glVertex2f(0.0, 10.0);
    glEnd();
}

void disk() {
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); // Define la vista en el plano XY
    GLUquadricObj *pt;
    pt = gluNewQuadric();
    gluQuadricDrawStyle(pt, GLU_LINE);
    glColor3f(1.0, 0.0, 0.0);
    gluDisk(pt, 0, 7, 20, 6);
}