#include "noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

std::map<cl_device_id, std::weak_ptr<cl_context>>        noise_generator_module_gpu_manager::_device_contexts;
std::map<cl_device_id, std::weak_ptr<cl_command_queue>>  noise_generator_module_gpu_manager::_device_command_queues;

std::shared_ptr<cl_context> noise_generator_module_gpu_manager::get_device_context(cl_device_id device)
{
    auto context_it = _device_contexts.find(device);

    if (context_it != _device_contexts.end())
    {
        if (auto context = context_it->second.lock())
        {
            return context;
        }
        else
        {
            _device_contexts.erase(context_it);
        }
    }

    std::shared_ptr<cl_context> context = std::shared_ptr<cl_context>(
        new cl_context(clCreateContext(nullptr, 1, &device, nullptr, nullptr, nullptr)),
        [](cl_context* context) {
            clReleaseContext(*context);
            delete context;
        });

    _device_contexts[device] = context;

    return context;
}

std::shared_ptr<cl_command_queue> noise_generator_module_gpu_manager::get_device_command_queue(cl_device_id device)
{
    auto command_queue_it = _device_command_queues.find(device);

    if (command_queue_it != _device_command_queues.end())
    {
        if (auto command_queue = command_queue_it->second.lock())
        {
            return command_queue;
        }
        else
        {
            _device_command_queues.erase(command_queue_it);
        }
    }

    std::shared_ptr<cl_command_queue> command_queue = std::shared_ptr<cl_command_queue>(
        new cl_command_queue(clCreateCommandQueue(*get_device_context(device), device, cl_command_queue_properties(), nullptr)),
        [](cl_command_queue* command_queue) {
            clFlush(*command_queue);
            clFinish(*command_queue);
            clReleaseCommandQueue(*command_queue);
            delete command_queue;
        });

    _device_command_queues[device] = command_queue;

    return command_queue;
}

gnoise::module_type noise_generator_module_base::module_type() const
{
    return module_type::generator;
}

GNOISE_NAMESPACE_END
