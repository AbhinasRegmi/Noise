#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../external/glad/glad.h"
#include "../external/GLFW/glfw3.h"

class Keyboard{
    public:

        //whenever there is change in keyboard state call this
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        //get info about the key states
        static bool key(int key);
        static bool keyChanged(int key);
        static bool keyWentUp(int key);
        static bool keyWentDown(int key);

    private:
        static bool keys[];
        static bool keysChanged[];

};

#endif