#pragma once

#include <algorithm>
#include <stdexcept>

#ifndef NDEBUG
    #include <fmt/format.h>
#endif

#include "functional.h"
#include "utility/cassert.h"

namespace stdsharp::utility
{
    // clang-format off
    inline constexpr auto set_if = []<typename T, typename U, ::std::predicate<T, U> Comp>(
        T& left,
        U&& right,
        Comp comp = {}
    ) noexcept(
        ::stdsharp::utility::nothrow_invocable_r<bool, Comp, U&, T&> &&
        ::stdsharp::utility::nothrow_assignable_from<T, U>
    ) -> T&
    {
        // clang-format on
        if(::std::invoke(::std::move(comp), right, left)) left = ::std::forward<U>(right);
        return left;
    };

    inline constexpr auto set_if_greater = []<typename T, typename U>(T& left, U&& right) //
        noexcept( //
            noexcept( //
                ::stdsharp::utility::set_if(
                    left,
                    ::std::forward<U>(right),
                    ::stdsharp::utility::greater_v // clang-format off
                )
            )
        ) -> T& // clang-format on
    {
        return ::stdsharp::utility::set_if(
            left, ::std::forward<U>(right), ::stdsharp::utility::greater_v //
        ); //
    };

    inline constexpr auto set_if_less = []<typename T, typename U>(T& left, U&& right) //
        noexcept( //
            noexcept( //
                ::stdsharp::utility::set_if(
                    left,
                    ::std::forward<U>(right),
                    ::stdsharp::utility::less_v // clang-format off
                )
            )
        ) -> T& // clang-format on
    {
        return ::stdsharp::utility::set_if(left, ::std::forward<U>(right), less_v); //
    };

    namespace details
    {
        struct is_between_fn
        {
            template<
                typename T,
                typename Min,
                typename Max,
                typename Proj // clang-format off
            > // clang-format on
            struct require
            {
                using proj_t = ::std::invoke_result_t<Proj, T>;
                using proj_min = ::std::invoke_result_t<Proj, Min>;
                using proj_max = ::std::invoke_result_t<Proj, Max>;

                template<typename Compare>
                    requires ::std::predicate<Compare, const proj_t, const proj_min> &&
                        ::std::predicate<Compare, const proj_max, const proj_t> &&
                        ::std::predicate<Compare, const proj_max, const proj_min>
                static constexpr bool nothrow_v = !::stdsharp::utility::is_debug &&
                    ::stdsharp::utility::
                        nothrow_predicate<Compare, const proj_t, const proj_min> && //
                    ::stdsharp::utility::
                        nothrow_predicate<Compare, const proj_max, const proj_t> && //
                    ::stdsharp::utility::
                        nothrow_predicate<Compare, const proj_max, const proj_min> //

                    ;
            };
        };
    }

    // clang-format off
    inline constexpr ::stdsharp::utility::nodiscard_invocable_obj is_between{
        []< // clang-format on
        typename T,
        typename U,
        typename V,
        typename Compare = ::std::ranges::less,
        typename Proj = ::std::identity,
        auto noexcept_ = ::stdsharp::utility::details:: // clang-format off
                is_between_fn::require<T, U, V, Proj>::template nothrow_v<Compare>
        >
        (
            T&& v,
            U&& min,
            V&& max,
            Compare cmp = {},
            Proj proj = {}
        ) noexcept(noexcept_)
        {
            using traits = ::stdsharp::utility::details::
                is_between_fn::require<T, U, V, Proj>;

            const auto& projected_v = ::std::invoke(proj, ::std::forward<T>(v));
            const auto& projected_min = ::std::invoke(proj, ::std::forward<U>(min));
            const auto& projected_max = ::std::invoke(proj, ::std::forward<V>(max));

            if constexpr(::stdsharp::utility::is_debug)
                if(::stdsharp::utility::invoke_r<bool>(cmp, projected_max, projected_min))
                {
                    if constexpr(
                        ::fmt::formattable<typename traits::proj_min>::value &&
                        ::fmt::formattable<typename traits::proj_max>::value
                    ) throw ::std::invalid_argument{
                        ::fmt::format(
                            "projected max value {} "
                            "should not less than projected min value {}",
                            projected_max,
                            projected_min
                        )
                    };
                    else throw ::std::invalid_argument{
                        "projected max value should not less than projected min value"
                    };
                }

            return !::stdsharp::utility::invoke_r<bool>(cmp, projected_v, projected_min) &&
                !::stdsharp::utility::invoke_r<bool>(cmp, projected_max, projected_v);
        }
    }; // clang-format on
}
