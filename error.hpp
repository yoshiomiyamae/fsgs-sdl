#pragma once

#include <string>
#include <exception>

namespace FSGS
{
#define Error unsigned int
#define ERROR_INIT_FAILED 0x00000001u
#define ERROR_CREATE_WINDOW_FAILED 0x00000002u
#define ERROR_CREATE_RENDERER_FAILED 0x00000004u
#define ERROR_CREATE_FONT_FAILED 0x00000008u
#define ERROR_SET_RENDER_DRAW_COLOR 0x00000010u
#define ERROR_RENDER_CLEAR 0x00000020u
#define ERROR_QUERY_TEXTURE 0x00000040u
#define ERROR_RENDER_COPY 0x00000080u

  class Exception
  {
  public:
    Exception(
        Error error);
    Exception(
        Error error,
        std::string message);
    ~Exception();

    Error getError();
    std::string getMessage();

  protected:
    Exception();
    Error m_error;
    std::string m_message;
  };

  class InitFailedException : public Exception
  {
  public:
    InitFailedException() {}
    ~InitFailedException() {}

  private:
    Error m_error = ERROR_INIT_FAILED;
    std::string m_message = "FSGS Initialization failed.";
  };

  class CreateWindowFailedException : public Exception
  {
  public:
    CreateWindowFailedException() {}
    ~CreateWindowFailedException() {}

  private:
    Error m_error = ERROR_CREATE_WINDOW_FAILED;
    std::string m_message = "FSGS Create window failed.";
  };

  class CreateRendererFailedException : public Exception
  {
  public:
    CreateRendererFailedException() {}
    ~CreateRendererFailedException() {}

  private:
    Error m_error = ERROR_CREATE_RENDERER_FAILED;
    std::string m_message = "FSGS Create renderer failed.";
  };

  class CreatFontFailedException : public Exception
  {
  public:
    CreatFontFailedException() {}
    ~CreatFontFailedException() {}

  private:
    Error m_error = ERROR_CREATE_FONT_FAILED;
    std::string m_message = "FSGS Create font failed.";
  };

  class SetRenderDrawColorException : public Exception
  {
  public:
    SetRenderDrawColorException() {}
    ~SetRenderDrawColorException() {}

  private:
    Error m_error = ERROR_SET_RENDER_DRAW_COLOR;
    std::string m_message = "FSGS set render draw color failed.";
  };

  class RenderClearException : public Exception
  {
  public:
    RenderClearException() {}
    ~RenderClearException() {}

  private:
    Error m_error = ERROR_RENDER_CLEAR;
    std::string m_message = "FSGS render clear failed.";
  };

  class QueryTextureException : public Exception
  {
  public:
    QueryTextureException() {}
    ~QueryTextureException() {}

  private:
    Error m_error = ERROR_QUERY_TEXTURE;
    std::string m_message = "FSGS query texture failed.";
  };

  class RenderCopyException : public Exception
  {
  public:
    RenderCopyException() {}
    ~RenderCopyException() {}

  private:
    Error m_error = ERROR_RENDER_COPY;
    std::string m_message = "FSGS render copy failed.";
  };
}