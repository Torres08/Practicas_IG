
#include "Escena.h"

/*
    Modelos
*/

Ejes ejesCoordenadas;
MiMalla cubo("recursos/cubo.ply");
MiMalla suelo("recursos/cubo.ply");
MiMalla pared("recursos/cubo.ply");
MiMalla poster("recursos/cubo.ply");

MiMalla base("recursos/cubo.ply");
MiMalla baseArriba("recursos/cubo.ply");

MiMalla estante("recursos/cubo.ply");
MiMalla baseEstante("recursos/cubo.ply");

MiMalla cristal("recursos/cubo.ply");

MiMalla cristalLobo("recursos/cubo.ply");

MiMalla manzana("recursos/apple.ply");
MiDado dado;

// Botones
GLfloat colorLuz[4] = {1.0f, 1.0f, 0.0f, 1.0f};
Boton botonLuz(100, colorLuz);

GLfloat colorEscena[4] = {0.0f, 0.0f, 1.0f, 1.0f};
Boton botonEscena(101, colorEscena);

GLfloat colorAccion[4] = {1.0f, 0.0f, 0.0f, 1.0f};
Boton botonAccion(102, colorAccion);

GLfloat colorDisco[4] = {0.5f, 0.0f, 0.5f, 1.0f}; // Violeta
Boton botonDisco(103, colorDisco);

MiBrazoMecanico brazoMecanico;

MiMalla panelControl("recursos/ControlPanel/EmergencyExitControl.ply");
MiMalla lobo("recursos/Lobo/lobo.ply");

// hacer un initModel
void initModelEscena()
{
  printf("Iniciando Texturas .... \n");
  suelo.asignarTextura("recursos/metal.jpeg");
  pared.asignarTextura("recursos/pared.jpg");
  poster.asignarTextura("recursos/cat.jpeg");

  // panelControl.asignarTextura("recursos/ControlPanel2/PanelControl.jpg");
  //  Panel Control Metal
  panelControl.setDiffuseReflectivity(0.5f, 0.5f, 0.5f);
  panelControl.setSpecularReflectivity(1.0f, 1.0f, 1.0f);
  panelControl.setAmbientReflectivity(0.3f, 0.3f, 0.3f);
  panelControl.setShininess(128.0f);

  cristal.setDiffuseReflectivity(0.0f, 0.0f, 0.3f);  // Azul oscuro
  cristal.setSpecularReflectivity(0.5f, 0.5f, 1.0f); // Azul claro
  cristal.setAmbientReflectivity(0.0f, 0.0f, 0.3f);  // Azul tenue
  cristal.setShininess(100.0f);
  cristal.setTransparency(0.1f); // Ajusta la transparencia del cristal

  // Configuración del material para cristalLobo
  
  cristalLobo.setDiffuseReflectivity(0.0f, 0.3f, 0.3f);  // Verde oscuro
  cristalLobo.setSpecularReflectivity(0.5f, 1.0f, 0.0f); // Verde claro
  cristalLobo.setAmbientReflectivity(0.0f, 0.3f, 0.0f);  // Verde tenue
  cristalLobo.setShininess(100.0f);
  cristalLobo.setTransparency(0.1f); // Ajusta la transparencia del cristal
  
  suelo.setDiffuseReflectivity(0.8f, 0.8f, 0.8f);
  suelo.setSpecularReflectivity(0, 0, 0);
  suelo.setAmbientReflectivity(0, 0, 0);
  suelo.setShininess(100.0f);

  base.asignarTextura("recursos/base2.jpg");
  baseArriba.asignarTextura("recursos/base.jpeg");

  lobo.asignarTextura("recursos/Lobo/lobo.jpeg");

  dado.asignarTextura("recursos/dado.jpg");

  estante.asignarTextura("recursos/cuero.jpeg");
  baseEstante.asignarTextura("recursos/cuero.jpeg");
}

/**
 * @brief Aplicar material a una malla.
 * @param malla La malla a la que se le aplicará el material.
 */
