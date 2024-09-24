//
// Created by 20722 on 2024/9/22.
//
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include <fstream>
#include <cmath>
#include <ctime>
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#define PI 3.14159265
#define  winWidth  400
#define  winHeight  400
#define clock_radius 190

int hour, minute, second;
bool is_am = true;
int xc = winWidth / 2, yc = winHeight / 2;
unsigned char clock_num[12][4] = {"6", "5", "4", "3", "2", "1", "12", "11", "10", "9", "8", "7"};
using namespace std;

void set_pixel(int x, int y) {
    // set a pixel as (x, y)
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int x0, int y0, int xEnd, int yEnd) {
    // draw a line from (x0, y0) to (xEnd, yEnd)
    const int dx = abs(xEnd - x0);
    const int sx = x0 < xEnd ? 1 : -1;
    const int dy = abs(yEnd - y0);
    const int sy = y0 < yEnd ? 1 : -1;
    int e1 = (dx > dy ? dx : -dy) >> 1;

    while(set_pixel(x0,y0), x0 != xEnd || y0 != yEnd){
        int e2 = e1;
        if(e2 > -dx) { e1 -= dy; x0 += sx;}
        if(e2 <  dy) { e1 += dx; y0 += sy;}
    }
}

void SymPointPlot(int center_x0, int center_y0, int x, int y) {
    // plot (x, y) and other 7 symmetry pixels with respect to (center_x0, center_y0)
    set_pixel(center_x0 + x, center_y0 + y);
    set_pixel(center_x0 + x, center_y0 - y);
    set_pixel(center_x0 - x, center_y0 - y);
    set_pixel(center_x0 - x, center_y0 + y);
    set_pixel(center_x0 + y, center_y0 + x);
    set_pixel(center_x0 + y, center_y0 - x);
    set_pixel(center_x0 - y, center_y0 + x);
    set_pixel(center_x0 - y, center_y0 - x);
}

void draw_circle(int xc, int yc, int radius) {
    // draw a circle
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    SymPointPlot(xc, yc, x, y);
    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * x - 2 * y + 5;
            y--;
        }
        x++;
        SymPointPlot(xc, yc, x, y);
    }
}

void RenderString(float x, float y, const unsigned char *str)
{
    // Render string at (x, y)
    glColor3ub(255, 124, 62);
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
}




void reshape(int w, int h) {
    //callback when reshape
    glutReshapeWindow(winWidth, winHeight);
}



void clock_plate() {
    // draw clock plate
    if (is_am) glColor3f(0.0f, 0.0f, 0.0f);
    else glColor3f(1.0f, 1.0f, 1.0f);
    //set line width 6
    glPointSize(6.0f);
    set_pixel(xc, yc); // clock center
    //set line width 3
    glPointSize(2.0f);
    draw_circle(xc, yc, clock_radius + 1);
    draw_circle(xc, yc, clock_radius + 6);
    glPointSize(2.0f);
    int num1 = 12*5;
    for (int i=0; i< num1;i++) {
        draw_line(xc + clock_radius*sin(i*2*PI/num1),yc + clock_radius*cos(i*2*PI/num1),
            xc + (clock_radius - 5)*sin(i*2*PI/num1), yc +(clock_radius - 5)*cos(i*2*PI/num1));
    }

    glPointSize(3.0f);
    int num2 = 12;
    for (int i=0; i< num2;i++) {
        if (is_am) glColor3f(0.0f, 0.0f, 0.0f);
        else glColor3f(1.0f, 1.0f, 1.0f);
        draw_line(xc + clock_radius*sin(i*2*PI/num2),yc + clock_radius*cos(i*2*PI/num2),
    xc + (clock_radius - 10)*sin(i*2*PI/num2), yc +(clock_radius - 10)*cos(i*2*PI/num2));

        RenderString(xc + (clock_radius - 35)*sin(i*2*PI/num2) - 5, yc +(clock_radius - 35)*cos(i*2*PI/num2) + 5, clock_num[i]);
    }
}

void clock_hand(int h, int m, int s) {
    if (is_am) glColor3f(0.0f, 0.0f, 0.0f);
    else glColor3f(1.0f, 1.0f, 1.0f);
    // draw clock hand
    h = h % 12;
    // hours
    glPointSize(4.0f);
    // glColor3f(1.0f, 1.0f, 1.0f);
    draw_line(xc, yc, xc + 0.4*clock_radius*sin(PI-h*PI/6 - m*PI/360),
                            yc + 0.4*clock_radius*cos(PI-h*PI/6 - m*PI/360));
    // minutes
    glPointSize(2.0f);
    // glColor3f(1.0f, 1.0f, 1.0f);
    draw_line(xc, yc, xc + 0.8*clock_radius*sin(PI-m*2*PI/60),
                            yc + 0.8*clock_radius*cos(PI-m*2*PI/60));
    // seconds
    glPointSize(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    draw_line(xc, yc, yc + clock_radius*sin(PI-s*2*PI/60),
                                yc + clock_radius*cos(PI-s*2*PI/60));
}

void get_time() {
    // get local time
    time_t t = time(nullptr);
    struct tm timeinfo{};
    localtime_s(&timeinfo, &t);
    second = timeinfo.tm_sec;
    minute = timeinfo.tm_min;
    hour = timeinfo.tm_hour;
    if (hour >= 12) is_am = false;
}

void timer_core(int id) {
    second = (second + 1) % 60;
    minute = (minute + (second == 0)) % 60;
    hour = (hour + ((minute == 0) && (second == 0))) % 24;
    if (hour >= 12) is_am = false;
    // printf("%d:%d:%d\n", hour, minute, second);
    if (second == 0) get_time(); //automatically set every minute
    glutPostRedisplay(); // refresh windows
    glutTimerFunc(1000, timer_core, id);
}

void display() {
    if (is_am) glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    else glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    clock_plate();
    clock_hand(hour, minute, second);
    glutSwapBuffers();
}

void init()
{
    if (is_am) glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    else glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winWidth, winHeight,0);
    glViewport(0, 0, winWidth, winHeight);

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE  | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("Clock");
    // get local time
    get_time();
    init();
    // display callback
    glutDisplayFunc(display);
    // timer
    glutTimerFunc(1000, timer_core, 0);
    // reshape callback
    glutReshapeFunc(reshape);
    glutMainLoop();
}
