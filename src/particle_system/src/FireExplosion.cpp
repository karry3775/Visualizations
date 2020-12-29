#include <particle_system/Core.h>
#include <particle_system/FireExplosion.h>
#include <particle_system/Swarm.h>

namespace particlesystem {

FireExplosionParticleSystem::FireExplosionParticleSystem() : 
    window_(nullptr), renderer_(nullptr), texture_(nullptr), buffer_(nullptr) {}

void FireExplosionParticleSystem::initialize(){
    
    // Initialize SDL 
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL Init Failed! " << std::endl; /** \TODO: glog**/
        return;
    }

    // Create window
    window_ = SDL_CreateWindow("Fire Explosion Particle System",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);

    // Check for null
    if(window_ == nullptr) {
        std::cout << "Cannot create window! " << SDL_GetError() << std::endl;
        destroy();
        return;
    }

    // Create a renderer
    renderer_ = SDL_CreateRenderer(window_,
                                   -1,
                                   SDL_RENDERER_PRESENTVSYNC);
    // check for null
    if(renderer_ == nullptr) {
        std::cout << "Cannot create renderer! " << SDL_GetError() << std::endl;
        destroy();
        return;
    }

    texture_ = SDL_CreateTexture(renderer_,
                                 SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_STATIC,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT);
    // check for null
    if(texture_ == nullptr) {
        std::cout << "Cannot create texture! " << SDL_GetError() << std::endl;
        destroy();
        return;
    }
    
    // initialize our buffer
    buffer_ = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    memset(buffer_, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    
}

void FireExplosionParticleSystem::destroy() {
    // free the buffer
    if(buffer_ != nullptr)  delete[] buffer_;
    // destroy texture if exists
    if(texture_ != nullptr)    SDL_DestroyTexture(texture_);
    // destroy window if exists
    if(renderer_ != nullptr)   SDL_DestroyRenderer(renderer_);
    // destroy window if exists
    if(window_ != nullptr)     SDL_DestroyWindow(window_);
    // finally quit
    SDL_Quit();
}

void FireExplosionParticleSystem::setPixelValue(int posx, int posy, Uint8 red, Uint8 green, Uint8 blue) {
    if(posx <= 0 || posx >= SCREEN_WIDTH || posy <= 0 || posy >= SCREEN_HEIGHT) return;

    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF; // this for alpha value

    buffer_[(posy* SCREEN_WIDTH) + posx] = color;
}

void FireExplosionParticleSystem::updateParticles() {
    SDL_UpdateTexture(texture_, NULL, buffer_, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture_, NULL, NULL);
    SDL_RenderPresent(renderer_);
}

void FireExplosionParticleSystem::clearBuffer() {
    memset(buffer_, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}

void FireExplosionParticleSystem::drawBreathingWindowAllColors() {
    int time_elapsed    = SDL_GetTicks();
    double green_factor = sin(time_elapsed * 0.001);
    double red_factor   = cos(time_elapsed * 0.001);
    double blue_factor  = sin(time_elapsed * 0.001 + M_PI/5);

    for(int posx = 0; posx < SCREEN_WIDTH; ++posx) {
        for(int posy = 0; posy < SCREEN_HEIGHT; ++posy) {
            
            setPixelValue(posx, posy, Uint8(abs(255 * red_factor)), 
                                      Uint8(abs(255 * green_factor)), 
                                      Uint8(abs(255 * blue_factor)));
        }
    }
}

void FireExplosionParticleSystem::run() {
    // srand(time(NULL));

    Swarm swarm;
    Particle* particles = swarm.getParticles();    
    SDL_Event event;

    int min_dim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);  

    int last_time = -1.0;

    while (true){
        
        // Draw particles
        // we are following the image cordinate system
        // drawBreathingWindowAllColors();
        int time_elapsed    = SDL_GetTicks();
        double green_factor = sin(time_elapsed * 0.001);
        double red_factor   = cos(time_elapsed * 0.001);
        double blue_factor  = sin(time_elapsed * 0.001 + M_PI/5);

        if (last_time == -1) last_time = time_elapsed;

        int interval = time_elapsed - last_time;

        last_time = time_elapsed;
        
        for (int i = 0; i < Swarm::NPARTICLES; ++i) {

            std::cout << "interval is: " << interval << std::endl;

            double speedx = particles[i].speed * cos(particles[i].direction) *interval; // mutliplying by elapsed time to ensure constant speed on different systems
            double speedy = particles[i].speed * sin(particles[i].direction) *interval;

            if((particles[i].x + speedx)*min_dim + SCREEN_WIDTH / 2  >= SCREEN_WIDTH || (particles[i].x + speedx)*min_dim + SCREEN_WIDTH / 2   <= 0) {
                // particles[i].x = 0;
                // particles[i].y = 0;
            }
            if((particles[i].y + speedy)*min_dim + SCREEN_HEIGHT / 2 >= SCREEN_HEIGHT || (particles[i].y + speedy)*min_dim + SCREEN_HEIGHT / 2 <= 0)
            {
                // particles[i].x = 0;
                // particles[i].y = 0;
            }

            double new_x = particles[i].x + speedx;
            double new_y = particles[i].y + speedy;

            particles[i].updateParticlePosition(new_x, new_y); 
            // // we need to set a pixel at this location
            // setPixelValue(particles[i].x * min_dim + SCREEN_WIDTH / 2, particles[i].y * min_dim + SCREEN_HEIGHT / 2, int(abs(red_factor) * 255), int(abs(green_factor) * 255), int(abs(blue_factor) * 255));
            setPixelValue(particles[i].x * min_dim + SCREEN_WIDTH / 2, particles[i].y * min_dim + SCREEN_HEIGHT / 2, 255, 255, 255);
        }
        // Update particles
        updateParticles();
        // Clear Buffer
        clearBuffer();
        // Check for messages/events
        if(breakLoopOnQuit(event)) break;
    }
}

bool FireExplosionParticleSystem::breakLoopOnQuit(SDL_Event& event) {
    
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT){
            return true;
        }
    }

    return false;
}

