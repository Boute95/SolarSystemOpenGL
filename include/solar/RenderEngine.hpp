#ifndef SOLAR_RENDERENGINE_HPP
#define SOLAR_RENDERENGINE_HPP

#include <vector>
#include <memory>
#include <solar/Drawable.hpp>
#include <solar/LightSource.hpp>
#include <solar/Camera.hpp>
#include <solar/GLManager.hpp>
#include <glimac/SDLWindowManager.hpp>

namespace solar {

    class RenderEngine {

    private:
        std::vector<std::shared_ptr<Drawable>> drawables;
        std::vector<std::shared_ptr<LightSource>> lightSources;
        const glimac::SDLWindowManager& windowManager;
        const Camera& camera;
        GLManager glManager;

    public:
        RenderEngine(const glimac::SDLWindowManager& iWinManager, const Camera& iC);
        void addObject(const std::shared_ptr<Drawable>& iObj);
        void addObjects(const std::vector<std::shared_ptr<Drawable>>& iObjects);
        void addLight(const std::shared_ptr<LightSource>& iLight);
        void render();

    };

}

#endif