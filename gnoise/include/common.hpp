#pragma once

#include <CL/cl.hpp>
#include <optional>
#include <variant>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <thread>
#include <array>

#undef min
#undef max

#define GNOISE gnoise
#define GNOISE_NAMESPACE_BEGIN namespace GNOISE{
#define GNOISE_NAMESPACE_END }

GNOISE_NAMESPACE_BEGIN

template<size_t S>
struct vectorf
{
    vectorf()
    {
        for (size_t i = 0; i < S; i++)
        {
            coords[i] = 0.0f;
        }
    }

    float coords[S];
};

using vector1f = vectorf<1>;
using vector2f = vectorf<2>;
using vector3f = vectorf<3>;
using vector4f = vectorf<4>;

template<size_t D>
class rangef
{
public:
    rangef() noexcept
    {
        for(size_t i=0;i<D;i++)
        {
            _dim_ranges[i] = vector2f();
        }
    }
    template<size_t _D>
    rangef(const rangef<_D>& other) noexcept
    {
        std::copy(other._dim_ranges, other._dim_ranges + std::min(D, _D), _dim_ranges);
    }
    template<size_t _D>
    rangef(rangef<_D>&& other) noexcept
    {
        std::copy(other._dim_ranges, other._dim_ranges + std::min(D, _D), _dim_ranges);
    }
    template<size_t _D>
    rangef& operator=(const rangef<_D>& other) noexcept
    {
        std::copy(other._dim_ranges, other._dim_ranges + std::min(D, _D), _dim_ranges);
    }
    template<size_t _D>
    rangef& operator=(rangef<_D>&& other) noexcept
    {
        std::copy(other._dim_ranges, other._dim_ranges + std::min(D, _D), _dim_ranges);
    }
public:
    constexpr const vector2f* begin() const
    {
        return _dim_ranges;
    }

    constexpr const vector2f* end() const
    {
        return _dim_ranges + D;
    }

    vector2f& operator [](size_t i)
    {
        return _dim_ranges[i];
    }

    vector2f operator [](size_t i) const
    {
        return _dim_ranges[i];
    }

    constexpr size_t    dimensions() const
    {
        return D;
    }

    template<size_t I, std::enable_if_t< 0 < I && I <= D, int> = 0>
    float               dimension_min() const
    {
        return _dim_ranges[I-1].coords[0];
    }
    template<size_t I, std::enable_if_t< 0 < I && I <= D, int > = 0>
    float               dimension_max() const
    {
        return _dim_ranges[I - 1].coords[1];
    }

    template<size_t I, std::enable_if_t< 0 < I && I <= D, int > = 0>
    void               set_dimension_min(float value)
    {
        _dim_ranges[I - 1].coords[0] = value;
    }
    template<size_t I, std::enable_if_t< 0 < I && I <= D, int > = 0>
    void               set_dimension_max(float value)
    {
        _dim_ranges[I - 1].coords[1] = value;
    }
private:
    vector2f _dim_ranges[D];
};

template<size_t D>
class precision
{
public:
    precision() noexcept
    {
        for (size_t i = 0; i < D; i++)
        {
            _dim_precision[i] = 0;
        }
    }
    template<size_t _D>
    precision(const precision<_D>& other) noexcept
    {
        std::copy(other._dim_precision, other._dim_precision + std::min(D, _D), _dim_precision);
    }
    template<size_t _D>
    precision(precision<_D>&& other) noexcept
    {
        std::copy(other._dim_precision, other._dim_precision + std::min(D, _D), _dim_precision);
    }
    template<size_t _D>
    precision& operator=(const precision<_D>& other) noexcept
    {
        std::copy(other._dim_precision, other._dim_precision + std::min(D, _D), _dim_precision);
    }
    template<size_t _D>
    precision& operator=(precision<_D>&& other) noexcept
    {
        std::copy(other._dim_precision, other._dim_precision + std::min(D, _D), _dim_precision);
    }
public:
    constexpr const unsigned long long int* begin() const
    {
        return _dim_precision;
    }

    constexpr const unsigned long long int* end() const
    {
        return _dim_precision + D;
    }

    unsigned long long int& operator [](size_t i)
    {
        return _dim_precision[i];
    }

    unsigned long long int operator [](size_t i) const
    {
        return _dim_precision[i];
    }

    constexpr size_t    dimensions() const
    {
        return D;
    }

    template<size_t I, std::enable_if_t< 0 < I && I <= D, int > = 0>
    unsigned long long int dimension_precision() const
    {
        return _dim_precision[I - 1];
    }

    template<size_t I, std::enable_if_t< 0 < I && I <= D, int > = 0>
    void               set_dimension_precision(unsigned long long int value)
    {
        _dim_precision[I - 1] = value;
    }
private:
    unsigned long long int _dim_precision[D];
};

using range1f = rangef<1>;
using range2f = rangef<2>;
using range3f = rangef<3>;
using range4f = rangef<4>;

using precision1 = precision<1>;
using precision2 = precision<2>;
using precision3 = precision<3>;
using precision4 = precision<4>;

using accelerated_computation_target = cl::Device;
template<class T>
using optional = std::optional<T>;
template<class T>
using vector = std::vector<T>;
template<class T, size_t S>
using array = std::array<T, S>;

enum module_computation_target
{
    stcpu,
    single_thread_cpu = stcpu,
    mtcpu,
    multi_thread_cpu = mtcpu,
    gpu,
    open_cl = gpu,
};

enum module_type
{
    generator,
    modifier,
    combiner,
    selector,
    transformer,
    miscellaneous,
    other
};

GNOISE_NAMESPACE_END