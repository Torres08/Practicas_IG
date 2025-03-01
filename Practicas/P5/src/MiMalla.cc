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
    vector<double> temp_texturas;

    // inicializar id
    static int nextId = 1;
    id = nextId++;
    printf("id: %d\n", id);

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

    ply::read(filename, temp_vertices, temp_triangulos, temp_texturas);

    for (size_t i = 0; i < temp_vertices.size(); i += 3)
    {
        addVertice(temp_vertices[i], temp_vertices[i + 1], temp_vertices[i + 2]);
    }

    for (size_t i = 0; i < temp_triangulos.size(); i += 3)
    {
        addTriangulo(temp_triangulos[i], temp_triangulos[i + 1], temp_triangulos[i + 2]);
    }
    //

    for (size_t i = 0; i < temp_texturas.size(); i += 2)
    {
        /*
             Vertice v;
            v.x = x;
            v.y = y;
            v.z = z;
            vertices.push_back(v);
        */
        CoordenadaTextura ct;
        ct.s = temp_texturas[i];
        ct.t = temp_texturas[i + 1];
        coordenadasTextura.push_back(ct);
        // printf("Coordenada de textura: (%.8f, %.8f)\n", ct.s, ct.t);
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

void MiMalla::drawWithOutlineNormal(){
    draw();
    drawWithOutline();
}

void MiMalla::drawWithOutlineTextura(){
    drawConTextura();
    drawWithOutline();
}


void MiMalla::drawWithOutline()
{
    
    // Guardar el estado actual de OpenGL
    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);

    // Desactivar la iluminación y el sombreado
    glDisable(GL_LIGHTING);
    glDisable(GL_DITHER);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Establecer el color del contorno a amarillo
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); // Iniciar el dibujo de triángulos

    for (size_t i = 0; i < triangulos.size(); i++)
    {
        Triangulo t = triangulos[i]; // Obtener el triángulo

        Vertice v1 = vertices[t.v1]; // Obtener los vértices
        Vertice v2 = vertices[t.v2];
        Vertice v3 = vertices[t.v3];

        // Dibujar los vértices
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd();

    // Restaurar el estado anterior de OpenGL
    glPopAttrib();
}

void MiMalla::drawWithOutlineLobo()
{
    // Dibujar el objeto normalmente
    drawLobo();

    // Guardar el estado actual de OpenGL
    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);

    // Desactivar la iluminación y el sombreado
    glDisable(GL_LIGHTING);
    glDisable(GL_DITHER);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Establecer el color del contorno a amarillo
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); // Iniciar el dibujo de triángulos

    for (size_t i = 0; i < triangulos.size(); i++)
    {
        Triangulo t = triangulos[i]; // Obtener el triángulo

        Vertice v1 = vertices[t.v1]; // Obtener los vértices
        Vertice v2 = vertices[t.v2];
        Vertice v3 = vertices[t.v3];

        // Dibujar los vértices
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd();

    // Restaurar el estado anterior de OpenGL
    glPopAttrib();
}

