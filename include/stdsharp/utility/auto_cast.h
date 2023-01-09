#pragma once

#include "../concepts/concepts.h"

namespace stdsharp
{
    inline constexpr struct
    {
    private:
        template<typename T>
        struct auto_cast_operator
        {
            T&& t;

            template<typename U>
                requires explicitly_convertible<T, U>
            [[nodiscard]] constexpr operator U() const&& //
                noexcept(nothrow_explicitly_convertible<T, U>)
            {
                return static_cast<U>(::std::forward<T>(t));
            }
        };

    public:
        template<typename T>
        [[nodiscard]] constexpr auto operator()(T&& t) const noexcept
        {
            return auto_cast_operator<T>{::std::forward<T>(t)}; //
        }
    } auto_cast{};


}