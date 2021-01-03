#include <solar/Engine.hpp>

int main(int argc, char** argv) {

    if (argc > 0) {
        solar::Engine engine;
        engine.start(argv[0]);
    }
    

    return 0;
}
