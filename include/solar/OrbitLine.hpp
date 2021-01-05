#ifndef SOLAR_ORBITLINE_HPP
#define SOLAR_ORBITLINE_HPP

#include <solar/SolarSphereDecorator.hpp>

namespace solar {

    class OrbitLine : public SolarSphereDecorator {
    
    private:
        std::vector<glimac::ShapeVertex> allVertices;
        std::vector<glimac::ShapeVertex> orbitVertices;
        std::shared_ptr<GLManager> glManager;
        double apoapsis;
        double periapsis;
        double orbitalEccentricity;
        glm::vec3 color;
        float thickness;

        std::vector<glimac::ShapeVertex> getOrbitVertices(size_t vertexCount) const;

    public:
        OrbitLine(glm::vec3 iColor, float iThickness, std::shared_ptr<SolarSphere>);
        void draw() override;
        const std::vector<glimac::ShapeVertex>& getVertices() override;
        void setGLManager(std::shared_ptr<GLManager>) override;
        virtual void setApoapsis(const double km) override;
        virtual void setPeriapsis(const double km) override;
        virtual void setOrbitalEccentricity(const double) override;

    };

}

#endif