void MiMalla::drawLobo()
{
    processVertices();

    // Si no se ha asignado reflectividad ambiente, usar la reflectividad difusa
    if (ambientReflectivity[0] == 0.0f && ambientReflectivity[1] == 0.0f && ambientReflectivity[2] == 0.0f)
    {
        ambientReflectivity[0] = diffuseReflectivity[0];
        ambientReflectivity[1] = diffuseReflectivity[1];
        ambientReflectivity[2] = diffuseReflectivity[2];
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

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

        /*
        printf("Vértice 1: (%.9f, %.9f, %.9f)\n", v1.x, v1.y, v1.z);
        printf("Coordenadas de textura: (%.9f, %.9f)\n", coordenadasTextura[t.v1].s, coordenadasTextura[t.v1].t);
        printf("Vértice 2: (%.9f, %.9f, %.9f)\n", v2.x, v2.y, v2.z);
        printf("Coordenadas de textura: (%.9f, %.9f)\n", coordenadasTextura[t.v2].s, coordenadasTextura[t.v2].t);
        printf("Vértice 3: (%.9f, %.9f, %.9f)\n", v3.x, v3.y, v3.z);
        printf("Coordenadas de textura: (%.9f, %.9f)\n", coordenadasTextura[t.v3].s, coordenadasTextura[t.v3].t);
        */

        // Dibujar los vértices
        glTexCoord2f(coordenadasTextura[t.v1].s, coordenadasTextura[t.v1].t);
        glVertex3f(v1.x, v1.y, v1.z);

        glTexCoord2f(coordenadasTextura[t.v2].s, coordenadasTextura[t.v2].t);
        glVertex3f(v2.x, v2.y, v2.z);

        glTexCoord2f(coordenadasTextura[t.v3].s, coordenadasTextura[t.v3].t);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd(); // Finalizar el dibujo

    glDisable(GL_TEXTURE_2D);
}

/**
 * @brief Dibuja la malla con textura cilíndrica.
 */
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

        // Calcular coordenadas de textura cilíndricas
        float u1 = atan2(v1.z - centerZ, v1.x - centerX) / (2 * M_PI) + 0.5f;
        float v1_tex = (v1.y - minY) / (maxY - minY); // Normalizar la coordenada y
        float u2 = atan2(v2.z - centerZ, v2.x - centerX) / (2 * M_PI) + 0.5f;
        float v2_tex = (v2.y - minY) / (maxY - minY); // Normalizar la coordenada y
        float u3 = atan2(v3.z - centerZ, v3.x - centerX) / (2 * M_PI) + 0.5f;
        float v3_tex = (v3.y - minY) / (maxY - minY); // Normalizar la coordenada y

        glNormal3f(n1.x, n1.y, n1.z);
        glTexCoord2f(u1, v1_tex);
        glVertex3f(v1.x, v1.y, v1.z);

        glNormal3f(n2.x, n2.y, n2.z);
        glTexCoord2f(u2, v2_tex);
        glVertex3f(v2.x, v2.y, v2.z);

        glNormal3f(n3.x, n3.y, n3.z);
        glTexCoord2f(u3, v3_tex);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

/**
 * @brief Dibuja la malla con textura esférica. (otra forma que no he optado)
 */
void MiMalla::drawConTextura()
{
    processVertices();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    if (ambientReflectivity[0] == 0.0f && ambientReflectivity[1] == 0.0f && ambientReflectivity[2] == 0.0f)
    {
        ambientReflectivity[0] = diffuseReflectivity[0];
        ambientReflectivity[1] = diffuseReflectivity[1];
        ambientReflectivity[2] = diffuseReflectivity[2];
    }

    glShadeModel(GL_SMOOTH); // Establecer el modo de sombreado suave

    // Configurar la generación automática de coordenadas de textura
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Ajustar los planos de generación de coordenadas de textura para cubrir todo el cubo
    GLfloat sPlane[] = {1.0f, 0.0f, 0.0f, 0.5f};
    GLfloat tPlane[] = {0.0f, 1.0f, 0.0f, 0.5f};
    glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

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

/**
 * @brief Establece la reflectividad difusa del material.
 *
 * @param r Componente roja de la reflectividad difusa.
 * @param g Componente verde de la reflectividad difusa.
 * @param b Componente azul de la reflectividad difusa.
 */
void MiMalla::setDiffuseReflectivity(float r, float g, float b)
{
    diffuseReflectivity[0] = r;
    diffuseReflectivity[1] = g;
    diffuseReflectivity[2] = b;
}

/**
 * @brief Establece la reflectividad especular del material.
 *
 * @param r Componente roja de la reflectividad especular.
 * @param g Componente verde de la reflectividad especular.
 * @param b Componente azul de la reflectividad especular.
 */
void MiMalla::setSpecularReflectivity(float r, float g, float b)
{
    specularReflectivity[0] = r;
    specularReflectivity[1] = g;
    specularReflectivity[2] = b;
}

/**
 * @brief Establece la reflectividad ambiente del material.
 *
 * @param r Componente roja de la reflectividad ambiente.
 * @param g Componente verde de la reflectividad ambiente.
 * @param b Componente azul de la reflectividad ambiente.
 */
void MiMalla::setAmbientReflectivity(float r, float g, float b)
{
    ambientReflectivity[0] = r;
    ambientReflectivity[1] = g;
    ambientReflectivity[2] = b;
}

/**
 * @brief Establece el brillo del material.
 * @param s Brillo del material.
 */
void MiMalla::setShininess(float s)
{
    // printf("shininess: %f", shininess);
    shininess = s;
}

/**
 * @brief Devuelve la Reflectividad de la malla.
 */
std::tuple<float, float, float> MiMalla::getDiffuseReflectivity() const
{
    return std::make_tuple(diffuseReflectivity[0], diffuseReflectivity[1], diffuseReflectivity[2]);
}

/**
 * @brief Devuelve la Reflectividad Especular de la malla.
 */
std::tuple<float, float, float> MiMalla::getSpecularReflectivity() const
{
    return std::make_tuple(specularReflectivity[0], specularReflectivity[1], specularReflectivity[2]);
}

/**
 * @brief Devuelve la Reflectividad Ambiente de la malla.
 */
std::tuple<float, float, float> MiMalla::getAmbientReflectivity() const
{
    return std::make_tuple(ambientReflectivity[0], ambientReflectivity[1], ambientReflectivity[2]);
}

/**
 * @brief Devuelve el Brillo de la malla.
 */
float MiMalla::getShininess() const
{
    return shininess;
}

// box

/**
 * @brief Calcula los valores mínimos y máximos de las coordenadas x, y, z de los vértices.
 */
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

/**
 * @brief Calcula las dimensiones de la malla.
 */
void MiMalla::calculateDimensions()
{
    width = x_max - x_min;
    height = y_max - y_min;
    depth = z_max - z_min;
}

/**
 * @brief Calcula la dimensión máxima de la malla.
 */
float MiMalla::calculateMaxDimension()
{
    return std::max({width, height, depth});
}

/*
float MiMalla::calculateMaxDimension() {
    return *std::max_element(std::initializer_list<float>{width, height, depth}.begin(), std::initializer_list<float>{width, height, depth}.end());
}
*/

/**
 * @brief Normaliza las coordenadas de los vértices de la malla.
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

/**
 * @brief Activa la normalización automática.
 */
void MiMalla::enableAutoNormalize()
{
    glEnable(GL_NORMALIZE);
}

/**
 * @brief Procesa los vértices de la malla. (draw box)
 *
 * Esta función realiza varias operaciones en los vértices de la malla:
 * 1. Calcula los valores mínimos y máximos de los vértices.
 * 2. Calcula las dimensiones de la malla.
 * 3. Determina la dimensión máxima de la malla.
 * 4. Normaliza los vértices para que se ajusten dentro de un rango estándar.
 * 5. Activa la normalización automática para futuras operaciones con vértices.
 */
void MiMalla::processVertices()
{
    calculateMinMax();
    calculateDimensions();
    dim_max = calculateMaxDimension();
    normalizeVertices();
    enableAutoNormalize();
}

int MiMalla::getId()
{
    return id;
}

void MiMalla::setId(int _id)
{
    id = _id;
};