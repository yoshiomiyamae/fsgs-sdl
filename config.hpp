#include <SDL.h>
#include <string>
#include <yaml-cpp/yaml.h>

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
      std::stringstream ss(path);
      std::string key;
      YAML::Node node = YAML::Clone(m_config);
      while (std::getline(ss, key, '.'))
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