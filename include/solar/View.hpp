#ifndef SOLAR_VIEW_HPP
#define SOLAR_VIEW_HPP

#include <glm/glm.hpp>

namespace solar {

    class View {

    private:
        glm::vec3 target;
        double distanceFromTarget;
        double angleX;
        double angleY;
        glm::vec3 position;
        bool trackball;

    public:
        void setTrackball(const glm::vec3& iTarget, const double iDistanceFromTarget, const double iAngleX, const double iAngleY);
        void setFree(const glm::vec3& iTarget, const glm::vec3& iPosition);
        bool isTrackball() const;
        glm::vec3 getTarget() const;
        glm::vec3 getPosition() const;
        double getDistanceFromTarget() const;
        double getAngleX() const;
        double getAngleY() const;
    };

}

#endif