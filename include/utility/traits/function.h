﻿// Created by BlurringShadow at 2021-03-03-下午 4:33

#pragma once
#include "type_sequence.h"

namespace stdsharp::utility::traits
{
    namespace details
    {
        template<typename T>
        struct function_traits_helper;

        template<bool IsNoexcept>
        struct function_qualifiers_traits
        {
            static auto constexpr is_noexcept = IsNoexcept;
        };

        template<typename R, typename... Args>
        struct function_traits_helper_base
        {
            using result_t = R;
            using args_t = ::stdsharp::utility::traits::type_sequence<Args...>;
        };

        template<typename R, typename... Args>
        struct function_traits_helper<R (*)(Args...)> :
            ::stdsharp::utility::traits::details::function_traits_helper_base<R, Args...>,
            ::stdsharp::utility::traits::details::function_qualifiers_traits<false>
        {
        };

        template<typename R, typename... Args>
        struct function_traits_helper<R (*)(Args...) noexcept> :
            ::stdsharp::utility::traits::details::function_traits_helper_base<R, Args...>,
            function_qualifiers_traits<true>
        {
        };
    }

    template<typename T>
    struct function_traits :
        ::stdsharp::utility::traits::details::function_traits_helper<::std::decay_t<T>>
    {
    };

    template<auto Ptr>
    struct function_pointer_traits :
        ::stdsharp::utility::traits::function_traits<::std::decay_t<decltype(Ptr)>>
    {
    };
}
