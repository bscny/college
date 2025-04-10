//Computer Graphics 2025 HW swgl-rast simple version
//NCCU CS
//Line and Triangle rasterization, zbuffer

#include <GL/glew.h>
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//OpenGL Mathematics (GLM)  https://glm.g-truc.net/
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "swgl.h"
#include <iostream>

using namespace glm;
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool RANDOM_MODE = true;
bool RANDOM_Z = true;

bool USE_DEFAULT_LOOK_AT = true;
GLdouble FLAG = -1;

int SEED = 6;

int         winWidth=800, winHeight=400;

float       angle = 0.0, axis[3], trans[3];
bool        trackingMouse = false;
bool        redrawContinue = false;
bool        trackballMove = false;
GLdouble    TRACKM[16]={1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

GLdouble    DEBUG_M[16];

GLdouble    Angle1=0, Angle2=0;
GLint       TICK=0;

int         NUM_LINES = 20;
int         NUM_TRIS = 5;

/*----------------------------------------------------------------------*/
/*
** Draw the wire-frame cube.
*/
/* GLfloat vertices[][3] = {
    {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0}, {1.0,1.0,-1.0}, {-1.0,1.0,-1.0},
    {-1.0,-1.0,1.0}, {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}
};

GLfloat colors[][3] = {
    {0.0,0.0,0.0},{1.0,0.0,0.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0},
    {0.0,0.0,1.0}, {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}
}; */


void SwglTri1(GLdouble x1, GLdouble y1, GLdouble z1,
			 GLdouble x2, GLdouble y2, GLdouble z2,
			 GLdouble x3, GLdouble y3, GLdouble z3)
{
	//copy to homogenous coordinate
	GLdouble h1[4]={x1, y1, z1, 1.0};
	GLdouble h2[4]={x2, y2, z2, 1.0};
	GLdouble h3[4]={x3, y3, z3, 1.0};

	//implement the opengl pipeline here
	//swTransformation(h1, w1);
	//swTransformation(h2, w2);
	//swTransformation(h3, w3);

	//window coordinate
	GLdouble w1[4]={x1, y1, z1, 1.0}; 
	GLdouble w2[4]={x2, y2, z2, 1.0};
	GLdouble w3[4]={x3, y3, z3, 1.0};

    //get current color
    GLdouble col[4];
    glGetDoublev(GL_CURRENT_COLOR, col);

    swTriangle(w1[0], w1[1], w1[2],
               w2[0], w2[1], w2[2],
               w3[0], w3[1], w3[2],
               col[0], col[1], col[2]);

}


void SwglLine1(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2)
{
	//copy to homogenous coordinate
	GLdouble h1[4]={x1, y1, z1, 1.0};
	GLdouble h2[4]={x2, y2, z2, 1.0};

	GLdouble w1[4]={x1, y1, z1, 1.0}; //window coordinate
	GLdouble w2[4]={x2, y2, z2, 1.0};

	//implement
	GLdouble col[4];
	glGetDoublev(GL_CURRENT_COLOR, col);
	BresenhamLine(w1[0], w1[1], w1[2], w2[0], w2[1], w2[2], col[0], col[1], col[2]);
}


void OpenglLine(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2)
{
	glBegin(GL_LINES);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y2, z2);
	glEnd();
}

/* void OpenglLine(int index1, int index2)
{
	OpenglLine(vertices[index1][0], vertices[index1][1], vertices[index1][2],
		       vertices[index2][0], vertices[index2][1], vertices[index2][2]);
} */


