#ifndef SOLAR_SOLARSPHEREOBJECT_HPP
#define SOLAR_SOLARSPHEREOBJECT_HPP

#include <glimac/Sphere.hpp>
#include <solar/Drawable.hpp>
#include <vector>

namespace solar {

    class SolarSphereObject : public Drawable {

    private:
        glimac::Sphere sphere;
        std::vector<glimac::ShapeVertex> vertices;

    public:
        SolarSphereObject(float radiusInKm);
        virtual void draw(GLManager& glManager) override;
        virtual const std::vector<glimac::ShapeVertex>& getVertices() override;

    };

}

#endif