#pragma once
#include <iostream>
#include <filesystem>

#include <SDL.h>
#include <SDL_ttf.h>

#include "error.hpp"
#define FONT_PATH "Cica-Regular.ttf"
#define FPS 60.0

namespace FSGS
{
  class Game
  {
  public:
    void init();
    void cleanUp();
    void event();
    void update();
    void render();
    void fps(double duration);
    void mainLoop();

    const std::string getSdlError();

    void renderText(std::string text, SDL_Color color, SDL_Point destination);

    Game();
    ~Game();

  private:
    bool m_running;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    TTF_Font *m_font;

    Uint64 m_performanceFrequency;
    Uint64 m_countPerFrame;
    Uint64 m_lastTicks;
  };
}