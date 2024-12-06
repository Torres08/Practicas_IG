
#include "Escena.h"

/*
    Modelos
*/

Ejes ejesCoordenadas;
MiMalla cubo("recursos/cubo.ply");
MiMalla suelo("recursos/cubo.ply");
MiMalla pared("recursos/cubo.ply");
MiMalla poster("recursos/cubo.ply");

// Botones
GLfloat colorLuz[4] = {1.0f, 1.0f, 0.0f, 1.0f};
Boton botonLuz(100, colorLuz);

GLfloat colorEscena[4] = {0.0f, 0.0f, 1.0f, 1.0f};
Boton botonEscena(101, colorEscena);

MiBrazoMecanico brazoMecanico;


// hacer un initModel 

void initModelEscena()
{
  printf("Iniciando Texturas .... \n");
  suelo.asignarTextura("recursos/metal.jpeg");
  pared.asignarTextura("recursos/pared.jpg");
  poster.asignarTextura("recursos/cat.jpeg");
}


bool botonAnimacionLuz = false;

bool getBotonAnimacionLuz()
{
  return botonAnimacionLuz;
}

void setBotonAnimacionLuz(bool value)
{
  botonAnimacionLuz = value;
  if (botonAnimacionLuz)
  {
    botonLuz.iniciarAnimacion();
  }
}

bool botonAnimacionEscena = false;

bool getBotonAnimacionEscena()
{
  return botonAnimacionEscena;
}

void setBotonAnimacionEscena(bool value)
{

  botonAnimacionEscena = value;
  if (botonAnimacionEscena)
  {
    botonEscena.iniciarAnimacion();
  }
}

/* ------------------------------------------------------------------------------------- */

void Escena::ComenzarAnimacionBoton()
{
  botonLuz.iniciarAnimacion();
}

Escena::Escena()
{

  static GLfloat pos[4] = {0.0, 10.0, 0.0, 1.0}; // Posición de la fuente de luz 
  float color[4] = {0.8, 0.0, 1, 1};
  //GLfloat colorLuzDifusa[4] = {0.1f, 0.1f, 0.1f, 1.0f}; // Color oscuro difuso
  //GLfloat colorLuzEspecular[4] = {0.1f, 0.1f, 0.1f, 1.0f}; // Color oscuro especular


  glClearColor(0.0, 0.0, 0.0, 1.0);                   // Fija el color de fondo a negro
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, colorLuzDifusa);
  //glLightfv(GL_LIGHT0, GL_SPECULAR, colorLuzEspecular);
  glEnable(GL_LIGHT0);

  
  transformacionVisualizacion(); // Carga transformación de visualización
  ejesCoordenadas.draw();        // Dibuja los ejes

  // dibujar un plano
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

  // Boton Izquierda

  /*
  glPushMatrix();

  glTranslatef(-5, 0, 5);

  if (seleccion)
  {
    configurarSeleccion();
    ColorSeleccion(botonEscena.getId());
  }

  if (getBotonAnimacionEscena())
  {
    botonEscena.animacion();
  }
  else
  {
    botonEscena.draw();
  }

  // Para seleccion
  if (seleccion)
  {
    restaurarEstado();
  }

  glPopMatrix();
  */

  // brazoMecanico
  //brazoMecanico.draw();


  glPopMatrix();
}

void Escena::Escena2(bool seleccion)
{
  glPushMatrix();

  // Habitacion 

  // suelo 
  glPushMatrix();
    GLfloat colorSuelo[4] = {0.5f, 0.5f, 0.5f, 1.0f}; // Gris 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorSuelo);
    glScalef(20.0f, 0.1f, 20.0f); // Escalar el cubo para convertirlo en un plano más grande
    glRotatef(90, 1, 0, 0);
    suelo.drawConTextura();
  glPopMatrix();
  
  // pared
  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glTranslatef(7.48, 10.05, 0);
  glPushMatrix();
    GLfloat colorPared[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // Blanco
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorPared);
    glScalef(15.0f, 0.1f, 20.0f); // Escalar el cubo para convertirlo en un plano más grande
    glRotatef(90, 1, 0, 0);
    pared.drawConTextura();
  glPopMatrix();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 7.48, -10.05);
  glRotatef(90, 0, 0, 1);
  glRotatef(90, 1, 0, 0);
  glPushMatrix();
    GLfloat colorPared2[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // Blanco
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorPared2);
    glScalef(15.0f, 0.1f, 20.0f); // Escalar el cubo para convertirlo en un plano más grande
    glRotatef(90, 1, 0, 0);
    pared.drawConTextura();
  glPopMatrix();
  glPopMatrix();

  glPushMatrix();
  glRotatef(180, 0, 1, 0);
  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glTranslatef(7.48, 10.05, 0);
  glPushMatrix();
    GLfloat colorPared3[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // Blanco
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorPared3);
    glScalef(15.0f, 0.1f, 20.0f); // Escalar el cubo para convertirlo en un plano más grande
    glRotatef(90, 1, 0, 0);
    pared.drawConTextura();
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();

  //glRotatef(90, 0, 1, 0);
  glPushMatrix();
  glTranslatef(-5, 8, -9.9);
  glRotatef(90, 0, 1, 0);
  glRotatef(90, 0, 0, 1);
  glPushMatrix();
  glScalef(9.0f, 0.1f, 6.0f); // Escalar el cubo para convertirlo en un plano más grande
  glRotatef(90, 1, 0, 0);
  poster.drawConTextura();
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();


  

  /* ------------------------- */

  // boton luz

  glPushMatrix();

  glTranslatef(0, 0.3, 5);

  if (seleccion)
  {
    configurarSeleccion();
    ColorSeleccion(botonLuz.getId());
  }


  if (!getIluminacion())
  {
    GLfloat colorOscuro[4] = {0.0f, 0.0f, 0.0f, 1.0f}; // Negro
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorOscuro);
  }

  if (getBotonAnimacionLuz())
  {
    botonLuz.animacion();
  }
  else
  {
    botonLuz.draw();
  }

  // Para seleccion
  if (seleccion)
  {
    restaurarEstado();
  }

  glPopMatrix();

  // Boton Izquierda
  glPushMatrix();

  glTranslatef(-5, 0.3, 5);
  if (seleccion)
  {
    configurarSeleccion();
    ColorSeleccion(botonEscena.getId());
  }

  if (getBotonAnimacionEscena())
  {
    botonEscena.animacion();
  }
  else
  {
    botonEscena.draw();
  }

  // Para seleccion
  if (seleccion)
  {
    restaurarEstado();
  }

  glPopMatrix();

  glPopMatrix();
}