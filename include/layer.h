#include <string>
#include <vector>

class Layer {
   public:
    std::string name;
    int width;
    int height;
    float opacity;
    bool visible;
    std::vector<int> data;
};
