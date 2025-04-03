#include "swgl.h"
#include <iostream>

using namespace std;

float *swdepthbuffer = NULL;

//---------------------------------------------------------------------------
//cghw-rast
//---------------------------------------------------------------------------

//You can change it to speed up
void writepixel(int x, int y, GLdouble r, GLdouble g, GLdouble b)
{
	GLubyte map[1]={255};

	glColor3d(r, g, b);
	glRasterPos2i(x, y);
	glBitmap(1, 1, 0, 0, 0, 0, map);
}

bool BresenhamLine(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2, GLdouble r, GLdouble g, GLdouble b)
{
    writepixel(x1, y1, r, g, b);
    writepixel(x2, y2, r, g, b);

    int x1_ground;
    int y1_ground;
    int x2_ground;
    int y2_ground;

    // using reference https://zh.wikipedia.org/zh-tw/%E5%B8%83%E9%9B%B7%E6%A3%AE%E6%BC%A2%E5%A7%86%E7%9B%B4%E7%B7%9A%E6%BC%94%E7%AE%97%E6%B3%95
    // the optimal solution: all integer
    bool steep = abs(y2 - y1) > abs(x2 - x1);
    if(steep){
        // swap x and y since slope is grater than 1
        x1_ground = (int)y1;
        y1_ground = (int)x1;

        x2_ground = (int)y2;
        y2_ground = (int)x2;
    }else{
        x1_ground = (int)x1;
        y1_ground = (int)y1;
        x2_ground = (int)x2;
        y2_ground = (int)y2;
    }

    if(x1_ground > x2_ground){
        // swap x1 and x2 since we are going right to left
        swap(x1_ground, x2_ground);
        swap(y1_ground, y2_ground);
    }

    int dx = x2_ground - x1_ground;
    int dy = abs(y2_ground - y1_ground);
    int err = dx / 2;

    int ystep;
    if(y1_ground < y2_ground){
        ystep = 1;
    }else{
        ystep = -1;
    }
    int y = y1_ground;

    for(int x = x1_ground; x <= x2_ground; x ++){
        if(steep){
            writepixel(y, x, r, g, b);
        }else{
            writepixel(x, y, r, g, b);
        }

        err -= dy;
        if(err < 0){
            // it's time to increase(decrease) y value by 1
            y += ystep;
            err += dx;
        }
    }

	return true;
}

void fill_topflat_triangle(GLdouble x1, GLdouble y1, GLdouble z1,
                        GLdouble x2, GLdouble y2, GLdouble z2,
                        GLdouble x3, GLdouble y3, GLdouble z3,
                        GLdouble r, GLdouble g, GLdouble b)
{
    GLdouble inv_slopeX_3to1 = (x1 - x3) / (y1 - y3);
    GLdouble inv_slopeZ_3to1 = (z1 - z3) / (y1 - y3);
    GLdouble inv_slopeX_3to2 = (x2 - x3) / (y2 - y3);
    GLdouble inv_slopeZ_3to2 = (z2 - z3) / (y2 - y3);

    GLdouble x_3to1 = x3;
    GLdouble z_3to1 = z3;
    GLdouble x_3to2 = x3;
    GLdouble z_3to2 = z3;

    for(int y = (int)y3; y <= y2; y ++){
        BresenhamLine(x_3to1, y, z_3to1, x_3to2, y, z_3to2, r, g, b);
        x_3to1 += inv_slopeX_3to1;
        z_3to1 += inv_slopeZ_3to1;
        x_3to2 += inv_slopeX_3to2;
        z_3to2 += inv_slopeZ_3to2;
    }
}

void fill_bottomflat_triangle(GLdouble x1, GLdouble y1, GLdouble z1,
                        GLdouble x2, GLdouble y2, GLdouble z2,
                        GLdouble x3, GLdouble y3, GLdouble z3,
                        GLdouble r, GLdouble g, GLdouble b)
{
    GLdouble inv_slopeX_1to2 = (x2 - x1) / (y2 - y1);
    GLdouble inv_slopeZ_1to2 = (z2 - z1) / (y2 - y1);
    GLdouble inv_slopeX_1to3 = (x3 - x1) / (y3 - y1);
    GLdouble inv_slopeZ_1to3 = (z3 - z1) / (y3 - y1);

    GLdouble x_1to2 = x1;
    GLdouble z_1to2 = z1;
    GLdouble x_1to3 = x1;
    GLdouble z_1to3 = z1;

    for(int y = (int)y1; y >= y2; y --){
        BresenhamLine(x_1to2, y, z_1to2, x_1to3, y, z_1to3, r, g, b);
        x_1to2 -= inv_slopeX_1to2;
        z_1to2 -= inv_slopeZ_1to2;
        x_1to3 -= inv_slopeX_1to3;
        z_1to3 -= inv_slopeZ_1to3;
    }
}

bool swTriangle(GLdouble x1, GLdouble y1, GLdouble z1,
			 GLdouble x2, GLdouble y2, GLdouble z2,
			 GLdouble x3, GLdouble y3, GLdouble z3,
			 GLdouble r, GLdouble g, GLdouble b)
{
    writepixel(x1, y1, r, g, b);
    writepixel(x2, y2, r, g, b);
    writepixel(x3, y3, r, g, b);

    BresenhamLine(x1, y1, z1, x2, y2, z2, r, g, b);
    BresenhamLine(x2, y2, z2, x3, y3, z3, r, g, b);
    BresenhamLine(x3, y3, z3, x1, y1, z1, r, g, b);

    if((int)y3 == (int)y2 == (int)y1){
        // it's a line...
        return true;
    }

    // using the method https://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
    // sort the 3 vertices according to y (y1 >= y2 >= y3)
    // seperate the tringle to top & bottom 2 parts
    // scan line for the 2 triangles
    if((int)y3 > (int)y2){
        swap(x2, x3);
        swap(y2, y3);
        swap(z2, z3);
    }
    if((int)y3 > (int)y1){
        swap(x1, x3);
        swap(y1, y3);
        swap(z1, z3);
    }
    if((int)y2 > (int)y1){
        swap(x1, x2);
        swap(y1, y2);
        swap(z1, z2);
    }

    if((int)y2 == (int)y3){
        fill_bottomflat_triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, r, g, b);
    }else if((int)y1 == (int)y2){
        fill_topflat_triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, r, g, b);
    }else{
        // find the v4 that has the same y value as v2 and sits on line v1---v3
        GLdouble x4 = x1 + ((y2 - y1) / (y3 - y1)) * (x3 - x1);
        GLdouble y4 = y2;
        GLdouble z4 = z1 + ((y2 - y1) / (y3 - y1)) * (z3 - z1);
        fill_bottomflat_triangle(x1, y1, z1, x2, y2, z2, x4, y4, z4, r, g, b);
        fill_topflat_triangle(x4, y4, z4, x2, y2, z2, x3, y3, z3, r, g, b);
    }

	return true;
}


bool swInitZbuffer(int width, int height)
{
    //allocate/reallocate swdepthbuffer

    return true;
}



bool swClearZbuffer()
{

    return true;
}
