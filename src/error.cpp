#include "error.hpp"

namespace FSGS {
  Exception::Exception() {
    m_error = 0;
    m_message = "";
  }

  Exception::Exception(Error error) {
    m_error = error;
    m_message = "";
  }

  Exception::~Exception() {

  }

  Error Exception::getError() {
    return m_error;
  }

  std::string Exception::getMessage() {
    return m_message;
  }

  InitFailedException::InitFailedException() {
    m_error = ERROR_INIT_FAILED;
    m_message = "FSGS Initialization failed.";
  }

  InitFailedException::~InitFailedException() {

  }

  CreateWindowFailedException::CreateWindowFailedException() {
    m_error = ERROR_CREATE_WINDOW_FAILED;
    m_message = "FSGS Create window failed.";
  }

  CreateWindowFailedException::~CreateWindowFailedException() {

  }

  CreateRendererFailedException::CreateRendererFailedException() {
    m_error = ERROR_CREATE_RENDERER_FAILED;
    m_message = "FSGS Create renderer failed.";
  }

  CreateRendererFailedException::~CreateRendererFailedException() {

  }

  CreatFontFailedException::CreatFontFailedException() {
    m_error = ERROR_CREATE_FONT_FAILED;
    m_message = "FSGS Create font failed.";
  }

  CreatFontFailedException::~CreatFontFailedException() {

  }
}