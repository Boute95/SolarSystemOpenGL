#include <solar/RenderEngine.hpp>
#include <GL/glew.h>

///////////////////////////////////////////////////////////////////////////////
solar::RenderEngine::RenderEngine(const glimac::Program& p, glimac::SDLWindowManager& iWinManager, const Camera& iC)
 : windowManager(iWinManager), camera(iC), glManager(p) {}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::addObject(const std::shared_ptr<Drawable>& iObj) {
    drawables.push_back(iObj);
    glManager.addVertices(iObj->getVertices());
}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::addObjects(const std::vector<std::shared_ptr<Drawable>>& iObjects) {
    drawables.insert(drawables.end(), iObjects.begin(), iObjects.end());
    //TODO : glManager.addVertices
}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::addLight(const std::shared_ptr<LightSource>& iLight) {
    lightSources.push_back(iLight);
}



///////////////////////////////////////////////////////////////////////////////
void solar::RenderEngine::render() {

    glManager.bind();

    glManager.setUniformValue("uProjMatrix", camera.getProjMatrix());
    glManager.setUniformValue("uViewMatrix", camera.getViewMatrix());

    for (auto d : drawables) {
        d->draw(glManager);
    }

    windowManager.swapBuffers();
    glManager.unbind();

}

