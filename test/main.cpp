//
// Created by 20722 on 2024/9/22.
//
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include <fstream>
#include <cmath>
#include <ctime>
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include "draw.h"

using namespace std;

struct clock_color
{
    Color3I background;
    Color3I hand_s;
    Color3I hand_m2h;
    Color3I face;
    Color3I edge;
};

int winWidth = 600;
int winHeight = 600;
int clock_radius = winHeight * 0.45;
int hour, minute, second;
int xc = winWidth / 2, yc = winHeight / 2;
unsigned char clock_num[12][4] = {"6", "5", "4", "3", "2", "1", "12", "11", "10", "9", "8", "7"};

clock_color night_color, day_color; // color of the clock in night and day
clock_color color; // current color
bool day_flag = true;
DrawTools tool; // drawing tool

void init_color();
void reshape(int w, int h);
void clock_face();
void clock_hand(int h, int m, int s);
void get_time();
void timer_core(int id);
void display();
void change_theme(int button, int state, int x, int y);

void init_color(){
    day_color = {
        .background = {242, 247, 255},
        // .background = {244, 244, 244},
        .hand_s = {251, 159, 82},
        .hand_m2h = {57, 78, 106},
        .face = {255, 255, 255},
        .edge = {201, 206, 214}
    };
    night_color = {
        .background = {6, 8, 15},
        .hand_s = {218, 129, 56},
        .hand_m2h = {200, 203, 208},
        .face = {14, 23, 41},
        .edge = {70, 77, 91}
    };

    if (hour < 6 || hour > 18){
        color = night_color;
        day_flag = false;
    } else {
        color = day_color;
        day_flag = true;
    }

}


void reshape(int w, int h) {
    //callback when reshape
    winWidth = w;
    winHeight = h;
    xc = w / 2;
    yc = h / 2;
    clock_radius = min(winWidth, winHeight)*0.45;
    glLoadIdentity();
    gluOrtho2D(0, winWidth, winHeight,0);
    glViewport(0, 0, winWidth, winHeight);
}



void clock_face() {
    // draw clock plate
    //set line width 2
    tool.set_pen_width(2.0f);
    tool.set_pen_color(color.edge);
    tool.fill_circle(xc, yc, clock_radius + 1, color.face);
    tool.set_pen_width(2.0f);
    tool.set_pen_color(color.edge);
    int num1 = 12*5;
    for (int i=0; i< num1;i++) {
        tool.draw_line(xc + clock_radius*sin(i*2*PI/num1),yc + clock_radius*cos(i*2*PI/num1),
            xc + (clock_radius - 5)*sin(i*2*PI/num1), yc +(clock_radius - 5)*cos(i*2*PI/num1));
    }

    tool.set_pen_width(4.0f);
    int num2 = 12;
    for (int i=0; i< num2;i++) {
        tool.set_pen_color(color.edge);
        tool.draw_line(xc + clock_radius*sin(i*2*PI/num2),yc + clock_radius*cos(i*2*PI/num2),
    xc + (clock_radius - 10)*sin(i*2*PI/num2), yc +(clock_radius - 10)*cos(i*2*PI/num2));

        tool.RenderString(xc + (clock_radius - 35)*sin(i*2*PI/num2) - 5, yc +(clock_radius - 35)*cos(i*2*PI/num2) + 5, 
        clock_num[i], color.hand_m2h);
    }
}

void clock_hand(int h, int m, int s) {
    tool.set_pen_color(color.hand_m2h);
    // draw clock hand
    h = h % 12;
    // hours
    tool.set_pen_width(9.0f);
    tool.draw_line(xc, yc, xc + 0.4*clock_radius*sin(PI-h*PI/6 - m*PI/360),
                            yc + 0.4*clock_radius*cos(PI-h*PI/6 - m*PI/360));
    // minutes
    tool.draw_line(xc, yc, xc + 0.7*clock_radius*sin(PI-m*2*PI/60),
                            yc + 0.7*clock_radius*cos(PI-m*2*PI/60));
    // seconds
    tool.set_pen_width(3.0f);
    tool.set_pen_color(color.hand_s);
    tool.draw_line(xc, yc, xc + clock_radius*sin(PI-s*2*PI/60),
                                yc + clock_radius*cos(PI-s*2*PI/60));
    
    // center
    tool.set_pen_width(2.0f);
    tool.set_pen_color(color.face);
    tool.fill_circle(xc, yc, 8, color.hand_m2h);
}

void get_time() {
    // get local time
    time_t t = time(nullptr);
    struct tm timeinfo{};
    localtime_s(&timeinfo, &t);
    second = timeinfo.tm_sec;
    minute = timeinfo.tm_min;
    hour = timeinfo.tm_hour;
}

void timer_core(int id) {
    second = (second + 1) % 60;
    minute = (minute + (second == 0)) % 60;
    hour = (hour + ((minute == 0) && (second == 0))) % 24;
    // printf("%d:%d:%d\n", hour, minute, second);
    if (second == 0) get_time(); //automatically set every minute
    glutPostRedisplay(); // refresh windows
    glutTimerFunc(1000, timer_core, id);
}

void display() {
    tool.set_clear_color(color.background);
    glClear(GL_COLOR_BUFFER_BIT);
    clock_face();
    clock_hand(hour, minute, second);
    glutSwapBuffers();
}

void change_theme(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        day_flag = !day_flag;
    }
    if (day_flag) color = day_color;
    else color = night_color;
}

void init()
{
    // get local time
    get_time();
    // init color
    init_color();
    // opengl init
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winWidth, winHeight,0);
    glViewport(0, 0, winWidth, winHeight);

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH |GLUT_RGBA | GLUT_MULTISAMPLE); // antialiasing
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("Clock");
    init();
    // display callback
    glutDisplayFunc(display);
    // timer
    glutTimerFunc(1000, timer_core, 0);
    // mouse callback
    glutMouseFunc(change_theme);
    // reshape callback
    glutReshapeFunc(reshape);
    glutMainLoop();
}
