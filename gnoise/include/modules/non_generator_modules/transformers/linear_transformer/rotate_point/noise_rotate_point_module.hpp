#pragma once

#include "../noise_linear_transformer_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_rotate_point_module;

inline constexpr float default_rotation_xy_plane = 0.0f;
inline constexpr float default_rotation_yz_plane = 0.0f;
inline constexpr float default_rotation_zx_plane = 0.0f;

inline constexpr float default_rotation_xw_plane = 0.0f;
inline constexpr float default_rotation_yw_plane = 0.0f;
inline constexpr float default_rotation_zw_plane = 0.0f;

struct rotate_point
{
    template<unsigned int D>
    inline static void transform(const noise_rotate_point_module* module, vectorf<D>& point);
};

class noise_rotate_point_module : public noise_linear_transformer_module_base_def_impl<rotate_point, noise_rotate_point_module>
{
public:
    noise_rotate_point_module() noexcept;
public:
    inline const auto&                              rotation_matrix() const
    {
        return _matrix;
    }
    inline float                                    xy_plane_rotation() const
    {
        return _xy_plane_rotation;
    }
    inline float                                    yz_plane_rotation() const
    {
        return _yz_plane_rotation;
    }
    inline float                                    zx_plane_rotation() const
    {
        return _zx_plane_rotation;
    }
    inline float                                    xw_plane_rotation() const
    {
        return _xw_plane_rotation;
    }
    inline float                                    yw_plane_rotation() const
    {
        return _yw_plane_rotation;
    }
    inline float                                    zw_plane_rotation() const
    {
        return _zw_plane_rotation;
    }

    void                                            set_xy_plane_rotation(float angle);
    void                                            set_yz_plane_rotation(float angle);
    void                                            set_zx_plane_rotation(float angle);
    void                                            set_xw_plane_rotation(float angle);
    void                                            set_yw_plane_rotation(float angle);
    void                                            set_zw_plane_rotation(float angle);
protected:
    virtual void                                    on_configuration_changed() override;
private:
    void                                            recalculate_rotation_matrix();
private:
    float                                           _xy_plane_rotation = default_rotation_xy_plane;
    float                                           _yz_plane_rotation = default_rotation_yz_plane;
    float                                           _zx_plane_rotation = default_rotation_zx_plane;
    float                                           _xw_plane_rotation = default_rotation_xw_plane;
    float                                           _yw_plane_rotation = default_rotation_yw_plane;
    float                                           _zw_plane_rotation = default_rotation_zw_plane;
    float                                           _matrix[4][4];
};

template<unsigned int D>
inline void multiply_matrix_vector(vectorf<D>& point, const float _matrix[4][4])
{
    vectorf<D> out;

    for (size_t y = 0; y < D; y++)
    {
        float inner_product = 0.0f;
        for (size_t x = 0; x < D; x++)
        {
            inner_product += point.coords[x] * _matrix[x][y];
        }
        out.coords[y] = inner_product;
    }
    for (size_t i = 0; i < D; i++)
    {
        point.coords[i] = out.coords[i];
    }
}

template<unsigned int D>
inline void rotate_point::transform(const noise_rotate_point_module* module, vectorf<D>& point)
{
    multiply_matrix_vector(point, module->rotation_matrix());
}

GNOISE_NAMESPACE_END