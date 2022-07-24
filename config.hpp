#include <SDL.h>
#include <string>
#include <yaml-cpp/yaml.h>
#include "common.hpp"

namespace FSGS
{
  class Config
  {
  public:
    static Config *getInstance();
    static void cleanUp();

    template <typename T>
    T get(std::string path)
    {
      YAML::Node node = YAML::Clone(m_config);
      for (std::string key : split(path, '.'))
      {
        node = node[key];
      }
      return node.as<T>();
    }

  private:
    void load();
    YAML::Node m_config;

  protected:
    static Config *m_instance;
  };
}