#ifndef SOLAR_SOLARSPHEREOBJECT_HPP
#define SOLAR_SOLARSPHEREOBJECT_HPP

#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <solar/Drawable.hpp>
#include <solar/Simulable.hpp>
#include <vector>

namespace solar {

    class SolarSphereObject : public Drawable, public Simulable {

    private:
        std::shared_ptr<GLManager> glManager;
        glimac::Sphere sphere;
        std::vector<glimac::ShapeVertex> vertices;
        GLuint colorTexture;
        // GLuint cloudTexture;
        // GLuint normalTexture;
        glm::mat4 transformMatrix;
        std::shared_ptr<Transformable> parent;
        float apoapsis;
        float periapsis;
        float orbitalEccentricity;
        float orbitalPeriod;
        float rotationPeriod;
        float orbitalInclination;

    public:
        SolarSphereObject(float radiusInKm);
        virtual void draw() override;
        virtual const std::vector<glimac::ShapeVertex>& getVertices() override;
        virtual void setGLManager(std::shared_ptr<GLManager>) override;
        virtual void translate(const glm::vec3&) override;
        virtual void rotate(const float angle, const glm::vec3& axis) override;
        virtual void scale(const glm::vec3&) override;
        virtual void resetTransforms() override;
        virtual glm::mat4 getTransformMatrix() const override;
        virtual void setParent(std::shared_ptr<Transformable>) override;
        virtual void setApoapsis(const float km) override;
        virtual void setPeriapsis(const float km) override;
        virtual void setOrbitalEccentricity(const float) override;
        virtual void setOrbitalPeriod(const float hours) override;
        virtual void setRotationPeriod(const float hours) override;
        virtual void setOrbitalInclination(const float degrees) override;
        virtual void update(const float timeInHour) override;
        virtual void addColorTexture(const std::string& path);

    };

}

#endif