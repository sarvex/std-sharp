// Created by BlurringShadow at 2021-02-27-���� 10:24

#pragma once

#include <random>

namespace blurringshadow::utility
{
    [[nodiscard]] inline auto& get_random_device()
    {
        static thread_local std::random_device random_device;
        return random_device;
    }
}