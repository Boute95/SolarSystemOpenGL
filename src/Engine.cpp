#include <GL/glew.h>
#include <solar/Engine.hpp>
#include <solar/CameraController.hpp>
#include <solar/ControlsManager.hpp>
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

    // Initializing program
    glimac::FilePath applicationPath(appPathStr);
    glimac::FilePath vs = applicationPath.dirPath() + "../assets/shaders/SolarSphereObject.vs.glsl";
    glimac::FilePath fs = applicationPath.dirPath() + "../assets/shaders/SolarSphereObject.fs.glsl";
    std::cout << "Vertex Shader : " << vs << '\n'; 
    std::cout << "Frag Shader : " << fs << std::endl;
    glimac::Program program = glimac::loadProgram(vs, fs);
    program.use();

    // Initializing Engines and controllers
    solar::CameraController cameraController(1920 / 1080.);
    solar::ControlsManager controlsManager;
    RenderEngine renderEngine(program, winManager, cameraController.getCamera());
    PhysicsEngine physicsEngine;
    physicsEngine.setHourPerSecond(50.);

    // Initializing solar objects
    initObjects(applicationPath, renderEngine, physicsEngine);

    // Setting up the different views
    View topView;
    topView.setTrackball(solarObjects["sun"]->getWorldPosition(), -4e9, 0., 180. - 60.);
    cameraController.addView("topView", topView);
    cameraController.switchView("topView");

    // Main loop
    bool done = false;
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(winManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            } else {
                controlsManager.update(e, winManager, cameraController);
            }

        }

        renderEngine.render();
        physicsEngine.simulate();

    }

    renderEngine.clear();

}



