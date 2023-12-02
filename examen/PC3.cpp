// La pantalla se encuentra dividida en dos rectangulos verticales
//

#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#define tableroLista 1

// Estructura para definir una lista enlazada simple
// Se ha decidido por esta estructura de datos debido a
// que nos permite capturar los puntos con mayor cantidad que un
// vector.

struct punto
{
    float x = 0;
    float y = 0;
    struct punto *sgte;
};

typedef struct punto *Tlista;
Tlista lista = NULL;

// tamanyo de ventana
int width = 1000, height = 800;

// Variables del Mouse
float clickedX = 0, clickedY = 0;
bool mouseClicked = false;
int selectedVertex = -1;

// Posicion del viewport derecho
float vx = 0, vy = 0, vz = 0;

// Contador de los puntos ingresados con el mouse
int N = 0;

// Altura de la superficie generada
float h = 0.2;

// Variables Menu
int mainMenu, menuPuntos, menuPolilinea, menuSpline, menuMover, menuEjes, menuColor, menuGrosor, menuColor3d;
bool dibujarPunto = false, dibujarPolilinea = false, dibujarSpline = false, moverPuntos = false, dibujarEjes = false;
float grosor = 1;

// Variables para los colores
float superficieR = 0.1, superficieG = 0.3, superficieB = 0.2;
float curvaR = 0.2, curvaG = 0.5, curvaB = 0.7;

// Declaraciones de funciones
void display();
void idle();
void teclado(unsigned char, int, int);
void mouse(int, int, int, int);
void motion_callback(int, int);
void reshape(int, int);
void ladoIzquierdo();
void ladoDerecho();
void tablero();
void ejes3d(int);
void ejes(int);
void drawPoint();
void dibujarPControl();
float bSpline(float, int, Tlista);
void graficarBSpline();
void graficarBSpline2d();
void insertarFinal(float, float);
void dibujarPoliline();
void editarNodo(int, float, float);

// Funciones de Menu
void menu();
void menuFunc(int);
void puntosMenu(int);
void polilineaMenu(int);
void splineMenu(int);
void moverMenu(int);
void ejesMenu(int);
void colorMenu(int);
void grosorMenu(int);
void color3dMenu(int);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Practica Calificada 3");
    glClearColor(0.5, 0.5, 0.5, 0.4);
    glEnable(GL_DEPTH_TEST);
    // Definimos las funciones de la ventana
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);
    glutMotionFunc(motion_callback);
    glutReshapeFunc(reshape);

    // Iniciar otras funcionas
    tablero();
    menu();
    glutMainLoop();
    return 0;
}

void reshape(int w, int h)
{
    glutReshapeWindow(width, height);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Definimos dos funciones para cada lado de la ventana (Izquierda - derecha)
    // Estan separadas por una linea vertical en el medio
    ladoIzquierdo();
    ladoDerecho();
    glutSwapBuffers();
}

// Para dibujar los puntos y recorremos la lista para esto
void drawPoint()
{
    if (lista != NULL)
    {
        Tlista t = lista;
        float x, y;
        glBegin(GL_POINTS);
        while (t != NULL)
        {
            x = t->x;
            y = t->y;
            glVertex2f(x, y);
            t = t->sgte;
        }
        glEnd();
    }
}

// Para dibujar la polilinea de la izquierda
void dibujarPoliline()
{
    if (lista != NULL)
    {
        Tlista t = lista;
        float x, y;
        glBegin(GL_LINE_STRIP);
        while (t != NULL)
        {
            x = t->x;
            y = t->y;
            glVertex2f(x, y);
            t = t->sgte;
        }
        glEnd();
    }
}

void ladoIzquierdo()
{
    glViewport(0, 0, width / 2, height);
    glColor3f(1.0, 0.0, 0.0);
    if (dibujarEjes)
        ejes(2);
    if (dibujarSpline)
    {
        glLineWidth(grosor);
        glColor3f(curvaR, curvaG, curvaB);
        graficarBSpline2d();
    }
    if (dibujarPolilinea)
    {
        glLineWidth(1.0);
        glColor3f(0, 0, 0);
        dibujarPoliline();
    }
    if (mouseClicked)
    {
        glColor3f(0.0, 0.0, 1.0);
        glPointSize(5.0);
        glViewport(0, 0, width / 2, height);
        drawPoint();
    }
}

