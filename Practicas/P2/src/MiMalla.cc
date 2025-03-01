/**
 * @file MiMalla.cc
 * @brief Implementación de la clase MiMalla
 * @author Torres Ramos, Juan Luis
 */

#include "MiMalla.h"
#include "file_ply_stl.h"
#include "modelo.h"
using namespace std;

/**
 * @brief Constructor de la clase MiMalla.
 *
 * Este constructor inicializa la malla leyendo los datos de vértices y triángulos desde un archivo PLY.
 * Luego, agrega los vértices y triángulos a la malla y calcula las normales.
 *
 * @param filename La ruta al archivo PLY que contiene los datos de la malla.
 */
MiMalla::MiMalla(const char *filename)
{
    vector<float> temp_vertices;
    vector<int> temp_triangulos; // caras

    ply::read(filename, temp_vertices, temp_triangulos);

    for (size_t i = 0; i < temp_vertices.size(); i += 3)
    {
        addVertice(temp_vertices[i], temp_vertices[i + 1], temp_vertices[i + 2]);
    }

    for (size_t i = 0; i < temp_triangulos.size(); i += 3)
    {
        addTriangulo(temp_triangulos[i], temp_triangulos[i + 1], temp_triangulos[i + 2]);
    }

    // calcular normales
    this->calcularNormales();
}

/**
 * @brief Agrega un vértice a la malla.
 *
 * @param x Coordenada x del vértice.
 * @param y Coordenada y del vértice.
 * @param z Coordenada z del vértice.
 */
void MiMalla::addVertice(float x, float y, float z)
{
    Vertice v;
    v.x = x;
    v.y = y;
    v.z = z;
    vertices.push_back(v);
}

/**
 * @brief Añade un triángulo a la malla.
 *
 * @param v1 Índice del primer vértice del triángulo.
 * @param v2 Índice del segundo vértice del triángulo.
 * @param v3 Índice del tercer vértice del triángulo.
 */
void MiMalla::addTriangulo(int v1, int v2, int v3)
{
    Triangulo t;
    t.v1 = v1;
    t.v2 = v2;
    t.v3 = v3;
    triangulos.push_back(t);
}



/**
 * @brief Calcula las normales de los vértices y de los triángulos de la malla.
 */
void MiMalla::calcularNormales()
{
    // 1. Inicializamos las normales (normalesVertices, normalesTriangulos) a 0
    normalesVertices.resize(vertices.size(), {0.0f, 0.0f, 0.0f});
    normalesTriangulos.resize(triangulos.size(), {0.0f, 0.0f, 0.0f});

    // 2. Calculamos las normales de los triángulos (caras)
    for (size_t i = 0; i < triangulos.size(); ++i)
    {
        const Triangulo &t = triangulos[i]; // Usamos const porque no modificamos el triángulo

        // Obtenemos los vértices del triángulo
        const Vertice &p0 = vertices[t.v1];
        const Vertice &p1 = vertices[t.v2];
        const Vertice &p2 = vertices[t.v3];

        // Calculamos los vectores de las aristas
        Vertice v1 = {p1.x - p0.x, p1.y - p0.y, p1.z - p0.z};
        Vertice v2 = {p2.x - p0.x, p2.y - p0.y, p2.z - p0.z};

        // Calculamos el producto vectorial para obtener la normal del triángulo
        Normal normalTriangulo;
        normalTriangulo.x = v1.y * v2.z - v1.z * v2.y;
        normalTriangulo.y = v1.z * v2.x - v1.x * v2.z;
        normalTriangulo.z = v1.x * v2.y - v1.y * v2.x;

        // Normalizamos la normal
        float modulo = sqrt(normalTriangulo.x * normalTriangulo.x +
                            normalTriangulo.y * normalTriangulo.y +
                            normalTriangulo.z * normalTriangulo.z);

        if (modulo > 0.0f)
        {
            normalTriangulo.x /= modulo;
            normalTriangulo.y /= modulo;
            normalTriangulo.z /= modulo;
        }

        // Guardamos la normal del triángulo en el vector de normales de triángulos
        normalesTriangulos[i] = normalTriangulo;

        // 3. Acumulamos las normales de los triángulos en los vértices
        normalesVertices[t.v1].x += normalTriangulo.x;
        normalesVertices[t.v1].y += normalTriangulo.y;
        normalesVertices[t.v1].z += normalTriangulo.z;

        normalesVertices[t.v2].x += normalTriangulo.x;
        normalesVertices[t.v2].y += normalTriangulo.y;
        normalesVertices[t.v2].z += normalTriangulo.z;

        normalesVertices[t.v3].x += normalTriangulo.x;
        normalesVertices[t.v3].y += normalTriangulo.y;
        normalesVertices[t.v3].z += normalTriangulo.z;
    }

    // 4. Normalizamos las normales de los vértices
    for (size_t i = 0; i < normalesVertices.size(); ++i)
    {
        Normal &normal = normalesVertices[i]; // normal del vértice
        float modulo = sqrt(normal.x * normal.x +
                            normal.y * normal.y +
                            normal.z * normal.z);

        if (modulo > 0.0f)
        {
            normal.x /= modulo;
            normal.y /= modulo;
            normal.z /= modulo;
        }
    }
}

/**
 * @brief Dibuja la malla.
 */
void MiMalla::draw()
{

    glBegin(GL_TRIANGLES); // Iniciar el dibujo de triángulos

    for (size_t i = 0; i < triangulos.size(); i++)
    {
        Triangulo t = triangulos[i]; // Obtener el triángulo

        Vertice v1 = vertices[t.v1]; // Obtener los vértices
        Vertice v2 = vertices[t.v2];
        Vertice v3 = vertices[t.v3];

        Normal n = normalesTriangulos[i]; // Obtener la normal del triángulo

        // Establecer la normal de la cara
        glNormal3f(n.x, n.y, n.z);

        // Dibujar los vértices
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd(); // Finalizar el dibujo 
}


/**
 * @brief Dibuja la malla con sombreado plano.
 */
void MiMalla::drawFlat()
{
    glShadeModel(GL_FLAT); 

    this->draw();
}

/**
 * @brief Dibuja la malla con sombreado suave
 */
void MiMalla::drawSmooth()
{
    glShadeModel(GL_SMOOTH); // Establecer el modo de sombreado suave

    glBegin(GL_TRIANGLES); 

    for (size_t i = 0; i < triangulos.size(); i++)
    {
        Triangulo t = triangulos[i];

        Vertice v1 = vertices[t.v1]; 
        Vertice v2 = vertices[t.v2];
        Vertice v3 = vertices[t.v3];

        // Establecer la normal para cada vértice
        Normal n1 = normalesVertices[t.v1]; 
        Normal n2 = normalesVertices[t.v2]; 
        Normal n3 = normalesVertices[t.v3]; 

        glNormal3f(n1.x, n1.y, n1.z); 
        glVertex3f(v1.x, v1.y, v1.z); 

        glNormal3f(n2.x, n2.y, n2.z); 
        glVertex3f(v2.x, v2.y, v2.z); 

        glNormal3f(n3.x, n3.y, n3.z); 
        glVertex3f(v3.x, v3.y, v3.z); 
    }

    glEnd(); 
}
