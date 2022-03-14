#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>
#include <exception>

namespace FSGS {
  #define Error                         unsigned int
  #define ERROR_INIT_FAILED             0x00000001u
  #define ERROR_CREATE_WINDOW_FAILED    0x00000002u
  #define ERROR_CREATE_RENDERER_FAILED  0x00000004u
  #define ERROR_CREATE_FONT_FAILED      0x00000008u

  class Exception {
    public:
      Exception(
        Error error
      );
      Exception(
        Error error,
        std::string message
      );
      ~Exception();

      Error getError();
      std::string getMessage();
    protected:
      Exception();
      Error m_error;
      std::string m_message;
  };

  class InitFailedException: public Exception {
    public:
      InitFailedException();
      ~InitFailedException();
  };

  class CreateWindowFailedException: public Exception {
    public:
      CreateWindowFailedException();
      ~CreateWindowFailedException();
  };

  class CreateRendererFailedException: public Exception {
    public:
      CreateRendererFailedException();
      ~CreateRendererFailedException();
  };

  class CreatFontFailedException: public Exception {
    public:
      CreatFontFailedException();
      ~CreatFontFailedException();
  };
}

#endif