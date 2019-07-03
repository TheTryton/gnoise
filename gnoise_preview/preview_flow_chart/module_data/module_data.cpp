#include "module_data.hpp"
#include <functional>

template<class T>
using function = std::function<T>;

Q_DECLARE_METATYPE(noise_quality)

//GENERATORS

//perlin

QString perlin_module_data::module_name() const
{
    return "Perlin";
}

size_t perlin_module_data::property_count() const
{
    return 6;
}

QVariant perlin_module_data::property_value(size_t property_index) const
{
    if(property_index >= 6)
    {
        return QVariant();
    }

    const array<QVariant, 6> properties
    {
        _module.frequency(),
        _module.lacunarity(),
        _module.persistence(),
        _module.octave_count(),
        _module.seed(),
        QVariant::fromValue(_module.quality()),
    };

    return properties[property_index];
}

bool perlin_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 6)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 6> properties
    {
        [&](const QVariant& v) { _module.set_frequency(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_lacunarity(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_persistence(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_octave_count(static_cast<unsigned int>(v.toInt())); },
        [&](const QVariant& v) { _module.set_seed(v.toInt()); },
        [&](const QVariant& v) { _module.set_quality(v.value<noise_quality>()); },
    };
    
    properties[property_index](value);

    return true;
}

QString perlin_module_data::property_name(size_t property_index) const
{
    if (property_index >= 6)
    {
        return QString();
    }

    const array<QString, 6> properties
    {
        "frequency",
        "lacunarity",
        "persistence",
        "octave_count",
        "seed",
        "quality",
    };

    return properties[property_index];
}

//billow

QString billow_module_data::module_name() const
{
    return "Billow";
}

size_t billow_module_data::property_count() const
{
    return 6;
}

QVariant billow_module_data::property_value(size_t property_index) const
{
    if (property_index >= 6)
    {
        return QVariant();
    }

    const array<QVariant, 6> properties
    {
        _module.frequency(),
        _module.lacunarity(),
        _module.persistence(),
        _module.octave_count(),
        _module.seed(),
        QVariant::fromValue(_module.quality()),
    };

    return properties[property_index];
}

bool billow_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 6)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 6> properties
    {
        [&](const QVariant& v) { _module.set_frequency(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_lacunarity(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_persistence(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_octave_count(static_cast<unsigned int>(v.toInt())); },
        [&](const QVariant& v) { _module.set_seed(v.toInt()); },
        [&](const QVariant& v) { _module.set_quality(v.value<noise_quality>()); },
    };

    properties[property_index](value);

    return true;
}

QString billow_module_data::property_name(size_t property_index) const
{
    if (property_index >= 6)
    {
        return QString();
    }

    const array<QString, 6> properties
    {
        "frequency",
        "lacunarity",
        "persistence",
        "octave_count",
        "seed",
        "quality",
    };

    return properties[property_index];
}

//ridged multifractal

QString ridged_multifractal_module_data::module_name() const
{
    return "Ridged Multifractal";
}

size_t ridged_multifractal_module_data::property_count() const
{
    return 5;
}

QVariant ridged_multifractal_module_data::property_value(size_t property_index) const
{
    if (property_index >= 5)
    {
        return QVariant();
    }

    const array<QVariant, 5> properties
    {
        _module.frequency(),
        _module.lacunarity(),
        _module.octave_count(),
        _module.seed(),
        QVariant::fromValue(_module.quality()),
    };

    return properties[property_index];
}

bool ridged_multifractal_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 5)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 5> properties
    {
        [&](const QVariant& v) { _module.set_frequency(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_lacunarity(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_octave_count(static_cast<unsigned int>(v.toInt())); },
        [&](const QVariant& v) { _module.set_seed(v.toInt()); },
        [&](const QVariant& v) { _module.set_quality(v.value<noise_quality>()); },
    };

    properties[property_index](value);

    return true;
}

QString ridged_multifractal_module_data::property_name(size_t property_index) const
{
    if (property_index >= 5)
    {
        return QString();
    }

    const array<QString, 5> properties
    {
        "frequency",
        "lacunarity",
        "octave_count",
        "seed",
        "quality",
    };

    return properties[property_index];
}

//voronoi

QString voronoi_module_data::module_name() const
{
    return "Voronoi";
}

size_t voronoi_module_data::property_count() const
{
    return 4;
}

QVariant voronoi_module_data::property_value(size_t property_index) const
{
    if (property_index >= 4)
    {
        return QVariant();
    }

    const array<QVariant, 4> properties
    {
        _module.frequency(),
        _module.displacement(),
        _module.seed(),
        _module.uses_distance()
    };

    return properties[property_index];
}

bool voronoi_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 4)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 4> properties
    {
        [&](const QVariant& v) { _module.set_frequency(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_displacement(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_seed(v.toInt()); },
        [&](const QVariant& v) { _module.set_use_distance(v.toBool()); },
    };

    properties[property_index](value);

    return true;
}

QString voronoi_module_data::property_name(size_t property_index) const
{
    if (property_index >= 4)
    {
        return QString();
    }

    const array<QString, 4> properties
    {
        "frequency",
        "displacement",
        "seed",
        "use distance",
    };

    return properties[property_index];
}

//const

QString const_module_data::module_name() const
{
    return "Const";
}

size_t const_module_data::property_count() const
{
    return 0;
}

QVariant const_module_data::property_value(size_t property_index) const
{
    return QVariant();
}

bool const_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    return false;
}

QString const_module_data::property_name(size_t property_index) const
{
    return QString();
}

//checkerboard

QString checkerboard_module_data::module_name() const
{
    return "Checkerboard";
}

size_t checkerboard_module_data::property_count() const
{
    return 0;
}

QVariant checkerboard_module_data::property_value(size_t property_index) const
{
    return QVariant();
}

bool checkerboard_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    return false;
}

QString checkerboard_module_data::property_name(size_t property_index) const
{
    return QString();
}

//cylinders

QString cylinders_module_data::module_name() const
{
    return "Cylinders";
}

size_t cylinders_module_data::property_count() const
{
    return 1;
}

QVariant cylinders_module_data::property_value(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QVariant();
    }

    const array<QVariant, 1> properties
    {
        _module.frequency(),
    };

    return properties[property_index];
}

