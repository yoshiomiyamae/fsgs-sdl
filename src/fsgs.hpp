#ifndef _FSGS_HPP_
#define _FSGS_HPP_

#include <iostream>
#include <filesystem>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "error.hpp"
#define FONT_PATH "Cica-Regular.ttf"

namespace FSGS {
  class Game {
    public:

      void init ();
      void cleanUp ();
      void event ();
      void update ();
      void render();
      void fps();
      void mainLoop ();

      const char* getSdlError();

      Game();
      ~Game();
    private:
      bool m_running;
      SDL_Window* m_window;
      SDL_Renderer* m_renderer;

      TTF_Font* m_font;
  };
}

#endif