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
    camera.translate(glm::vec3(0.f, 0.f, -8e9));
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

    solarObjects["mercure"] = std::make_shared<SolarSphereObject>(2439.7f * 3000);
    renderEngine.addObject(solarObjects["mercure"]);
    physicsEngine.addObject(solarObjects["mercure"]);
    solarObjects["mercure"]->setParent(stars["sun"]);
    solarObjects["mercure"]->setApoapsis(69.8e6);
    solarObjects["mercure"]->setPeriapsis(46.0e6);
    solarObjects["mercure"]->setOrbitalEccentricity(0.205f);
    solarObjects["mercure"]->setOrbitalPeriod(88.f * 24);
    solarObjects["mercure"]->setRotationPeriod(1407.6f);
    solarObjects["mercure"]->addColorTexture(appPath.dirPath() + "../assets/textures/mercure.jpg");
    
    solarObjects["venus"] = std::make_shared<SolarSphereObject>(6051.8f * 2000);
    renderEngine.addObject(solarObjects["venus"]);
    physicsEngine.addObject(solarObjects["venus"]);
    solarObjects["venus"]->setParent(stars["sun"]);
    solarObjects["venus"]->setApoapsis(108.9e6);
    solarObjects["venus"]->setPeriapsis(107.5e6);
    solarObjects["venus"]->setOrbitalEccentricity(0.007f);
    solarObjects["venus"]->setOrbitalPeriod(224.7f * 24);
    solarObjects["venus"]->setRotationPeriod(-5832.5f);
    solarObjects["venus"]->addColorTexture(appPath.dirPath() + "../assets/textures/venus.jpg");

    solarObjects["earth"] = std::make_shared<SolarSphereObject>(6378.137f * 2000);
    renderEngine.addObject(solarObjects["earth"]);
    physicsEngine.addObject(solarObjects["earth"]);
    solarObjects["earth"]->setParent(stars["sun"]);
    solarObjects["earth"]->setApoapsis(147.1e6);
    solarObjects["earth"]->setPeriapsis(152.1e6);
    solarObjects["earth"]->setOrbitalEccentricity(0.017f);
    solarObjects["earth"]->setOrbitalPeriod(365.2f * 24);
    solarObjects["earth"]->setRotationPeriod(23.9f);
    solarObjects["earth"]->addColorTexture(appPath.dirPath() + "../assets/textures/earth.jpg");

    solarObjects["mars"] = std::make_shared<SolarSphereObject>(3389.5f * 2000);
    renderEngine.addObject(solarObjects["mars"]);
    physicsEngine.addObject(solarObjects["mars"]);
    solarObjects["mars"]->setParent(stars["sun"]);
    solarObjects["mars"]->setApoapsis(249.2e6);
    solarObjects["mars"]->setPeriapsis(206.6e6);
    solarObjects["mars"]->setOrbitalEccentricity(0.094f);
    solarObjects["mars"]->setOrbitalPeriod(687.0f * 24);
    solarObjects["mars"]->setRotationPeriod(24.6f);
    solarObjects["mars"]->addColorTexture(appPath.dirPath() + "../assets/textures/mars.jpg");

    solarObjects["jupiter"] = std::make_shared<SolarSphereObject>(69911.f * 1000);
    renderEngine.addObject(solarObjects["jupiter"]);
    physicsEngine.addObject(solarObjects["jupiter"]);
    solarObjects["jupiter"]->setParent(stars["sun"]);
    solarObjects["jupiter"]->setApoapsis(816.6e6);
    solarObjects["jupiter"]->setPeriapsis(740.5e6);
    solarObjects["jupiter"]->setOrbitalEccentricity(0.049f);
    solarObjects["jupiter"]->setOrbitalPeriod(4331.f * 24);
    solarObjects["jupiter"]->setRotationPeriod(9.9f);
    solarObjects["jupiter"]->addColorTexture(appPath.dirPath() + "../assets/textures/jupiter.jpg");

    solarObjects["saturn"] = std::make_shared<SolarSphereObject>(58232.f * 1000);
    renderEngine.addObject(solarObjects["saturn"]);
    physicsEngine.addObject(solarObjects["saturn"]);
    solarObjects["saturn"]->setParent(stars["sun"]);
    solarObjects["saturn"]->setApoapsis(1514.5e6);
    solarObjects["saturn"]->setPeriapsis(1352.6e6);
    solarObjects["saturn"]->setOrbitalEccentricity(0.057f);
    solarObjects["saturn"]->setOrbitalPeriod(10747.f * 24);
    solarObjects["saturn"]->setRotationPeriod(10.7f);
    solarObjects["saturn"]->addColorTexture(appPath.dirPath() + "../assets/textures/saturn.jpg");

    solarObjects["uranus"] = std::make_shared<SolarSphereObject>(25559.f * 1000);
    renderEngine.addObject(solarObjects["uranus"]);
    physicsEngine.addObject(solarObjects["uranus"]);
    solarObjects["uranus"]->setParent(stars["sun"]);
    solarObjects["uranus"]->setApoapsis(3003.6e6);
    solarObjects["uranus"]->setPeriapsis(2741.3e6);
    solarObjects["uranus"]->setOrbitalEccentricity(0.046f);
    solarObjects["uranus"]->setOrbitalPeriod(30589.f * 24);
    solarObjects["uranus"]->setRotationPeriod(-17.2f);
    solarObjects["uranus"]->addColorTexture(appPath.dirPath() + "../assets/textures/uranus.jpg");

    solarObjects["neptune"] = std::make_shared<SolarSphereObject>(24622.f * 1000);
    renderEngine.addObject(solarObjects["neptune"]);
    physicsEngine.addObject(solarObjects["neptune"]);
    solarObjects["neptune"]->setParent(stars["sun"]);
    solarObjects["neptune"]->setApoapsis(4545.7e6);
    solarObjects["neptune"]->setPeriapsis(4444.5e6);
    solarObjects["neptune"]->setOrbitalEccentricity(0.011f);
    solarObjects["neptune"]->setOrbitalPeriod(59800.f * 24);
    solarObjects["neptune"]->setRotationPeriod(16.1f);
    solarObjects["neptune"]->addColorTexture(appPath.dirPath() + "../assets/textures/neptune.jpg");

    solarObjects["pluto"] = std::make_shared<SolarSphereObject>(1188.3f * 4000);
    renderEngine.addObject(solarObjects["pluto"]);
    physicsEngine.addObject(solarObjects["pluto"]);
    solarObjects["pluto"]->setParent(stars["sun"]);
    solarObjects["pluto"]->setApoapsis(7375.9e6);
    solarObjects["pluto"]->setPeriapsis(4436.8e6);
    solarObjects["pluto"]->setOrbitalEccentricity(0.244f);
    solarObjects["pluto"]->setOrbitalPeriod(90560.f * 24);
    solarObjects["pluto"]->setRotationPeriod(-153.3f);
    solarObjects["pluto"]->addColorTexture(appPath.dirPath() + "../assets/textures/pluto.jpg");
    
}

