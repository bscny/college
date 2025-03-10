#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLFWwindow* window;
int PMAX = 100;

void myinit()
{
    /* attributes */
    glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
    glColor3f(1.0, 0.0, 0.0); /* draw in red */

    /* set up viewing */
    /* 500 x 500 window with origin lower left */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 50.0, 0.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}


void display(void)
{
    GLfloat vertices[3][2] = { {0.0, 0.0}, {25.0, 50.0}, {50.0, 0.0} }; /* A triangle */

    int j, k;
    rand();       /* standard random number generator */
    GLfloat p[2] = { 7.5, 5.0 };  /* An arbitrary initial point inside traingle */

    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

    /* compute and plots 5000 new points */
    glBegin(GL_POINTS);
    for (k = 0; k < 5000; k++)
    {
        j = rand() % 3; /* pick a vertex at random */


        /* Compute point halfway between selected vertex and old point */
        p[0] = (p[0] + vertices[j][0]) / 2.0;
        p[1] = (p[1] + vertices[j][1]) / 2.0;

        /* plot new point */
        glVertex2fv(p);

    }
    glEnd();

    glfwSwapBuffers(window);
}

int main(void)
{
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