void openglPath1(void)
{
    //view transform
	glViewport(0, 0, winWidth/2, winHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if(USE_DEFAULT_LOOK_AT){
		glOrtho(0, winWidth/2, 0, winHeight, -100, 100);
	}else{
		glOrtho(-winWidth/2, 0, 0, winHeight, -100, 100);
	}
	glGetDoublev(GL_PROJECTION_MATRIX, DEBUG_M);


    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(USE_DEFAULT_LOOK_AT){
		// gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	}else{
		// look at +z
		gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);
	}
	glGetDoublev(GL_MODELVIEW_MATRIX, DEBUG_M);

	// Line
	for(int i=0; i<NUM_LINES; i++) {
	    float x1 = float(rand())/RAND_MAX*winWidth/2;
	    float y1 = float(rand())/RAND_MAX*winHeight/2;

	    float x2 = float(rand())/RAND_MAX*winWidth/2;
	    float y2 = float(rand())/RAND_MAX*winHeight/2;

        glColor3f(float(rand())/RAND_MAX, float(rand())/RAND_MAX, float(rand())/RAND_MAX);
        OpenglLine(x1, y1, 0, x2, y2, 0);
	}

	// triangle
	glBegin(GL_TRIANGLES);
	for(int i=0; i<NUM_TRIS; i++) {
	    float x1 = float(rand())/RAND_MAX*winWidth/2;
	    float y1 = float(rand())/RAND_MAX*winHeight/2+winHeight/2;

	    float x2 = float(rand())/RAND_MAX*winWidth/2;
	    float y2 = float(rand())/RAND_MAX*winHeight/2+winHeight/2;

	    float x3 = float(rand())/RAND_MAX*winWidth/2;
	    float y3 = float(rand())/RAND_MAX*winHeight/2+winHeight/2;

		float z;

		if(RANDOM_MODE){
			z = float(rand())/RAND_MAX;

			glColor3f(float(rand())/RAND_MAX, float(rand())/RAND_MAX, float(rand())/RAND_MAX);
		}else{
			z = float(i) / float(NUM_TRIS);

			if(i == 0){
				glColor3f(1, 0, 0);
			}else if(i == 1){
				glColor3f(0, 1, 0);
			}else{
				glColor3f(0, 0, 1);
			}
		}

		if(RANDOM_Z){
			float z1 = z;
			float z2 = float(rand())/RAND_MAX;
			float z3 = float(rand())/RAND_MAX;

			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
			glVertex3f(x3, y3, z3);
		}else{
			glVertex3f(x1, y1, z);
			glVertex3f(x2, y2, z);
			glVertex3f(x3, y3, z);
		}
	}

	glEnd();

}

