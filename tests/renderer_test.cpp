// renderer_test.cpp — Unit tests for the Renderer

#include "external/catch_amalgamated.hpp"
#include "renderer/renderer.h"

using rengen::Color;
using rengen::Renderer;

TEST_CASE("Renderer constructor sets dimensions", "[renderer]") {
    Renderer r(640, 480);
    REQUIRE(r.width() == 640);
    REQUIRE(r.height() == 480);
    REQUIRE(r.framebuffer().size() == 640 * 480);
}

TEST_CASE("Renderer clear fills framebuffer with solid color", "[renderer]") {
    Renderer r(10, 10);
    r.clear({0.4f, 0.5f, 0.6f, 1.0f});

    for (const Color& px : r.framebuffer()) {
        REQUIRE(px.r == 0.4f);
        REQUIRE(px.g == 0.5f);
        REQUIRE(px.b == 0.6f);
        REQUIRE(px.a == 1.0f);
    }
}

TEST_CASE("Color arithmetic operators", "[renderer]") {
    Color a(0.5f, 0.5f, 0.5f, 1.0f);
    Color b(0.2f, 0.2f, 0.2f, 1.0f);

    Color sum = a + b;
    REQUIRE(sum.r == 0.7f);
    REQUIRE(sum.g == 0.7f);

    Color scaled = a * 2.0f;
    REQUIRE(scaled.r == 1.0f);
    REQUIRE(scaled.b == 1.0f);
}
