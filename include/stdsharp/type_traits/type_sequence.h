// Created by BlurringShadow at 2021-03-03-下午 4:35

#pragma once

#include "value_sequence.h"

namespace stdsharp
{
    template<typename...>
    struct type_sequence;

    namespace details
    {
        struct type_seq
        {
            template<auto... Values>
            static regular_type_sequence<::meta::_t<decltype(Values)>...>
                from_value_seq(regular_value_sequence<Values...>);

            template<template<typename...> typename S, typename... T>
            static regular_value_sequence<(type_constant<T>{})...> to_value_seq(S<T...>);

            template<typename Seq>
            using from_value_seq_t = decltype(from_value_seq(::std::declval<Seq>()));

            template<typename Seq>
            using to_value_seq_t = decltype(to_value_seq(::std::declval<Seq>()));
        };

        struct as_type_sequence
        {
            template<typename... T>
            using invoke = type_sequence<T...>;
        };
    }

    template<typename T>
    using as_type_sequence_t = ::meta::apply<details::as_type_sequence, T>;

    template<typename... Types>
    struct type_sequence :
        private value_sequence<type_constant<Types>{}...>,
        private details::type_seq
    {
    private:
        using base = value_sequence<type_constant<Types>{}...>;
        using type_seq::from_value_seq_t;
        using type_seq::to_value_seq_t;

    public:
        using base::size;
        using base::for_each;
        using base::for_each_n;
        using base::find_if;
        using base::find_if_not;
        using base::find;
        using base::count_if;
        using base::count_if_not;
        using base::count;
        using base::all_of;
        using base::any_of;
        using base::none_of;
        using base::contains;
        using base::adjacent_find;
        using base::at_v;

        template<template<typename...> typename T>
        using apply_t = T<Types...>;

        template<::std::size_t I>
        using get_t = typename decltype(get<I>(base{}))::type;

        template<::std::size_t... I>
        using at_t = regular_type_sequence<get_t<I>...>;

        template<::std::size_t Size>
        using back_t = from_value_seq_t<typename base::template back_t<Size>>;

        template<::std::size_t Size>
        using front_t = from_value_seq_t<typename base::template front_t<Size>>;

        template<typename... Others>
        using append_t = regular_type_sequence<Types..., Others...>;

        template<typename T = void>
        using invoke_fn = typename base::template invoke_fn<T>;

        template<typename T = empty_t>
        static constexpr invoke_fn<T> invoke{};

        template<typename... Others>
        using append_front_t = regular_type_sequence<Others..., Types...>;

        template<::std::size_t Index, typename... Other>
        using insert_t = from_value_seq_t< //
            typename base::template insert_t<
                Index,
                static_const_v<type_constant<Other>>... // clang-format off
            >
        >; // clang-format on

        template<::std::size_t... Index>
        using remove_at_t = from_value_seq_t<typename base::template remove_at_t<Index...>>;

        template<::std::size_t Index, typename Other>
        using replace_t =
            from_value_seq_t<typename base::template replace_t<Index, type_constant<Other>{}>>;

        template<::std::size_t From, ::std::size_t Size>
        using select_range_t = from_value_seq_t<typename base::template select_range_t<From, Size>>;
    };

    template<typename... T>
    using reverse_type_sequence_t = as_type_sequence_t< //
        details::type_seq::from_value_seq_t<
            reverse_value_sequence_t<type_constant<T>{}...> // clang-format off
        >
    >; // clang-format on

    template<typename... T>
    using unique_type_sequence_t = as_type_sequence_t< //
        details::type_seq::from_value_seq_t<
            unique_value_sequence_t<type_constant<T>{}...> // clang-format off
        >
    >; // clang-format on
}

namespace std
{
    template<typename... Types>
    struct tuple_size<::stdsharp::type_sequence<Types...>> :// NOLINT(cert-dcl58-cpp)
        ::stdsharp:: // clang-format off
            index_constant<::stdsharp::type_sequence<Types...>::size>
    // clang-format on
    {
    };
}