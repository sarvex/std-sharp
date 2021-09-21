﻿// Created by BlurringShadow at 2021-03-05-下午 11:53

#pragma once

#include "type_sequence.h"

namespace stdsharp::type_traits
{
    struct unique_object
    {
        unique_object() noexcept = default;
        unique_object(const unique_object&) noexcept = delete;
        unique_object(unique_object&&) noexcept = default;
        unique_object& operator=(const unique_object&) noexcept = delete;
        unique_object& operator=(unique_object&&) noexcept = default;
        ~unique_object() = default;
    };

    template<typename T>
    struct private_object
    {
        friend T;

    protected:
        private_object() noexcept = default;
        private_object(const private_object&) noexcept = default;
        private_object& operator=(const private_object&) noexcept = default;
        private_object(private_object&&) noexcept = default;
        private_object& operator=(private_object&&) noexcept = default;
        ~private_object() = default;
    };
}
