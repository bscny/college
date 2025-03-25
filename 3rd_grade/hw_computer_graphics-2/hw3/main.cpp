//Computer Graphics HW-SWGL 2025
//simple modeling tool
//Transformation and Projection
//move from glut to glfw
#include <iostream>

#include <cmath>

#include <GL/glu.h>
#include <GLFW/glfw3.h>

//OpenGL Mathematics (GLM)  https://glm.g-truc.net/
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

using namespace std;
using namespace glm;

const bool STEP2 = true;
const bool STEP3 = true;
const bool USE_CUSTOM_MATRIX = true && STEP2; // this controlls if to use swView and swProject on the grids
                                               // adding && STEP2 because we can't use our projection matrix after gluLookAt is used
                                               // in other words, we can't "only" apply our projection matrix without our view matrix

const float PI = 3.14159265359;

float theta = PI / 4.0f;
float tho = PI / 4.0f;

int winWidth = 1280;
int winHeight = 720;

mat4x4 TransformMat = mat4x4(1);

mat4x4 ViewMat = mat4x4(1);
mat4x4 ProjectionMat = mat4x4(1);

vec3 default_tetrahedron_vertices[4] = {
	vec3(1,0,0), vec3(0,1,0), vec3(0,0,1), vec3(0,0,0)
};

vec3 tetrahedron_verts[4];

bool DRAW_CUBE = false;

void Draw_glVertex3f(float x, float y, float z, bool model, bool view, bool project){
    vec4 v;
    v = vec4(x, y, z, 1);

    mat4x4 P(1);
    mat4x4 V(1);
    mat4x4 M(1);

    if(model){
        M = TransformMat;
    }

    if(view){
        V = ViewMat;
    }

    if(project){
        P = ProjectionMat;
    }

    v = P * V * M * v;
    v /= v[3];

    glVertex3f(v[0], v[1], v[2]);
}

// Model Matrix Related -----------------------------------------------------------------------------
mat4x4 swTranslate(float x, float y, float z)
{
	mat4x4 Translate = mat4x4(1);
	Translate[3][0] = x;
    Translate[3][1] = y;
    Translate[3][2] = z;

	return Translate;
}

mat4x4 swRotate(float angle,float x, float y, float z)
{
    // normalize the given Vector first
    float k = pow(x, 2) + pow(y, 2) + pow(z, 2);
    k = sqrt(k);
    x /= k;
    y /= k;
    z /= k;

    // get cos and sin for given Theta
    float s = sin(angle);
    float c = cos(angle);

    // start calculatin the matrix:
    // x^2(1-c)+c  xy(1-c)-zs  xz(1-c)+ys
    // xy(1-c)+zs  y^2(1-c)+c  yz(1-c)-xs
    // xz(1-c)-ys  yz(1-c)+xs  z^2(1-c)+c
	mat4x4 Rotate = mat4x4(1);

    Rotate[0][0] = pow(x, 2) * (1 - c) + c;
    Rotate[1][0] = x * y * (1 - c) - z * s;
    Rotate[2][0] = x * z * (1 - c) + y * s;

    Rotate[0][1] = x * y * (1 - c) + z * s;
    Rotate[1][1] = pow(y, 2) * (1 - c) + c;
    Rotate[2][1] = y * z * (1 - c) - x * s;

    Rotate[0][2] = x * z * (1 - c) - y * s;
    Rotate[1][2] = y * z * (1 - c) + x * s;
    Rotate[2][2] = pow(z, 2) * (1 - c) + c;

	return Rotate;
}

mat4x4 swRotateX(float angle)
{
	mat4x4 Rotate = swRotate(angle, 1, 0, 0);

	return Rotate;
}

mat4x4 swRotateY(float angle)
{
	mat4x4 Rotate = swRotate(angle, 0, 1, 0);

	return Rotate;
}

mat4x4 swRotateZ(float angle)
{
	mat4x4 Rotate = swRotate(angle, 0, 0, 1);

	return Rotate;
}

mat4x4 swScale(float x, float y, float z)
{
	mat4x4 Scale = mat4x4(1);

    Scale[0][0] = x;
    Scale[1][1] = y;
    Scale[2][2] = z;

	return Scale;
}