void ladoDerecho()
{
    // Localizamos el viewport en el lado derecho y le damos vista 3d
    glViewport(width / 2, 0, width / 2, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)(width / 2) / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0f, 3.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(vx, 1.0, 0.0, 0.0);
    glRotatef(vy, 0.0, 1.0, 0.0);
    glRotatef(vz, 0.0, 0.0, 1.0);
    // Como en las instrucciones indica que los ejes 2d solo son controlables
    // asumimos que los ejes 3d siempre aparecen.
    ejes3d(2);
    if (dibujarSpline)
    {
        glColor3f(0, 0, 0);
        dibujarPControl();
        glColor3f(superficieR, superficieG, superficieB);
        graficarBSpline();
    }
    glPushMatrix();
    glColor3f(0.5, 0.3, 0.2);
    glCallList(tableroLista);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ejes3d(int longitud)
{
    glPushMatrix();
    glLineWidth(2.0);
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3d(0, 0, longitud);
    glVertex3d(0, 0, -longitud);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0, -longitud, 0);
    glVertex3d(0, longitud, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(-longitud, 0, 0);
    glVertex3d(longitud, 0, 0);
    glEnd();
    glPopMatrix();
}

void ejes(int longitud)
{
    glPushMatrix();
    glLineWidth(2.0);
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3d(0, -longitud, 0);
    glVertex3d(0, longitud, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(-longitud, 0, 0);
    glVertex3d(longitud, 0, 0);
    glEnd();
    glPopMatrix();
}

void tablero()
{
    glNewList(tableroLista, GL_COMPILE);
    // Bases
    glBegin(GL_POLYGON);
    glVertex3f(1, 0, 1);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1, -0.2, 1);
    glVertex3f(-1, -0.2, 1);
    glVertex3f(-1, -0.2, -1);
    glVertex3f(1, -0.2, -1);
    glEnd();

    // Alturas
    glBegin(GL_POLYGON);
    glVertex3f(1, 0, 1);
    glVertex3f(1, -0.2, 1);
    glVertex3f(-1, -0.2, 1);
    glVertex3f(-1, 0, 1);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1, 0, 1);
    glVertex3f(1, -0.2, 1);
    glVertex3f(1, -0.2, -1);
    glVertex3f(1, 0, -1);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-1, 0, -1);
    glVertex3f(-1, -0.2, -1);
    glVertex3f(1, -0.2, -1);
    glVertex3f(1, 0, -1);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, -0.2, 1);
    glVertex3f(-1, -0.2, -1);
    glVertex3f(-1, 0, -1);
    glEnd();
    glEndList();
}

void idle()
{
    if (vx >= 360.0 || vx <= -360.0)
        vx = 0;
    if (vy >= 360.0 || vy <= -360.0)
        vy = 0;
    if (vz >= 360.0 || vz <= -360.0)
        vz = 0;
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x < width / 2)
    {
        if (dibujarPunto)
        {
            clickedX = (float)(x * 2) / (width / 2) - 1.0f;
            clickedY = 1.0f - (float)(y * 2) / height;
            mouseClicked = true;
            insertarFinal(clickedX, clickedY);
            glutPostRedisplay();
        }
        else
        {
            float mouseX = (float)(x * 2) / (width / 2) - 1.0f;
            float mouseY = 1.0f - (float)(y * 2) / height;
            Tlista t = lista;
            for (int i = 0; i < N; i++)
            {
                float distance = std::sqrt((mouseX - t->x) * (mouseX - t->x) +
                                           (mouseY - t->y) * (mouseY - t->y));
                // Segun la distancia lo más corta posible indicará cual seleccionamos
                if (distance < 0.1)
                {
                    selectedVertex = i;
                    break;
                }
                t = t->sgte;
            }
        }
    }
}

