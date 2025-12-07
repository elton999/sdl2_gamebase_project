#include <iostream>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "UmbrellaToolsKit/Core/Sprite.h"
#include "UmbrellaToolsKit/Core/ResourceManager.h"

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

    GLuint VertexBuffer;
    Uint32 frameStart;
    int frameTime;

    Sprite squareMesh = {};
    Texture2D *texture2D = ResourceManager::LoadTexture2D("content/texture.png");

    if (!texture2D)
    {
        cout << "Failed to load texture 'content/texture.png'" << endl;
    }

    // Enable alpha blending for textures with transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set an orthographic projection and configure shader sampler
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, -1.0f, 1.0f);
    if (squareMesh.GetShader())
    {
        squareMesh.GetShader()->Use();
        squareMesh.GetShader()->SetInt("image", 0);
        squareMesh.GetShader()->SetMatrix4("projection", projection);
    }

    while (!Loop())
    {
        frameStart = SDL_GetTicks();

        ClearRender();

        Update();
        squareMesh.DrawSprite(*texture2D, glm::vec2(0.0f, 0.0f), glm::vec2((float)texture2D->GetWidth(), (float)texture2D->GetHight()), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
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