// View Matrix Related ------------------------------------------------------------------------
void swLookAt(float eyeX, float eyeY, float eyeZ,
    float centerX, float centerY, float centerZ,
    float upX, float upY, float upZ)
{
    
    // firstly, get F which is camera --> at
    float F[3] = {centerX - eyeX, centerY - eyeY, centerZ - eyeZ};
    
    // normalize F
    float k = pow(F[0], 2) + pow(F[1], 2) + pow(F[2], 2);
    k = sqrt(k);
    F[0] /= k;
    F[1] /= k;
    F[2] /= k;

    // get F cross up, S
    float S[3] = {
        (F[2 - 1] * upZ) - (F[3 - 1] * upY),
        (F[3 - 1] * upX) - (F[1 - 1] * upZ),
        (F[1 - 1] * upY) - (F[2 - 1] * upX)
    };

    // normalize S
    k = pow(S[0], 2) + pow(S[1], 2) + pow(S[2], 2);
    k = sqrt(k);
    S[0] /= k;
    S[1] /= k;
    S[2] /= k;

    // get S cross F, U
    float U[3] = {
        (S[2 - 1] * F[3 - 1]) - (S[3 - 1] * F[2 - 1]),
        (S[3 - 1] * F[1 - 1]) - (S[1 - 1] * F[3 - 1]),
        (S[1 - 1] * F[2 - 1]) - (S[2 - 1] * F[1 - 1])
    };

    // normalize U
    k = pow(U[0], 2) + pow(U[1], 2) + pow(U[2], 2);
    k = sqrt(k);
    U[0] /= k;
    U[1] /= k;
    U[2] /= k;

    // after we have F, S, U, we can get matrix M and T, we do T first
    // translate vector eye relative to world space
    mat4x4 T(1);
    T[3][0] = -eyeX;
    T[3][1] = -eyeY;
    T[3][2] = -eyeZ;

    // map the world space to camera space
    mat4x4 M(1);
    M[0][0] = S[0];
    M[1][0] = S[1];
    M[2][0] = S[2];

    M[0][1] = U[0];
    M[1][1] = U[1];
    M[2][1] = U[2];

    M[0][2] = -F[0];
    M[1][2] = -F[1];
    M[2][2] = -F[2];

    // finally, we have view matrix = M * T
    ViewMat = M * T;
}

// Projection Matrix Related -------------------------------------------------------------------------
void swPerspective(float fovY, float aspect, float near, float far){
    // behind the scene, we are mapping https://registry.khronos.org/OpenGL-Refpages/gl2.1/
    // to this https://registry.khronos.org/OpenGL-Refpages/gl2.1/
    // in short, we want to find a matrix P that transform the space in the camera to a cube with length of 2
    // and P is:
    // f/aspect  0  0                      0
    // 0         f  0                      0
    // 0         0  (near+far)/(near-far)  (2*near*far)/(near-far)
    // 0         0  -1                     0
    // where f is cot(fovY/2)

    fovY = fovY * PI / 180.0f;
    float f = 1 / tan(fovY / 2);

    mat4x4 P(1);

    P[0][0] = f / aspect;
    P[1][1] = f;
    P[2][2] = (near + far) / (near - far);
    P[3][2] = (2 * near * far) / (near - far);
    P[2][3] = -1;
    P[3][3] = 0;

    ProjectionMat = P;
}

void swTriangle(vec3 color, vec3 in_v1, vec3 in_v2, vec3 in_v3, mat4x4 Modelmatrix)
{
	vec4 v1(in_v1.x, in_v1.y, in_v1.z, 1);
	vec4 v2(in_v2.x, in_v2.y, in_v2.z, 1);
	vec4 v3(in_v3.x, in_v3.y, in_v3.z, 1);

	// step1: model matrix only
	// step2: remove glLookAt, compute view matrix
	// step3: remove glProjection, compute project matrix
    v1 = ProjectionMat * ViewMat * Modelmatrix * v1;
    v1 /= v1[3];
    v2 = ProjectionMat * ViewMat * Modelmatrix * v2;
    v2 /= v2[3];
    v3 = ProjectionMat * ViewMat * Modelmatrix * v3;
    v3 /= v3[3];

	// prespective division
	// ...

	glColor3f(color.r, color.g, color.b);
	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);
}

