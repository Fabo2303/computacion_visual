#include <cmath>
#include <GL/glut.h>

void drawAxis();
void drawVertex(int,int,int);
void drawPolygonPoints(int,int,int);
void drawPolygonLines(int,int,int);
void drawPolygon(int,int,int);
void drawPolygonDashedLines(int,int,int);
void init();
void display();
void reshape(int,int);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,250);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Mi grafico");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void drawAxis()
{
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
        //Eje X
        glVertex2f(-20,0.0);
        glVertex2f(20,0.0);
        //Eje Y
        glVertex2f(0,-20.0);
        glVertex2f(0,20.0);
    glEnd();
    glBegin(GL_POLYGON);
        //Triangulo para el eje X
        glVertex2f(20,0.0);
        glVertex2f(20-1,0.5);
        glVertex2f(20-1,-0.5);
    glEnd();
    glBegin(GL_POLYGON);
        //Triangulo para el eje Y
        glVertex2f(0.0,10);
        glVertex2f(-0.5,10-1);
        glVertex2f(0.5,10-1);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(1.0, 9.7);
        glVertex2f(1.25, 9.45);
        glVertex2f(1.5, 9.7);
        glVertex2f(1.25, 9.45);
        glVertex2f(1.25, 9.45);
        glVertex2f(1.25, 9.2);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(18.5, 1.5);
        glVertex2f(19, 1);
        glVertex2f(19, 1.5);
        glVertex2f(18.5, 1);
    glEnd();
}

void drawVertex(int radio,int h,int k)
{
    float x,y,ang;
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/10)
    {
        x = radio * cos(ang) + h;
        y = radio * sin(ang) + k;
        glVertex2f(x,y);
    }
}

void drawPolygonPoints(int radio,int h,int k)
{
    glColor3f(1,0.0,0.0);
    glPointSize(4);
    glBegin(GL_POINTS);
        drawVertex(radio,h,k);
    glEnd();
}

void drawPolygonLines(int radio,int h,int k)
{
    glBegin(GL_LINE_LOOP);
        drawVertex(radio,h,k);
    glEnd();
}

void drawPolygon(int radio,int h,int k)
{
    glBegin(GL_POLYGON);
        drawVertex(radio,h,k);
    glEnd();
}

void drawPolygonDashedLines(int radio, int h, int k){
    glLineStipple(4, 0xAAAA); // Factor y patrón para líneas punteadas
    glEnable(GL_LINE_STIPPLE);

    glBegin(GL_LINE_LOOP);
        drawVertex(radio, h, k);
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

void init()
{
    glClearColor(1.0,1.0,1.0,0.0);  //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
    glShadeModel(GL_FLAT);
}

void display()
{
    GLfloat ang, radio = 8.0f, x, y;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    drawAxis();

    drawPolygonPoints(4,-15,5);
    
    glColor3f(1.0,0.0,0.0);
    glLineWidth(2.0);
    drawPolygonLines(4,0,5);

    glColor3f(0,1.0,0.0);
    glLineWidth(4.0);
    drawPolygonLines(4,15,5);

    glColor3f(0,0.0,1.0);
    drawPolygon(4,-15,-5);

    glColor3f(0,0.0,1.0);
    drawPolygonDashedLines(4,0,-5);

    glColor3f(0.0,1.0,0.0);
    drawPolygon(4,15,-5);

    glColor3f(0.0, 0.0, 1.0);
    drawPolygonDashedLines(4, 15, -5);

    glPopMatrix();      // reecupera el estado del matriz
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0,20.0,-10.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}