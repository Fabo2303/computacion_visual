#include <GL/glut.h>
#include <iostream>

// Función para dibujar un punto en la pantalla
void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// Función para dibujar una línea entre dos puntos p y q utilizando el algoritmo de punto medio
void drawLine(int x0, int y0, int xf, int yf) {
    int dx = xf - x0;
    int dy = yf - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; ++i) {
        drawPixel(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5)); // Dibuja el píxel más cercano

        x += xIncrement;
        y += yIncrement;
    }
}

// Función de dibujo principal
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Color blanco

    // Definir los puntos de inicio y fin de la línea
    int x0 = 100, y0 = 150;
    int xf = 300, yf = 50;

    drawLine(x0, y0, xf, yf);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Dibujar Linea con Algoritmo de Punto Medio");
    gluOrtho2D(0, 400, 0, 400); // Configura la proyección ortográfica
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}