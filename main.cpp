#include <iostream>
#include <vector>

#include "include/io/keyboard.h"
#include "include/io/mouse.h"
#include "include/io/camera.h"

#include "include/graphics/shaders.h"

//globals

//set camera position
glm::vec3 cameraPosition = glm::vec3(0.0f, 3.0f, 0.0f);
Camera ourCamera(cameraPosition);   //defines the initial viewing position

//define model factors
glm::mat4 model = glm::mat4(1.0f);  //defines the size of rendered object, scene
glm::mat4 view = glm::mat4(1.0f);   //defines the visibility, angle of viewing
glm::mat4 projection = glm::mat4(1.0f); //defines how the prespective should look

//prototype for processing keyboard, mouse inputs
void processsInput(double dt);

//helps in calculation of delta time, to determine change in mouse position, fps
float deltaTime = 0.0f;
float lastFrame = 0.0f;



int main(){

    std::cout<<"Hello world!"<<std::endl;
    
    return 0;
}


void processInput(double dt){
    
    if( Keyboard::key(GLFW_KEY_ESCAPE) ){
        //glfwSetWindowShouldClose(window, true);
    }

    
    //move camera with keys
    if( Keyboard::key(GLFW_KEY_W)){
        ourCamera.updateCameraPos(cameraMovement::FORWARD, dt);
    }

    if( Keyboard::key(GLFW_KEY_S)){
        ourCamera.updateCameraPos(cameraMovement::BACKWARD, dt);
    }
    
    if( Keyboard::key(GLFW_KEY_A)){
        ourCamera.updateCameraPos(cameraMovement::LEFT, dt);
    }
    
    if( Keyboard::key(GLFW_KEY_D)){
        ourCamera.updateCameraPos(cameraMovement::RIGHT, dt);
    }

    if( Keyboard::key(GLFW_KEY_SPACE)){
        ourCamera.updateCameraPos(cameraMovement::UP, dt);
    }

    if( Keyboard::key(GLFW_KEY_LEFT_CONTROL)){
        ourCamera.updateCameraPos(cameraMovement::DOWN, dt);
    }

    //move camera with mouse
    double dx = Mouse::getDX(), dy = Mouse::getDY();

    if( dx != 0 || dy != 0 ){
        ourCamera.updateCameraDirection(dx, dy);
    }

    //adjust zoom
    double scrolldy = Mouse::getScrollDY();
    
    if( scrolldy != 0 ){
    
        ourCamera.updateCameraZoom(scrolldy);
    }
};