void aplicarMaterial(const MiMalla &malla)
{
  float diffuse[3], specular[3], ambient[3];
  std::tie(diffuse[0], diffuse[1], diffuse[2]) = malla.getDiffuseReflectivity();
  std::tie(specular[0], specular[1], specular[2]) = malla.getSpecularReflectivity();
  std::tie(ambient[0], ambient[1], ambient[2]) = malla.getAmbientReflectivity();
  float shininess = malla.getShininess();
  float transparency = malla.getTransparency(); // Obtener la transparencia

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
  glMaterialf(GL_FRONT, GL_ALPHA, transparency);
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

bool botonAnimacionAccion = false;

bool getBotonAnimacionAccion()
{
  return botonAnimacionAccion;
}

void setBotonAnimacionAccion(bool value)
{

  botonAnimacionAccion = value;
  if (botonAnimacionAccion)
  {
    botonAccion.iniciarAnimacion();
  }
}

bool botonAnimacionDisco= false;

bool getBotonAnimacionDisco()
{
  return botonAnimacionDisco;
}

void setBotonAnimacionDisco(bool value)
{

  botonAnimacionDisco = value;
  if (botonAnimacionDisco)
  {
    botonDisco.iniciarAnimacion();
  }
}


/**
 * @brief Get y set para cambiar angulo para cada punto del brazo Mecánico
 */

void global_setAnguloA(float angulo)
{
  brazoMecanico.setAnguloA(angulo);
}

float global_getAnguloA()
{
  return brazoMecanico.getAnguloA();
}

void global_setAnguloB(float angulo)
{
  brazoMecanico.setAnguloB(angulo);
}

float global_getAnguloB()
{
  return brazoMecanico.getAnguloB();
}

void global_setAnguloC(float angulo)
{
  brazoMecanico.setAnguloC(angulo);
}

float global_getAnguloC()
{
  return brazoMecanico.getAnguloC();
}

void global_setAnguloD(float angulo)
{
  brazoMecanico.setAnguloD(angulo);
}

float global_getAnguloD()
{
  return brazoMecanico.getAnguloD();
}

void global_setAnguloE(float angulo)
{
  brazoMecanico.setAnguloE(angulo);
}

float global_getAnguloE()
{
  return brazoMecanico.getAnguloE();
}

void global_setAnguloF(float angulo)
{
  brazoMecanico.setAnguloF(angulo);
}

float global_getAnguloF()
{
  return brazoMecanico.getAnguloF();
}

void global_setAnguloG(float angulo)
{
  brazoMecanico.setAnguloG(angulo);
}

float global_getAnguloG()
{
  return brazoMecanico.getAnguloG();
}

void global_setAnguloH(float angulo)
{
  brazoMecanico.setAnguloH(angulo);
}

float global_getAnguloH()
{
  return brazoMecanico.getAnguloH();
}

void global_setAnguloI(float angulo)
{
  brazoMecanico.setAnguloI(angulo);
}

float global_getAnguloI()
{
  return brazoMecanico.getAnguloI();
}


void cambioTexturaManzana(bool value)
{
  if (value)
  {
    manzana.asignarTextura("recursos/madera.jpg");
  }
  else
  {
    manzana.asignarTextura("recursos/marmol.jpg");
  }
}

int animacion = 0;

void setAnimacion(int a)
{
  animacion = a;
}

int getAnimacion()
{
  return animacion;
}

/* ------------------------------------------------------------------------------------- */

void Escena::LaboratorioModelo()
{
  // Habitacion
  glPushMatrix();

  // suelo
  glPushMatrix();
  GLfloat colorSuelo[4] = {0.5f, 0.5f, 0.5f, 1.0f}; // Gris
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorSuelo);
  glScalef(20.0f, 0.1f, 20.0f); // Escalar el cubo para convertirlo en un plano más grande
  glRotatef(90, 1, 0, 0);
  aplicarMaterial(suelo);
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

  // Base
  glPushMatrix();

  glPushMatrix();
  glTranslatef(0, 6, -3);
  glScalef(6.0f, 0.01f, 6.0f); // Escalar el cubo para convertirlo en un plano más grande
  glRotatef(90, 1, 0, 0);
  baseArriba.drawConTextura();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 3, -3);
  glScalef(6, 6, 6);
  base.drawConTexturaCilindrica();
  glPopMatrix();

  glPopMatrix();

  glPopMatrix();
}

