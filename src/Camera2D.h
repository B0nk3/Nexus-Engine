#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {
    private:
        glm::vec2 position;
        float zoom;
        float rotation;
        
        float viewPortWidth;
        float viewPortHeight;

        float shakeIntensity = 0.0f;
        float shakeDuration = 0.0f;
    public:
        //constructors
        Camera2D(float width, float height);
        Camera2D();
        ~Camera2D();

        // getters and setters
        void setPosition(const glm::vec2& newPosition){
            this->position = newPosition;
        };

        glm::vec2 getPosition(){
            return this->position;
        };

        void setZoom(float value){
            this->zoom = value;
        };
        float getZoom(){
            return this->zoom;
        };

        void setRotation(float value){
            this->rotation = value;
        };
        float getRotation(){
            return this->rotation;
        };

        void setViewPortSize(float width, float height){
            this->viewPortWidth = width;
            this->viewPortHeight = height;
        };


        //main functions

        void move(const glm::vec2& offset){
            this->position += offset;
        };

        //returns view matrix
        glm::mat4 getViewMatrix() const;
        
        //returns projection matrix
        glm::mat4 getProjectionMatrix() const;

        //return combined matrix(view + projection)
        glm::mat4 getViewProjectionMatrix() const;

        void follow(const glm::vec2& targetPosition, float deltaTime, float speed);
        void clamToBoundaries(const glm::vec2& minBounds, const glm::vec2& maxBounds);
        void startShake(float intensity, float duartion);
        void updateShake(float deltaTime);

        glm::vec2 screenToWorld(const glm::vec2& screenCoords) const;
};

#endif