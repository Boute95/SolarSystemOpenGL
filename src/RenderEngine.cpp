#include <solar/RenderEngine.hpp>
#include <GL/glew.h>

///////////////////////////////////////////////////////////////////////////////
solar::RenderEngine::RenderEngine(const glimac::Program& p, glimac::SDLWindowManager& iWinManager, const Camera& iC) 
    : windowManager(iWinManager), camera(iC) {
    glManager = std::make_shared<GLManager>(p);
 }



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
    glManager->setUniformValue("uProjMatrix", camera.getProjMatrix());
    glManager->setUniformValue("uViewMatrix", camera.getViewMatrix());
    for (auto d : drawables) {
        d->draw();
    }
    windowManager.swapBuffers();
    glManager->unbind();

}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::clear() {
    glManager->clear();
}

