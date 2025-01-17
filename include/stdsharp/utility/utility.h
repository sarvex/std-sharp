
#pragma once

#include <utility>

#include "pack_get.h"
#include "value_wrapper.h"
#include "adl_proof.h"

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

    template<typename T>
    struct forward_like_fn
    {
    private:
        template<typename U>
        using copy_const_t = ::std::conditional_t<const_<::std::remove_reference_t<T>>, const U, U>;

    public:
        template<typename U>
        [[nodiscard]] constexpr ref_align_t<T&&, copy_const_t<::std::remove_reference_t<U>>>
            operator()(U&& u) const noexcept
        {
            return auto_cast(u);
        }
    };

    template<typename T>
    inline constexpr forward_like_fn<T> forward_like{};

    template<typename T, typename U>
    using forward_like_t = decltype(forward_like<T>(::std::declval<U>()));
}