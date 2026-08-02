// renderer.h — Core rendering surface and pipeline entry point

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace rengen {

/// A HDR-capable RGBA color with float components in [0, 1].
/// Using float internally avoids clamping issues during blending,
/// lighting accumulation, and tone mapping. Conversion to 8-bit
/// happens only at the final PNG write.
struct Color {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 1.0f;

    Color() = default;
    Color(float r, float g, float b, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}

    // Arithmetic helpers — useful for shading math
    Color operator+(const Color& other) const {
        return {r + other.r, g + other.g, b + other.b, a + other.a};
    }
    Color operator*(float scalar) const {
        return {r * scalar, g * scalar, b * scalar, a * scalar};
    }
};

/// The main renderer object. Holds a framebuffer and provides basic
/// operations: clearing, presenting (no-op placeholder), and PNG export.
class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    /// Fill every pixel with a solid color.
    void clear(Color color);

    /// Flush framebuffer to display or swapchain. (No-op in Phase 1.)
    void present();

    /// Write the framebuffer to a PNG file.
    bool save_png(const std::string& filename) const;

    int width() const { return width_; }
    int height() const { return height_; }
    const std::vector<Color>& framebuffer() const { return framebuffer_; }

private:
    int width_;
    int height_;
    std::vector<Color> framebuffer_;
};

}  // namespace rengen
