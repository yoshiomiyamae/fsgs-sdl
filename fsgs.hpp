#pragma once
#include <iostream>
#include <filesystem>

#include <SDL.h>
#include <SDL_ttf.h>

#include "error.hpp"
#define FONT_PATH "Cica-Regular.ttf"
#define FPS 60.0
#define MS_PER_S 1000.0
#define MS_PER_FRAME (MS_PER_S / FPS)

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
    void fps();
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

    Uint64 m_lastTicks;
  };
}