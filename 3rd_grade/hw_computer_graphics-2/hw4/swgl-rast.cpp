#include "swgl.h"

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
        int temp = x1_ground;
        x1_ground = x2_ground;
        x2_ground = temp;

        temp = y1_ground;
        y1_ground = y2_ground;
        y2_ground = temp;
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
