#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
// Definimos las listas necesarias para graficar el cilindro y el adn
#define cilindroHLista 1
#define cilindroVLista 2
#define esferaLista 3
#define duoLista 4
#define alambrico 5
#define virtual 6
#define enlaceVert 7
#define alambricoVert 8

// Variables para los menús
int mainMenu, cilindro, axis, rotacion;

// Variables para manejar el movimiento de la camara
GLdouble anguloH = 0, incremento_angulo = 0.1, anguloV = 0;
GLfloat px0 = 0, py0 = 0, pz0 = 5;
GLfloat px1 = 0, py1 = 0, pz1 = 4;
GLfloat pnx = 0, pny = 1, pnz = 0;
GLfloat vx, vy, vz;

// Variables globales para graficar
GLfloat R = 2, H = 10;

// Variable booleanas para permitir los dibujos
bool dibujar = false;
bool drawAxis = false;
bool solid = false;
bool alam = false;
bool rotar = false;
double veloz = 0.01;

// Variables que permiten graficar el cilindro y el adn en la misma escala
GLfloat enlaceLen = 2 * R, enlaceWidth = 0.1, semilado = enlaceLen / 2, radioEsfera = 0.5, radio = 1, enlacesDiv = 1, aux = 2 * pow(R + radioEsfera, 2) - 2 * pow(R + radioEsfera, 2) * cos(M_PI / 9);
GLfloat vertLen = sqrt(aux + pow(enlacesDiv, 2)) - 2 * radioEsfera, vertRot = 180 / M_PI * atan(sqrt(aux) / enlacesDiv);

void enlace(void);

void enlaceVertical();

void enlace_alambrico_vert();

void cilindro_v(double, double, double, double);

void Mi_Cilindro_Wire(int, int, float);

void ejes(int);

void solido();

void alambre();

void menu();

void enlace_alambrico();

void iniciar(void);

void display(void);

void spin(void);

void rotacamara(void);

void avanza(void);

void retro(void);

void rotarvertical(void);

void teclado(unsigned char, int, int);

void myReshape(int, int);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("camara movil");
    iniciar();
    menu();
    glutReshapeFunc(myReshape);
    // LLamamos las listas en el main para compilarlas para usarse en el display
    glNewList(cilindroHLista, GL_COMPILE);
    Mi_Cilindro_Wire(15, 10, enlaceLen);
    glEndList();

    glNewList(cilindroVLista, GL_COMPILE);
    Mi_Cilindro_Wire(15, 10, vertLen);
    glEndList();

    glNewList(esferaLista, GL_COMPILE);
    glColor3f(1, 0, 0);
    glutWireSphere(radioEsfera, 15, 15);
    glEndList();

    enlace();
    enlaceVertical();
    enlace_alambrico();
    enlace_alambrico_vert();
    cilindro_v(R, H, 30, 30);

    glutDisplayFunc(display);
    glutIdleFunc(spin);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

//Funcion para dibujar los enlaces entre las hebras
void enlace_alambrico()
{
    glNewList(alambrico, GL_COMPILE);

    glLineWidth(5.0f);

    glBegin(GL_LINES);
    glVertex3f(-R, 0, 0);
    glVertex3f(R, 0, 0);
    glEnd();

    glPointSize(10.0f);

    glBegin(GL_POINTS);
    glVertex3f(-R, 0, 0);
    glVertex3f(R, 0, 0);
    glEnd();

    glEndList();
}

//Funcion para dibujar los enlaces de las hebras
void enlace_alambrico_vert()
{
    float auxVert = 2 * pow(R, 2) - 2 * pow(R, 2) * cos(M_PI / 9);
    float len = sqrt(aux + pow(enlacesDiv, 2));
    float vertRotAl = 180 / M_PI * atan(sqrt(auxVert) / enlacesDiv);
    int auxlista = 10;

    glNewList(auxlista, GL_COMPILE);
    glLineWidth(5.0f);

    glBegin(GL_LINES);

    glPushMatrix();
    glVertex3f(0, 0, 0);
    glVertex3f(0, len, 0);
    glPopMatrix();

    glEnd();

    glEndList();

    glNewList(alambricoVert, GL_COMPILE);

    glLineWidth(5.0f);

    glPushMatrix();
    glTranslatef(R, 0, 0);
    glRotatef(-vertRotAl, 1, 0, -2.0 / 9.0);
    glCallList(auxlista);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-R, 0, 0);
    glRotatef(+vertRotAl, 1, 0, -2.0 / 9.0);
    glCallList(auxlista);
    glPopMatrix();

    glEndList();
}

