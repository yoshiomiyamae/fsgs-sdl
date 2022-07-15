#include "fsgs.hpp"

namespace FSGS
{
  void Game::init()
  {
    try
    {
      auto cwd = std::filesystem::current_path();
      std::cout << "CWD: " << cwd << std::endl;
      if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
      {
        throw InitFailedException();
      }

      m_window = SDL_CreateWindow(
          "FSGS",
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          640,
          480,
          0);

      if (!m_window)
      {
        throw CreateWindowFailedException();
      }

      m_renderer = SDL_CreateRenderer(
          m_window,
          -1,
          SDL_RENDERER_ACCELERATED);

      if (!m_renderer)
      {
        throw CreateRendererFailedException();
      }

      if (TTF_Init() < 0)
      {
        throw InitFailedException();
      }

      m_font = TTF_OpenFont(
          FONT_PATH,
          40);

      if (!m_font)
      {
        throw CreatFontFailedException();
      }

      m_running = true;
    }
    catch (FSGS::Exception &e)
    {
      throw;
    }

    return;
  }

  void Game::renderText(std::string text, SDL_Color color, SDL_Point destination)
  {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(
        m_font,
        text.c_str(),
        color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(
        m_renderer,
        surface);
    int w;
    int h;
    if (SDL_QueryTexture(
            texture,
            NULL,
            NULL,
            &w,
            &h) < 0)
    {
      throw QueryTextureException();
    }
    SDL_Rect sourceRect = {0, 0, w, h};
    SDL_Rect destinationRect = {destination.x, destination.y, w, h};
    if (SDL_RenderCopy(
            m_renderer,
            texture,
            &sourceRect,
            &destinationRect) < 0)
    {
      throw RenderCopyException();
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
  }

  void Game::cleanUp()
  {
    TTF_Quit();
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }

  void Game::event()
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
      {
        m_running = false;
        break;
      }
      default:
      {
        break;
      }
      }
    }
  }

  void Game::update()
  {
    try
    {
      // Fill background
      if (SDL_SetRenderDrawColor(
              m_renderer,
              0x00,
              0x00,
              0x00,
              0xFF) < 0)
      {
        throw SetRenderDrawColorException();
      }

      if (SDL_RenderClear(m_renderer) < 0)
      {
        throw RenderClearException();
      }

      renderText("Hello, World!!", {0xFF, 0xFF, 0xFF, 0xFF}, {rand() % 640, rand() % 480});
    }
    catch (FSGS::Exception &e)
    {
      throw;
    }
  }

  void Game::render()
  {
    SDL_RenderPresent(m_renderer);
  }

  void Game::fps()
  {
    Uint64 ticks = SDL_GetTicks64();
    Uint64 duration = ticks - m_lastTicks;
    Uint8 fps = MS_PER_S / (double)(ticks - m_lastTicks);
    renderText(std::to_string(fps), {0x00, 0xFF, 0x00, 0x7F}, {0, 0});
    m_lastTicks = ticks;
    int waitTime = MS_PER_FRAME - duration;
    if (waitTime > 0)
    {
      SDL_Delay(waitTime);
    }
  }

  const std::string Game::getSdlError()
  {
    return (std::string)SDL_GetError();
  }

  void Game::mainLoop()
  {
    try
    {
      while (m_running)
      {
        event();
        update();
        fps();
        render();
      }
    }
    catch (FSGS::Exception &e)
    {
      throw;
    }
  }

  Game::Game()
      : m_lastTicks(0)
  {
    try
    {
      init();
    }
    catch (FSGS::Exception &e)
    {
      std::cerr << "Error: " << e.getError() << std::endl;
      std::cerr << e.getMessage() << std::endl;
      std::cerr << getSdlError() << std::endl;
      cleanUp();
      exit(1);
    }
  }

  Game::~Game()
  {
    cleanUp();
  }
}