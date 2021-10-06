//
// Created by BlurringShadow on 2021-9-27.
//
#pragma once
#include <ranges>
#include <range/v3/range.hpp>

#include "functional/cpo.h"

namespace stdsharp
{
    namespace ranges
    {
        template<typename T>
        using const_iterator_t = decltype(::std::ranges::cbegin(std::declval<T&>()));

        template<typename T>
        using range_const_reference_t =
            ::stdsharp::type_traits::add_const_lvalue_ref_t<::std::ranges::range_value_t<T>>;
    }

    namespace functional
    {
#define BS_STD_RANGES_NODISCARD_OBJ(obj_name)                                         \
    template<>                                                                        \
    struct is_nodiscard_func_obj<::std::decay_t<decltype(::std::ranges::obj_name)>> : \
        ::std::bool_constant<true>                                                    \
    {                                                                                 \
    };

#define BS_STD_RANGES_RANGE_OBJ(obj_name)    \
    BS_STD_RANGES_NODISCARD_OBJ(obj_name)    \
    BS_STD_RANGES_NODISCARD_OBJ(c##obj_name) \
    BS_STD_RANGES_NODISCARD_OBJ(cr##obj_name)

        BS_STD_RANGES_RANGE_OBJ(begin)
        BS_STD_RANGES_RANGE_OBJ(end)

#undef BS_STD_RANGES_RANGE_OBJ

        BS_STD_RANGES_NODISCARD_OBJ(size)
        BS_STD_RANGES_NODISCARD_OBJ(ssize)
        BS_STD_RANGES_NODISCARD_OBJ(empty)
        BS_STD_RANGES_NODISCARD_OBJ(data)
        BS_STD_RANGES_NODISCARD_OBJ(cdata)

#undef BS_STD_RANGES_NODISCARD_OBJ

#define BS_RANGES_NODISCARD_OBJ(obj_name)                                        \
    template<>                                                                   \
    struct is_nodiscard_func_obj<::std::decay_t<decltype(::ranges::obj_name)>> : \
        ::std::bool_constant<true>                                               \
    {                                                                            \
    };

#define BS_RANGES_RANGE_OBJ(obj_name)    \
    BS_RANGES_NODISCARD_OBJ(obj_name)    \
    BS_RANGES_NODISCARD_OBJ(c##obj_name) \
    BS_RANGES_NODISCARD_OBJ(cr##obj_name)

        BS_RANGES_RANGE_OBJ(begin)
        BS_RANGES_RANGE_OBJ(end)

#undef BS_RANGES_RANGE_OBJ

        BS_RANGES_NODISCARD_OBJ(at)
        BS_RANGES_NODISCARD_OBJ(size)
        BS_RANGES_NODISCARD_OBJ(front)
        BS_RANGES_NODISCARD_OBJ(back)
        BS_RANGES_NODISCARD_OBJ(index)
        BS_RANGES_NODISCARD_OBJ(empty)
        BS_RANGES_NODISCARD_OBJ(data)
        BS_RANGES_NODISCARD_OBJ(cdata)

#undef BS_RANGES_NODISCARD_OBJ
    }
}