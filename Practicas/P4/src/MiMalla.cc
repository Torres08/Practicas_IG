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

    // Inicializar las propiedades del material
    diffuseReflectivity[0] = 0.8f;
    diffuseReflectivity[1] = 0.8f;
    diffuseReflectivity[2] = 0.8f;

    specularReflectivity[0] = 0.0f;
    specularReflectivity[1] = 0.0f;
    specularReflectivity[2] = 0.0f;

    ambientReflectivity[0] = 0.2f;
    ambientReflectivity[1] = 0.2f;
    ambientReflectivity[2] = 0.2f;

    shininess = 1.0f;

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
    // Si no se ha asignado reflectividad ambiente, usar la reflectividad difusa
    if (ambientReflectivity[0] == 0.0f && ambientReflectivity[1] == 0.0f && ambientReflectivity[2] == 0.0f)
    {
        ambientReflectivity[0] = diffuseReflectivity[0];
        ambientReflectivity[1] = diffuseReflectivity[1];
        ambientReflectivity[2] = diffuseReflectivity[2];
    }

    // Asignar las propiedades del material
    /*
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseReflectivity);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectivity);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientReflectivity);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess); // Asignar el brillo
    */

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
        // glTexCoord2f(coordenadasTextura[t.v1].u, coordenadasTextura[t.v1].v);
        glVertex3f(v1.x, v1.y, v1.z);

        // glTexCoord2f(coordenadasTextura[t.v2].u, coordenadasTextura[t.v2].v);
        glVertex3f(v2.x, v2.y, v2.z);

        // glTexCoord2f(coordenadasTextura[t.v3].u, coordenadasTextura[t.v3].v);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd(); // Finalizar el dibujo
}

