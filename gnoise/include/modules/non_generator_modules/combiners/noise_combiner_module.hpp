#pragma once

#include "../noise_non_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

template<size_t I_C, class F, class D>
using noise_combiner_module_base = noise_non_generator_module_def_impl<I_C, F, D, module_type::combiner>;

//trivial combiners
class noise_add_module;
class noise_subtract_module;
class noise_multiply_module;
class noise_divide_module;
class noise_min_module;
class noise_max_module;
class noise_power_module;

struct add
{
    inline static float apply(const noise_add_module* module, float a, float b)
    {
        return a + b;
    }
};

struct subtract
{
    inline static float apply(const noise_subtract_module* module, float a, float b)
    {
        return a - b;
    }
};

struct multiply
{
    inline static float apply(const noise_multiply_module* module, float a, float b)
    {
        return a * b;
    }
};

struct divide
{
    inline static float apply(const noise_divide_module* module, float a, float b)
    {
        return a / b;
    }
};

struct power
{
    inline static float apply(const noise_power_module* module, float a, float b)
    {
        return std::pow(a, b);
    }
};

struct min
{
    inline static float apply(const noise_min_module* module, float a, float b)
    {
        return std::min(a, b);
    }
};

struct max
{
    inline static float apply(const noise_max_module* module, float a, float b)
    {
        return std::max(a, b);
    }
};

class noise_add_module : public noise_combiner_module_base<2, add, noise_add_module> {};
class noise_subtract_module : public noise_combiner_module_base<2, subtract, noise_subtract_module> {};

class noise_multiply_module : public noise_combiner_module_base<2, multiply, noise_multiply_module> {};
class noise_divide_module : public noise_combiner_module_base<2, divide, noise_divide_module> {};

class noise_power_module : public noise_combiner_module_base<2, power, noise_power_module> {};

class noise_min_module : public noise_combiner_module_base<2, min, noise_min_module> {};
class noise_max_module : public noise_combiner_module_base<2, max, noise_max_module> {};

GNOISE_NAMESPACE_END