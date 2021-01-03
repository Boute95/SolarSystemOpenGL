#ifndef SOLAR_CAMERA_HPP
#define SOLAR_CAMERA_HPP

#include <glm/geometric.hpp>
#include <glm/matrix.hpp>
#include <solar/Transformable.hpp>

namespace solar {

    class Camera : public Transformable {

    private:
        float aspectRatio;
        glm::mat4 transformMatrix;

    public:
        Camera(float iAspectRatio);
        virtual void translate(const glm::vec3&) override;
        virtual void rotate(const float angle, const glm::vec3& axis) override;
        virtual void scale(const glm::vec3&) override;
        virtual void resetTransforms() override;
        virtual glm::mat4 getTransformMatrix() const override;
        glm::mat4 getProjMatrix() const;
        glm::mat4 getViewMatrix() const;

    };

}

#endif