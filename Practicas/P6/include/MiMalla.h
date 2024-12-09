
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
#include <tuple>
#include <limits>
#include <vector>
#include <array>
#include <algorithm>
#include <initializer_list>

using namespace std;

/**
 * @brief Estructura para un vértice
 */
struct Vertice
{
    float x, y, z; // Coordenadas del vértice
    float s, t;    // Coordenadas de textura
};

/**
 * @brief Estructura para una normal
 */
struct Normal
{
    float x, y, z;
};

/**
 * @brief Estructura para un triángulo / cara
 */
struct Triangulo
{
    int v1, v2, v3; // Índices de los vértices
};

struct CoordenadaTextura
{
    double s, t;
};

/*
 * @brief Clase para representar una malla de triángulos
 */
class MiMalla : public Objeto3D
{

private:
    // propiedades del materia
    float diffuseReflectivity[3] = {0.8f, 0.8f, 0.8f};
    float specularReflectivity[3] = {0.0f, 0.0f, 0.0f};
    float ambientReflectivity[3] = {0.0f, 0.0f, 0.0f};
    float shininess = 0.0f;
    float transparency = 1.0f; // Añadir propiedad de transparencia


    float x_min, y_min, z_min, x_max, y_max, z_max;
    float width, height, depth;
    float dim_max;

    int id;

public:
    vector<Vertice> vertices;          // Lista de vértices
    vector<Triangulo> triangulos;      // Lista de triángulos
    vector<Normal> normalesVertices;   // Normales por vértice
    vector<Normal> normalesTriangulos; // Normales por triángulo

    vector<CoordenadaTextura> coordenadasTextura;

    MiMalla(const char *filename);

    void addVertice(float x, float y, float z);
    void addTriangulo(int v1, int v2, int v3);

    void draw();
    void calcularNormales();

    void setDiffuseReflectivity(float r, float g, float b);
    void setSpecularReflectivity(float r, float g, float b);
    void setAmbientReflectivity(float r, float g, float b);
    void setShininess(float s);
    void setTransparency(float t);

    // Getter methods
    std::tuple<float, float, float> getDiffuseReflectivity() const;
    std::tuple<float, float, float> getSpecularReflectivity() const;
    std::tuple<float, float, float> getAmbientReflectivity() const;
    float getShininess() const;
    float getTransparency() const;

    void calculateMinMax();
    void calculateDimensions();
    float calculateMaxDimension();
    void normalizeVertices();
    void processVertices();
    void enableAutoNormalize();

    int getId();
    void setId(int id);

    void drawConTextura();
    void drawConTexturaCoordenada();
    void drawConTexturaCilindrica();

};

#endif // MIMALLATRIANGULO_H
