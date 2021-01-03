#ifndef SOLAR_SOLARSPHEREOBJECT_HPP
#define SOLAR_SOLARSPHEREOBJECT_HPP

#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <solar/Drawable.hpp>
#include <vector>

namespace solar {

    class SolarSphereObject : public Drawable {

    private:
        std::shared_ptr<GLManager> glManager; 
        glimac::Sphere sphere;
        std::vector<glimac::ShapeVertex> vertices;
        GLuint colorTexture;
        // GLuint cloudTexture;
        // GLuint normalTexture;

    public:
        SolarSphereObject(float radiusInKm);
        virtual void draw() override;
        virtual const std::vector<glimac::ShapeVertex>& getVertices() override;
        virtual void setGLManager(std::shared_ptr<GLManager>) override;
        virtual void addColorTexture(const std::string& path);

    };

}

#endif