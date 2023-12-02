#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

// Variables para los vértices del triángulo
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};

// Índice del vértice seleccionado (-1 si ninguno está seleccionado)
int selectedVertex = -1;
int order = 4;
bool listo = false;
int indice = 0;

void drawSierpinski(int order, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{
    if (order == 0)
    {
        // Dibuja una línea simple si el orden es 0
        glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }
    else
    {
        GLfloat xA = (x3 + x1) / 2;
        GLfloat yA = (y3 + y1) / 2;
        GLfloat xB = (x3 + x2) / 2;
        GLfloat yB = (y3 + y2) / 2;
        GLfloat xC = (x2 + x1) / 2;
        GLfloat yC = (y2 + y1) / 2;

        // Llama a la función recursivamente para los segmentos de la curva
        drawSierpinski(order - 1, x1, y1, xA, yA, xC, yC);
        drawSierpinski(order - 1, xA, yA, x3, y3, xB, yB);
        drawSierpinski(order - 1, xC, yC, xB, yB, x2, y2);
    }
}

// Función de devolución de llamada para manejar eventos del mouse
void mouse_callback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (listo)
        {
            float mouseX = static_cast<float>(x) / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
            float mouseY = 1.0f - static_cast<float>(y) / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

            // Verificar si el clic del mouse está cerca de alguno de los vértices
            for (int i = 0; i < 9; i += 3)
            {
                float distance = std::sqrt((mouseX - vertices[i]) * (mouseX - vertices[i]) +
                                           (mouseY - vertices[i + 1]) * (mouseY - vertices[i + 1]));

                if (distance < 0.1) // Ajusta este valor según sea necesario para la sensibilidad de selección
                {
                    selectedVertex = i;
                    std::cout << "Vértice seleccionado: " << i / 3 + 1 << std::endl;
                    break;
                }
            }
        }
        else
        {
            vertices[indice] = static_cast<float>(x) / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
            vertices[indice + 1] = 1.0f - static_cast<float>(y) / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;
            indice += 3;
            listo = (indice == 9);
        }
    }
}

// Función de devolución de llamada para manejar eventos de arrastre del mouse
void motion_callback(int x, int y)
{
    if (selectedVertex != -1 && listo)
    {
        // Actualizar las coordenadas del vértice seleccionado
        vertices[selectedVertex] = static_cast<float>(x) / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        vertices[selectedVertex + 1] = 1.0f - static_cast<float>(y) / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

        // Solicitar una actualización de la pantalla
        glutPostRedisplay();
    }
}

// Función de dibujo
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar el triángulo con los vértices actualizados
    if (listo)
    {
        drawSierpinski(order, vertices[0], vertices[1], vertices[3], vertices[4], vertices[6], vertices[7]);
    }

    // Intercambiar los búferes frontal y trasero
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'b':
        order++;
        glutPostRedisplay();
        break;

    case 'n':
        order--;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    // Inicializar GLUT y crear la ventana
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Triángulo con selección y edición de puntos");

    // Configurar las devoluciones de llamada del mouse
    glutMouseFunc(mouse_callback);
    glutMotionFunc(motion_callback);

    // Configurar el modo de proyección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // Configurar la función de dibujo
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);

    // Iniciar el bucle de eventos de GLUT
    glutMainLoop();

    return 0;
}
