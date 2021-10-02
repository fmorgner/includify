#ifndef INCLUDIFY_INCLUDIFY_HPP
#define INCLUDIFY_INCLUDIFY_HPP

#include <string>
#include <string_view>

namespace includify
{

  /**
   * @brief Generate a definition for a classic (or C-like) string
   * 
   * @param text The text data to generate an instance for
   * @return std::string the generated string
   */
  auto as_classic_string(std::string_view text) -> std::string;

}

#endif