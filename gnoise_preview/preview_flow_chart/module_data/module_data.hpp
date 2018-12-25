#pragma once

#include "../preview_common.hpp"

template<class T>
class module_data_def_impl : public module_data
{
protected:
    T                                               _module;
public:
    virtual noise_module*                           module() override
    {
        return &_module;
    }
};

template<class T>
class module_data_non_generator_def_impl : public module_data_def_impl<T>
{
public:
    virtual size_t                          input_modules_count() const override
    {
        return _module.input_modules_count();
    }
};

//GENERATORS

template<class T>
class module_data_generator_def_impl : public module_data_def_impl<T>
{
public:
    virtual size_t                          input_modules_count() const override
    {
        return 0;
    }
    virtual vector<QString>                         input_names() const override
    {
        return vector<QString>();
    }
};

class perlin_module_data : public module_data_generator_def_impl<noise_perlin_generator_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class billow_module_data : public module_data_generator_def_impl<noise_billow_generator_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class ridged_multifractal_module_data : public module_data_generator_def_impl<noise_ridged_multifractal_generator_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class voronoi_module_data : public module_data_generator_def_impl<noise_voronoi_generator_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class const_module_data : public module_data_generator_def_impl<noise_const_generator_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class checkerboard_module_data : public module_data_generator_def_impl<noise_checkerboard_generator_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class cylinders_module_data : public module_data_generator_def_impl<noise_cylinders_generator_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class spheres_module_data : public module_data_generator_def_impl<noise_spheres_generator_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

//COMBINERS

template<class T>
class module_data_combiner_def_impl : public module_data_non_generator_def_impl<T>
{
public:
    virtual vector<QString>                         input_names() const override
    {
        return { "Module 1", "Module 2" };
    }

    virtual size_t                                  property_count() const override
    {
        return 0;
    }
    virtual QVariant                                property_value(size_t property_index) const override
    {
        return QVariant();
    }
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override
    {
        return false;
    }

    virtual QString                                 property_name(size_t property_index) const override
    {
        return QString();
    }
};

class add_module_data : public module_data_combiner_def_impl<noise_add_module>
{
public:
    virtual QString                                 module_name() const override;
};

class subtract_module_data : public module_data_combiner_def_impl<noise_subtract_module>
{
public:
    virtual QString                                 module_name() const override;
};

class multiply_module_data : public module_data_combiner_def_impl<noise_multiply_module>
{
public:
    virtual QString                                 module_name() const override;
};

class divide_module_data : public module_data_combiner_def_impl<noise_divide_module>
{
public:
    virtual QString                                 module_name() const override;
};

class power_module_data : public module_data_combiner_def_impl<noise_power_module>
{
public:
    virtual QString                                 module_name() const override;
};

class min_module_data : public module_data_combiner_def_impl<noise_min_module>
{
public:
    virtual QString                                 module_name() const override;
};

class max_module_data : public module_data_combiner_def_impl<noise_max_module>
{
public:
    virtual QString                                 module_name() const override;
};

//MODIFIERS

template<class T>
class module_data_modifier_def_impl : public module_data_non_generator_def_impl<T>
{
public:
    virtual vector<QString>                         input_names() const override
    {
        return { "Module" };
    }
};

class abs_module_data : public module_data_modifier_def_impl<noise_abs_module>
{
public:
    virtual QString                         module_name() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};

class base_module_data : public module_data_modifier_def_impl<noise_base_module>
{
public:
    virtual QString                         module_name() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};

class exponent_module_data : public module_data_modifier_def_impl<noise_exponent_module>
{
public:
    virtual QString                         module_name() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};

class clamp_module_data : public module_data_modifier_def_impl<noise_clamp_module>
{
public:
    virtual QString                         module_name() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};

class scale_bias_module_data : public module_data_modifier_def_impl<noise_scale_bias_module>
{
public:
    virtual QString                         module_name() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};

//SELECTORS

template<class T>
class module_data_selector_def_impl : public module_data_non_generator_def_impl<T>
{
public:
    virtual vector<QString>                         input_names() const override
    {
        return { "Control", "Module 1", "Module 2" };
    }
};

class select_module_data : public module_data_selector_def_impl<noise_select_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class blend_module_data : public module_data_selector_def_impl<noise_blend_module>
{
public:
    virtual QString                                 module_name() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

//TRANSFORMERS

class displace_module_data : public module_data_non_generator_def_impl<noise_displace_module>
{
public:
    virtual QString                                 module_name() const override;
    virtual vector<QString>                         input_names() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

class turbulence_module_data : public module_data_non_generator_def_impl<noise_turbulence_module>
{
public:
    virtual QString                                 module_name() const override;
    virtual vector<QString>                         input_names() const override;

    virtual size_t                                  property_count() const override;
    virtual QVariant                                property_value(size_t property_index) const override;
    virtual bool                                    set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                                 property_name(size_t property_index) const override;
};

template<class T>
class module_data_linear_transformer_def_impl : public module_data_modifier_def_impl<T>{};

class translate_point_module_data : public module_data_linear_transformer_def_impl<noise_translate_point_module>
{
public:
    virtual QString                         module_name() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};

class rotate_point_module_data : public module_data_modifier_def_impl<noise_rotate_point_module>
{
public:
    virtual QString                         module_name() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};

class scale_point_module_data : public module_data_modifier_def_impl<noise_scale_point_module>
{
public:
    virtual QString                         module_name() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};