#include "includify/includify.hpp"

#include <string>
#include <string_view>

namespace includify
{

  auto as_classic_string(std::string_view text) -> std::string
  {
    static_cast<void>(text);

    return R"(auto constexpr data = "";)";
  }

}  // namespace includify