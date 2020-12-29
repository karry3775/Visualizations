#include <stdlib.h>
#include <math.h>
#include <particle_system/Particle.h>


namespace particlesystem {

Particle::Particle() {

    x = 0; 
    y = 0; 

    orig_x = x;
    orig_y = y;

    // double speed_factor = 0.1;
    speed = 0.0001 * (((1.0* rand()) / RAND_MAX ) - 1.0); //speed_factor * x;
    direction = (2 * M_PI * rand()) / RAND_MAX;

}

} // namespace particlesystem