///////////////////////////////////////////////////////////////////////////////
void solar::Engine::initObjects(const glimac::FilePath& appPath, RenderEngine& renderEngine, PhysicsEngine& physicsEngine) {
    solarObjects["sun"] = std::make_shared<SolarSphereBase>(696340. * 10);
    renderEngine.addObject(solarObjects["sun"]);
    solarObjects["sun"]->setRotationPeriod(25. * 24); // 25 days
    solarObjects["sun"]->addColorTexture(appPath.dirPath() + "../assets/textures/sun.jpg");

    solarObjects["mercure"] = std::make_shared<SolarSphereBase>(2439.7 * 3000);
    renderEngine.addObject(solarObjects["mercure"]);
    physicsEngine.addObject(solarObjects["mercure"]);
    solarObjects["mercure"]->setParent(solarObjects["sun"]);
    solarObjects["mercure"]->setApoapsis(69.8e6);
    solarObjects["mercure"]->setPeriapsis(46.0e6);
    solarObjects["mercure"]->setOrbitalEccentricity(0.205);
    solarObjects["mercure"]->setOrbitalPeriod(88. * 24);
    solarObjects["mercure"]->setRotationPeriod(1407.6);
    solarObjects["mercure"]->addColorTexture(appPath.dirPath() + "../assets/textures/mercure.jpg");
    
    solarObjects["venus"] = std::make_shared<SolarSphereBase>(6051.8 * 2000);
    renderEngine.addObject(solarObjects["venus"]);
    physicsEngine.addObject(solarObjects["venus"]);
    solarObjects["venus"]->setParent(solarObjects["sun"]);
    solarObjects["venus"]->setApoapsis(108.9e6);
    solarObjects["venus"]->setPeriapsis(107.5e6);
    solarObjects["venus"]->setOrbitalEccentricity(0.007);
    solarObjects["venus"]->setOrbitalPeriod(224.7 * 24);
    solarObjects["venus"]->setRotationPeriod(-5832.5);
    solarObjects["venus"]->addColorTexture(appPath.dirPath() + "../assets/textures/venus.jpg");

    solarObjects["earth"] = std::make_shared<SolarSphereBase>(6378.137 * 2000);
    renderEngine.addObject(solarObjects["earth"]);
    physicsEngine.addObject(solarObjects["earth"]);
    solarObjects["earth"]->setParent(solarObjects["sun"]);
    solarObjects["earth"]->setApoapsis(147.1e6);
    solarObjects["earth"]->setPeriapsis(152.1e6);
    solarObjects["earth"]->setOrbitalEccentricity(0.017);
    solarObjects["earth"]->setOrbitalPeriod(365.2 * 24);
    solarObjects["earth"]->setRotationPeriod(23.9);
    solarObjects["earth"]->addColorTexture(appPath.dirPath() + "../assets/textures/earth.jpg");

    solarObjects["mars"] = std::make_shared<SolarSphereBase>(3389.5 * 2000);
    renderEngine.addObject(solarObjects["mars"]);
    physicsEngine.addObject(solarObjects["mars"]);
    solarObjects["mars"]->setParent(solarObjects["sun"]);
    solarObjects["mars"]->setApoapsis(249.2e6);
    solarObjects["mars"]->setPeriapsis(206.6e6);
    solarObjects["mars"]->setOrbitalEccentricity(0.094);
    solarObjects["mars"]->setOrbitalPeriod(687.0 * 24);
    solarObjects["mars"]->setRotationPeriod(24.6);
    solarObjects["mars"]->addColorTexture(appPath.dirPath() + "../assets/textures/mars.jpg");

    solarObjects["jupiter"] = std::make_shared<SolarSphereBase>(69911. * 1000);
    renderEngine.addObject(solarObjects["jupiter"]);
    physicsEngine.addObject(solarObjects["jupiter"]);
    solarObjects["jupiter"]->setParent(solarObjects["sun"]);
    solarObjects["jupiter"]->setApoapsis(816.6e6);
    solarObjects["jupiter"]->setPeriapsis(740.5e6);
    solarObjects["jupiter"]->setOrbitalEccentricity(0.049);
    solarObjects["jupiter"]->setOrbitalPeriod(4331. * 24);
    solarObjects["jupiter"]->setRotationPeriod(9.9);
    solarObjects["jupiter"]->addColorTexture(appPath.dirPath() + "../assets/textures/jupiter.jpg");

    solarObjects["saturn"] = std::make_shared<SolarSphereBase>(58232. * 1000);
    renderEngine.addObject(solarObjects["saturn"]);
    physicsEngine.addObject(solarObjects["saturn"]);
    solarObjects["saturn"]->setParent(solarObjects["sun"]);
    solarObjects["saturn"]->setApoapsis(1514.5e6);
    solarObjects["saturn"]->setPeriapsis(1352.6e6);
    solarObjects["saturn"]->setOrbitalEccentricity(0.057);
    solarObjects["saturn"]->setOrbitalPeriod(10747. * 24);
    solarObjects["saturn"]->setRotationPeriod(10.7);
    solarObjects["saturn"]->addColorTexture(appPath.dirPath() + "../assets/textures/saturn.jpg");

    solarObjects["uranus"] = std::make_shared<SolarSphereBase>(25559. * 1000);
    renderEngine.addObject(solarObjects["uranus"]);
    physicsEngine.addObject(solarObjects["uranus"]);
    solarObjects["uranus"]->setParent(solarObjects["sun"]);
    solarObjects["uranus"]->setApoapsis(3003.6e6);
    solarObjects["uranus"]->setPeriapsis(2741.3e6);
    solarObjects["uranus"]->setOrbitalEccentricity(0.046);
    solarObjects["uranus"]->setOrbitalPeriod(30589. * 24);
    solarObjects["uranus"]->setRotationPeriod(-17.2);
    solarObjects["uranus"]->addColorTexture(appPath.dirPath() + "../assets/textures/uranus.jpg");

    solarObjects["neptune"] = std::make_shared<SolarSphereBase>(24622. * 1000);
    renderEngine.addObject(solarObjects["neptune"]);
    physicsEngine.addObject(solarObjects["neptune"]);
    solarObjects["neptune"]->setParent(solarObjects["sun"]);
    solarObjects["neptune"]->setApoapsis(4545.7e6);
    solarObjects["neptune"]->setPeriapsis(4444.5e6);
    solarObjects["neptune"]->setOrbitalEccentricity(0.011);
    solarObjects["neptune"]->setOrbitalPeriod(59800. * 24);
    solarObjects["neptune"]->setRotationPeriod(16.1);
    solarObjects["neptune"]->addColorTexture(appPath.dirPath() + "../assets/textures/neptune.jpg");

    solarObjects["pluto"] = std::make_shared<SolarSphereBase>(1188.3 * 4000);
    renderEngine.addObject(solarObjects["pluto"]);
    physicsEngine.addObject(solarObjects["pluto"]);
    solarObjects["pluto"]->setParent(solarObjects["sun"]);
    solarObjects["pluto"]->setApoapsis(7375.9e6);
    solarObjects["pluto"]->setPeriapsis(4436.8e6);
    solarObjects["pluto"]->setOrbitalEccentricity(0.244);
    solarObjects["pluto"]->setOrbitalPeriod(90560. * 24);
    solarObjects["pluto"]->setRotationPeriod(-153.3);
    solarObjects["pluto"]->addColorTexture(appPath.dirPath() + "../assets/textures/pluto.jpg");
    
}

