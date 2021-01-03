#include <GL/glew.h>
#include <solar/Engine.hpp>
#include <solar/RenderEngine.hpp>
#include <solar/Camera.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <iostream> // std::cout


///////////////////////////////////////////////////////////////////////////////
solar::Engine::Engine() {}



///////////////////////////////////////////////////////////////////////////////
void solar::Engine::start(char* appPathStr) {

    glimac::SDLWindowManager winManager(1280, 720, "SolarSystemOpenGL");

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

    solar::Camera camera(1280 / 720.f);
    RenderEngine renderEngine(program, winManager, camera);

    // solarObjects.emplace("mercure", std::make_shared<SolarSphereObject>(2439.7));
    // solarObjects.emplace("venus", std::make_shared<SolarSphereObject>(6051.8));
    // stars.emplace("sun", std::make_shared<Star>(696340.f, glm::vec3(1.f), 10000));
    solarObjects.emplace("testSphere", std::make_shared<SolarSphereObject>(1.0f));

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