bool cylinders_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 1)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 1> properties
    {
        [&](const QVariant& v) { _module.set_frequency(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return false;
}

QString cylinders_module_data::property_name(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QString();
    }

    const array<QString, 1> properties
    {
        "frequency",
    };

    return properties[property_index];
}

//spheres

QString spheres_module_data::module_name() const
{
    return "Spheres";
}

size_t spheres_module_data::property_count() const
{
    return 1;
}

QVariant spheres_module_data::property_value(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QVariant();
    }

    const array<QVariant, 1> properties
    {
        _module.frequency(),
    };

    return properties[property_index];
}

bool spheres_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 1)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 1> properties
    {
        [&](const QVariant& v) { _module.set_frequency(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString spheres_module_data::property_name(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QString();
    }

    const array<QString, 1> properties
    {
        "frequency",
    };

    return properties[property_index];
}

//COMBINERS

//add

QString add_module_data::module_name() const
{
    return "Add";
}

//subtract

QString subtract_module_data::module_name() const
{
    return "Subtract";
}

//multiply

QString multiply_module_data::module_name() const
{
    return "Multiply";
}

//divide

QString divide_module_data::module_name() const
{
    return "Divide";
}
//power

QString power_module_data::module_name() const
{
    return "Power";
}

//min

QString min_module_data::module_name() const
{
    return "Min";
}

//max

QString max_module_data::module_name() const
{
    return "Max";
}

//MODIFIERS

//abs

QString abs_module_data::module_name() const
{
    return "Abs";
}

size_t abs_module_data::property_count() const
{
    return 0;
}

QVariant abs_module_data::property_value(size_t property_index) const
{
    return QVariant();
}

bool abs_module_data::set_property_value(size_t property_index, const QVariant & value)
{
    return false;
}

QString abs_module_data::property_name(size_t property_index) const
{
    return QString();
}

//base

QString base_module_data::module_name() const
{
    return "Base";
}

size_t base_module_data::property_count() const
{
    return 1;
}

QVariant base_module_data::property_value(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QVariant();
    }

    const array<QVariant, 1> properties
    {
        _module.base(),
    };

    return properties[property_index];
}

bool base_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 1)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 1> properties
    {
        [&](const QVariant& v) { _module.set_base(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString base_module_data::property_name(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QString();
    }

    const array<QString, 1> properties
    {
        "base",
    };

    return properties[property_index];
}

//exponent

QString exponent_module_data::module_name() const
{
    return "Exponent";
}

size_t exponent_module_data::property_count() const
{
    return 1;
}

QVariant exponent_module_data::property_value(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QVariant();
    }

    const array<QVariant, 1> properties
    {
        _module.exponent(),
    };

    return properties[property_index];
}

bool exponent_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 1)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 1> properties
    {
        [&](const QVariant& v) { _module.set_exponent(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString exponent_module_data::property_name(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QString();
    }

    const array<QString, 1> properties
    {
        "exponent",
    };

    return properties[property_index];
}

//clamp 

QString clamp_module_data::module_name() const
{
    return "Clamp";
}

size_t clamp_module_data::property_count() const
{
    return 2;
}

QVariant clamp_module_data::property_value(size_t property_index) const
{
    if (property_index >= 2)
    {
        return QVariant();
    }

    const array<QVariant, 2> properties
    {
        _module.lower_bound(),
        _module.upper_bound(),
    };

    return properties[property_index];
}

bool clamp_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 2)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 2> properties
    {
        [&](const QVariant& v) { _module.set_lower_bound(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_upper_bound(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString clamp_module_data::property_name(size_t property_index) const
{
    if (property_index >= 2)
    {
        return QString();
    }

    const array<QString, 2> properties
    {
        "lower_bound",
        "upper_bound",
    };

    return properties[property_index];
}

//scale_bias

QString scale_bias_module_data::module_name() const
{
    return "Scale Bias";
}

size_t scale_bias_module_data::property_count() const
{
    return 2;
}

QVariant scale_bias_module_data::property_value(size_t property_index) const
{
    if (property_index >= 2)
    {
        return QVariant();
    }

    const array<QVariant, 2> properties
    {
        _module.scale(),
        _module.bias(),
    };

    return properties[property_index];
}

bool scale_bias_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 2)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 2> properties
    {
        [&](const QVariant& v) { _module.set_scale(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_bias(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString scale_bias_module_data::property_name(size_t property_index) const
{
    if (property_index >= 2)
    {
        return QString();
    }

    const array<QString, 2> properties
    {
        "scale",
        "bias",
    };

    return properties[property_index];
}

//SELECTORS

//select

QString select_module_data::module_name() const
{
    return "Select";
}

size_t select_module_data::property_count() const
{
    return 3;
}

QVariant select_module_data::property_value(size_t property_index) const
{
    if (property_index >= 3)
    {
        return QVariant();
    }

    const array<QVariant, 3> properties
    {
        _module.min(),
        _module.max(),
        _module.falloff(),
    };

    return properties[property_index];
}

bool select_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 3)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 3> properties
    {
        [&](const QVariant& v) { _module.set_min(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_max(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_falloff(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString select_module_data::property_name(size_t property_index) const
{
    if (property_index >= 3)
    {
        return QString();
    }

    const array<QString, 3> properties
    {
        "min",
        "max",
        "falloff",
    };

    return properties[property_index];
}

//blend

QString blend_module_data::module_name() const
{
    return "Blend";
}

size_t blend_module_data::property_count() const
{
    return 0;
}

QVariant blend_module_data::property_value(size_t property_index) const
{
    return QVariant();
}

bool blend_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    return false;
}

QString blend_module_data::property_name(size_t property_index) const
{
    return QString();
}

//TRANSFORMERS

//displace

QString displace_module_data::module_name() const
{
    return "Displace";
}

vector<QString> displace_module_data::input_names() const
{
    return {"Computation module", "Displace X", "Displace Y", "Displace Z", "Displace W"};
}

size_t displace_module_data::property_count() const
{
    return 0;
}

QVariant displace_module_data::property_value(size_t property_index) const
{
    return QVariant();
}

bool displace_module_data::set_property_value(size_t property_index, const QVariant & value)
{
    return false;
}

QString displace_module_data::property_name(size_t property_index) const
{
    return QString();
}

//turbulence

QString turbulence_module_data::module_name() const
{
    return "Turbulence";
}

vector<QString> turbulence_module_data::input_names() const
{
    return { "Computation module", "Displace X", "Displace Y", "Displace Z", "Displace W" };
}

size_t turbulence_module_data::property_count() const
{
    return 1;
}

QVariant turbulence_module_data::property_value(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QVariant();
    }

    const array<QVariant, 1> properties
    {
        _module.power(),
    };

    return properties[property_index];
}

bool turbulence_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 1)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 1> properties
    {
        [&](const QVariant& v) { _module.set_power(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString turbulence_module_data::property_name(size_t property_index) const
{
    if (property_index >= 1)
    {
        return QString();
    }

    const array<QString, 1> properties
    {
        "power",
    };

    return properties[property_index];
}

//translate_point

QString translate_point_module_data::module_name() const
{
    return "Translate Point";
}

size_t translate_point_module_data::property_count() const
{
    return 4;
}

QVariant translate_point_module_data::property_value(size_t property_index) const
{
    if (property_index >= 4)
    {
        return QVariant();
    }

    const array<QVariant, 4> properties
    {
        _module.translation_x(),
        _module.translation_y(),
        _module.translation_z(),
        _module.translation_w(),
    };

    return properties[property_index];
}

bool translate_point_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 4)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 4> properties
    {
        [&](const QVariant& v) { _module.set_translation_x(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_translation_y(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_translation_z(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_translation_w(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString translate_point_module_data::property_name(size_t property_index) const
{
    if (property_index >= 4)
    {
        return QString();
    }

    const array<QString, 4> properties
    {
        "translation x",
        "translation y",
        "translation z",
        "translation w",
    };

    return properties[property_index];
}

//rotate_point

QString rotate_point_module_data::module_name() const
{
    return "Rotate Point";
}

size_t rotate_point_module_data::property_count() const
{
    return 6;
}

QVariant rotate_point_module_data::property_value(size_t property_index) const
{
    if (property_index >= 6)
    {
        return QVariant();
    }

    const array<QVariant, 6> properties
    {
        _module.xy_plane_rotation(),
        _module.yz_plane_rotation(),
        _module.zx_plane_rotation(),
        _module.xw_plane_rotation(),
        _module.yw_plane_rotation(),
        _module.zw_plane_rotation(),
    };

    return properties[property_index];
}

bool rotate_point_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 6)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 6> properties
    {
        [&](const QVariant& v) { _module.set_xy_plane_rotation(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_yz_plane_rotation(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_zx_plane_rotation(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_xw_plane_rotation(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_yw_plane_rotation(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_zw_plane_rotation(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString rotate_point_module_data::property_name(size_t property_index) const
{
    if (property_index >= 6)
    {
        return QString();
    }

    const array<QString, 6> properties
    {
        "xy plane rotation",
        "yz plane rotation",
        "zx plane rotation",
        "xw plane rotation",
        "yw plane rotation",
        "zw plane rotation",
    };

    return properties[property_index];
}

//scale_point

QString scale_point_module_data::module_name() const
{
    return "Scale Point";
}

size_t scale_point_module_data::property_count() const
{
    return 4;
}

QVariant scale_point_module_data::property_value(size_t property_index) const
{
    if (property_index >= 4)
    {
        return QVariant();
    }

    const array<QVariant, 4> properties
    {
        _module.scale_x(),
        _module.scale_y(),
        _module.scale_z(),
        _module.scale_w(),
    };

    return properties[property_index];
}

bool scale_point_module_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 4)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 4> properties
    {
        [&](const QVariant& v) { _module.set_scale_x(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_scale_y(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_scale_z(static_cast<float>(v.toDouble())); },
        [&](const QVariant& v) { _module.set_scale_w(static_cast<float>(v.toDouble())); },
    };

    properties[property_index](value);

    return true;
}

QString scale_point_module_data::property_name(size_t property_index) const
{
    if (property_index >= 4)
    {
        return QString();
    }

    const array<QString, 4> properties
    {
        "scale x",
        "scale y",
        "scale z",
        "scale w",
    };

    return properties[property_index];
}