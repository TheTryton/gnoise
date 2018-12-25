#pragma once

#include "../preview_base/preview_node_base.hpp"
#include "../module_data/module_data.hpp"

template<class MD>
class noise_module_node final : public preview_node_base
{
private:
    static MD* _init_data(MD*& data)
    {
        data = new MD;
        return data;
    }
public:
    MD*                             _module_data;
public:
    noise_module_node(QGraphicsWidget* parent = nullptr) :
        preview_node_base(_init_data(_module_data), parent)
    {
    }
    virtual ~noise_module_node() noexcept override
    {
        delete _module_data;
    }
public:
    virtual ::module_data*          module_data() override
    {
        return _module_data;
    }
};

//GENERATORS

using const_module_node = noise_module_node<const_module_data>;
using checkerboard_module_node = noise_module_node<checkerboard_module_data>;
using cylinders_module_node = noise_module_node<cylinders_module_data>;
using spheres_module_node = noise_module_node<spheres_module_data>;
using perlin_module_node = noise_module_node<perlin_module_data>;
using billow_module_node = noise_module_node<billow_module_data>;
using ridged_multifractal_module_node = noise_module_node<ridged_multifractal_module_data>;
using voronoi_module_node = noise_module_node<voronoi_module_data>;

//COMBINERS

using add_module_node = noise_module_node<add_module_data>;
using subtract_module_node = noise_module_node<subtract_module_data>;
using multiply_module_node = noise_module_node<multiply_module_data>;
using divide_module_node = noise_module_node<divide_module_data>;
using power_module_node = noise_module_node<power_module_data>;
using min_module_node = noise_module_node<min_module_data>;
using max_module_node = noise_module_node<max_module_data>;

//MODIFIERS

using abs_module_node = noise_module_node<abs_module_data>;
using clamp_module_node = noise_module_node<clamp_module_data>;
using base_module_node = noise_module_node<base_module_data>;
using exponent_module_node = noise_module_node<exponent_module_data>;
using scale_bias_module_node = noise_module_node<scale_bias_module_data>;

//SELECTORS

using blend_module_node = noise_module_node<blend_module_data>;
using select_module_node = noise_module_node<select_module_data>;

//TRANSFORMERS

using displace_module_node = noise_module_node<displace_module_data>;
using turbulence_module_node = noise_module_node<turbulence_module_data>;
using translate_point_module_node = noise_module_node<translate_point_module_data>;
using rotate_point_module_node = noise_module_node<rotate_point_module_data>;
using scale_point_module_node = noise_module_node<scale_bias_module_data>;