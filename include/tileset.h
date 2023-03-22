#include <SDL2/SDL.h>

#include <string>

class Tileset {
   public:
    std::string name;
    int firstGID;
    int tileWidth;
    int tileHeight;

    // optional?
    int spacing;
    int margin;

    int imageWidth;
    int imageHeight;

    std::string imageSource;

    SDL_Texture* texture;
};
