#include "includify/includify.hpp"

#include <catch2/catch.hpp>

#include <string_view>

using Catch::Matchers::Equals;

SCENARIO("a string_view can be includified as a classic string", "[core][classic]")
{
    GIVEN("A default constructed string_view")
    {
        auto view = std::string_view{};

        WHEN("the view is includified as a classic string")
        {
            auto includified = includify::as_classic_string(view);

            THEN("it is equal to 'auto constexpr data = \"\";");
            {
                CHECK_THAT(includified, Equals("auto constexpr data = \"\";"));
            }
        }
    }
}