#include "swgl.h"

#include <cmath>

#include <GL/glu.h>
#include <GLFW/glfw3.h>

//OpenGL Mathematics (GLM)  https://glm.g-truc.net/
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

using namespace glm;

GLdouble CTM_MV[16];	//Current Transformation Matrix: ModelView
GLdouble CTM_P[16];		//Current Transformation Matrix: Projection
GLdouble *CTM;			//Pointer to Current Transformation Matrix

const float PI = 3.14159265359;

mat4x4 TransformMat = mat4x4(1);
mat4x4 ViewMat = mat4x4(1);
mat4x4 ProjectionMat = mat4x4(1);

bool swTransformation(const GLdouble h[4], GLdouble w[4])
{
	//p = CTM_P*CTM_MV*h


	//prespective division


	//viewport transformation



	return true;
}

void swTranslated(GLdouble x, GLdouble y, GLdouble z)
{
	mat4x4 Translate = mat4x4(1);
	Translate[3][0] = x;
    Translate[3][1] = y;
    Translate[3][2] = z;

	TransformMat = Translate * TransformMat;
}

void swRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
    // normalize the given Vector first
    GLdouble k = pow(x, 2) + pow(y, 2) + pow(z, 2);
    k = sqrt(k);
    x /= k;
    y /= k;
    z /= k;

    // get cos and sin for given Theta
    GLdouble s = sin(angle);
    GLdouble c = cos(angle);

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

	TransformMat = Rotate * TransformMat;
}

void swScaled(GLdouble x, GLdouble y, GLdouble z)
{
	mat4x4 Scale = mat4x4(1);

    Scale[0][0] = x;
    Scale[1][1] = y;
    Scale[2][2] = z;

	TransformMat = Scale * TransformMat;
}

// View Matrix Related ------------------------------------------------------------------------
void swuLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
               GLdouble centerX, GLdouble centerY, GLdouble centerZ,
               GLdouble upX, GLdouble upY, GLdouble upZ)
{
    
    // firstly, get F which is camera --> at
    GLdouble F[3] = {centerX - eyeX, centerY - eyeY, centerZ - eyeZ};
    
    // normalize F
    GLdouble k = pow(F[0], 2) + pow(F[1], 2) + pow(F[2], 2);
    k = sqrt(k);
    F[0] /= k;
    F[1] /= k;
    F[2] /= k;

    // get F cross up, S
    GLdouble S[3] = {
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
    GLdouble U[3] = {
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

    // map the world space to camera space:
    // S[0]   S[1]   S[2]
    // U[0]   U[1]   U[2]
    // -F[0]  -F[1]  -F[2]
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
void swuPerspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar){
    // behind the scene, we are mapping https://registry.khronos.org/OpenGL-Refpages/gl2.1/
    // to this https://registry.khronos.org/OpenGL-Refpages/gl2.1/
    // in short, we want to find a matrix P that transform the space in the camera to a cube with length of 2
    // and P is:
    // f/aspect  0  0                      0
    // 0         f  0                      0
    // 0         0  (zNear+zFar)/(zNear-zFar)  (2*zNear*zFar)/(zNear-zFar)
    // 0         0  -1                     0
    // where f is cot(fovY/2)

    fovY = fovY * PI / 180.0f;
    GLdouble f = 1 / tan(fovY / 2);

    mat4x4 P(1);

    P[0][0] = f / aspect;
    P[1][1] = f;
    P[2][2] = (zNear + zFar) / (zNear - zFar);
    P[3][2] = (2 * zNear * zFar) / (zNear - zFar);
    P[2][3] = -1;
    P[3][3] = 0;

    ProjectionMat = P;
}

void swOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar){
    // https://registry.khronos.org/OpenGL-Refpages/gl2.1/
    // in short we want to map this rectangle to a cube with length of 2 at (0, 0, 0)
    // therefore, the P looks like this:
    // 2/(right - left)  0                 0                  -(right + left)/(right - left)
    // 0                 2/(top - bottom)  0                  -(top + bottom)/(top - bottom)
    // 0                 0                 -2/(zFar - zNear)  -(zFar + zNear)/(zFar - zNear)
    // 0                 0                 0                  1

    mat4x4 P(1);

    P[0][0] = 2 / (right - left);
    P[3][0] = -(right + left) / (right - left);
    P[1][1] = 2 / (top - bottom);
    P[3][1] = -(top + bottom) / (top - bottom);
    P[2][2] = -2 / (zFar - zNear);
    P[3][2] = -(zFar + zNear) / (zFar - zNear);
    P[3][3] = 1;

    ProjectionMat = P;
}