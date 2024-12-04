
#include "Escena.h"

/*
    Modelos
*/

Ejes ejesCoordenadas;
MiMalla cubo("recursos/cubo.ply");
Boton boton;

void Escena::ComenzarAnimacionBoton(){
  boton.iniciarAnimacion();
}

Escena::Escena()
{
  static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0}; // Posición de la fuente de luz
  float color[4] = {0.8, 0.0, 1, 1};

  glClearColor(0.0, 0.0, 0.0, 1.0);                   // Fija el color de fondo a negro
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glEnable(GL_LIGHT0);

  // deberia ir el manejo de la luz aqui
  /*
  if (getModo() == GL_FILL && getIluminacion())
  {
    glEnable(GL_LIGHTING);
  }
  else
  {
    glDisable(GL_LIGHTING);
  }
  */

  transformacionVisualizacion(); // Carga transformación de visualización
  ejesCoordenadas.draw();        // Dibuja los ejes
}

void Escena::configurarSeleccion()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS); // Guardar el estado actual de OpenGL
  glDisable(GL_LIGHTING);
  glDisable(GL_DITHER);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glDisable(GL_FOG);
  glDisable(GL_MULTISAMPLE);
}

void Escena::restaurarEstado()
{
  glPopAttrib(); // Restaurar el estado anterior de OpenGL
}

void Escena::Escena1(bool seleccion)
{
  glPushMatrix();

  if (seleccion)
  {
    configurarSeleccion();
    ColorSeleccion(cubo.getId());
  }
  else
  {
    GLfloat color1[4] = {0.0f, 1.0f, 1.0f, 1.0f}; // Magenta
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
  }

  cubo.draw(); // dibujo el cubo

  if (seleccion)
  {
    restaurarEstado();
  }

  glPopMatrix();
}

void Escena::Escena2(bool seleccion)
{
  glPushMatrix();

  if (seleccion)
  {
    configurarSeleccion();
    ColorSeleccion(boton.getId());
  } 
  
  if (getSelectedObjectId() == boton.getId()){
    printf("Animacion\n");
    boton.animacion();
    boton.iniciarAnimacion();

  } else {
    printf("No animo\n");
    boton.draw();
    glTranslatef(0, 2, 0);
    cubo.draw();
  }



  if (seleccion)
  {
    restaurarEstado();
  }

  glPopMatrix();
}