#include "noise_module.hpp"

GNOISE_NAMESPACE_BEGIN

float clamp(float x, float min, float max)
{
    return std::min(std::max(x, min), max);
}

singlethreaded_target_configuration::singlethreaded_target_configuration(noise_module_configuration* configuration):
    _configuration(configuration)
{
}

singlethreaded_target_configuration& singlethreaded_target_configuration::operator=(singlethreaded_target_configuration&& other) noexcept
{
    _configuration = other._configuration;
    return *this;
}

multithreaded_target_configuration::multithreaded_target_configuration(noise_module_configuration* configuration):
    _configuration(configuration)
{
}

multithreaded_target_configuration& multithreaded_target_configuration::operator=(const multithreaded_target_configuration& other) noexcept
{
    _percentage_affinity = other._percentage_affinity;
    _configuration->post_changes();
    return *this;
}

multithreaded_target_configuration& multithreaded_target_configuration::operator=(multithreaded_target_configuration&& other) noexcept
{
    _percentage_affinity = other._percentage_affinity;
    _configuration->post_changes();
    return *this;
}

float multithreaded_target_configuration::percentage_affinity() const
{
    return _percentage_affinity;
}

void multithreaded_target_configuration::set_percentage_affinity(float affinity)
{
    _percentage_affinity = clamp(affinity, percentage_affinity_min, percentage_affinity_max);
    _configuration->post_changes();
}

accelerated_target_configuration::accelerated_target_configuration(noise_module_configuration* configuration):
    _configuration(configuration)
{
}

accelerated_target_configuration& accelerated_target_configuration::operator=(const accelerated_target_configuration& other) noexcept
{
    _opencl_target = other._opencl_target;
    _configuration->post_changes();
    return *this;
}

accelerated_target_configuration& accelerated_target_configuration::operator=(accelerated_target_configuration&& other) noexcept
{
    _configuration = other._configuration;
    return *this;
}

accelerated_computation_target accelerated_target_configuration::target() const
{
    return _opencl_target;
}

void accelerated_target_configuration::set_target(accelerated_computation_target target)
{
    _opencl_target = target;
    _configuration->post_changes();
}

void noise_module_configuration::post_changes()
{
    _configuration_owner->on_configuration_changed();
}

noise_module_configuration::configuration_union::configuration_union(noise_module_configuration* configuration)
{
    st = st_c(configuration);
}

noise_module_configuration::configuration_union::~configuration_union()
{
}

noise_module_configuration::noise_module_configuration(noise_module* owner) noexcept:
    _target_configuration(this),
    _configuration_owner(owner)
{
    _computation_target = module_computation_target::single_thread_cpu;
}

noise_module_configuration& noise_module_configuration::operator=(const noise_module_configuration& other) noexcept
{
    _computation_target = other._computation_target;
    switch (other._computation_target)
    {
        case module_computation_target::stcpu:
        {
            _target_configuration.st = other._target_configuration.st;
        }
        break;
        case module_computation_target::mtcpu:
        {
            _target_configuration.mt = other._target_configuration.mt;
        }
        break;
        case module_computation_target::gpu:
        {
            _target_configuration.at = other._target_configuration.at;
        }
        break;
    }
    return *this;
}

singlethreaded_target_configuration* noise_module_configuration::singlethreaded_target_configuration()
{
    if (_computation_target == gnoise::module_computation_target::stcpu)
    {
        return &_target_configuration.st;
    }
    return nullptr;
}

multithreaded_target_configuration* noise_module_configuration::multithreaded_target_configuration()
{
    if (_computation_target == gnoise::module_computation_target::mtcpu)
    {
        return &_target_configuration.mt;
    }
    return nullptr;
}

accelerated_target_configuration* noise_module_configuration::accelerated_target_configuration()
{
    if (_computation_target == gnoise::module_computation_target::gpu)
    {
        return &_target_configuration.at;
    }
    return nullptr;
}

const singlethreaded_target_configuration* noise_module_configuration::singlethreaded_target_configuration() const
{
    if (_computation_target == gnoise::module_computation_target::stcpu)
    {
        return &_target_configuration.st;
    }
    return nullptr;
}

const multithreaded_target_configuration* noise_module_configuration::multithreaded_target_configuration() const
{
    if (_computation_target == gnoise::module_computation_target::mtcpu)
    {
        return &_target_configuration.mt;
    }
    return nullptr;
}

const accelerated_target_configuration* noise_module_configuration::accelerated_target_configuration() const
{
    if(_computation_target == gnoise::module_computation_target::gpu)
    {
        return &_target_configuration.at;
    }
    return nullptr;
}

module_computation_target noise_module_configuration::computation_target() const
{
    return _computation_target;
}

void noise_module_configuration::set_computation_target(module_computation_target computation_target)
{
    _computation_target = computation_target;
    switch(_computation_target)
    {
        case module_computation_target::stcpu:
        {
            _target_configuration.st = st_c(this);
        }
        break;
        case module_computation_target::mtcpu:
        {
            _target_configuration.mt = mt_c(this);
        }
        break;
        case module_computation_target::gpu:
        {
            _target_configuration.at = at_c(this);
        }
        break;
    }
    post_changes();
}

noise_module_configuration& noise_module::configuration()
{
    return _configuration;
}

const noise_module_configuration& noise_module::configuration() const
{
    return _configuration;
}

noise_module::noise_module() noexcept:
    _configuration(this)
{
}

GNOISE_NAMESPACE_END