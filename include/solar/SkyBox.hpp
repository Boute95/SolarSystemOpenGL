#ifndef SOLAR_SKYBOX_HPP
#define SOLAR_SKYBOX_HPP

#include <solar/Drawable.hpp>
#include <solar/GLManager.hpp>

namespace solar {

    class SkyBox : public Drawable {

    private:
        std::vector<glimac::ShapeVertex> vertices;
        std::shared_ptr<GLManager> glManager;
        GLuint texture;


    public:
        virtual void draw(const glm::mat4& projMatrix, const glm::mat4& viewMatrix) override;
        virtual const std::vector<glimac::ShapeVertex>& getVertices() override;
        virtual void setGLManager(std::shared_ptr<GLManager>) override;
        virtual void setShader(const std::string vs, const std::string fs) override;
        virtual void addTextures(const std::array<std::string, 6>& paths);

    };

}

#endif
