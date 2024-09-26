#include "draw.h"



Color3F ColorI2F(Color3I color3i){
    Color3F color3f;
    color3f.r = color3i.r/255.0;
    color3f.g = color3i.g/255.0;
    color3f.b = color3i.b/255.0;
    return color3f;
}

void set_pen_color(Color3I color3i){
    glColor3f(color3i.r/255.0, color3i.g/255.0, color3i.b/255.0);
}

void set_clear_color(Color3I color3i){
    glClearColor(color3i.r/255.0, color3i.g/255.0, color3i.b/255.0, 1.0);
}

void set_pixel(float x, float y) {
    // set a pixel as (x, y)
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void draw_line(float x0, float y0, float xEnd, float yEnd) {
    // draw a line from (x0, y0) to (xEnd, yEnd)
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(xEnd, yEnd);
    glEnd();

}

void draw_circle(int xc, int yc, int radius) {
    // draw a circle
    int steps = radius * 2 * PI;
    for (int i = 0; i < steps; i++) {
        float angle = i * 2 * PI / steps;
        float x = xc + radius * cos(angle);
        float y = yc + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}

void RenderString(float x, float y, const unsigned char *str, Color3I color)
{
    // Render string at (x, y)
    glColor3ub(color.r, color.g, color.b);
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
}