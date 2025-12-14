#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

// ---------- Shader helpers ----------
GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cerr << "Shader error:\n" << log << std::endl;
        exit(1);
    }
    return shader;
}

GLuint makeProgram(const char* vs, const char* fs) {
    GLuint p = glCreateProgram();
    glAttachShader(p, compileShader(GL_VERTEX_SHADER, vs));
    glAttachShader(p, compileShader(GL_FRAGMENT_SHADER, fs));
    glLinkProgram(p);
    return p;
}

// ---------- Simple texture loader (PNG) ----------
GLuint loadTexture(const char* path) {
    SDL_Surface* surf = IMG_Load(path);
    if (!surf) {
        std::cerr << "IMG_Load failed: " << IMG_GetError() << std::endl;
        exit(1);
    }

    GLenum format = (surf->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(
        GL_TEXTURE_2D, 0, format,
        surf->w, surf->h, 0,
        format, GL_UNSIGNED_BYTE, surf->pixels
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surf);
    return tex;
}


// ---------- Shaders ----------
const char* vertexShader = R"(
#version 330 core
layout(location = 0) in vec2 pos;
out vec2 uv;

void main() {
    uv = pos * 0.5 + 0.5;
    gl_Position = vec4(pos, 0.0, 1.0);
}
)";

const char* fragmentShader = R"(
#version 330 core
in vec2 uv;
out vec4 frag;

uniform sampler2D earthTex;
uniform sampler2D skyTex;
uniform float angle;
uniform vec2 resolution;

void main() {
    // Background
    vec3 color = texture(skyTex, uv).rgb;

    // Sphere setup
    vec2 p = (gl_FragCoord.xy - resolution * 0.5) / (min(resolution.x, resolution.y) * 0.5);
    float r2 = dot(p, p);

    if (r2 <= 1.0) {
        float z = sqrt(1.0 - r2);

        // Rotate around Y axis
        float x =  cos(angle) * p.x + sin(angle) * z;
        float y =  p.y;
        float z2 = -sin(angle) * p.x + cos(angle) * z;

        float lon = atan(z2, x);
        float lat = asin(y);

        vec2 texUV;
        texUV.x = (-lon + 3.14159265) / (2.0 * 3.14159265);
        texUV.y = 1.0 - (0.5 + lat / 3.14159265);

        color = texture(earthTex, texUV).rgb;
    }

    frag = vec4(color, 1.0);
}
)";

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = SDL_CreateWindow(
        "Spinning Earth",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    SDL_MaximizeWindow(win);


    SDL_GLContext ctx = SDL_GL_CreateContext(win);
    glewInit();

    GLuint prog = makeProgram(vertexShader, fragmentShader);

    // Fullscreen quad
    float quad[] = {
        -1, -1,  1, -1,  -1, 1,
        -1,  1,  1, -1,   1, 1
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    GLuint earth = loadTexture("earth_small.png");
    GLuint sky   = loadTexture("skymap_small.png");

    glUseProgram(prog);
    glUniform1i(glGetUniformLocation(prog, "earthTex"), 0);
    glUniform1i(glGetUniformLocation(prog, "skyTex"),   1);

    bool running = true;
    float angle = 0.0f;
    float spinRate = 0.5f;   // radians per second

    Uint64 last = SDL_GetPerformanceCounter();
    Uint64 freq = SDL_GetPerformanceFrequency();
    int frames = 0;
    double fpsTimer = 0.0;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_UP)
                    spinRate += 0.1f;
                if (e.key.keysym.sym == SDLK_DOWN)
                    spinRate -= 0.1f;

                spinRate = std::clamp(spinRate, -5.0f, 5.0f);
            }

        }

        Uint64 now = SDL_GetPerformanceCounter();
        float dt = (now - last) / (float)freq;
        last = now;

        angle -= dt * spinRate;

        fpsTimer += dt;
        frames++;
        if (fpsTimer >= 1.0) {
            std::string title = "Spinning Earth - FPS: " + std::to_string(frames) + " || Spin: " + std::to_string(spinRate);
            SDL_SetWindowTitle(win, title.c_str());
            fpsTimer = 0.0;
            frames = 0;
        }

        int w, h;
        SDL_GetWindowSize(win, &w, &h);
        glViewport(0, 0, w, h);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(prog);
        glUniform1f(glGetUniformLocation(prog, "angle"), angle);
        glUniform2f(glGetUniformLocation(prog, "resolution"), (float)w, (float)h);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, earth);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, sky);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        SDL_GL_SwapWindow(win);
    }

    SDL_Quit();
    return 0;
}

