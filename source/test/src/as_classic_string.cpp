#include "includify/includify.hpp"

#include "random_sequence.hpp"

#include <catch2/catch.hpp>

#include <string>
#include <string_view>

using Catch::Matchers::Equals;
using namespace std::literals;

SCENARIO("a string_view can be includified as a classic string", "[core][classic]")
{
    auto rng = includify::test::make_rng();

    GIVEN("A default constructed string_view")
    {
        auto view = std::string_view{};

        WHEN("the view is includified as a classic string")
        {
            auto includified = includify::as_classic_string(view);

            THEN("it is equal to 'auto constexpr data = \"\";")
            {
                CHECK_THAT(includified, Equals("auto constexpr data = \"\";"));
            }
        }
    }

    GIVEN("A random string")
    {
        auto string = includify::test::get_random_character_sequence(rng, 5);
        auto view = std::string_view{string};

        WHEN("a view of the string is includified as a classic string")
        {
            auto includified = includify::as_classic_string(view);

            THEN("the literal on the right hand side is the same string")
            {
                auto expected = "auto constexpr data = \"" + string + "\";";
                CHECK_THAT(includified, Equals(expected));
            }
        }
    }
}