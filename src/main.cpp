#include "blemderer.h"

int main() {
    Blemderer blemderer;

    if (!blemderer.init()) {
        return 1;
    }

    blemderer.run();
    blemderer.cleanup();

    return 0;
}
