#pragma once

namespace particlesystem {
    
struct Particle {
    double x;
    double y;
    double orig_x;
    double orig_y;

    double speed;
    double direction;
    
    Particle();
    void updateParticlePosition(double x, double y) {this->x = x ; this->y = y;};
};

} // namespace particlesystem
