#ifndef CAMERA_H
#define CAMERA_H

#include "../external/glm/glm.hpp"
#include "../external/glm/gtc/matrix_transform.hpp"

enum cameraMovement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera{

    public:
        glm::vec3 cameraPos;

        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;

        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float speed;
        float sensitivity;
        float zoom;

        Camera(glm::vec3 position);

        void updateCameraDirection(double dx, double dy);
        void updateCameraPos(cameraMovement dir, double dt);
        void updateCameraZoom(double dy);

        glm::mat4 getViewMatrix();

    private:
        void updateCameraVectors();

};

#endif