#ifndef MOUSE_H
#define MOUSE_H

#include "../external/glad/glad.h"
#include "../external/GLFW/glfw3.h"


#include<iostream>

class Mouse{

    public:

        static void cursorPosCallBack(GLFWwindow* window, double _x, double _y);
        static void mouseWheelCallBack(GLFWwindow* window, double dx, double dy);

        static double getMouseX();
        static double getMouseY();

        static double getDX();
        static double getDY();

        static double getScrollDX();
        static double getScrollDY();

    private:
    
        static double x;
        static double y;

        static double lastX;
        static double lastY;

        static double dx;
        static double dy;

        static double scrollDX;
        static double scrollDY;

        static bool firstMouse;
};

#endif