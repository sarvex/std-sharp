#pragma once
#include <boost/ut.hpp>
#include <fmt/format.h>

template<auto...>
struct static_params
{
};

namespace boost::inline ext::ut
{
    namespace details
    {
        template<typename T>
        concept ut_expectable = requires(T v)
        {
            expect(v);
        };
    }

    template<auto Value>
    auto static_expect()
    {
        // clang-format off
        if constexpr(details::ut_expectable<decltype(Value)>) return expect(Value);
        else return expect(_t{Value}); // clang-format on
    }

    inline auto print(const std::string& str) { return log << fmt::format(" \"{}\"", str); }

    inline auto println(const std::string& str) { return log << fmt::format(" \"{}\"\n", str); }
}
