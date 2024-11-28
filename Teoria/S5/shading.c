#include <GL/glut.h>
#include <math.h>

// Variables para almacenar las coordenadas de la luz
GLfloat light_pos[] = { 0.0f, 0.0f, 2.0f, 1.0f };

// Variables para los materiales
GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess[] = { 50.0f };

// Shader program para Phong (con GLSL)
GLuint phongShaderProgram;

// Carga los shaders Phong
void loadShaders() {
    const char* vertexShaderSource = "#version 120\n"
        "varying vec3 normal, lightDir, viewDir;"
        "void main() {"
        "   vec4 vertexPos = gl_ModelViewMatrix * gl_Vertex;"
        "   lightDir = vec3(gl_LightSource[0].position - vertexPos);"
        "   viewDir = vec3(-vertexPos.xyz);"
        "   normal = gl_NormalMatrix * gl_Normal;"
        "   gl_Position = ftransform();"
        "}";

    const char* fragmentShaderSource = "#version 120\n"
        "varying vec3 normal, lightDir, viewDir;"
        "void main() {"
        "   vec3 N = normalize(normal);"
        "   vec3 L = normalize(lightDir);"
        "   vec3 V = normalize(viewDir);"
        "   vec3 R = reflect(-L, N);"
        "   float lambertTerm = max(dot(N, L), 0.0);"
        "   vec4 diffuse = lambertTerm * gl_FrontMaterial.diffuse;"
        "   vec4 ambient = 0.1*gl_FrontMaterial.ambient;"
        "   vec4 specular = vec4(0.0);"
        "   if (lambertTerm > 0.0) {"
        "       float spec = pow(max(dot(R, V), 0.0), gl_FrontMaterial.shininess);"
        "       specular = spec * gl_FrontMaterial.specular;"
        "   }"
        "   gl_FragColor = ambient + diffuse + specular;"
        "}";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    phongShaderProgram = glCreateProgram();
    glAttachShader(phongShaderProgram, vertexShader);
    glAttachShader(phongShaderProgram, fragmentShader);

    glLinkProgram(phongShaderProgram);
}

// Dibuja una esfera con sombreado plano
void drawFlatShadedSphere() {
    glShadeModel(GL_FLAT);
    glutSolidSphere(1.0, 20, 20);
}

// Dibuja una esfera con sombreado Gouraud
void drawGouraudShadedSphere() {
    glShadeModel(GL_SMOOTH);
    glutSolidSphere(1.0, 20, 20);
}

// Dibuja una esfera con sombreado Phong usando shaders GLSL
void drawPhongShadedSphere() {
    glUseProgram(phongShaderProgram);
    glutSolidSphere(1.0, 20, 20);
    glUseProgram(0);  // Desactiva los shaders
}

// Función para dibujar la escena
void dibuja(void) {
    float posicion[4]={10,10,2,0};
    float verde[4]={0.1,1,0.1,1};
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0,GL_POSITION,posicion);
    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE,verde);
    glPushMatrix();
    // Esfera con sombreado plano (Flat)
    glTranslatef(0.0f, 2.5f, 0.0f);
    drawFlatShadedSphere();

    // Esfera con sombreado Gouraud
    glTranslatef(0.0f, -2.5f, 0.0f);
    drawGouraudShadedSphere();

    // Esfera con sombreado Phong
    glTranslatef(0.0f, -2.5f, 0.0f);
    drawPhongShadedSphere();

    glPopMatrix();
    glutSwapBuffers();
}

// Configuración inicial de OpenGL
void init(void) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configuración de la luz
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    // Configuración del material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Cargar shaders Phong
    loadShaders();
}

// Función para manejar el redimensionamiento de la ventana
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sombreado Flat, Gouraud y Phong");

    init();

    glutDisplayFunc(dibuja);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

