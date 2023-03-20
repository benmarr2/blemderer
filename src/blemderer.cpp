#include "blemderer.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "settings.h"

Blemderer::Blemderer() = default;

bool Blemderer::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    const int defaultWindowWidth = 1920;
    const int defaultWindowHeight = 1080;

    window_ = SDL_CreateWindow("Blemderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               defaultWindowWidth, defaultWindowHeight, SDL_WINDOW_OPENGL);

    if (window_ == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
        return false;
    }

    gl_context_ = SDL_GL_CreateContext(window_);
    SDL_GL_MakeCurrent(window_, gl_context_);
    SDL_GL_SetSwapInterval(1);  // Enable vsync

    bool err = glewInit() != GLEW_OK;
    if (err) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize GLEW: %s",
                     glewGetErrorString(static_cast<GLenum>(err)));
        return false;
    }

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window_, gl_context_);
    ImGui_ImplOpenGL3_Init("#version 130");

    return true;
}

void Blemderer::handleEvent(SDL_Event& event) {
    ImGui_ImplSDL2_ProcessEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            quit_ = true;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                int newWidth = 0;
                int newHeight = 0;
                SDL_GetWindowSize(window_, &newWidth, &newHeight);
            }
            break;
    }
}

void Blemderer::renderFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window_);
    ImGui::NewFrame();

    ShowSettingsMenu(window_, nullptr);

    ImGui::Render();
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window_);
}

void Blemderer::run() {
    SDL_Event event;

    while (!quit_) {
        while (SDL_PollEvent(&event) != 0) {
            handleEvent(event);
        }

        renderFrame();
    }
}

void Blemderer::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context_);
    SDL_DestroyWindow(window_);
}
