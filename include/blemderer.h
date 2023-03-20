#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

class Blemderer {
   public:
    Blemderer();
    bool init();
    void renderFrame();
    void handleEvent(SDL_Event& event);
    void run();
    void cleanup();

   private:
    SDL_Window* window_{};
    SDL_GLContext gl_context_{};
    bool quit_{false};
};
