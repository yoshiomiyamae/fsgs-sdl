#include <string>

namespace FSGS
{
  template <typename Cont, typename Pred>
  Cont filter(const Cont &container, Pred predicate)
  {
    Cont result;
    std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
    return result;
  }

  template <typename Cont, typename Ret>
  Ret get(const Cont &container, std::string key, Ret default)
  {
    auto ret = container.find(key);
    if (ret == container.end())
    {
      return default;
    }
    return std::any_cast<const Ret &>(ret->second);
  }
}