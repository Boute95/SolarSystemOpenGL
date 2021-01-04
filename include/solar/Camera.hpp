#ifndef SOLAR_CAMERA_HPP
#define SOLAR_CAMERA_HPP

#include <glm/geometric.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <solar/Transformable.hpp>

namespace solar {

    class Camera : public Transformable {

    private:
        double aspectRatio;
        glm::mat4 transformMatrix;

    public:
        Camera(double iAspectRatio);
        virtual void translate(const glm::vec3&) override;
        virtual void rotate(const float angle, const glm::vec3& axis) override;
        virtual void scale(const glm::vec3&) override;
        virtual void resetTransforms() override;
        virtual glm::vec3 getWorldPosition() const override;
        glm::mat4 getProjMatrix() const;
        glm::mat4 getViewMatrix() const;

    };

}

#endif