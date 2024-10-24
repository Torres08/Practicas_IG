/*

    J.C. Torres
    Dpto. Lenguajes y Sistemas Inform�ticos
    E.T.S.I. Inform�tica
    Univ. de Granada

    Dibuja un cubo girando
    compilar con: gcc cubo.c -lglut -lGLU -lGL -o cubo
*/

/*
    gcc cubo.c -lglut -lGLU -lGL -o cubo
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float roty = 30.0;

void plano(float t)
// Construye un plano horizontal de tamano t x t
{

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(t, 0, t);
    glVertex3f(t, 0, -t);
    glVertex3f(-t, 0, -t);
    glVertex3f(-t, 0, t);
    glEnd();
}

void Dibuja()
{
    float pos[4] = {5.0, 5.0, 10.0, 0.0};
    float morado[4] = {0.8, 0, 1, 1}, verde[4] = {0, 1, 0, 1};
    float azul[4] = {0.0, 0.0, 1.0, 1.0};  // Color azul
    glClearColor(1, 1, 1, 1); // Fondo blanco
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-0.5, -0.5, -100);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glRotatef(20, 1.0, 0.0, 0.0);

    /*
      Cambiarlo a marron
    */
    float marron[4] = {0.6, 0.3, 0.0, 1.0}; // Color marrón
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
    // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, marron);

    plano(30);
    glRotatef(roty, 0.0, 1.0, 0.0);
    glTranslatef(0, 5, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado);
    glutSolidCube(10);


    // Añadir esfera azul a la derecha del cubo
    glTranslatef(15, 0, 0);                               // Mover a la derecha del cubo
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul); // Aplicar color azul
    glutSolidSphere(5, 50, 50);  // Dibujar esfera de radio 5

    glutSwapBuffers();
}
/* ------------------------------------------------------------------------- */

void Ventana(GLsizei ancho, GLsizei alto)
{ // Se ejecuta cuando se cambia la ventana, recibe el ancho y alto de la ventana X
    float D = ancho;
    if (D < alto)
        D = alto;
    glViewport(0, 0, ancho, alto); // fija el area de dibujo en la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ancho / D, ancho / D, -alto / D, alto / D, 5, 250);

    gluPerspective(45.0, (float)ancho / (float)alto, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}
/*
void Ventana(GLsizei ancho, GLsizei alto)
{ 
    float D = ancho; 
    if (D < alto) 
        D = alto;

    glViewport(0, 0, ancho, alto); // fija el área de dibujo en la ventana 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Establecer la proyección en perspectiva
    gluPerspective(45.0, (float)ancho / (float)alto, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}
*/

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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}