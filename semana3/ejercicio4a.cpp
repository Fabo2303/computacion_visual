#include <GL/glut.h>
#include <iostream>

int indicador, X0, X1, Y0, Y1;
bool entrar = false;

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


void controlRaton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (indicador == 0) {
            X0 = x -200;
            Y0 = 200 - y;
            indicador++;
            std::cout << "X: " << X0 << " Y: " << Y0 << "\n";
        } else if (indicador == 1) {
            X1 = x - 200;
            Y1 = 200 - y;
            indicador++;
            entrar = true;
            std::cout << "X: " << X1 << " Y: " << Y1 << "\n";
            glutPostRedisplay();
        }
    }
}

// Función de dibujo principal
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Color blanco

    if(entrar)
        drawLine(X0, Y0, X1, Y1);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Dibujar Linea con Algoritmo de Punto Medio");
    gluOrtho2D(-200, 200, -200, 200); // Configura la proyección ortográfica
    glutDisplayFunc(display);
    glutMouseFunc(controlRaton);
    glutMainLoop();

    return 0;
}