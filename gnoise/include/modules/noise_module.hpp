#pragma once

#include "../common.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_module;
class noise_module_configuration;
class accelerated_target_configuration;
class multithreaded_target_configuration;
class singlethreaded_target_configuration;

class singlethreaded_target_configuration
{
    friend class noise_module_configuration;
private:
    singlethreaded_target_configuration() = delete;
    singlethreaded_target_configuration(noise_module_configuration* configuration);
    singlethreaded_target_configuration& operator=(singlethreaded_target_configuration&& other) noexcept;
    ~singlethreaded_target_configuration() noexcept = default;
public:
    singlethreaded_target_configuration& operator=(const singlethreaded_target_configuration& other) noexcept = default;

    singlethreaded_target_configuration(const singlethreaded_target_configuration& other) = delete;
    singlethreaded_target_configuration(singlethreaded_target_configuration&&) = delete;
private:
    noise_module_configuration*                 _configuration;
};

inline constexpr float percentage_affinity_100  = 1.0f;
inline constexpr float percentage_affinity_75   = 0.75f;
inline constexpr float percentage_affinity_50   = 0.50f;
inline constexpr float percentage_affinity_25   = 0.25f;
inline constexpr float percentage_affinity_0    = 0.0f;
inline constexpr float percentage_affinity_max  = 1.0f;
inline constexpr float percentage_affinity_min  = 0.0f;

class multithreaded_target_configuration
{
    friend class noise_module_configuration;
private:
    multithreaded_target_configuration() = delete;
    multithreaded_target_configuration(noise_module_configuration* configuration);
    multithreaded_target_configuration& operator=(multithreaded_target_configuration&& other) noexcept;
    ~multithreaded_target_configuration() noexcept = default;
public:
    multithreaded_target_configuration& operator=(const multithreaded_target_configuration& other) noexcept;

    multithreaded_target_configuration(const multithreaded_target_configuration&) = delete;
    multithreaded_target_configuration(multithreaded_target_configuration&&) = delete;
private:
    noise_module_configuration*                 _configuration;
    float                                       _percentage_affinity = percentage_affinity_100;
public:
    float                                       percentage_affinity() const;
    void                                        set_percentage_affinity(float affinity = percentage_affinity_100);
};

class accelerated_target_configuration
{
    friend class noise_module_configuration;
private:
    accelerated_target_configuration() = delete;
    accelerated_target_configuration(noise_module_configuration* configuration);
    accelerated_target_configuration& operator=(accelerated_target_configuration&& other) noexcept;
    ~accelerated_target_configuration() noexcept = default;
public:
    accelerated_target_configuration& operator=(const accelerated_target_configuration& other) noexcept;

    accelerated_target_configuration(const accelerated_target_configuration&) = delete;
    accelerated_target_configuration(accelerated_target_configuration&&) = delete;
private:
    accelerated_computation_target              _opencl_target;
    noise_module_configuration*                 _configuration;
public:
    accelerated_computation_target              target() const;
    void                                        set_target(accelerated_computation_target target);
};

class noise_module_configuration
{
    friend class singlethreaded_target_configuration;
    friend class multithreaded_target_configuration;
    friend class accelerated_target_configuration;
    friend class noise_module;
private:
    using st_c = singlethreaded_target_configuration;
    using mt_c = multithreaded_target_configuration;
    using at_c = accelerated_target_configuration;
private:
    noise_module_configuration(noise_module* owner) noexcept;
    ~noise_module_configuration() noexcept = default;
public:
    noise_module_configuration& operator=(const noise_module_configuration& other) noexcept;

    noise_module_configuration(const noise_module_configuration& other) = delete;
    noise_module_configuration(noise_module_configuration&&) = delete;
    noise_module_configuration& operator=(noise_module_configuration&&) = delete;
public:
    accelerated_target_configuration*                               accelerated_target_configuration();
    multithreaded_target_configuration*                             multithreaded_target_configuration();
    singlethreaded_target_configuration*                            singlethreaded_target_configuration();
    const gnoise::accelerated_target_configuration*                 accelerated_target_configuration() const;
    const gnoise::multithreaded_target_configuration*               multithreaded_target_configuration() const;
    const gnoise::singlethreaded_target_configuration*              singlethreaded_target_configuration() const;
    
    module_computation_target                                       computation_target() const;
    void                                                            set_computation_target(module_computation_target computation_target);
private:
    union configuration_union
    {
        configuration_union(noise_module_configuration* configuration);
        ~configuration_union();
        st_c st;
        mt_c mt;
        at_c at;
    } _target_configuration;
    module_computation_target                                       _computation_target;
    noise_module*                                                   _configuration_owner;
private:
    void                                                            post_changes();
};

class noise_module
{
    friend class noise_module_configuration;
protected:
    noise_module() noexcept;
    virtual ~noise_module() = default;
public:
    noise_module(const noise_module&) = delete;
    noise_module(noise_module&&) = delete;
    noise_module& operator=(const noise_module&) = delete;
    noise_module& operator=(noise_module&&) = delete;
public:
    virtual float                                   compute(const vector1f& point) const = 0;
    virtual float                                   compute(const vector2f& point) const = 0;
    virtual float                                   compute(const vector3f& point) const = 0;
    virtual float                                   compute(const vector4f& point) const = 0;

    virtual vector<float>                           compute(const vector<vector1f>& points) const = 0;
    virtual vector<float>                           compute(const vector<vector2f>& points) const = 0;
    virtual vector<float>                           compute(const vector<vector3f>& points) const = 0;
    virtual vector<float>                           compute(const vector<vector4f>& points) const = 0;

    virtual vector<float>                           compute(const range1f& range, const precision1& precision) const = 0;
    virtual vector<float>                           compute(const range2f& range, const precision2& precision) const = 0;
    virtual vector<float>                           compute(const range3f& range, const precision3& precision) const = 0;
    virtual vector<float>                           compute(const range4f& range, const precision4& precision) const = 0;

    virtual gnoise::module_type                     module_type() const = 0;
public:
    noise_module_configuration&                     configuration();
    const noise_module_configuration&               configuration() const;
protected:
    noise_module_configuration                      _configuration;
protected:
    virtual void                                    on_configuration_changed() = 0;
};

GNOISE_NAMESPACE_END