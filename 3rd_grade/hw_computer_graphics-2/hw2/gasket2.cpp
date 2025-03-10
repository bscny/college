#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLFWwindow* window;

/* initial triangle */
GLfloat v[3][2] = { {-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15} };

int n = 5;

/* specify one triangle */
void triangle(GLfloat* a, GLfloat* b, GLfloat* c)
{
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m)
{

    /* triangle subdivision using vertex numbers */
    GLfloat v0[2], v1[2], v2[2];
    int j;
    if (m > 0)
    {
        for (j = 0; j < 2; j++) v0[j] = (a[j] + b[j]) / 2;
        for (j = 0; j < 2; j++) v1[j] = (a[j] + c[j]) / 2;
        for (j = 0; j < 2; j++) v2[j] = (b[j] + c[j]) / 2;
        divide_triangle(a, v0, v1, m - 1);
        divide_triangle(c, v1, v2, m - 1);
        divide_triangle(b, v2, v0, m - 1);
    }
    else triangle(a, b, c); /* draw triangle at end of recursion */
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    divide_triangle(v[0], v[1], v[2], n);
    glEnd();

    glfwSwapBuffers(window);
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
}


int main(int argc, char** argv)
{
    /* or set number of subdivision steps here */
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Sierpinski Gasket", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    }

    myinit();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        display();

        /* Poll for and process events */
        //glfwPollEvents();
        glfwWaitEvents();
    }

    glfwTerminate();
    return 0;
}