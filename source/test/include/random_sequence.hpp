#ifndef INCLUDIFY_TEST_RANDOM_SEQUENCE_HPP
#define INCLUDIFY_TEST_RANDOM_SEQUENCE_HPP

#include <algorithm>
#include <array>
#include <iterator>
#include <random>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>

namespace includify::test
{

  namespace detail
  {
    auto constexpr character_set = std::string_view{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 "};
  }

  auto make_rng() -> std::mt19937
  {
    auto constexpr number_of_seeds = std::mt19937::state_size * sizeof(std::mt19937::result_type) + 1;

    auto random_source = std::random_device{};
    auto seed_view = std::views::iota(decltype(number_of_seeds){}, number_of_seeds) |
                     std::views::transform([&](auto) { return random_source(); });
    auto seeds = std::seed_seq(std::begin(seed_view), std::end(seed_view));
    return std::mt19937{seeds};
  }

  auto get_random_character_sequence(std::mt19937 & rng, std::size_t length) -> std::string
  {
    auto distribution = std::uniform_int_distribution{std::size_t{}, detail::character_set.size()};
    auto data_view = std::views::iota(std::size_t{}, length - 1) |
                     std::views::transform([&](auto) { return detail::character_set[distribution(rng)]; });

    auto sequence = std::string{};
    std::ranges::copy(data_view, back_inserter(sequence));
    return sequence;
  }

}  // namespace includify::test

#endif