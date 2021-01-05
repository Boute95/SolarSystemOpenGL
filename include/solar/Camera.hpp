#ifndef SOLAR_CAMERA_HPP
#define SOLAR_CAMERA_HPP

#include <solar/Transformable.hpp>

namespace solar {

    class Camera : public Transformable {

    private:
        double aspectRatio;
        float angleX;
        float angleY;
        glm::mat4 transformMatrix;

    public:
        Camera(double iAspectRatio);
        virtual void translate(const glm::vec3&) override;
        virtual void rotate(const float angle, const glm::vec3& axis) override;
        virtual void rotate(const glm::quat&) override;
        virtual void scale(const glm::vec3&) override;
        virtual void resetTransforms() override;
        virtual glm::mat4 getTransformMatrix() const override;
        glm::mat4 getProjMatrix() const;
        glm::mat4 getViewMatrix() const;

    };

}

#endif