#include "video_settings.h"

#include <SDL_video.h>

#include "imgui.h"

void ShowVideoSettings(SDL_Window *window, SDL_Renderer *renderer) {
    ImGui::Begin("Settings");

    static bool fullscreen = false;
    static bool last_fullscreen_state = fullscreen;
    static int current_resolution = 0;
    const char *resolutions[] = {"800x600", "1024x768", "1280x720", "1920x1080", "3440x1440"};

    if (ImGui::Combo("Resolution", &current_resolution, resolutions, IM_ARRAYSIZE(resolutions))) {
        int new_width, new_height;
        if (sscanf(resolutions[current_resolution], "%dx%d", &new_width, &new_height) != 2) {
            return;
        }
        SDL_SetWindowSize(window, new_width, new_height);
        SDL_RenderSetLogicalSize(renderer, new_width, new_height);
    }

    ImGui::Checkbox("fullscreen", &fullscreen);

    if (fullscreen != last_fullscreen_state) {
        if (fullscreen) {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        } else {
            SDL_SetWindowFullscreen(window, 0);
        }
        last_fullscreen_state = fullscreen;
    }

    ImGui::End();
}
