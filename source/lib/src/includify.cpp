#include "includify/includify.hpp"

#include <fmt/format.h>

#include <string>
#include <string_view>

namespace includify
{

  namespace
  {
    auto constexpr classic_string_template = FMT_STRING("auto constexpr data = \"{}\";");
  }

  auto as_classic_string(std::string_view text) -> std::string
  {
    return fmt::format(classic_string_template, text);
  }

}  // namespace includify