void iniciar(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

//Funcion para dibujar el adn solido
void solido()
{
    float i;

    for (i = -H / 2; i < H / 2; i += enlacesDiv)
    {
        glRotatef(20, 0, 1, 0);

        glPushMatrix();
        glTranslated(0, i, 0);
        glCallList(enlaceVert);
        glTranslated(semilado + radioEsfera, 0, 0);
        glRotatef(90, 0, 0, 1);
        glCallList(duoLista);
        glPopMatrix();
    }

    glPushMatrix();
    glRotatef(20, 0, 1, 0);
    glTranslated(semilado + radioEsfera, i, 0);
    glRotatef(90, 0, 0, 1);
    glCallList(duoLista);
    glPopMatrix();
}

//Funcion para dibujar el adn alambrico
void alambre()
{

    glPushMatrix();
    for (float i = -H / 2; i < H / 2; i += enlacesDiv)
    {
        glRotatef(20, 0, 1, 0);

        glPushMatrix();
        glTranslated(0, i, 0);
        glCallList(alambricoVert);
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    for (float i = -H / 2; i <= H / 2; i += enlacesDiv)
    {
        glRotatef(20, 0, 1, 0);

        glPushMatrix();
        glTranslated(0, i, 0);
        glCallList(alambrico);
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    for (float i = -H / 2; i <= H / 2; i += enlacesDiv)
    {
        glRotatef(20, 0, 1, 0);

        glPushMatrix();
        glTranslated(0, i, 0);
        glCallList(alambrico);
        glPopMatrix();
    }
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(px0, py0, pz0, px1, py1, pz1, pnx, pny, pnz);
    glColor3f(0.0, 0.0, 1.0);

    glRotatef(vx, 1, 0, 0);
    glRotatef(vy, 0, 1, 0);
    glRotatef(vz, 0, 0, 1);

    glColor3f(0.0, 0.0, 1.0);

    // Se permite el grafico del solido adn si solid es true
    if (solid)
    {
        glLineWidth(1);
        solido();
    }
    // Se permite el grafico del alambrico adn si alam es true
    if (alam)
    {
        glLineWidth(1);
        alambre();
    }
    // Se permite el grafico de los ejes si drawAxis es true
    if (drawAxis)
    {
        ejes(10);
    }
    // Se permite el grafico del cilindro si dibujar es true
    if (dibujar)
    {
        glCallList(virtual);
    }

    glFlush();

    glutSwapBuffers();
}

void spin()
{
    // Si se ha presionado R mayuscula entonces empezará a rotar en el ejeY
    if (rotar)
    {
        vy += veloz;
        if (vx > 360)
            vx -= 360.0;
        if (vy > 360)
            vy -= 360.0;
        if (vz > 360)
            vz -= 360.0;
    }
    display();
}

void rotarvertical()
{
    // Y aumenta
    py1 = py0 + radio * sin(anguloV);
    // Z disminuye
    pz1 = pz0 - radio * cos(anguloV) * cos(anguloH);
    // X disminuye
    px1 = px0 + radio * cos(anguloV) * sin(anguloH);
}

void rotacamara()
{
    // X aumenta
    px1 = px0 + radio * sin(anguloH);
    // Z disminuye
    pz1 = pz0 - radio * cos(anguloH) * cos(anguloV);
    // Y disminuye
    py1 = py0 + radio * cos(anguloH) * sin(anguloV);
}

void avanza()
{
    px0 = px1;
    pz0 = pz1;
    py0 = py1;
    px1 = px0 + radio * cos(anguloV) * sin(anguloH);
    py1 = py0 + radio * sin(anguloV) * cos(anguloH);
    pz1 = pz0 - radio * cos(anguloV);
}

void retro()
{
    px1 = px0;
    pz1 = pz0;
    py1 = py0;
    px0 = px0 - radio * cos(anguloV) * sin(anguloH);
    py0 = py0 - radio * sin(anguloV) * cos(anguloH);
    pz0 = pz0 + radio * cos(anguloV);
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'i':
        avanza();
        break;
    case 'm':
        retro();
        break;
    case 'j':
        anguloH = anguloH + incremento_angulo;
        rotacamara();
        break;
    case 'k':
        anguloH = anguloH - incremento_angulo;
        rotacamara();
        break;
    case 'u':
        anguloV = anguloV + incremento_angulo;
        rotarvertical();
        break;
    case 'o':
        anguloV = anguloV - incremento_angulo;
        rotarvertical();
        break;
    case 'a':
        vx++;
        break;
    case 'd':
        vx--;
        break;
    case 'w':
        vy++;
        break;
    case 's':
        vy--;
        break;
    case 'q':
        vz++;
        break;
    case 'e':
        vz--;
        break;
    case 'Z':
        veloz += 0.01;
        break;
    case 'X':
        veloz -= 0.01;
        break;
    case 'R':
        rotar = !rotar;
        break;
    case 'f':
        exit(0);
        break;
    }
}

void ejes(int longitud)
{
    glLineWidth(4.0f);
    // Eje X (Rojo)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(longitud, 0.0, 0.0);
    glEnd();

    // Eje Y (Verde)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, longitud, 0.0);
    glEnd();

    // Eje Z (Azul)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, longitud);
    glEnd();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//La funcion Mi_Cilindro_Wire permite el grafico de los cilindros que se usen
//en el grafico del adn solido
void Mi_Cilindro_Wire(int Npara, int Ncortes, float largo)
{
    float x, z, salto = largo / (Npara - 1);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);

    for (float ang = 0; ang < 2 * M_PI; ang += 2 * M_PI / Ncortes)
    {
        x = enlaceWidth * cos(ang);
        z = enlaceWidth * sin(ang);
        glVertex3f(x, 0, z);
        glVertex3f(x, largo, z);
    }

    glEnd();

    for (float para = 0; para <= largo + salto; para += salto)
    {

        glBegin(GL_LINE_LOOP);

        for (float ang = 0; ang < 2 * M_PI; ang += 2 * M_PI / Ncortes)
        {
            x = enlaceWidth * cos(ang);
            z = enlaceWidth * sin(ang);
            glVertex3f(x, para, z);
        }

        glEnd();
    }
}

// La funcion enlace vertical dibuja las hebras del adn
void enlaceVertical()
{
    glNewList(enlaceVert, GL_COMPILE);

    glPushMatrix();

    glTranslatef(-enlaceLen / 2 - radioEsfera, 0, 0);

    glRotatef(vertRot, 1, 0, -2.0 / 9.0);

    glTranslatef(0, radioEsfera, 0);

    glCallList(cilindroVLista);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(enlaceLen / 2 + radioEsfera, 0, 0);

    glRotatef(-vertRot, 1, 0, -2.0 / 9.0);

    glTranslatef(0, radioEsfera, 0);

    glCallList(cilindroVLista);

    glPopMatrix();

    glEndList();
}

// La funcion enlace dibuja los enlaces entre las esferas de las hebras
// del adn
void enlace()
{
    glNewList(duoLista, GL_COMPILE);

    glCallList(esferaLista);

    glTranslatef(0, radioEsfera, 0);

    glCallList(cilindroHLista);

    glTranslatef(0, enlaceLen + radioEsfera, 0);

    glCallList(esferaLista);

    glEndList();
}

void menu_rotaciones(int value)
{
    // Si el valor es de 1 y la velocidad es mayor que cero cambiamos a
    // sentido horario
    if (veloz > 0 && value == 1)
        veloz = -veloz;
    // Si el valor es de 2 y la velocidad es menor que cero cambiamos a
    // sentido antihorario
    if (veloz < 0 && value == 2)
        veloz = -veloz;
}

void menu_ejes(int value)
{
    // Si el valor es de 1 es porque se selecciono dibujar los ejes
    drawAxis = value == 1;
}

void menu_cilindro(int value)
{
    // Si el valor es de 1 es porque se selecciono dibujar el cilindro
    dibujar = value == 1;
}

void menuFunc(int value)
{
    // Si el valor es de 1 es porque se selecciono dibujar el adn alambrico
    alam = value == 1;
    // Si el valor es de 2 es porque se selecciono dibujar el adn solido
    solid = value == 2;
    // Si valor es 100 entonces se termina la ejecucion del programa
    if (value == 100)
        exit(0);
}

void menu()
{
    // Menu principal
    mainMenu = glutCreateMenu(menuFunc);

    // Menu para el cilindro
    cilindro = glutCreateMenu(menu_cilindro);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 2);

    // Menu para los ejes
    axis = glutCreateMenu(menu_ejes);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 2);

    // Menu para la rotacion
    rotacion = glutCreateMenu(menu_rotaciones);
    glutAddMenuEntry("Horario", 1);
    glutAddMenuEntry("Antihorario", 2);

    glutSetMenu(mainMenu);
    glutAddSubMenu("Cilindro Virtual", cilindro);
    glutAddSubMenu("Ejes", axis);
    glutAddMenuEntry("Modelo Alambrico", 1);
    glutAddMenuEntry("Modelo solido", 2);
    glutAddSubMenu("Rotaciones", rotacion);
    glutAddMenuEntry("Salir", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// La funcion cilindro_v dibuja un cilindro que se dibuja con la mitad de
// la altura en la direccion -y, la otra altura se encuentra en +y
void cilindro_v(double radius, double altura, double base, double cortes)
{
    double i, j, k;
    double x, y, z, twopi;
    twopi = 2 * M_PI;
    double ang = 0;
    double av = twopi / (base);
    bool entrar = false;
    glNewList(virtual, GL_COMPILE);
    glLineWidth(4.0f);
    glColor3f(0.5, 0, 0.6);
    // Dibuja las caras del cilindro dependiendo del valor de base
    for (i = 0; i < base; i++)
    {
        glBegin(GL_LINE_LOOP);
        for (j = 0; j < 2; j++)
        {
            for (k = altura / 2; k >= -altura / 2; k -= altura)
            {
                x = radius * cos(ang);
                y = entrar ? -k : k;
                z = radius * sin(ang);
                glVertex3f(x, y, z);
            }
            entrar = !entrar;
            ang = entrar ? ang + av : ang;
        }
        glEnd();
    }
    ang = 0;
    // Genera los segmentos paralelos a la base (incluye base inferior y superior)
    for (i = altura / 2; i >= -altura / 2; i -= altura / cortes)
    {
        glBegin(GL_LINE_LOOP);
        for (j = 0; j < base; j++)
        {
            x = radius * cos(ang);
            y = i;
            z = radius * sin(ang);
            glVertex3f(x, y, z);
            ang += av;
        }
        glEnd();
    }
    glEndList();
}
