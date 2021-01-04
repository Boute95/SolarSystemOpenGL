#ifndef SOLAR_SOLARSPHEREDECORATOR_HPP
#define SOLAR_SOLARSPHEREDECORATOR_HPP

#include <solar/SolarSphere.hpp>
#include <memory>

namespace solar {

    class SolarSphereDecorator : public SolarSphere {

    private:
        std::shared_ptr<SolarSphere> base;

    public:
        SolarSphereDecorator(std::shared_ptr<SolarSphere> iSolarSphere);
        // Drawable
        virtual void draw() override;
        virtual const std::vector<glimac::ShapeVertex>& getVertices() override;
        virtual void setGLManager(std::shared_ptr<GLManager>) override;
        // Simulable
        virtual void translate(const glm::vec3&) override;
        virtual void rotate(const float angle, const glm::vec3& axis) override;
        virtual void scale(const glm::vec3&) override;
        virtual void resetTransforms() override;
        virtual glm::vec3 getWorldPosition() const override;
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