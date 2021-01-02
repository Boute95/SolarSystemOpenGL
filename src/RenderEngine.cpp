#include <solar/RenderEngine.hpp>
#include <GL/glew.h>
#include <iostream> // std::cerr

///////////////////////////////////////////////////////////////////////////////
solar::RenderEngine::RenderEngine(const glimac::SDLWindowManager& iWinManager, const Camera& iC) : 
    windowManager(iWinManager), camera(iC) {
        // Initialize glew for OpenGL3+ support
        GLenum glewInitError = glewInit();
        if(GLEW_OK != glewInitError) {
            std::cerr << glewGetErrorString(glewInitError) << std::endl;
            throw std::exception();
        }
    }



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::addObject(const std::shared_ptr<Drawable>& iObj) {
    drawables.push_back(iObj);
    glManager.addVertices(iObj->getVertices());
}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::addObjects(const std::vector<std::shared_ptr<Drawable>>& iObjects) {
    drawables.insert(drawables.end(), iObjects.begin(), iObjects.end());
}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::addLight(const std::shared_ptr<LightSource>& iLight) {
    lightSources.push_back(iLight);
}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::render() {

    glManager.bind();
    for (auto d : drawables) {
        d->draw(glManager);
    }
    glManager.unbind();
    
}

