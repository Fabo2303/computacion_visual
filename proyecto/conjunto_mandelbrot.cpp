#include <GL/freeglut.h>
#include <complex>
#include <iostream>

const int width = 800;    // Ancho de la ventana
const int height = 800;   // Alto de la ventana
const double xmin = -2.0; // Coordenadas del área de visualización
const double xmax = 1.0;
const double ymin = -1.5;
const double ymax = 1.5;
const int maxIterations = 1000; // Máximo número de iteraciones

// Función para determinar si un punto está dentro del conjunto de Mandelbrot
int mandelbrot(double real, double imag) {
    std::complex<double> c(real, imag);
    std::complex<double> z(0, 0);

    int n = 0;
    while (std::abs(z) <= 2.0 && n < maxIterations) {
        z = z * z + c;
        n++;
    }

    return n;
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Establece el color de fondo a blanco
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    
    // Dibuja el conjunto de Mandelbrot
    double stepX = (xmax - xmin) / width;
    double stepY = (ymax - ymin) / height;
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            double x = xmin + i * stepX;
            double y = ymin + j * stepY;

            int value = mandelbrot(x, y);

            // Color del píxel basado en el número de iteraciones
            if (value == maxIterations) {
                glColor3d(0.0, 0.0, 1.0); // Establece el color del conjunto de Mandelbrot
            } else {
                glColor3d(1.0, 1.0, 1.0); // Establece el color del fondo
            }

            glBegin(GL_QUADS);
            glVertex2d(x, y);
            glVertex2d(x + stepX, y);
            glVertex2d(x + stepX, y + stepY);
            glVertex2d(x, y + stepY);
            glEnd();
        }
    }

    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Conjunto de Mandelbrot");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
