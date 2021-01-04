#ifndef SOLAR_RENDERENGINE_HPP
#define SOLAR_RENDERENGINE_HPP

#include <vector>
#include <memory>
#include <solar/Drawable.hpp>
#include <solar/LightSource.hpp>
#include <solar/Camera.hpp>
#include <solar/GLManager.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>

namespace solar {

    class RenderEngine {

    private:
        std::vector<std::shared_ptr<Drawable>> drawables;
        std::vector<std::shared_ptr<LightSource>> lightSources;
        glimac::SDLWindowManager& windowManager;
        const Camera& camera;
        std::shared_ptr<GLManager> glManager;

    public:
        RenderEngine(const glimac::Program& p, glimac::SDLWindowManager& iWinManager, const Camera& iC);
        void addObject(std::shared_ptr<Drawable> iObj);
        void addLight(std::shared_ptr<LightSource> iLight);
        void render();
        void clear();

    };

}

#endif