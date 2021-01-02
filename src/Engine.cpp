#include <solar/Engine.hpp>
#include <solar/RenderEngine.hpp>
#include <solar/Camera.hpp>
#include <glimac/SDLWindowManager.hpp>


///////////////////////////////////////////////////////////////////////////////
solar::Engine::Engine() {}



///////////////////////////////////////////////////////////////////////////////
void solar::Engine::start() {

    solarObjects.emplace("mercure", std::make_shared<SolarSphereObject>(2439.7));
    solarObjects.emplace("venus", std::make_shared<SolarSphereObject>(6051.8));
    stars.emplace("sun", std::make_shared<Star>(696340.f, glm::vec3(1.f), 10000));

    solar::Camera camera;
    glimac::SDLWindowManager winManager(1280, 720, "SolarSystemOpenGL");
    RenderEngine renderEngine(winManager, camera);

    for(const auto& o : solarObjects) {
        renderEngine.addObject(o.second);
    }
    for(const auto& o : stars) {
        renderEngine.addLight(o.second);
    }

    // Main loop
    bool done = false;
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(winManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        renderEngine.render();

    }

    

}
