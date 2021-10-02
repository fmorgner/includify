#ifndef INCLUDIFY_INCLUDIFY_HPP
#define INCLUDIFY_INCLUDIFY_HPP

#include <string>
#include <string_view>

namespace includify
{

  /**
   * @brief Generate a defintio
   * 
   * @param text 
   * @return std::string 
   */
  auto as_classic_string(std::string_view text) -> std::string;

}

#endif