#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
// Tsoding [https://www.youtube.com/watch?v=qjWkNZ0SXfo]
// ======================
// Terminal control
// ======================
void term_init() {
    std::cout << "\033[?1049h"; // alternate screen
    std::cout << "\033[?25l";   // hide cursor
}

void term_shutdown() {
    std::cout << "\033[?25h";   // show cursor
    std::cout << "\033[?1049l"; // normal screen
}

void term_clear() {
    std::cout << "\033[H"; // cursor home
}

// ======================
// Math Types
// ======================
struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };

// ======================
// Math Functions
// ======================
Vec3 scaleUniform(Vec3 v, float s) {
    return { v.x * s, v.y * s, v.z * s };
}

Vec3 translate_z(Vec3 v, float dz) {
    return { v.x, v.y, v.z + dz };
}

Vec3 rotate_xz(Vec3 v, float a) {
    float c = std::cos(a), s = std::sin(a);
    return { v.x * c - v.z * s, v.y, v.x * s + v.z * c };
}

Vec3 rotate_yz(Vec3 v, float a) {
    float c = std::cos(a), s = std::sin(a);
    return { v.x, v.y * c - v.z * s, v.y * s + v.z * c };
}

Vec2 project(Vec3 v) {
    return { v.x / v.z, v.y / v.z };
}

Vec2 to_screen(Vec2 p, int w, int h) {
    return {
        (p.x + 1.f) * 0.5f * w,
        (1.f - (p.y + 1.f) * 0.5f) * h
    };
}

// ======================
// Framebuffer + Drawing
// ======================
// buf -> linear character framebuffer (w*h entries)
// w,h -> screen width and height
// a,b -> floating point endpoitns (already projected to screen space)
void draw_line(std::vector<char>& buf, int w, int h, Vec2 a, Vec2 b) {
    // Convert float coord to integer pixel coord
    // Bresenham works off of integers -1 to 1 or 1 to 2
    int x0 = int(a.x), y0 = int(a.y);
    int x1 = int(b.x), y1 = int(b.y);
    
    // Absolute vertical distance of the line
    int dx = std::abs(x1 - x0);     // x side
    int dy = -std::abs(y1 - y0);    // y side (- flip for proper direction)
    // Step direction for each axis [all 8 octants can be handled by the same code
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    // Error accumulator (core of Bresenham)
    // how far from ideal are we
    int err = dx + dy;

    // loop until we get to the end of the pixel
    while (true) {
        if (x0 >= 0 && x0 < w && y0 >= 0 && y0 < h)
            buf[y0 * w + x0] = '#';

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

// ======================
// Main
// ======================
int main() {
    constexpr int WIDTH = 80;
    constexpr int HEIGHT = 40;
    constexpr float FPS = 60.f;

    term_init();

    std::vector<Vec3> vs = {
        { 0.25f,  0.25f,  0.25f},
        {-0.25f,  0.25f,  0.25f},
        {-0.25f, -0.25f,  0.25f},
        { 0.25f, -0.25f,  0.25f},
        { 0.25f,  0.25f, -0.25f},
        {-0.25f,  0.25f, -0.25f},
        {-0.25f, -0.25f, -0.25f},
        { 0.25f, -0.25f, -0.25f},
    };

    std::vector<std::vector<int>> fs = {
        {0,1,2,3},
        {4,5,6,7},
        {0,4},
        {1,5},
        {2,6},
        {3,7}
    };

    float angle = 0.f;
    float dz = 2.f;

    while (true) {
        std::vector<char> buffer(WIDTH * HEIGHT, ' ');

        angle += M_PI / FPS;

        for (auto& f : fs) {
            for (size_t i = 0; i < f.size(); ++i) {
                Vec3 a = scaleUniform(vs[f[i]], 2.8f);
                Vec3 b = scaleUniform(vs[f[(i + 1) % f.size()]], 2.8f);

                Vec3 ta = rotate_yz(rotate_xz(a, angle), angle * 0.7f);
                Vec3 tb = rotate_yz(rotate_xz(b, angle), angle * 0.7f);

                Vec2 pa = to_screen(project(translate_z(ta, dz)), WIDTH, HEIGHT);
                Vec2 pb = to_screen(project(translate_z(tb, dz)), WIDTH, HEIGHT);

                draw_line(buffer, WIDTH, HEIGHT, pa, pb);
            }
        }

        term_clear();
        std::cout << "\033[32m"; // green
        for (int y = 0; y < HEIGHT; ++y) {
            std::cout.write(&buffer[y * WIDTH], WIDTH);
            std::cout << '\n';
        }
        std::cout << "\033[0m"; // reset
        std::cout.flush();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(int(1000 / FPS))
        );
    }

    term_shutdown();
}

