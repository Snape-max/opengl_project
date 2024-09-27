#include "draw.h"



Color3F ColorI2F(Color3I color3i){
    Color3F color3f;
    color3f.r = color3i.r/255.0;
    color3f.g = color3i.g/255.0;
    color3f.b = color3i.b/255.0;
    return color3f;
}

DrawTools::DrawTools() {
    pen_color = Color3I {0, 0, 0};
    pen_width = 2;
}




void DrawTools::set_pen_color(Color3I color3i){
    pen_color = color3i;
    glColor3f(color3i.r/255.0, color3i.g/255.0, color3i.b/255.0);
}

void DrawTools::set_pen_width(float width){
    pen_width = width;
    glLineWidth(width);
}

void DrawTools::set_clear_color(Color3I color3i){
    glClearColor(color3i.r/255.0, color3i.g/255.0, color3i.b/255.0, 1.0);
}

void DrawTools::set_pixel(float x, float y) {
    // set a pixel as (x, y)
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void DrawTools::draw_line(float x0, float y0, float xEnd, float yEnd) {
    // draw a line from (x0, y0) to (xEnd, yEnd)
    enable_smoothing();
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(xEnd, yEnd);
    glEnd();

}

void DrawTools::draw_circle(float xc, float yc, float radius, int mode) {
    // draw a circle
    int steps = radius * 2 * PI;
    glBegin(mode);
    for (int i = 0; i < steps; i++) {
        float angle = i * 2 * PI / steps;
        float x = xc + radius * cos(angle);
        float y = yc + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void DrawTools::fill_circle(float xc, float yc, float radius, Color3I color) {
    // fill a circle
    draw_circle(xc, yc, radius, GL_LINE_LOOP);
    set_pen_color(color);
    draw_circle(xc, yc, radius - pen_width/2, GL_POLYGON);
}


void DrawTools::draw_rect(float x, float y, float w, float h, int mode) {
    // draw a rectangle
    glBegin(mode);
    glVertex2f(x, y);
    glVertex2f(x, y + h);
    glVertex2f(x + w, y + h);
    glVertex2f(x + w, y);
    glEnd();
}

void DrawTools::fill_rect(float x, float y, float w, float h, Color3I color) {
    glColor3ub(pen_color.r, pen_color.g, pen_color.b);
    draw_rect(x, y, w, h, GL_LINE_LOOP);
    glColor3ub(color.r, color.g, color.b);
    draw_rect(x + pen_width /2, y + pen_width/2, w - pen_width /2, h - pen_width/2, GL_POLYGON);

}

void DrawTools::RenderString(float x, float y, const unsigned char *str, Color3I color)
{
    // Render string at (x, y)
    glColor3ub(color.r, color.g, color.b);
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
    // glutStrokeCharacter(GLUT_STROKE_ROMAN, str);
}

void DrawTools::enable_smoothing()
{
    // Enable smoothing and multi-sampling
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_MULTISAMPLE);
}