// functions to draw-----------------------------------------------------------------------------------------------------
void Draw_Tetrahedron() {
	vec3 color(1, 1, 0);
	//glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
		swTriangle(vec3(1, 0, 0), tetrahedron_verts[0], tetrahedron_verts[1], tetrahedron_verts[2], TransformMat);
		swTriangle(vec3(0, 0, 1), tetrahedron_verts[3], tetrahedron_verts[0], tetrahedron_verts[1], TransformMat);
		swTriangle(vec3(0, 1, 0), tetrahedron_verts[2], tetrahedron_verts[3], tetrahedron_verts[0], TransformMat);
		swTriangle(vec3(1, 1, 0), tetrahedron_verts[1], tetrahedron_verts[2], tetrahedron_verts[3], TransformMat);
	glEnd();
}

void Draw_cube(float x, float y, float z, float length) {
    float half = length / 2.0f;

    glBegin(GL_QUADS);
        // Front face
        glColor3f(1.0, 0.0, 0.0); // Red
        Draw_glVertex3f(x - half, y - half, z + half, true, true, true);
        Draw_glVertex3f(x + half, y - half, z + half, true, true, true);
        Draw_glVertex3f(x + half, y + half, z + half, true, true, true);
        Draw_glVertex3f(x - half, y + half, z + half, true, true, true);

        // Back face
        glColor3f(0.0, 1.0, 0.0); // Green
        Draw_glVertex3f(x - half, y - half, z - half, true, true, true);
        Draw_glVertex3f(x + half, y - half, z - half, true, true, true);
        Draw_glVertex3f(x + half, y + half, z - half, true, true, true);
        Draw_glVertex3f(x - half, y + half, z - half, true, true, true);

        // Left face
        glColor3f(0.0, 0.0, 1.0); // Blue
        Draw_glVertex3f(x - half, y - half, z - half, true, true, true);
        Draw_glVertex3f(x - half, y - half, z + half, true, true, true);
        Draw_glVertex3f(x - half, y + half, z + half, true, true, true);
        Draw_glVertex3f(x - half, y + half, z - half, true, true, true);

        // Right face
        glColor3f(1.0, 1.0, 0.0); // Yellow
        Draw_glVertex3f(x + half, y - half, z - half, true, true, true);
        Draw_glVertex3f(x + half, y - half, z + half, true, true, true);
        Draw_glVertex3f(x + half, y + half, z + half, true, true, true);
        Draw_glVertex3f(x + half, y + half, z - half, true, true, true);

        // Top face
        glColor3f(1.0, 0.0, 1.0); // Magenta
        Draw_glVertex3f(x - half, y + half, z - half, true, true, true);
        Draw_glVertex3f(x + half, y + half, z - half, true, true, true);
        Draw_glVertex3f(x + half, y + half, z + half, true, true, true);
        Draw_glVertex3f(x - half, y + half, z + half, true, true, true);

        // Bottom face
        glColor3f(0.0, 1.0, 1.0); // Cyan
        Draw_glVertex3f(x - half, y - half, z - half, true, true, true);
        Draw_glVertex3f(x + half, y - half, z - half, true, true, true);
        Draw_glVertex3f(x + half, y - half, z + half, true, true, true);
        Draw_glVertex3f(x - half, y - half, z + half, true, true, true);
    glEnd();
}

void DrawSphere(float x, float y, float z, float radius, int slices, int stacks) {
    // for (int i = 0; i <= stacks; ++i) {
    //     float lat0 = PI * (-0.5 + (float)(i - 1) / stacks);
    //     float z0 = sin(lat0);
    //     float zr0 = cos(lat0);

    //     float lat1 = PI * (-0.5 + (float)i / stacks);
    //     float z1 = sin(lat1);
    //     float zr1 = cos(lat1);

    //     glBegin(GL_QUAD_STRIP);
    //         glColor3f(0.0, 0.5, 1.0);

    //         for (int j = 0; j <= slices; ++j) {
    //             float lng = 2 * PI * (float)(j - 1) / slices;
    //             float x0 = cos(lng);
    //             float y0 = sin(lng);

    //             glVertex3f(x + radius * x0 * zr0, 
    //                     y + radius * y0 * zr0, 
    //                     z + radius * z0);

    //             glVertex3f(x + radius * x0 * zr1, 
    //                     y + radius * y0 * zr1, 
    //                     z + radius * z1);
    //         }
    //     glEnd();
    // }

    for (int i = 0; i <= stacks; ++i) {
        float phi1 = PI * i / stacks;
        float phi2 = PI * (i + 1) / stacks;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float theta = 2 * PI * j / slices;

            float x1 = sin(phi1) * cos(theta);
            float y1 = sin(phi1) * sin(theta);
            float z1 = cos(phi1);

            float x2 = sin(phi2) * cos(theta);
            float y2 = sin(phi2) * sin(theta);
            float z2 = cos(phi2);

            glVertex3f(x + radius * x1, y + radius * y1, z + radius * z1);
            glVertex3f(x + radius * x2, y + radius * y2, z + radius * z2);
        }
        glEnd();
    }
}

