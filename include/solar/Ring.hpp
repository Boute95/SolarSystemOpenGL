#ifndef SOLAR_RING_HPP
#define SOLAR_RING_HPP

#include <solar/SolarSphereDecorator.hpp>
#include <vector>

namespace solar {

    class Ring : public SolarSphereDecorator {
    
    private:
        double inRadiusInKm;
        std::vector<glimac::ShapeVertex> allVertices;
        std::vector<glimac::ShapeVertex> ringVertices;
        std::shared_ptr<GLManager> glManager;
        GLuint ringColorTexture;
        GLuint ringTransparencyTexture;

        std::vector<glimac::ShapeVertex> getAnnulusVertices(const double innerR, const double outerR, const unsigned int iterationCount) const;

    public:
        Ring(const double innerRadiusInKm, const double outerRadiusInKm, std::shared_ptr<SolarSphere>);
        void draw() override;
        const std::vector<glimac::ShapeVertex>& getVertices() override;
        void setGLManager(std::shared_ptr<GLManager>) override;
        void addRingColorTexture(const std::string& path);
        void addRingTransparencyTexture(const std::string& path);

    };

}

#endif