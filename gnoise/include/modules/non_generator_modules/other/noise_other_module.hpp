#pragma once

#include "../noise_non_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

template<size_t I_C>
class noise_other_module : public noise_non_generator_module_impl<I_C>
{
protected:
    noise_other_module() noexcept = default;
public:
    virtual gnoise::module_type                     module_type() const override
    {
        return gnoise::module_type::other;
    }
};

GNOISE_NAMESPACE_END