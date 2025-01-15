#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>

/*
gcc lego.cc -lglut -lGLU -lGL -lm -o lego

*/

float roty = 30.0;
int figuraSeleccionada = 1; // Variable global para almacenar la figura seleccionada

float pos[4] = {10.0, 10.0, 15.0, 0.0};
float morado[4] = {0.8, 0, 1, 1}, verde[4] = {0, 1, 0, 1};
float rojo[4] = {1, 0, 0, 1};
float azul[4] = {0, 0, 1, 1};

class Ejes
{
public:
    float longitud = 30;
    // Dibuja el objeto
    void draw()
    {
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
        {
            glColor3f(0, 1, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, longitud, 0);

            glColor3f(1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(longitud, 0, 0);

            glColor3f(0, 0, 1);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, longitud);
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }
};

Ejes ejesCoordenadas;

using namespace std;

// Estructuras para almacenar vértices, triángulos y coordenadas de textura
struct _vertex3f
{
    float x, y, z;
}; // Coordenadas 3D
struct _vertex3ui
{
    unsigned int _0, _1, _2;
}; // Índices de triángulos
struct _vertex2f
{
    float u, v;
}; // Coordenadas de textura

void Figura1()
{
    // Vértices del tetraedro
    vector<_vertex3f> Vertices(4);
    Vertices[0] = {0.0f, 0.0f, 0.0f}; // V0
    Vertices[1] = {1.0f, 0.0f, 0.0f}; // V1
    Vertices[2] = {0.5f, 1.0f, 0.5f}; // V2
    Vertices[3] = {0.5f, 0.0f, 1.0f}; // V3

    // Triángulos (caras visibles)
    vector<_vertex3ui> Triangles(4);
    Triangles[0] = {0, 1, 2}; // Cara 1
    Triangles[1] = {0, 3, 2}; // Cara 2
    Triangles[2] = {1, 3, 2}; // Cara 3
    Triangles[3] = {0, 1, 3}; // Cara inferior

    // Coordenadas de textura
    vector<_vertex2f> Textures(4);
    Textures[0] = {0.0f, 0.0f}; // Coordenada para V0
    Textures[1] = {1.0f, 0.0f}; // Coordenada para V1
    Textures[2] = {0.5f, 1.0f}; // Coordenada para V2
    Textures[3] = {0.5f, 0.5f}; // Coordenada para V3

    // Dibujar el tetraedro
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < Triangles.size(); i++)
    {

        switch (i)
        {
        case 0:
            glColor3f(1.0, 0.0, 0.0);
            break; // Rojo
        case 1:
            glColor3f(0.0, 1.0, 0.0);
            break; // Verde
        case 2:
            glColor3f(0.0, 0.0, 1.0);
            break; // Azul
        case 3:
            glColor3f(1.0, 1.0, 0.0);
            break; // Amarillo
        }
        // Asignar coordenadas de textura y vértices para cada triángulo
        // glTexCoord2f(Textures[Triangles[i]._0].u, Textures[Triangles[i]._0].v);
        glVertex3f(Vertices[Triangles[i]._0].x, Vertices[Triangles[i]._0].y, Vertices[Triangles[i]._0].z);

        // glTexCoord2f(Textures[Triangles[i]._1].u, Textures[Triangles[i]._1].v);
        glVertex3f(Vertices[Triangles[i]._1].x, Vertices[Triangles[i]._1].y, Vertices[Triangles[i]._1].z);

        // glTexCoord2f(Textures[Triangles[i]._2].u, Textures[Triangles[i]._2].v);
        glVertex3f(Vertices[Triangles[i]._2].x, Vertices[Triangles[i]._2].y, Vertices[Triangles[i]._2].z);
    }
    glEnd();
}

void Dibuja()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-0.5, -5, -100);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glRotatef(20, 1.0, 0.0, 0.0);
    glRotatef(roty, 0.0, 1.0, 0.0);

    ejesCoordenadas.draw();

    // glTranslatef(2, 0.5, 1);

    // Cambiar de figura según la tecla presionada
    switch (figuraSeleccionada)
    {
    case 1:
        Figura1();
        break;

    default:
        break;
    }

    glPopMatrix();
    glutSwapBuffers();
}

// Función para manejar las teclas
void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case '1':
        figuraSeleccionada = 1;
        break;
    default:
        break;
    }
    glutPostRedisplay(); // Redibujar la ventana cuando se presiona una tecla
}

void Ventana(GLsizei ancho, GLsizei alto)
{
    float D = ancho;
    if (D < alto)
        D = alto;
    glViewport(0, 0, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ancho / D, ancho / D, -alto / D, alto / D, 5, 250);
    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    roty += 0.15;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("IG: cubo");
    glutDisplayFunc(Dibuja);
    glutReshapeFunc(Ventana);
    glutIdleFunc(idle);
    glutKeyboardFunc(teclado); // Asignar la función de teclado
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
