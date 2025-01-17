#include "stdsharp/functional/operations.h"
#include "stdsharp/functional/pipeable.h"
#include "test.h"

using namespace std;
using namespace fmt;
using namespace stdsharp;

SCENARIO("pipeable, [functional]") // NOLINT
{
    using left_pipeable_t = decltype(make_pipeable<>(identity_v));

    STATIC_REQUIRE(std::invocable<bit_or<>, int, left_pipeable_t>);
    STATIC_REQUIRE(!std::invocable<bit_or<>, left_pipeable_t, int>);

    using right_pipeable_t = decltype(make_pipeable<pipe_mode::right>(identity_v));

    STATIC_REQUIRE(!std::invocable<bit_or<>, int, right_pipeable_t>);
    STATIC_REQUIRE(std::invocable<bit_or<>, right_pipeable_t, int>);
}