void FireExplosionParticleSystem::demoBasic(){
    /** SO FAR **
     * We need the following things
     * 1. need to initialize via SDL_Init(SDL_INIT_VIDEO) , destroy via SDL_Quit() 
     * 2. need to create a window SDL_CreateWindow(...), destroy via SDL_DestroyWindow
     * 3. need to create a renderer SDL_CreateRenderer(...), destroy via SDL_DestroyRenderer()
     * 4. need to create a texture SDL_CreateTexture(...), destroy via SDL_DestroyTexture()
     * 5. finally we also need to a create a buffer that will actually be filled by some pixel value
     */ 

    if(SDL_Init(SDL_INIT_VIDEO) < 0 ){ // initialize and check if initialzed or not!
        std::cout << "SDL Init Failed!" << std::endl;
        return;
    }
    
    window_ = SDL_CreateWindow("Fire Explosion Particle System", /* Window name */
                                           SDL_WINDOWPOS_UNDEFINED, /* window pos */
                                           SDL_WINDOWPOS_UNDEFINED, /* window pos */
                                           SCREEN_WIDTH, /* screen width */
                                           SCREEN_HEIGHT, /* screen height */
                                           SDL_WINDOW_SHOWN);
    // check if the window is null or not
    if(window_ ==  NULL) {
        std::cout << "Could not create window! " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Create the renderer
    renderer_ = SDL_CreateRenderer(window_,
                                  -1,
                                  SDL_RENDERER_PRESENTVSYNC /* syncs with the vertical refresh rate */
                                  );
    // Check for NULL
    if(renderer_ == NULL) {
        std::cout << "Could not create renderer! " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window_);
        SDL_Quit();
        return ;
    }

    // Create a texture
    texture_ = SDL_CreateTexture(renderer_,
                                 SDL_PIXELFORMAT_RGBA8888,/* uses one byte for each pixel*/
                                 SDL_TEXTUREACCESS_STATIC,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT);

    // Check for NULL
    if(texture_ == NULL) {
        std::cout << "Could not create texture! " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit(); 
        return ;
    }

    // Create Buffer using SDL uints
    // by default int is 32 bits, but it might differ on different machines
    // that is why we have a explicit type offered by SDL
    buffer_ = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; // remember to free this later on
    /** \TODO: take care of the case when memory allocation fails **/

    // Write something in the buffer using memset
    memset(buffer_, 0/*hex value*/ /*value,*/, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)/* no of bytes*/);
    // why hex? -->  gives more info about what goes into byte information

    buffer_[30000] = 0x0000FFFF;  //  the format is kinda  RR GG BB AA
    // might not be the same sequence , wierd kinda, but check out yourself, it indeed is
    // RR GG BB AA

    for(int i=0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i){
        buffer_[i] = 0xFFFF00FF; // setting all to some colour
    }
    
    SDL_UpdateTexture(texture_, NULL, buffer_, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer_); // basically clear the previous render info
    SDL_RenderCopy(renderer_, texture_, NULL, NULL);
    SDL_RenderPresent(renderer_);

    bool quit = false;
    SDL_Event event;
    // Game Loop thingy that will update the screen 
    while(!quit) {
        // Update particles
        // Draw particles
        // Check for messages/events
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // lets deallocate some resources here, can do all this stuff inside the
    // destructor or a destroy function later (ORDER is important, good to to do it like this, do not know
    // what happens if you do not do this)
    delete[] buffer_;
    SDL_DestroyTexture(texture_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_); // if window was created we will destroy it here
    SDL_Quit(); // to finally close the SDL
}

} //namespace particlesystem