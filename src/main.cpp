#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

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
    ClearRender();

    bool running = true;
    Uint32 frameStart;
    int frameTime;

    while (!Loop())
    {
        frameStart = SDL_GetTicks();

        Update();
        Render();
        ClearRender();

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
}

void ClearRender()
{
    glViewport(0, 0, 800, 800);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

void KillWindow()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}