void softPath1(void)
{
    //view transform
	glViewport(winWidth/2, 0, winWidth/2, winHeight);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	// ProjectionMat = mat4x4(1);
	if(USE_DEFAULT_LOOK_AT){
		glOrtho(0, winWidth/2, 0, winHeight, -100, 100);

		// swOrtho(0, winWidth/2, 0, winHeight, -100, 100);
	}else{
		glOrtho(-winWidth/2, 0, 0, winHeight, -100, 100);

		// swOrtho(-winWidth/2, 0, 0, winHeight, -100, 100);
	}

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// ViewMat = mat4x4(1);
	if(USE_DEFAULT_LOOK_AT){
		// gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

		// swuLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	}else{
		// look at +z
		gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);

		// swuLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);
	}

    swClearZbuffer();

	//Line
	for(int i=0; i<NUM_LINES; i++) {
	    float x1 = float(rand())/RAND_MAX*winWidth/2;
	    float y1 = float(rand())/RAND_MAX*winHeight/2;

	    float x2 = float(rand())/RAND_MAX*winWidth/2;
	    float y2 = float(rand())/RAND_MAX*winHeight/2;

        glColor3f(float(rand())/RAND_MAX, float(rand())/RAND_MAX, float(rand())/RAND_MAX);
		vec4 v1(x1, y1, 0, 1);
		vec4 v2(x2, y2, 0, 1);
		v1 = ProjectionMat * ViewMat * TransformMat * v1;
		v2 = ProjectionMat * ViewMat * TransformMat * v2;
        SwglLine1(v1[0], v1[1], v1[2], v2[0], v2[1], v2[2]);
	}

	//Triangle
	for(int i=0; i<NUM_TRIS; i++) {
	    float x1 = float(rand())/RAND_MAX*winWidth/2;
	    float y1 = float(rand())/RAND_MAX*winHeight/2+winHeight/2;

	    float x2 = float(rand())/RAND_MAX*winWidth/2;
	    float y2 = float(rand())/RAND_MAX*winHeight/2+winHeight/2;

	    float x3 = float(rand())/RAND_MAX*winWidth/2;
	    float y3 = float(rand())/RAND_MAX*winHeight/2+winHeight/2;

		float z;
		
        if(RANDOM_MODE){
			z = float(rand())/RAND_MAX;

			glColor3f(float(rand())/RAND_MAX, float(rand())/RAND_MAX, float(rand())/RAND_MAX);
		}else{
			z = float(i) / float(NUM_TRIS);

			if(i == 0){
				glColor3f(1, 0, 0);
			}else if(i == 1){
				glColor3f(0, 1, 0);
			}else{
				glColor3f(0, 0, 1);
			}
		}

		if(RANDOM_Z){
			float z1 = z;
			float z2 = float(rand())/RAND_MAX;
			float z3 = float(rand())/RAND_MAX;

			vec4 v1(x1, y1, z1, 1);
			vec4 v2(x2, y2, z2, 1);
			vec4 v3(x3, y3, z3, 1);
			v1 = ProjectionMat * ViewMat * TransformMat * v1;
			v2 = ProjectionMat * ViewMat * TransformMat * v2;
			v3 = ProjectionMat * ViewMat * TransformMat * v3;
			
			SwglTri1(v1[0], v1[1], FLAG * v1[2],
					 v2[0], v2[1], FLAG * v2[2],
					 v3[0], v3[1], FLAG * v3[2]);
		}else{
			vec4 v1(x1, y1, z, 1);
			vec4 v2(x2, y2, z, 1);
			vec4 v3(x3, y3, z, 1);
			v1 = ProjectionMat * ViewMat * TransformMat * v1;
			v2 = ProjectionMat * ViewMat * TransformMat * v2;
			v3 = ProjectionMat * ViewMat * TransformMat * v3;

			SwglTri1(v1[0], v1[1], FLAG * v1[2],
					 v2[0], v2[1], FLAG * v2[2],
					 v3[0], v3[1], FLAG * v3[2]);
		}
	}
}

/*----------------------------------------------------------------------*/
void display(void)
{
    time_t time1 = time(0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glDepthFunc(GL_LESS);
	glDepthRange(-1, 1);

	glViewport(0, 0, winWidth, winHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	// gluOrtho2D(0, winWidth, 0, winHeight);
	// glOrtho(0, winWidth, 0, winHeight, 100, -100);
	glMatrixMode(GL_MODELVIEW);


    if (trackballMove) {
		glPushMatrix();
			glLoadMatrixd(TRACKM);
			glRotatef(angle, axis[0], axis[1], axis[2]);
			glGetDoublev(GL_MODELVIEW_MATRIX, TRACKM);
		glPopMatrix();
	}

	if(RANDOM_MODE){
		srand(time1);
	}else{
		srand(SEED);
	}
	glEnable(GL_DEPTH_TEST);
	openglPath1();

	//we must disable the opengl's depth test, then the software depth test will work
	glDisable(GL_DEPTH_TEST);
	if(RANDOM_MODE){
		srand(time1);
	}else{
		srand(SEED);
	}
	softPath1();
	glEnable(GL_DEPTH_TEST);
}

/*----------------------------------------------------------------------*/
void window_size_callback(GLFWwindow* window, int w, int h)
{
    winWidth = w;
    winHeight = h;

	//rast - zbuffer
	swInitZbuffer(w/2, h);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE: //ESC
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
		}
	}
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winWidth, winHeight, "CG_HW-Rast(Left: OpenGL; Right: SoftwareGL)", NULL, NULL);
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
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	//initGL();
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	if(!RANDOM_MODE){
		NUM_TRIS = 3;
	}

	if(!USE_DEFAULT_LOOK_AT){
		FLAG = 1;
	}

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		display();

		glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
