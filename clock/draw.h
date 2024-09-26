#ifndef __DRAW_H__
#define __DRAW_H__
#include <cmath>
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#define PI 3.14159265

typedef struct
{
    int r, g, b;

} Color3I;

typedef struct
{
    float r, g, b;

} Color3F;


Color3F ColorI2F(Color3I color3i);
void set_pen_color(Color3I color3i);
void set_clear_color(Color3I color3i);
void set_pixel(float x, float y);
void draw_line(float x0, float y0, float xEnd, float yEnd);
void draw_circle(int xc, int yc, int radius);
void RenderString(float x, float y, const unsigned char *str, Color3I color);

#endif