void motion_callback(int x, int y)
{
    if (selectedVertex != -1 && !dibujarPunto && moverPuntos)
    {
        // Actualizar las coordenadas del vértice seleccionado
        float motionX = (float)(x * 2) / (width / 2) - 1.0f;
        float motionY = 1.0f - (float)(y * 2) / height;
        // LLamamos a la funcion para editar las coordenadas del punto
        editarNodo(selectedVertex, motionX, motionY);
        glutPostRedisplay();
    }
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'x':
        vy += 1.0f;
        break;
    case 'y':
        vx += 1.0f;
        break;
    case 'z':
        vz -= 1.0f;
        break;
    case 'A':
        h += 0.1;
        break;
    case 'D':
        h -= 0.1;
        break;
    }

    glutPostRedisplay();
}

void menu()
{
    mainMenu = glutCreateMenu(menuFunc);

    menuPuntos = glutCreateMenu(puntosMenu);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 0);

    menuPolilinea = glutCreateMenu(polilineaMenu);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 0);

    menuSpline = glutCreateMenu(splineMenu);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 0);

    menuMover = glutCreateMenu(moverMenu);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 0);

    menuEjes = glutCreateMenu(ejesMenu);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 0);

    menuColor = glutCreateMenu(colorMenu);
    glutAddMenuEntry("Violeta", 0);
    glutAddMenuEntry("Rojo", 1);
    glutAddMenuEntry("Verde", 2);

    menuGrosor = glutCreateMenu(grosorMenu);
    glutAddMenuEntry("2.0", 0);
    glutAddMenuEntry("3.0", 1);
    glutAddMenuEntry("4.0", 2);

    menuColor3d = glutCreateMenu(color3dMenu);
    glutAddMenuEntry("Salmon", 0);
    glutAddMenuEntry("Amarillo Palido", 1);
    glutAddMenuEntry("Azul Royal", 2);

    glutSetMenu(mainMenu);
    glutAddSubMenu("Ingresar puntos de control", menuPuntos);
    glutAddSubMenu("Mostrar polilinea", menuPolilinea);
    glutAddSubMenu("Mostrar Curva B-Spline", menuSpline);
    glutAddSubMenu("Mover Puntos de control", menuMover);
    glutAddSubMenu("Mostrar Ejes coordenados 2D", menuEjes);
    glutAddSubMenu("Cambiar color de la curva", menuColor);
    glutAddSubMenu("Cambiar el grosor de la curva", menuGrosor);
    glutAddSubMenu("Cambiar el color de la superficie de la region derecha", menuColor3d);
    glutAddMenuEntry("Salir", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menuFunc(int value)
{
    if (value == 100)
        exit(0);
}

void puntosMenu(int value)
{
    dibujarPunto = value;
    // Reiniciamos las variables booleanas y la lista
    if (mouseClicked && value == 1)
    {
        mouseClicked = false, dibujarPolilinea = false, dibujarSpline = false, moverPuntos = false, dibujarEjes = false;
        N = 0;
        lista = NULL;
    }
    glutPostRedisplay();
}

void polilineaMenu(int value)
{
    dibujarPolilinea = value;
    dibujarPunto = false;
    glutPostRedisplay();
}

void splineMenu(int value)
{
    dibujarSpline = value;
    dibujarPunto = false;
    glutPostRedisplay();
}

void moverMenu(int value)
{
    moverPuntos = value;
    glutPostRedisplay();
}

void ejesMenu(int value)
{
    dibujarEjes = value;
    glutPostRedisplay();
}

void colorMenu(int value)
{
    switch (value)
    {
    case 0:
        curvaR = 0.541, curvaG = 0.169, curvaB = 0.886;
        break;
    case 1:
        curvaR = 0.647, curvaG = 0.165, curvaB = 0.165;
        break;
    case 2:
        curvaR = 0.678, curvaG = 1.000, curvaB = 0.184;
        break;
    }
    glutPostRedisplay();
}

void grosorMenu(int value)
{
    switch (value)
    {
    case 0:
        grosor = 2.0;
        break;
    case 1:
        grosor = 3.0;
        break;
    case 2:
        grosor = 4.0;
        break;
    }
    glutPostRedisplay();
}

void color3dMenu(int value)
{
    switch (value)
    {
    case 0:
        superficieR = 0.980, superficieG = 0.502, superficieB = 0.447;
        break;
    case 1:
        superficieR = 1.000, superficieG = 0.894, superficieB = 0.710;
        break;
    case 2:
        superficieR = 0.255, superficieG = 0.412, superficieB = 0.882;
        break;
    }
    glutPostRedisplay();
}

// Funcion para dibujar los puntos control en la region derecha
void dibujarPControl()
{
    Tlista t = lista;
    float x, y;
    glBegin(GL_POINTS);
    for (int p = 0; p < N; p++)
    {
        x = t->x;
        y = t->y;
        glVertex3f(x, 0, y);
        t = t->sgte;
    }
    glEnd();
}

// Funcion para graficar la curva spline en la region izquierda
void graficarBSpline2d()
{
    if (lista != NULL)
    {
        Tlista t = lista;
        float x, y;
        glBegin(GL_LINE_STRIP);
        for (int punto = 0; punto < N - 3; punto++)
        {
            for (float u = 0.0; u <= 1; u += 0.01)
            {
                x = bSpline(u, 0, t);
                y = bSpline(u, 1, t);
                glVertex2f(x, y);
                x = bSpline(u, 0, t);
                y = bSpline(u, 1, t);
                glVertex2f(x, y);
            }
            t = t->sgte;
        }
        glEnd();
    }
}

// Funcion para graficar el Bspline en la region derecha
void graficarBSpline()
{
    if (lista != NULL)
    {
        Tlista t = lista;
        float x, z;
        glBegin(GL_QUAD_STRIP);
        for (int punto = 0; punto < N - 3; punto++)
        {
            for (float u = 0.0; u <= 1; u += 0.01)
            {
                x = bSpline(u, 0, t);
                z = bSpline(u, 1, t);
                glVertex3f(x, 0, z);
                x = bSpline(u, 0, t);
                z = bSpline(u, 1, t);
                glVertex3f(x, h, z);
            }
            t = t->sgte;
        }
        glEnd();
    }
}

// Funcion para recuperar las posiciones de la curva
float bSpline(float u, int coordenada, Tlista punto)
{
    // Si coordenada es igual a 0 entonces queremos las ordenadas (punto->x)
    bool coor = coordenada == 0;
    float total = ((1 - u) * (1 - u) * (1 - u) / 6) * (coor ? punto->x : punto->y);
    punto = punto->sgte;
    total += ((3 * u * u * u - 6 * u * u + 4) / 6) * (coor ? punto->x : punto->y);
    punto = punto->sgte;
    total += ((1 + 3 * u + 3 * u * u - 3 * u * u * u) / 6) * (coor ? punto->x : punto->y);
    punto = punto->sgte;
    total += (u * u * u / 6) * (coor ? punto->x : punto->y);
    return total;
}

// Insertar los puntos en la lista enlazada
// punto 1 ----->  punto 2 ------> punto 3 -----> etc;
void insertarFinal(float x, float y)
{
    Tlista t;
    Tlista q = new (struct punto);

    q->x = x;
    q->y = y;
    q->sgte = NULL;

    if (lista == NULL)
    {
        lista = q;
    }
    else
    {
        t = lista;
        while (t->sgte != NULL)
        {
            t = t->sgte;
        }
        t->sgte = q;
    }
    N++;
}

// Funcion para editar la posicion del nodo
void editarNodo(int posicion, float nuevoX, float nuevoY)
{
    int indice = 0;
    Tlista actual = lista;

    // Recorre la lista hasta encontrar el nodo en la posición deseada
    while (actual != NULL && indice < posicion)
    {
        actual = actual->sgte;
        indice++;
    }

    // Si se encuentra el nodo en la posición indicada, actualiza sus valores x e y
    if (actual != NULL)
    {
        actual->x = nuevoX;
        actual->y = nuevoY;
    }
}