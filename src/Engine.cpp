#include <GL/glew.h>
#include <solar/Engine.hpp>
#include <solar/Camera.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <iostream> // std::cout


///////////////////////////////////////////////////////////////////////////////
solar::Engine::Engine() {}



///////////////////////////////////////////////////////////////////////////////
void solar::Engine::start(char* appPathStr) {

    glimac::SDLWindowManager winManager(1920, 1080, "SolarSystemOpenGL");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        throw std::exception();
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glimac::FilePath applicationPath(appPathStr);
    glimac::FilePath vs = applicationPath.dirPath() + "../assets/shaders/SolarSphereObject.vs.glsl";
    glimac::FilePath fs = applicationPath.dirPath() + "../assets/shaders/SolarSphereObject.fs.glsl";
    std::cout << "Vertex Shader : " << vs << '\n'; 
    std::cout << "Frag Shader : " << fs << std::endl;
    glimac::Program program = glimac::loadProgram(vs, fs);
    program.use();

    solar::Camera camera(1920 / 1080.f);
    camera.translate(glm::vec3(0.f, 0.f, -1e9));
    RenderEngine renderEngine(program, winManager, camera);
    PhysicsEngine physicsEngine;

    initObjects(applicationPath, renderEngine, physicsEngine);

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
        physicsEngine.simulate();

    }

    renderEngine.clear();

}



///////////////////////////////////////////////////////////////////////////////
void solar::Engine::initObjects(const glimac::FilePath& appPath, RenderEngine& renderEngine, PhysicsEngine& physicsEngine) {
    stars["sun"] = std::make_shared<Star>(696340.f * 10, glm::vec3(1.f), 10000);
    renderEngine.addObject(stars["sun"]);
    stars["sun"]->setRotationPeriod(25.f * 24); // 25 days
    stars["sun"]->addColorTexture(appPath.dirPath() + "../assets/textures/sun.jpg");

    solarObjects["mercure"] = std::make_shared<SolarSphereObject>(2439.7f * 2000);
    renderEngine.addObject(solarObjects["mercure"]);
    physicsEngine.addObject(solarObjects["mercure"]);
    solarObjects["mercure"]->setParent(stars["sun"]);
    solarObjects["mercure"]->setApoapsis(69.8e6);
    solarObjects["mercure"]->setPeriapsis(46.0e6);
    solarObjects["mercure"]->setOrbitalEccentricity(0.205f);
    solarObjects["mercure"]->setOrbitalPeriod(88.f * 24);
    solarObjects["mercure"]->setRotationPeriod(1407.6f);
    solarObjects["mercure"]->addColorTexture(appPath.dirPath() + "../assets/textures/mercure.jpg");
    
    // solarObjects["mercure"] = std::make_shared<SolarSphereObject>(2439.7f);
    // renderEngine.addObject(solarObjects["mercure"]);
    // // solarObjects["mercure"]->setParent(stars["sun"]);
    // solarObjects["mercure"]->setApoapsis(69.8e6);
    // solarObjects["mercure"]->setPeriapsis(46.0e6);
    // solarObjects["mercure"]->setOrbitalPeriod(88.f * 24);
    // solarObjects["mercure"]->setRotationPeriod(1407.6f);
    // solarObjects["mercure"]->addColorTexture(appPath.dirPath() + "../assets/textures/mercure.jpg");
    // solarObjects["venus"] = std::make_shared<SolarSphereObject>(6051.8f));
    
}

