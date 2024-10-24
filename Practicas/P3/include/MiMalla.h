
/**
 * @file MiMalla.h
 * @brief Clase para representar una malla de triángulos
 * @author Torres Ramos, Juan Luis 
 */

#ifndef MIMALLA_H
#define MIMALLA_H

#include <vector>
#include <GL/glut.h>
#include "modelo.h" 
#include "file_ply_stl.h"
#include <string>
#include <cmath>

using namespace std;


/**
 * @brief Estructura para un vértice
 */
struct Vertice {
    float x, y, z;
};

/**
 * @brief Estructura para una normal
 */
struct Normal {
    float x, y, z;
};

/**
 * @brief Estructura para un triángulo / cara
 */
struct Triangulo {
    int v1, v2, v3;  // Índices de los vértices
};


/**
 * @brief Clase para representar una malla de triángulos
 */
class MiMalla : Objeto3D {
public:
    vector<Vertice> vertices;          // Lista de vértices
    vector<Triangulo> triangulos;      // Lista de triángulos
    vector<Normal> normalesVertices;    // Normales por vértice
    vector<Normal> normalesTriangulos;  // Normales por triángulo

    MiMalla(const char *filename);

    void addVertice(float x, float y, float z);
    void addTriangulo(int v1, int v2, int v3);

    
    void draw(); 
    
    void calcularNormales();

    void drawFlat();
    void drawSmooth();

};

#endif // MIMALLATRIANGULO_H
