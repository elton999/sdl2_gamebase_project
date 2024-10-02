#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

const Uint32 fps = 60;
const Uint32 frameDelay = 1000 / fps;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

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
        SDL_RenderPresent(renderer);

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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
    SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
    SDL_RenderClear(renderer);
}

void KillWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}