void DrawGrid(int size = 10)
{
    vec4 v;

	glBegin(GL_LINES);
        glColor3f(0.3, 0.3, 0.3);
        for (int i = 1; i < size; i++) {
            Draw_glVertex3f(i, -size, 0, false, true, true);
            Draw_glVertex3f(i, size, 0, false, true, true);
            Draw_glVertex3f(-i, -size, 0, false, true, true);
            Draw_glVertex3f(-i, size, 0, false, true, true);
            Draw_glVertex3f(-size, i, 0, false, true, true);
            Draw_glVertex3f(size, i, 0, false, true, true);
            Draw_glVertex3f(-size, -i, 0, false, true, true);
            Draw_glVertex3f(size, -i, 0, false, true, true);
        }
	glEnd();

	glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        Draw_glVertex3f(0, 0, 0, false, true, true);
        Draw_glVertex3f(size, 0, 0, false, true, true);

        glColor3f(0.4, 0, 0);
        Draw_glVertex3f(0, 0, 0, false, true, true);
        Draw_glVertex3f(-size, 0, 0, false, true, true);

        glColor3f(0, 1, 0);
        Draw_glVertex3f(0, 0, 0, false, true, true);
        Draw_glVertex3f(0, size, 0, false, true, true);

        glColor3f(0, 0.4, 0);
        Draw_glVertex3f(0, 0, 0, false, true, true);
        Draw_glVertex3f(0, -size, 0, false, true, true);

        glColor3f(0, 0, 1);
        Draw_glVertex3f(0, 0, 0, false, true, true);
        Draw_glVertex3f(0, 0, size, false, true, true);
	glEnd();
}

void Display(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(USE_CUSTOM_MATRIX == false){
        // reset custom matrixes for DrawGrid function
        // since I'm lazy to write 2 version of glVertex3f()
        ViewMat = mat4x4(1);
        ProjectionMat = mat4x4(1);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 1, 0.1, 50);
    
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(10 * cos(theta), -10 * sin(theta), 10, 0, 0, 0, 0, 0, 1);
    
        DrawGrid();
    }

	//step 3: PROJECTION
	if (STEP3 == true) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0, winWidth, 0, winHeight, -2.0, 2.0);
		swPerspective(60, 1, 0.1, 50);
	} 

	//step 2: viewing 
	if (STEP2 == true) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
        ViewMat = mat4x4(1);
		swLookAt(10 * cos(theta), -10 * sin(theta), 10, 0, 0, 0, 0, 0, 1);
	}

    if(USE_CUSTOM_MATRIX == true){
        if(STEP3 == false){
            // didnt use custom project matrix
            // reset custom matrixes for DrawGrid function, since I'm lazy to write 2 version of glVertex3f()
            ProjectionMat = mat4x4(1);
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60, 1, 0.1, 50);
        }

        DrawGrid();
    }

	Draw_Tetrahedron();
    if(DRAW_CUBE){
        Draw_cube(1, 1, 5, 2);
    }

	glFlush();
	glfwSwapBuffers(window);
}

void init() {
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

// Converted special key function for GLFW.
void SpecialKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Process only key press and repeated actions.
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;
    
    switch (key) {
        case GLFW_KEY_F1:
            glfwSetWindowTitle(window, "F1: add a tetrahedron");
            for (int i = 0; i < 4; i++) {
                tetrahedron_verts[i][0] = default_tetrahedron_vertices[i][0];
                tetrahedron_verts[i][1] = default_tetrahedron_vertices[i][1];
                tetrahedron_verts[i][2] = default_tetrahedron_vertices[i][2];
            }
            break;
            
        case GLFW_KEY_F2:
            glfwSetWindowTitle(window, "F2: add a cube");
            DRAW_CUBE = true;
            break;
            
        case GLFW_KEY_F5:
            glfwSetWindowTitle(window, "F5: SAVE");
            // Add save functionality here.

            break;
            
        case GLFW_KEY_F6:
            glfwSetWindowTitle(window, "F6: LOAD");
            // Add load functionality here.

            break;

        case GLFW_KEY_F7:
            glfwSetWindowTitle(window, "F7: delete all object");
            DRAW_CUBE = false;
            for (int i = 0; i < 4; i++) {
                tetrahedron_verts[i][0] = 0;
                tetrahedron_verts[i][1] = 0;
                tetrahedron_verts[i][2] = 0;
            }
            break;
            
        default:
            break;
    }
}


