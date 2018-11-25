#pragma once

#include "../noise_non_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

template<size_t I_C>
class noise_transformer_module : public noise_non_generator_module_def_impl_base<I_C>
{
protected:
    noise_transformer_module() noexcept = default;
public:
    virtual gnoise::module_type                     module_type() const override
    {
        return gnoise::module_type::transformer;
    }
};

GNOISE_NAMESPACE_END