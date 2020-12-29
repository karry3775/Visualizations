#pragma once

#include "SDL2/SDL.h"

namespace particlesystem {

class FireExplosionParticleSystem {

public:
    const static int SCREEN_WIDTH = 800;
    const static int SCREEN_HEIGHT = 600;

private:   
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Texture* texture_;

    Uint32* buffer_;
    Uint32* blur_buffer_;

public: 
    FireExplosionParticleSystem();
    /** \TODO: Add description for each function here */
    void initialize();
    void destroy();
    void updateParticles();
    void clearBuffer();
    void drawBreathingWindowAllColors();
    void setPixelValue(int posx, int posy, Uint8 red, Uint8 green, Uint8 blue);
    void run();
    void boxBlur();
    bool breakLoopOnQuit(SDL_Event&);
    void demoBasic();

};

} // namespace particlesystem