# rengen — CPU 3D Graphics Rendering Engine

> A from-scratch, CPU-only 3D renderer written in C++20, built as a self-enrichment project.
> Mentors: AI pair (James Bland) + human. Built for learning lighting, reflections, and deep shadows.

## Philosophy

This is **not** a production engine. Every critical piece — math, rasterization, shading —
is implemented from scratch so you understand how it works under the hood. We start simple
and layer complexity one phase at a time.

## Project Phases

| Phase | Goal | Status |
|-------|------|--------|
| 1 | Build system, framebuffer, PNG output | ✅ Done |
| 2 | 3D math library (vectors, matrices, transforms) | 🚧 Next |
| 3 | Mesh loading and a basic OBJ parser | ⬜ |
| 4 | Software rasterization (scanline/pixel pipeline) | ⬜ |
| 5 | Shading pipeline (vertex + pixel/fragment shaders) | ⬜ |
| 6 | Phong/Blinn-Phong lighting model | ⬜ |
| 7 | Texture mapping (UV interpolation) | ⬜ |
| 8 | Reflection and refraction (ray-traced secondary rays) | ⬜ |
| 9 | Deep shadows (shadow mapping / ray-traced shadows) | ⬜ |
| 10 | Anti-aliasing (MSAA / supersampling) | ⬜ |

## Quick Start

```bash
# Prerequisites (Arch Linux)
sudo pacman -S cmake gcc libpng

# Or on Ubuntu/Debian
sudo apt install cmake g++ libpng-dev

# Fetch Catch2 single-header for tests
mkdir -p tests/external
curl -L -o tests/external/catch_amalgamated.hpp \
  https://raw.githubusercontent.com/catchorg/Catch2/v3.7.1/single_include/catch_amalgamated.hpp

cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Run the renderer
./build/bin/rengen output.png

# Run tests
./build/bin/rengen_tests
```

## Architecture

```
src/
├── main.cpp           # Entry point
├── math/              # Vector/Matrix/Quaternion types (Phase 2)
├── renderer/          # Framebuffer, pipeline, rasterizer
└── scene/             # Meshes, cameras, lights (Phase 3+)

tests/
├── test_main.cpp      # Catch2 bootstrap
└── renderer_test.cpp  # TDD tests for renderer
```

## License

MIT — see [LICENSE](LICENSE).