void Escena::PanelControlModelo(bool seleccion)
{
  /* ------------------------- */
  // Panel Control
  glPushMatrix();

  glPushMatrix();
  glTranslatef(0, 2.8, 6);
  glScalef(6, 6, 6);
  glRotatef(-90, 1, 0, 0);
  aplicarMaterial(panelControl);
  // panelControl.drawConTexturaCoordenada();
  panelControl.draw();

  glPopMatrix();

  // boton luz

  glPushMatrix();

  glTranslatef(-1.23, 4.5, 6);
  glRotatef(45, 1, 0, 0);

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

  glTranslatef(-1.23, 3.25, 7.25);
  glRotatef(45, 1, 0, 0);

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

  // Boton Acción
  glPushMatrix();

  glTranslatef(1.3, 3.7, 6.5);
  glRotatef(45, 1, 0, 0);
  glScalef(1.8, 1.8, 1.8);

  if (seleccion)
  {
    configurarSeleccion();
    ColorSeleccion(botonAccion.getId());
  }

  if (!getIluminacion())
  {
    GLfloat colorOscuro[4] = {0.0f, 0.0f, 0.0f, 1.0f}; // Negro
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorOscuro);
  }

  if (getBotonAnimacionAccion())
  {
    botonAccion.animacion();
  }
  else
  {
    botonAccion.draw();
  }

  // Para seleccion
  if (seleccion)
  {
    restaurarEstado();
  }

  glPopMatrix();

  glPopMatrix();
}

Escena::Escena()
{

  static GLfloat pos[4] = {0.0, 10.0, 0.0, 1.0}; // Posición de la fuente de luz
  float color[4] = {0.8, 0.0, 1, 1};
  // GLfloat colorLuzDifusa[4] = {0.1f, 0.1f, 0.1f, 1.0f}; // Color oscuro difuso
  // GLfloat colorLuzEspecular[4] = {0.1f, 0.1f, 0.1f, 1.0f}; // Color oscuro especular

  glClearColor(0.0, 0.0, 0.0, 1.0);                   // Fija el color de fondo a negro
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, colorLuzDifusa);
  // glLightfv(GL_LIGHT0, GL_SPECULAR, colorLuzEspecular);
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

  LaboratorioModelo();
  PanelControlModelo(seleccion);

  /* ------------------------- */
  glPushMatrix();

  glTranslatef(0, 6.75, -3);

  if (animacion)
  {
    brazoMecanico.draw_animacion();
  }
  else
  {
    brazoMecanico.draw();
  }

  // brazoMecanico.draw();

  glPopMatrix();

  // boton Disco

  glPushMatrix();

  glPushMatrix();

  glTranslatef(7, 2, -3.8);
    glScalef(1.8, 1.8, 1.8);
  glRotatef(90, 1, 0, 0);

  if (seleccion)
  {
    configurarSeleccion();
    ColorSeleccion(botonDisco.getId());
  }


  if (getBotonAnimacionDisco())
  {
    botonDisco.animacion();
  }
  else
  {
    botonDisco.draw();
  }

  glPopMatrix();

  // estante lobo
  glPushMatrix();
  glTranslatef(7, 9, -7);
  glScalef(9, 9, 9);
  glRotatef(-90, 1, 0, 0);
  lobo.drawConTexturaCoordenada();
  glPopMatrix();

  // Base Lobo
  glPushMatrix();
  glTranslatef(7, 0, -4);

  glScalef(1, 0.75, 1);
  glPushMatrix();

  glPushMatrix();
  glTranslatef(0, 6, -3);
  glScalef(6.0f, 0.01f, 6.0f); // Escalar el cubo para convertirlo en un plano más grande
  glRotatef(90, 1, 0, 0);
  baseEstante.drawConTextura();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 3, -3);
  glScalef(6, 6, 6);
  estante.drawConTexturaCilindrica();
  glPopMatrix();

  glPushMatrix();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Dibujar cristalLobo
  glPushMatrix();
  glPushMatrix();
  glTranslatef(0, 13, -3);
  glScalef(6, 14, 6);
  aplicarMaterial(cristalLobo);
  cristalLobo.draw();
  glPopMatrix();

  glPopMatrix();


  // Deshabilitar la mezcla de colores
  glDisable(GL_BLEND);

  glPopMatrix();

  glPopMatrix();
  glPopMatrix();

  glPopMatrix();
}