void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Here you can handle both regular and special keys.
    // Call your special key function for function keys.
    SpecialKey(window, key, scancode, action, mods);
    
    // Add handling for other keys as needed.

    // Only handle press and repeat events.
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;

    switch (key) {
        case GLFW_KEY_ESCAPE:  // ESC key
            exit(0);
            break;

        // rotate world
        case GLFW_KEY_9:
            glfwSetWindowTitle(window, "rotate camera +");
            theta += PI / 90.0f;
            break;
        case GLFW_KEY_0:
            glfwSetWindowTitle(window, "rotate camera -");
            theta -= PI / 90.0f;
            break;
        // Reset
        case GLFW_KEY_MINUS:
            glfwSetWindowTitle(window, "reset position");
            TransformMat = mat4x4(1);
            break;

        // translate +x (handles both 'q' and 'Q')
        case GLFW_KEY_Q:
            glfwSetWindowTitle(window, "translate +x");
            TransformMat = swTranslate(1, 0, 0) * TransformMat;
            break;

        // translate -x (handles both 'a' and 'A')
        case GLFW_KEY_A:
            glfwSetWindowTitle(window, "translate -x");
            TransformMat = swTranslate(-1, 0, 0) * TransformMat;
            break;

        // translate +y (handles both 'w' and 'W')
        case GLFW_KEY_W:
            glfwSetWindowTitle(window, "translate +y");
            TransformMat = swTranslate(0, 1, 0) * TransformMat;
            break;

        // translate -y (handles both 's' and 'S')
        case GLFW_KEY_S:
            glfwSetWindowTitle(window, "translate -y");
            TransformMat = swTranslate(0, -1, 0) * TransformMat;
            break;

        // translate +z (handles both 'e' and 'E')
        case GLFW_KEY_E:
            glfwSetWindowTitle(window, "translate +z");
            TransformMat = swTranslate(0, 0, 1) * TransformMat;
            break;

        // translate +z (handles both 'd' and 'D')
        case GLFW_KEY_D:
            glfwSetWindowTitle(window, "translate -z");
            TransformMat = swTranslate(0, 0, -1) * TransformMat;
            break;

        // rotate +x
        case GLFW_KEY_R:
            glfwSetWindowTitle(window, "rotate +x");
            TransformMat = swRotateX(theta) * TransformMat;
            break;

        // rotate -x
        case GLFW_KEY_F:
            glfwSetWindowTitle(window, "rotate -x");
            TransformMat = swRotateX(-theta) * TransformMat;
            break;

        // rotate +y
        case GLFW_KEY_T:
            glfwSetWindowTitle(window, "rotate +y");
            TransformMat = swRotateY(theta) * TransformMat;
            break;

        // rotate -y
        case GLFW_KEY_G:
            glfwSetWindowTitle(window, "rotate -y");
            TransformMat = swRotateY(-theta) * TransformMat;
            break;

        // rotate +z
        case GLFW_KEY_Y:
            glfwSetWindowTitle(window, "rotate +z");
            TransformMat = swRotateZ(theta) * TransformMat;
            break;

        // rotate -z
        case GLFW_KEY_H:
            glfwSetWindowTitle(window, "rotate -z");
            TransformMat = swRotateZ(-theta) * TransformMat;
            break;

        // Add other keys as needed.
        default:
            break;
    }
}


int main(void)
{
    // Initialize GLFW
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "trans: Press F1 to add a tetrahedron", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set callback for keyboard events
    glfwSetKeyCallback(window, KeyCallback);

    // Initialize OpenGL
    init();

    // Timing for periodic updates (~33ms interval)
    double previousTime = glfwGetTime();
    const double interval = 0.033; // ~33ms

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Check if it's time to update (simulate timer)
        double currentTime = glfwGetTime();
        if (currentTime - previousTime >= interval) {
            // Here you can include any periodic update logic.
            // In GLUT you used glutPostRedisplay(), but in GLFW,
            // since you're in control of the loop, just call Display().
            previousTime = currentTime;
        }

        // Render here
        Display(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}