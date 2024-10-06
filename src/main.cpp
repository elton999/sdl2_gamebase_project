#include <iostream>
#include <array>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

using namespace std;

const Uint32 fps = 60;
const Uint32 frameDelay = 1000 / fps;

SDL_Window *window = NULL;
SDL_GLContext renderer = NULL;

bool InitWindow();
bool Loop();
void Update();
void Render();
void ClearRender();
void KillWindow();

int main(int argc, char **args)
{
    if (!InitWindow())
    {
        return 1;
    }

    std::array<glm::vec3, 3> Triangle = {
        glm::vec3{-1.0f, -1.0f, 0.0f},
        glm::vec3{1.0f, -1.0f, 0.0f},
        glm::vec3{0.0f, 1.0f, 0.0f},
    };
    GLuint VertexBuffer;

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle.data(), GL_STATIC_DRAW);

    bool running = true;
    Uint32 frameStart;
    int frameTime;

    while (!Loop())
    {
        frameStart = SDL_GetTicks();

        ClearRender();

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
        glVertexAttribPointer(0, Triangle.size(), GL_FLOAT, GL_FALSE, 0, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, Triangle.size());
        glDisableVertexAttribArray(0);

        Update();
        Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    KillWindow();
    return 0;
}

bool InitWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("window title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!window)
    {
        cout << "Error creating window: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_GL_CreateContext(window);
    if (!renderer)
    {
        cout << "Error creating renderer: " << SDL_GetError() << endl;
        return false;
    }

    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }

    if (glewInit() != GLEW_OK)
    {
        cout << "Erro ao inicializar o GLEW" << endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    GLint GLMajorVersion = 0;
    GLint GLMinorVersion = 0;

    glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);

    cout << "OpenGL version " << GLMajorVersion << "." << GLMinorVersion << endl;

    glViewport(0, 0, 800, 800);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    return true;
}

bool Loop()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        return event.type == SDL_QUIT;
    }

    return false;
}

void Update()
{
}

void Render()
{
    SDL_GL_SwapWindow(window);
}

void ClearRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void KillWindow()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}