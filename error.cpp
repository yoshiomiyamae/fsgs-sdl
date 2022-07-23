#include "error.hpp"

namespace FSGS
{
  Exception::Exception()
  {
    m_error = 0;
    m_message = "";
  }

  Exception::Exception(Error error)
  {
    m_error = error;
    m_message = "";
  }

  Exception::~Exception()
  {
  }

  Error Exception::getError()
  {
    return m_error;
  }

  std::string Exception::getMessage()
  {
    return m_message;
  }
}