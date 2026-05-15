#include "Camera2D.h"

glm::mat4 Camera2D::getViewMatrix() const{
    // Start with an identity matrix (no transformations)
    glm::mat4 view = glm::mat4(1.0f);

    //translate the origin to the centet of screen
    view = glm::translate(view, glm::vec3(viewPortWidth * 0.5f, viewPortHeight * 0.5f, 0.0f));

    //apply camera rotaion
    view = glm::rotate(view, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    //apply camera zoom
    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));


    //screen shake calculations
    float shakeX = 0.0f;
    float shakeY = 0.0f;
    if(shakeDuration > 0.0f){
        // Generate a random float between -1.0f and 1.0f, then scale by intensity
        float randomX = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        float randomY = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        
        shakeX = randomX * shakeIntensity;
        shakeY = randomY * shakeIntensity;
    }
    //translate by the camera's positoin (inverted)
    //moving the camera to (+x +y) shift the world to (-x, -y)
    view = glm::translate(view, glm::vec3(-position.x, -position.y, 0.0f));

    return view;
};

glm::mat4 Camera2D::getProjectionMatrix() const{

    // Left: 0.0f
    // Right: viewportWidth (e.g., 800.0f)
    // Bottom: viewportHeight (e.g., 600.0f) -> Putting height at the bottom gives us Y-down!
    // Top: 0.0f
    // Near: -1.0f
    // Far: 1.0f
    return glm::ortho(0.0f, viewPortWidth, viewPortHeight, 0.0f, -1.0f, 1.0f);
};

glm::mat4 Camera2D::getViewProjectionMatrix() const {

    return getProjectionMatrix() * getViewMatrix(); 
}

void Camera2D::follow(const glm::vec2& targetPosition, float deltaTime, float speed){
    // Smoothly interpolate between current position and target position
    // Formula: Position = Position + (Target - Position) * speed * dt
    this->position = glm::mix(this->position, targetPosition, speed * deltaTime);
};

void Camera2D::clamToBoundaries(const glm::vec2& minBoundaries, const glm::vec2& maxBoundaries){
    float halfWidth = (viewPortWidth * 0.5f) / zoom;
    float halfHeight = (viewPortHeight * 0.5f) / zoom;

    //clamp the camera position  so the screen edges don't cross the map boundaries
    this->position.x = glm::clamp(this->position.x, minBoundaries.x + halfWidth, maxBoundaries.x - halfWidth);
    this->position.y = glm::clamp(this->position.y, minBoundaries.y + halfHeight, maxBoundaries.y - halfHeight);
};


void Camera2D::startShake(float intensity, float duartion){
    this->shakeIntensity = intensity;
    this->shakeDuration = duartion;
}

//call this in your update loop to decay the shake effect
void Camera2D::updateShake(float deltaTime){
    if(this->shakeDuration > 0.0f){
        this->shakeDuration -= deltaTime;
        if(this->shakeDuration <= 0.0f)
        this->shakeDuration = 0.0f;
    }
}


glm::vec2 Camera2D::screenToWorld(const glm::vec2& screenCoords) const{
    //convert screen coordinates to NDC
    float ndcX = (2.0f * screenCoords.x) / viewPortWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * screenCoords.y) / viewPortHeight; // Invert Y because screen Y is down

    //get inverser of view-projection matrix
    glm::mat4 invVP = glm::inverse(getViewProjectionMatrix());

    //mulltiply NDC by the inverse matrix to get world coordinates
    glm::vec4 worldCoords = invVP * glm::vec4(ndcX, ndcY, 0.0f, 1.0f);

    return glm::vec2(worldCoords.x, worldCoords.y);
}