void Escena::Escena2(bool seleccion)
{
  glPushMatrix();

  LaboratorioModelo();
  PanelControlModelo(seleccion);

  /* ------------------------- */

  // manzana
  glPushMatrix();

  glPushMatrix();
  // Ajusta la escala según sea necesario

  // printf("Escenario Accion %d\n", getEscenarioAccion());
  GLfloat colorManzana[4] = {1.0f, 0.0f, 0.0f, 1.0f}; // Violet
  static bool texturaAsignada = false;

  switch (getEscenarioAccion())
  {
  // drawFlat
  case 1:
    glPushMatrix();
    glTranslatef(0, 9, -3);
    glRotatef(get_roty(), 0, 1, 0);
    glScalef(3, 3, 3);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorManzana);
    manzana.draw();
    glPopMatrix();
    break;

  // drawSmooth
  case 2:
    glPushMatrix();
    glTranslatef(0, 9, -3);
    glRotatef(get_roty(), 0, 1, 0);
    glScalef(3, 3, 3);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorManzana);
    manzana.drawSmooth();
    glPopMatrix();
    break;

  //
  case 3:
    // Dibujar la manzana oro
    glPushMatrix();
    glTranslatef(0, 9, -3);
    glRotatef(get_roty(), 0, 1, 0);
    glScalef(3, 3, 3);

    manzana.setDiffuseReflectivity(0.83f, 0.69f, 0.22f); // Oro difuso
    manzana.setSpecularReflectivity(1.0f, 0.85f, 0.56f); // Oro especular
    manzana.setAmbientReflectivity(0.25f, 0.20f, 0.07f); // Oro ambiente
    manzana.setShininess(128.0f);

    aplicarMaterial(manzana);
    // Habilitar la mezcla de colores
    manzana.drawSmooth();

    glPopMatrix();

    // Dibujar el cristal

    break;

  case 4:
  {
    glPushMatrix();
    glTranslatef(0, 9, -3);
    glRotatef(get_roty(), 0, 1, 0);
    glScalef(3, 3, 3);

    GLint prevPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, prevPolygonMode);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Dibujar la manzana
    GLfloat colorManzana[] = {0.0f, 1.0f, 0.0f, 1.0f}; // Violet
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorManzana);
    manzana.drawSmooth();

    glPolygonMode(GL_FRONT, prevPolygonMode[0]);
    glPolygonMode(GL_BACK, prevPolygonMode[1]);
    glPopMatrix();

    break;
  }

  case 5:
  {
    glPushMatrix();
    glTranslatef(0, 9, -3);
    glRotatef(get_roty(), 0, 1, 0);
    glScalef(3, 3, 3);

    // mallaTaza.drawConTexturaCilindrica();
    manzana.drawConTextura();

    glPopMatrix();

    break;
  }
  case 6:
    glPushMatrix();
    glTranslatef(0, 9, -3);
    glRotatef(get_roty(), 0, 1, 0);
    glScalef(3, 3, 3);

    // mallaTaza.drawConTexturaCilindrica();
    manzana.drawConTexturaCilindrica();

    glPopMatrix();

    break;

  case 7:
    // Dibujar la manzana oro
    glPushMatrix();
    glTranslatef(0, 0, -3);
    glRotatef(get_roty(), 0, 1, 0);
    glTranslatef(-1.5, 7.5, -1.5);
    glScalef(3, 3, 3);

    dado.draw();

    glPopMatrix();
    break;

  default:
    break;
  }

  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 9, -3);
  glScalef(6, 6, 6);
  aplicarMaterial(cristal);
  // Habilitar la mezcla de colores
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  cristal.draw();

  glDisable(GL_BLEND);
  glPopMatrix();

  glPopMatrix();
}