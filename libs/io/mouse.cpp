#include "../../include/io/mouse.h"

double Mouse::x = 0;
double Mouse::y = 0;

double Mouse::lastX = 0;
double Mouse::lastY = 0;

double Mouse::dx = 0;
double Mouse::dy = 0;

double Mouse::scrollDX = 0;
double Mouse::scrollDY = 0;

bool Mouse::firstMouse = true;


void Mouse::cursorPosCallBack(GLFWwindow* window, double _x, double _y){

    x = _x;
    y = _y;

    if( firstMouse ){

        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    dx = x - lastX;
    dy = lastY - y;

    lastX = x;
    lastY = y;
};

void Mouse::mouseWheelCallBack(GLFWwindow* window, double dx, double dy){

    scrollDX = dx;
    scrollDY = dy;
};

double Mouse::getMouseX(){

    return x;
};

double Mouse::getMouseY(){

    return y;
};

double Mouse::getDX(){

    double temp_dx = dx;
    dx = 0;
    return temp_dx;
};

double Mouse::getDY(){
    double temp_dy = dy;
    dy = 0;
    return temp_dy;
};

double Mouse::getScrollDX(){

    double temp_scrollDX = scrollDX;
    scrollDX = 0;
    return temp_scrollDX;
};

double Mouse::getScrollDY(){

    double temp_scrollDY = scrollDY;
    scrollDY = 0;
    return temp_scrollDY;
};
