// renderer.cpp — Implementation of the Renderer class

#include "renderer/renderer.h"

#include <algorithm>
#include <png.h>

namespace rengen {

Renderer::Renderer(int width, int height)
    : width_(width), height_(height), framebuffer_(static_cast<size_t>(width_) * static_cast<size_t>(height_)) {}

void Renderer::clear(Color color) {
    for (auto& pixel : framebuffer_) {
        pixel = color;
    }
}

void Renderer::present() {
    // Phase 2: hook up a display backend (SDL2, GLFW, raw X11, etc.)
    // For now this is a no-op — the framebuffer is read back to PNG.
}

bool Renderer::save_png(const std::string& filename) const {
    FILE* fp = std::fopen(filename.c_str(), "wb");
    if (!fp) {
        return false;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        std::fclose(fp);
        return false;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        std::fclose(fp);
        return false;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        std::fclose(fp);
        return false;
    }

    png_init_io(png, fp);

    // Write 8-bit RGBA, top-down row order
    png_set_IHDR(png, info, static_cast<png_uint_32>(width_), static_cast<png_uint_32>(height_),
                 8, PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png, info);

    // Convert float [0,1] Color → 8-bit RGBA row
    std::vector<uint8_t> row(static_cast<size_t>(width_) * 4);
    for (int y = 0; y < height_; ++y) {
        const Color* row_colors = &framebuffer_[static_cast<size_t>(y) * static_cast<size_t>(width_)];
        for (int x = 0; x < width_; ++x) {
            const Color& c = row_colors[x];
            size_t base = static_cast<size_t>(x) * 4;
            // Clamp to [0,1] then scale to [0,255]
            row[base + 0] = static_cast<uint8_t>(std::clamp(c.r, 0.0f, 1.0f) * 255.0f);
            row[base + 1] = static_cast<uint8_t>(std::clamp(c.g, 0.0f, 1.0f) * 255.0f);
            row[base + 2] = static_cast<uint8_t>(std::clamp(c.b, 0.0f, 1.0f) * 255.0f);
            row[base + 3] = static_cast<uint8_t>(std::clamp(c.a, 0.0f, 1.0f) * 255.0f);
        }
        png_write_row(png, row.data());
    }

    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    std::fclose(fp);
    return true;
}

}  // namespace rengen
