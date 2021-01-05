#include <solar/SkyBox.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
void solar::SkyBox::draw(const glm::mat4& projMatrix, const glm::mat4& viewMatrix) {
    glManager->disableDepthWrite();
    glManager->useShader("skyBoxShader");
    glManager->setUniformValue("uProjMatrixSB", projMatrix);
    // Applying scale to make cube's sides farther than camera's near.
    glm::mat4 translationIndependentView = glm::scale(glm::mat4(glm::mat3(viewMatrix)), glm::vec3(1e6, 1e6, 1e6));
    glManager->setUniformValue("uViewMatrixSB", translationIndependentView);
    glManager->setUniformValue("uLightnessFactor", 0.2f);
    glManager->setActiveTexture("uCubeMapTexture", texture, GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);
    glManager->drawVertices(GL_TRIANGLES, GLint(vertices.size()));
    glManager->enableDepthWrite();
}



///////////////////////////////////////////////////////////////////////////////
const std::vector<glimac::ShapeVertex>& solar::SkyBox::getVertices() {
    if (vertices.size() == 0) {
        vertices.reserve(36);
        constexpr float cubeVertices[] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };

        for (unsigned int i = 0 ; i < 36 ; i++) {
            glimac::ShapeVertex v;
            v.position = glm::vec3(cubeVertices[i*3], cubeVertices[i*3+1], cubeVertices[i*3+2]);
            vertices.push_back(v);
        }
    }
    return vertices;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SkyBox::setGLManager(std::shared_ptr<GLManager> iGLManager) {
    glManager = iGLManager;
}



///////////////////////////////////////////////////////////////////////////////
void solar::SkyBox::setShader(const std::string vs, const std::string fs) {
    glManager->addShader("skyBoxShader", vs, fs);
}



///////////////////////////////////////////////////////////////////////////////
void solar::SkyBox::addTextures(const std::array<std::string, 6>& paths) {
    std::array<std::unique_ptr<glimac::Image>, 6> images;
    for(unsigned int i = 0 ; i < 6 ; i++) {
        std::unique_ptr<glimac::Image> p_tex = glimac::loadImage(paths[i]);
        if (!p_tex) {
            std::cout << "WARNING : Can't load " << paths[i] << std::endl;
            return;
        }
        images[i] = std::move(p_tex);
    }
    texture = glManager->addCubeMapTexture(images);
    
}