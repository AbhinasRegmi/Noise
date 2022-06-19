#include <iostream>
#include <vector>

#include "include/io/keyboard.h"
#include "include/io/mouse.h"
#include "include/io/camera.h"

#include "include/graphics/shaders.h"

//globals
int WIDTH = 1080;
int HEIGHT = 720;

//set camera position
glm::vec3 cameraPosition = glm::vec3(0.0f, 3.0f, 0.0f);
Camera ourCamera(cameraPosition);   //defines the initial viewing position

//define model factors
glm::mat4 model = glm::mat4(1.0f);  //defines the size of rendered object, scene
glm::mat4 view = glm::mat4(1.0f);   //defines the visibility, angle of viewing
glm::mat4 projection = glm::mat4(1.0f); //defines how the prespective should look

//prototype for processing keyboard, mouse inputs, callbacks
void processInput(double dt, GLFWwindow* window);
void screenResizeCallback(GLFWwindow* window, int width, int height);

//helps in calculation of delta time, to determine change in mouse position, fps
float deltaTime = 0.0f;
float lastFrame = 0.0f;



int main(){

    //initialize glfw and set opengl version
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Perlin Noise", NULL, NULL);

    //check if a window is successfully created
    if(!window){

        std::cerr<<"Failed to create a window.";
        return -1;
    }

    glfwMakeContextCurrent(window);

    //load opengl library
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){

        std::cerr<<"Failed to load opengl.";
        return -1;
    }

    //give opengl the window context
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0f, 0.7098f, 0.8862f, 1.0f);

    //enable depth test to correctly render the faces of distant and near objects
    glEnable(GL_DEPTH_TEST);

    //configure callbacks
    glfwSetFramebufferSizeCallback(window, screenResizeCallback);
    glfwSetKeyCallback(window, Keyboard::keyCallback);
    glfwSetCursorPosCallback(window, Mouse::cursorPosCallBack);
    glfwSetScrollCallback(window, Mouse::mouseWheelCallBack);

    //disable mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    //-----------------------------------------------------------------------------//

    //configure and compile the shaders
    //file position relative to the binary / executable
    Shader ourShader("../resources/vertexShader.vs", "../resources/fragmentShader.fs");
    

    //--------------------------------------------------------------------//

    //configure terrain properties
    const int PLANE_WIDTH = 1000;
    const int PLANE_HEIGHT = 1000; 
    const int PLANE_RESOLUTION = 9;  //the resolution of output triangles

    //we will render the plane in stripes so
    const int TOTAL_NUM_STRIPES = (PLANE_HEIGHT - 1) / PLANE_RESOLUTION;
    const int VERTICES_PER_STRIPE = (PLANE_WIDTH / PLANE_RESOLUTION) * 2;

    //the vertices for the terrain
    std::vector<float> vertices;

    //the indices for our terrain it determines the way the terrain is rendered
    std::vector<unsigned int> indices;

    //populate the vertices
    for( int i = 0; i < PLANE_HEIGHT; i++ ){

        for( int j = 0; j < PLANE_WIDTH; j++ ){

            vertices.push_back(i);  //x-coord of our vertices in plain
            vertices.push_back(0); //height of vertices in plain
            vertices.push_back(j); //z-coord of our vertices in plain
        }
    }

    //populate the indices
    //assume we have such points
    /*
    //this is our vertices in plane

            *   * 
            *   *
            
    //we manage indices such that the number in the following pattern

        we go from 0 -> 1 -> 3 -> 2 -> 1 

        we have to create similar pattern from our vertices
    */

    for( unsigned int i = 0; i < PLANE_HEIGHT - 1; i += PLANE_RESOLUTION ){

        for( unsigned int j = 0; j < PLANE_WIDTH; j += PLANE_RESOLUTION ){

            for( unsigned int k = 0; k < 2; k++ ){

                indices.push_back(j + PLANE_WIDTH * ( i + k * PLANE_RESOLUTION));
            }
        }
    }

    //configure vao, vbo, ebo
    unsigned int VAO, VBO, EBO; //vao vertex array buffer, vbo vertex buffer object, ebo indexbufferobject

    //generate buffers in gpu
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //bind the buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //binding vbo to vao and passing data to gpu
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    //make sense of data sent
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    //send ebo too
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //render in plane in wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    

    //main loop
    while(!glfwWindowShouldClose(window)){

        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        processInput(deltaTime, window);

        //bind vao and use shaders
        glBindVertexArray(VAO);
        ourShader.useShader();

        //set our transformations
        view = ourCamera.getViewMatrix();
        projection = glm::perspective(glm::radians(ourCamera.zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 600.0f);
        model = glm::scale(model, glm::vec3(1.0));

        //send to gpu to compute view Space, model size, projection
        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);

        //finally render the plane stripe by stripe
        for( unsigned int i = 0; i < TOTAL_NUM_STRIPES; i++  ){

            glDrawElements(
            GL_TRIANGLE_STRIP,
            VERTICES_PER_STRIPE + 2,
            GL_UNSIGNED_INT,
            (void*)(sizeof(unsigned int) * (VERTICES_PER_STRIPE + 2) * i));
        }

        //clear the buffer bits
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}

void screenResizeCallback(GLFWwindow* window, int width, int height){

    WIDTH = width;
    HEIGHT = height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
}

void processInput(double dt, GLFWwindow* window){
    
    if( Keyboard::key(GLFW_KEY_ESCAPE) ){

        glfwSetWindowShouldClose(window, true);
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