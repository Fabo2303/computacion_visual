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
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    
    // Dibuja el conjunto de Mandelbrot
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            double x = xmin + (xmax - xmin) * i / (width - 1);
            double y = ymin + (ymax - ymin) * j / (height - 1);

            int value = mandelbrot(x, y);

            // Color del píxel basado en el número de iteraciones
            double t = static_cast<double>(value) / static_cast<double>(maxIterations);
            glColor3d(0.0, 0.0, t); // Color basado en 't'

            glBegin(GL_POINTS);
            glVertex2d(x, y);
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
