#pragma once

#include "../noise_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_non_generator_module : public noise_module
{
protected:
    noise_non_generator_module() noexcept = default;
public:
    noise_non_generator_module(const noise_non_generator_module&) = delete;
    noise_non_generator_module(noise_non_generator_module&&) = delete;
    noise_non_generator_module& operator=(const noise_non_generator_module&) = delete;
    noise_non_generator_module& operator=(noise_non_generator_module&&) = delete;
public:
    virtual size_t                                  input_modules_count() const = 0;
    virtual vector<const noise_module*>             input_modules() const = 0;
    virtual const noise_module*                     input_module(size_t index) const = 0;
    
    virtual bool                                    set_input_modules(size_t index, const noise_module* module) = 0;
protected:
    virtual void                                    on_configuration_changed() override;
};

template<size_t I_C>
class noise_non_generator_module_impl : public noise_non_generator_module
{
protected:
    noise_non_generator_module_impl() noexcept:
        noise_non_generator_module()
    {
        std::fill(_source_modules.begin(), _source_modules.end(), nullptr);
    }
public:
    noise_non_generator_module_impl(const noise_non_generator_module_impl&) = delete;
    noise_non_generator_module_impl(noise_non_generator_module_impl&&) = delete;
    noise_non_generator_module_impl& operator=(const noise_non_generator_module_impl&) = delete;
    noise_non_generator_module_impl& operator=(noise_non_generator_module_impl&&) = delete;
public:
    virtual size_t                                  input_modules_count() const override
    {
        return I_C;
    }
    virtual vector<const noise_module*>             input_modules() const override
    {
        vector<const noise_module*> cp(I_C);
        std::copy(_source_modules.begin(), _source_modules.end(), cp.begin());
        return cp;
    }
    virtual const noise_module*                     input_module(size_t index) const override
    {
        if(index >= I_C)
        {
            return nullptr;
        }
        return _source_modules[index];
    }

    virtual bool                                    set_input_modules(size_t index, const noise_module* module) override
    {
        if (index >= I_C || !module)
        {
            return false;
        }
        _source_modules[I_C] = module;
        return true;
    }
protected:
    array<const noise_module*, I_C>                 _source_modules;
};

template<>
class noise_non_generator_module_impl<0> : public noise_non_generator_module
{
protected:
    noise_non_generator_module_impl() noexcept = default;
public:
    noise_non_generator_module_impl(const noise_non_generator_module_impl&) = delete;
    noise_non_generator_module_impl(noise_non_generator_module_impl&&) = delete;
    noise_non_generator_module_impl& operator=(const noise_non_generator_module_impl&) = delete;
    noise_non_generator_module_impl& operator=(noise_non_generator_module_impl&&) = delete;
public:
    virtual size_t                                  input_modules_count() const override
    {
        return 0;
    }
    virtual vector<const noise_module*>             input_modules() const override
    {
        return vector<const noise_module*>();
    }
    virtual const noise_module*                     input_module(size_t index) const override
    {
        return nullptr;
    }

    virtual bool                                    set_input_modules(size_t index, const noise_module* module) override
    {
        return false;
    }
};

GNOISE_NAMESPACE_END
