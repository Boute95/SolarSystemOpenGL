#include <solar/RenderEngine.hpp>
#include <GL/glew.h>

///////////////////////////////////////////////////////////////////////////////
solar::RenderEngine::RenderEngine(glimac::SDLWindowManager& iWinManager, const Camera& iC) 
    : windowManager(iWinManager), camera(iC), glManager(std::make_shared<GLManager>()) {}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::addObject(std::shared_ptr<Drawable> iObj) {
    drawables.push_back(iObj);
    iObj->setGLManager(glManager);
    glManager->addVertices(iObj->getVertices());
}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::addLight(std::shared_ptr<LightSource> iLight) {
    lightSources.push_back(iLight);
}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::render() {

    glManager->bind();
    for (auto d : drawables) {
        d->draw(camera.getProjMatrix(), camera.getViewMatrix());
    }
    windowManager.swapBuffers();
    glManager->unbind();
    

}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::clear() {
    glManager->clear();
}

