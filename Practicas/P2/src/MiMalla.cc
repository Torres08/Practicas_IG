
#include "MiMalla.h"
#include "file_ply_stl.h"
#include "modelo.h"

using namespace std;

// Constructor, usar read de file_pñy_stl
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

void MiMalla::addVertice(float x, float y, float z)
{
    Vertice v;
    v.x = x;
    v.y = y;
    v.z = z;
    vertices.push_back(v);
}

void MiMalla::addTriangulo(int v1, int v2, int v3)
{
    Triangulo t;
    t.v1 = v1;
    t.v2 = v2;
    t.v3 = v3;
    triangulos.push_back(t);
}

void MiMalla::draw() {

    // Establece el modo de sombreado aquí si es necesario (opcional)
    glShadeModel(GL_SMOOTH); // Sombreado suave
    
    // Inicia el dibujo de triángulos
    glBegin(GL_TRIANGLES);
    
    for (size_t i = 0; i < triangulos.size(); i++) {
        // Obtengo el triángulo
        Triangulo t = triangulos[i];

        // Obtengo los vértices
        Vertice v1 = vertices[t.v1];
        Vertice v2 = vertices[t.v2];
        Vertice v3 = vertices[t.v3];

        // Normal del triángulo
        Normal n = normalesTriangulos[i];

        // Dibujo
        glNormal3f(n.x, n.y, n.z); // Establece la normal para el triángulo
        glVertex3f(v1.x, v1.y, v1.z); // Vértice 1
        glVertex3f(v2.x, v2.y, v2.z); // Vértice 2
        glVertex3f(v3.x, v3.y, v3.z); // Vértice 3
    }

    glEnd(); // Finaliza el dibujo de triángulos
}

// PO X P1 | P0 X P2

// normales Triangulo
// se calculan a partir de los vertices de cada triangulo con el producto vectorial
// triangulos = caras

/*
1. Inicializar normales de todos los vértices a (0, 0, 0)
2. Para cada cara:
• Sumar su normal a sus tres vértices
3. Para cada vértice:
• Normalizar su normal
*/
void MiMalla::calcularNormales()
{
    // 1. Inicializamos las normales (normalesVertices, normalesTriangulos) a 0
    normalesVertices.resize(vertices.size(), {0.0f, 0.0f, 0.0f});
    normalesTriangulos.resize(triangulos.size(), {0.0f, 0.0f, 0.0f});

    // 2. Calculamos las normales de los triángulos (caras)
    for (size_t i = 0; i < triangulos.size(); ++i)
    {
        const Triangulo& t = triangulos[i];  // Usamos const porque no modificamos el triángulo

        // Obtenemos los vértices del triángulo
        const Vertice& p0 = vertices[t.v1];
        const Vertice& p1 = vertices[t.v2];
        const Vertice& p2 = vertices[t.v3];

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
        Normal& normal = normalesVertices[i]; // normal del vértice
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


void MiMalla::drawFlat() {
    glShadeModel(GL_FLAT); // Establecer el modo de sombreado plano

    glBegin(GL_TRIANGLES); // Iniciar el dibujo de triángulos

    for (size_t i = 0; i < triangulos.size(); i++) {
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

void MiMalla::drawSmooth() {
    glShadeModel(GL_SMOOTH); // Establecer el modo de sombreado suave

    glBegin(GL_TRIANGLES); // Iniciar el dibujo de triángulos

    for (size_t i = 0; i < triangulos.size(); i++) {
        Triangulo t = triangulos[i]; // Obtener el triángulo

        Vertice v1 = vertices[t.v1]; // Obtener los vértices
        Vertice v2 = vertices[t.v2];
        Vertice v3 = vertices[t.v3];

        // Establecer la normal para cada vértice
        Normal n1 = normalesVertices[t.v1]; // Normal del vértice 1
        Normal n2 = normalesVertices[t.v2]; // Normal del vértice 2
        Normal n3 = normalesVertices[t.v3]; // Normal del vértice 3

        glNormal3f(n1.x, n1.y, n1.z); // Normal para el vértice 1
        glVertex3f(v1.x, v1.y, v1.z); // Dibujar el vértice 1

        glNormal3f(n2.x, n2.y, n2.z); // Normal para el vértice 2
        glVertex3f(v2.x, v2.y, v2.z); // Dibujar el vértice 2

        glNormal3f(n3.x, n3.y, n3.z); // Normal para el vértice 3
        glVertex3f(v3.x, v3.y, v3.z); // Dibujar el vértice 3
    }

    glEnd(); // Finalizar el dibujo
}



