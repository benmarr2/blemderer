#include "settings.h"
#include "imgui.h"
#include "video_settings.h"
#include <SDL2/SDL.h>

void ShowSettingsMenu(SDL_Window *window, SDL_Renderer *renderer) {
  ImGui::Begin("Settings");

  ShowVideoSettings(window, renderer);

  ImGui::End();
}
