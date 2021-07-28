#include "algorithm_test.h"
#include "utility/algorithm.h"

namespace blurringshadow::test::utility
{
    boost::ut::suite& algorithm_test() noexcept
    {
        static boost::ut::suite suite = []() noexcept
        {
            using namespace std;
            using namespace boost::ut;
            using namespace bdd;
            using namespace blurringshadow::utility;

            feature("set_if") = []<auto First, auto Second>( // clang-format off
                const static_params<First, Second> 
            ) noexcept // clang-format on
            {
                given("given two values") = []() noexcept
                {
                    print(fmt::format("first value: {}, second value: {}", First, Second));

                    then("base on comparision result to set value") = []
                    {
                        constexpr auto order = std::partial_order(Second, First);
                        constexpr auto greater = order > 0;
                        constexpr auto less = order < 0;
                        constexpr auto f = [](const auto expect, auto&& func)
                        {
                            auto first = First;
                            return !(expect ^ (func(first, Second) == Second));
                        };

                        static_expect<f(greater, set_if_greater)>() << //
                            fmt::format(
                                "value should {} be set in set_if_greater",
                                greater ? "" : "not" //
                            );
                        static_expect<f(less, set_if_less)>() << //
                            fmt::format("value should {} be set in set_if_less", less ? "" : "not");
                    };
                }; // clang-format off
            } | std::tuple<static_params<1, 2>, static_params<2, 1>>{};
            // clang-format on


            feature("is_between") = []<auto Value, auto Min, auto Max>( // clang-format off
              const static_params<Value, Min, Max>
            ) noexcept // clang-format on
            {
                given("given three values") = []() noexcept
                {
                    print(fmt::format("value: {}, min value: {}, max value: {}", Value, Min, Max));
                    constexpr auto is_in_range = !(Value < Min) && !(Value > Max);
                    constexpr auto res = is_between(Value, Min, Max) == is_in_range;

                    then( // clang-format off
                            is_in_range ? 
                            "value should between min-max" :
                            "value should not between min-max" 
                    ) = &static_expect<res>;
                }; 
            } | std::tuple<
                static_params<1, 1, 2>,
                static_params<3, 2, 3>,
                static_params<4, 2, 4>,
                static_params<3, 5, 10>,
                static_params<10, -1, 9>,
                static_params<100u, 50l, 900ll>
            >{}; // clang-format on
        };

        return suite;
    }
}
