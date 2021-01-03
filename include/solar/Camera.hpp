#ifndef SOLAR_CAMERA_HPP
#define SOLAR_CAMERA_HPP

#include <glm/geometric.hpp>

namespace solar {

    class Camera {

    private:
        float aspectRatio;
        glm::vec2 position;
        glm::vec2 target;

    public:
        Camera(float iAspectRatio);
        void setPosition(const glm::vec2& p);
        void setTarget(const glm::vec2& t);
        glm::mat4 getProjMatrix() const;
        glm::mat4 getViewMatrix() const;

    };

}

#endif