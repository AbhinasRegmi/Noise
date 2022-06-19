#include "../../include/io/camera.h"

Camera::Camera(glm::vec3 position){

    cameraPos = position;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    yaw = -90.0f;
    pitch = 0.0f;
    speed = 10.0f;
    sensitivity = 0.5f;

    zoom = 45.0f;

    updateCameraVectors();
};

void Camera::updateCameraDirection(double dx, double dy){

    yaw += dx * sensitivity;
    pitch += dy * sensitivity;

    if( pitch > 89.0f ){

        pitch = 89.0f;
    }

    if( pitch < -89.0f ){

        pitch = 89.0f;
    }

    updateCameraVectors();
};

void Camera::updateCameraPos(cameraMovement dir, double dt){

    float velocity = (float)dt * speed;

    switch (dir)
    {
    case cameraMovement::FORWARD:
        cameraPos += cameraFront * velocity;
        break;

    case cameraMovement::BACKWARD:
        cameraPos -= cameraFront * velocity;
        break;

    case cameraMovement::RIGHT:
        cameraPos += cameraRight * velocity;
        break;

    case cameraMovement::LEFT:
        cameraPos -= cameraRight * velocity;
        break;
    
    case cameraMovement::UP:
        cameraPos += cameraUp * velocity;
        break;

    case cameraMovement::DOWN:
        cameraPos -= cameraUp * velocity;
        break;
    }

};

void Camera::updateCameraZoom(double dy){

    if( zoom >= 1.0f && zoom <= 45.0f ){

        zoom -= dy;
    }
    else if( zoom < 1.0f ){
        
        zoom = 1.0f;
    }
    else{

        zoom = 45.0f;
    }
};

void Camera::updateCameraVectors(){

    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
};

glm::mat4 Camera::getViewMatrix(){

    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
};
