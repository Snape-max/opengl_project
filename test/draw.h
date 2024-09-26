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


class DrawTools {
    public:
        void set_pen_color(Color3I color3i);
        void set_pen_width(float width);
        void set_clear_color(Color3I color3i);
        void set_pixel(float x, float y);
        void draw_line(float x1, float y1, float x2, float y2);
        void draw_circle(float xc, float yc, float radius, int mode);
        void fill_circle(float xc, float yc, float radius, Color3I color);
        void RenderString(float x, float y, const unsigned char *str, Color3I color);
        void enable_smoothing();
    private:
        Color3I pen_color;
        float pen_width;
};

#endif