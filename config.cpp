#include "config.hpp"

namespace FSGS
{
  Config *Config::m_instance = NULL;

  Config *Config::getInstance()
  {
    if (!m_instance)
    {
      m_instance = new Config;
      m_instance->load();
    }
    return m_instance;
  }

  void Config::cleanUp()
  {
    if (m_instance)
    {
      delete m_instance;
      m_instance = NULL;
    }
  }

  void Config::load()
  {
    m_config = YAML::LoadFile("config.yaml");
  }
}