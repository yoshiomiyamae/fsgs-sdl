#include "fsgs.hpp"

namespace FSGS {
  void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      throw InitFailedException();
    }

    m_window = SDL_CreateWindow(
      "FSGS",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      0
    );

    if (!m_window) {
      throw CreateWindowFailedException();
    }

    m_renderer = SDL_CreateRenderer(
      m_window,
      -1,
      SDL_RENDERER_ACCELERATED
    );

    if (!m_renderer) {
      throw CreateRendererFailedException();
    }

    TTF_Init();

    m_font = TTF_OpenFont(
      FONT_PATH,
      40
    );

    if (!m_font) {
      throw CreatFontFailedException();
    }

    m_running = true;

    return;
  }

  void Game::cleanUp() {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }

  void Game::event() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
      switch (event.type)
      {
        case SDL_QUIT: {
          m_running = false;
          break;
        }
        default: {
          break;
        }
      }
    }
  }

  void Game::update() {
  }

  void Game::render() {
    SDL_SetRenderDrawColor(
      m_renderer,
      0x00,
      0x00,
      0x00,
      0xFF
    );
    SDL_RenderClear(m_renderer);

    SDL_Color fontColor = {0xFF, 0xFF, 0xFF, 0xFF};
    SDL_Surface* surface = TTF_RenderUTF8_Blended(
      m_font,
      "Hello, World!!",
      fontColor
    );
    SDL_Texture* texture = SDL_CreateTextureFromSurface(
      m_renderer,
      surface
    );
    int w;
    int h;
    SDL_QueryTexture(
      texture,
      NULL,
      NULL,
      &w,
      &h
    );
    SDL_Rect sourceRect = {0, 0, w, h};
    SDL_Rect destinationRect = {200, 200, w, h};
    SDL_RenderCopy(
      m_renderer,
      texture,
      &sourceRect,
      &destinationRect
    );

    SDL_RenderPresent(m_renderer);
  }

  void Game::fps() {
    SDL_Delay(1);
  }

  const char * Game::getSdlError() {
    return SDL_GetError();
  }

  void Game::mainLoop() {
    while (m_running) {
      event();
      update();
      render();
      fps();
    }
  }

  Game::Game() {
    init();
  }

  Game::~Game() {
    cleanUp();
  }
}