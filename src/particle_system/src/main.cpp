#include <particle_system/Core.h>
#include <particle_system/FireExplosion.h>
#include <iomanip>

int main(int argc, char** argv) {


    auto fire_explosion = std::make_shared<particlesystem::FireExplosionParticleSystem>();

    fire_explosion->initialize();
    fire_explosion->run();
    fire_explosion->destroy();
    
    return 0;
}