void MiMalla::drawConTexturaCilindrica()
{
    processVertices();

    // Si no se ha asignado reflectividad ambiente, usar la reflectividad difusa
    if (ambientReflectivity[0] == 0.0f && ambientReflectivity[1] == 0.0f && ambientReflectivity[2] == 0.0f)
    {
        ambientReflectivity[0] = diffuseReflectivity[0];
        ambientReflectivity[1] = diffuseReflectivity[1];
        ambientReflectivity[2] = diffuseReflectivity[2];
    }

    // Calcular minY y maxY
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();
    for (const auto &vertice : vertices)
    {
        if (vertice.y < minY)
            minY = vertice.y;
        if (vertice.y > maxY)
            maxY = vertice.y;
    }

    // Calcular el centro geométrico de la malla
    float centerX = (x_min + x_max) / 2.0f;
    float centerY = (y_min + y_max) / 2.0f;
    float centerZ = (z_min + z_max) / 2.0f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < triangulos.size(); i++)
    {
        Triangulo t = triangulos[i];

        Vertice v1 = vertices[t.v1];
        Vertice v2 = vertices[t.v2];
        Vertice v3 = vertices[t.v3];

        Normal n = normalesTriangulos[i]; // Obtener la normal del triángulo

        glNormal3f(n.x, n.y, n.z);

        // Calcular coordenadas de textura cilíndricas
        /*
        float u1 = atan2(v1.z, v1.x) / (2 * M_PI) + 0.5f;
        float v1_tex = (v1.y - minY) / (maxY - minY); // Normalizar la coordenada y
        float u2 = atan2(v2.z, v2.x) / (2 * M_PI) + 0.5f;
        float v2_tex = (v2.y - minY) / (maxY - minY); // Normalizar la coordenada y
        float u3 = atan2(v3.z, v3.x) / (2 * M_PI) + 0.5f;
        float v3_tex = (v3.y - minY) / (maxY - minY); // Normalizar la coordenada y
        */

        float u1 = atan2(v1.z - centerZ, v1.x - centerX) / (2 * M_PI) + 0.5f;
        float v1_tex = (v1.y - minY) / (maxY - minY); // Normalizar la coordenada y
        float u2 = atan2(v2.z - centerZ, v2.x - centerX) / (2 * M_PI) + 0.5f;
        float v2_tex = (v2.y - minY) / (maxY - minY); // Normalizar la coordenada y
        float u3 = atan2(v3.z - centerZ, v3.x - centerX) / (2 * M_PI) + 0.5f;
        float v3_tex = (v3.y - minY) / (maxY - minY); // Normalizar la coordenada y

        glTexCoord2f(u1, v1_tex);
        glVertex3f(v1.x, v1.y, v1.z);
        glTexCoord2f(u2, v2_tex);
        glVertex3f(v2.x, v2.y, v2.z);
        glTexCoord2f(u3, v3_tex);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void MiMalla::drawConTextura() {

    processVertices();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    if (ambientReflectivity[0] == 0.0f && ambientReflectivity[1] == 0.0f && ambientReflectivity[2] == 0.0f)
    {
        ambientReflectivity[0] = diffuseReflectivity[0];
        ambientReflectivity[1] = diffuseReflectivity[1];
        ambientReflectivity[2] = diffuseReflectivity[2];
    }

    // Configurar la generación automática de coordenadas de textura

    //GL_OBJECT_LINEAR: Genera coordenadas de textura lineales en el espacio del objeto.
    //GL_SPHERE_MAP: Genera coordenadas de textura para mapeo esférico.
    //GL_REFLECTION_MAP: Genera coordenadas de textura para mapeo de reflexión.
    //GL_NORMAL_MAP: Genera coordenadas de textura para mapeo de normales


    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Ajustar los planos de generación de coordenadas de textura para cubrir todo el cubo
    GLfloat sPlane[] = { 1.0f, 0.0f, 0.0f, 0.0f };
    GLfloat tPlane[] = { 0.0f, 1.0f, 0.0f, 0.0f };
    glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < triangulos.size(); i++) {
        Triangulo t = triangulos[i];

        Vertice v1 = vertices[t.v1];
        Vertice v2 = vertices[t.v2];
        Vertice v3 = vertices[t.v3];

        Normal n = normalesTriangulos[i];

        glNormal3f(n.x, n.y, n.z);

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();

    // Deshabilitar la generación automática de coordenadas de textura
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
}

/**
 * @brief Dibuja la malla con sombreado plano.
 */
void MiMalla::drawFlat()
{
    glShadeModel(GL_FLAT);

    // this->draw();
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
        // glTexCoord2f(coordenadasTextura[t.v1].u, coordenadasTextura[t.v1].v);
        glVertex3f(v1.x, v1.y, v1.z);

        // glTexCoord2f(coordenadasTextura[t.v2].u, coordenadasTextura[t.v2].v);
        glVertex3f(v2.x, v2.y, v2.z);

        // glTexCoord2f(coordenadasTextura[t.v3].u, coordenadasTextura[t.v3].v);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd(); // Finalizar el dibujo
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

void MiMalla::setDiffuseReflectivity(float r, float g, float b)
{
    diffuseReflectivity[0] = r;
    diffuseReflectivity[1] = g;
    diffuseReflectivity[2] = b;
}

void MiMalla::setSpecularReflectivity(float r, float g, float b)
{
    specularReflectivity[0] = r;
    specularReflectivity[1] = g;
    specularReflectivity[2] = b;
}

void MiMalla::setAmbientReflectivity(float r, float g, float b)
{
    ambientReflectivity[0] = r;
    ambientReflectivity[1] = g;
    ambientReflectivity[2] = b;
}

void MiMalla::setShininess(float s)
{
    // printf("shininess: %f", shininess);
    shininess = s;
}

std::tuple<float, float, float> MiMalla::getDiffuseReflectivity() const
{
    return std::make_tuple(diffuseReflectivity[0], diffuseReflectivity[1], diffuseReflectivity[2]);
}

std::tuple<float, float, float> MiMalla::getSpecularReflectivity() const
{
    return std::make_tuple(specularReflectivity[0], specularReflectivity[1], specularReflectivity[2]);
}

std::tuple<float, float, float> MiMalla::getAmbientReflectivity() const
{
    return std::make_tuple(ambientReflectivity[0], ambientReflectivity[1], ambientReflectivity[2]);
}

float MiMalla::getShininess() const
{
    return shininess;
}

// box

void MiMalla::calculateMinMax()
{
    x_min = std::numeric_limits<float>::infinity();
    y_min = std::numeric_limits<float>::infinity();
    z_min = std::numeric_limits<float>::infinity();
    x_max = -std::numeric_limits<float>::infinity();
    y_max = -std::numeric_limits<float>::infinity();
    z_max = -std::numeric_limits<float>::infinity();

    for (const auto &vertex : vertices)
    {
        float x = vertex.x;
        float y = vertex.y;
        float z = vertex.z;
        if (x < x_min)
            x_min = x;
        if (y < y_min)
            y_min = y;
        if (z < z_min)
            z_min = z;
        if (x > x_max)
            x_max = x;
        if (y > y_max)
            y_max = y;
        if (z > z_max)
            z_max = z;
    }
}

void MiMalla::calculateDimensions()
{
    width = x_max - x_min;
    height = y_max - y_min;
    depth = z_max - z_min;
}

float MiMalla::calculateMaxDimension()
{
    return std::max({width, height, depth});
}

/*
float MiMalla::calculateMaxDimension() {
    return *std::max_element(std::initializer_list<float>{width, height, depth}.begin(), std::initializer_list<float>{width, height, depth}.end());
}
*/

void MiMalla::normalizeVertices()
{
    if (dim_max == 0)
    {
        printf("Dimensión máxima es 0\n");
        // Evitar división por cero
        return;
    }
    if (vertices.empty())
    {
        printf("No hay vértices\n");
        // Manejar el caso de que no haya vértices
        return;
    }

    std::vector<Vertice> normalized_vertices;
    for (const auto &vertex : vertices)
    {
        float x = vertex.x;
        float y = vertex.y;
        float z = vertex.z;
        float norm_x = (x - x_min - width / 2.0f) / dim_max;
        float norm_y = (y - y_min - height / 2.0f) / dim_max;
        float norm_z = (z - z_min - depth / 2.0f) / dim_max;
        normalized_vertices.push_back({norm_x, norm_y, norm_z});
    }

    vertices = normalized_vertices;
}

void MiMalla::enableAutoNormalize() {
    glEnable(GL_NORMALIZE);
}


void MiMalla::processVertices()
{
    calculateMinMax();
    calculateDimensions();
    dim_max = calculateMaxDimension();
    normalizeVertices();
    enableAutoNormalize();
}