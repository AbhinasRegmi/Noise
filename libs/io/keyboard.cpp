#include "../../include/io/keyboard.h"

//define the static variables
bool Keyboard::keys[GLFW_KEY_LAST] = {0};
bool Keyboard::keysChanged[GLFW_KEY_LAST] = {0};

//define the functions
void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    
    //check if the keys are pressed or not
    if( action != GLFW_RELEASE ){
        if( !keys[key] ){
            keys[key] = true;
        }
    }else{
        keys[key] = false;
    }

    keysChanged[key] = action != GLFW_REPEAT;

};

bool Keyboard::key(int key){
    return keys[key];
};

bool Keyboard::keyChanged(int key){
    //we will store the current key value and set the keychanged to false
    bool current = key;
    keysChanged[key] = false;
    return current;
};

bool Keyboard::keyWentUp(int key){
    return !keys[key] && keyChanged(key);
};

bool Keyboard::keyWentDown(int key){
    return keys[key] && keyChanged(key);
};
