#ifndef MIMALLA_H
#define MIMALLA_H

#include <vector>
#include <GL/glut.h>
#include "modelo.h" // aqui tengo objeto 3D
#include "file_ply_stl.h"
#include <string>
#include <cmath>

using namespace std;

// Estructura para un vértice
struct Vertice {
    float x, y, z;
};

// Estructura para una normal
struct Normal {
    float x, y, z;
};

// Estructura para un triángulo
struct Triangulo {
    int v1, v2, v3;  // Índices de los vértices
};

// Clase MiMallaTriangulo
class MiMalla : Objeto3D {
public:
    // Atributos
    vector<Vertice> vertices;          // Lista de vértices
    vector<Triangulo> triangulos;      // Lista de triángulos
    vector<Normal> normalesVertices;    // Normales por vértice
    vector<Normal> normalesTriangulos;  // Normales por triángulo

    // Constructor
    MiMalla(const char *filename);

    // Métodos
    void addVertice(float x, float y, float z);
    void addTriangulo(int v1, int v2, int v3);

    void addNormalVertice(float x, float y, float z);
    void addNormalTriangulo(float x, float y, float z);
    
    void draw(); 
    
    void calcularNormales();

    void drawFlat();
    void drawSmooth();

};

#endif // MIMALLATRIANGULO_H
