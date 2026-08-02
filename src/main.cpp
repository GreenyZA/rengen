// rengen — CPU-based 3D graphics rendering engine
// Entry point for Phase 1: image output via PNG

#include <cstdio>
#include <cstdlib>

#include "renderer/renderer.h"

int main(int argc, char* argv[]) {
    const int width = 800;
    const int height = 600;

    rengen::Renderer renderer(width, height);

    // Phase 1: solid color to verify the pipeline
    renderer.clear({0.2f, 0.3f, 0.5f, 1.0f});
    renderer.present();

    const char* filename = (argc > 1) ? argv[1] : "output.png";
    if (!renderer.save_png(filename)) {
        std::fprintf(stderr, "Failed to write %s\n", filename);
        return EXIT_FAILURE;
    }

    std::printf("Wrote %s (%d x %d)\n", filename, width, height);
    return EXIT_SUCCESS;
}
