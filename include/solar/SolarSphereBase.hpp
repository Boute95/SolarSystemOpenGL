#ifndef SOLAR_SOLARSPHEREBASE_HPP
#define SOLAR_SOLARSPHEREBASE_HPP

#include <solar/SolarSphere.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <vector>

namespace solar {

    class SolarSphereBase : public SolarSphere {

    private:
        std::shared_ptr<GLManager> glManager;
        glimac::Sphere sphere;
        std::vector<glimac::ShapeVertex> vertices;
        GLuint colorTexture;
        // GLuint cloudTexture;
        // GLuint normalTexture;
        glm::mat4 transformMatrix;
        std::shared_ptr<Transformable> parent;
        double apoapsis;
        double periapsis;
        double orbitalEccentricity;
        double orbitalPeriod;
        double rotationPeriod;
        double orbitalInclination;

    public:
        SolarSphereBase(double radiusInKm);
        // Drawable
        virtual void draw(const glm::mat4& projMatrix, const glm::mat4& viewMatrix) override;
        virtual const std::vector<glimac::ShapeVertex>& getVertices() override;
        virtual void setGLManager(std::shared_ptr<GLManager>) override;
        virtual void setShader(const std::string vs, const std::string fs) override;
        // Transformable
        virtual void translate(const glm::vec3&) override;
        virtual void rotate(const float angle, const glm::vec3& axis) override;
        virtual void rotate(const glm::quat&) override;
        virtual void scale(const glm::vec3&) override;
        virtual void resetTransforms() override;
        virtual glm::mat4 getTransformMatrix() const override;
        // Simulable
        virtual void setParent(std::shared_ptr<Transformable>) override;
        virtual void setApoapsis(const double km) override;
        virtual void setPeriapsis(const double km) override;
        virtual void setOrbitalEccentricity(const double) override;
        virtual void setOrbitalPeriod(const double hours) override;
        virtual void setRotationPeriod(const double hours) override;
        virtual void setOrbitalInclination(const double degrees) override;
        virtual void update(const double timeInHour) override;
        // SphereObject
        virtual void addColorTexture(const std::string& path) override;

    };

}

#endif