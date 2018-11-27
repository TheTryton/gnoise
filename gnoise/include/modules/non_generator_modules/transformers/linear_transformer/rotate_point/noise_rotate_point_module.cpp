#include "noise_rotate_point_module.hpp"

GNOISE_NAMESPACE_BEGIN

void matrix_identity(float mat[4][4])
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            mat[i][j] = 0.0f;
        }
    }

    for (size_t i = 0; i < 4; i++)
    {
        mat[i][i] = 1.0f;
    }
}

void matrix_multiply(float mat_out[4][4], float mat_in1[4][4], float mat_in2[4][4])
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            float inner_product = 0.0f;
            for (size_t k = 0; k < 4; k++)
            {
                inner_product += mat_in1[i][k] * mat_in2[k][j];
            }
            mat_out[i][j] = inner_product;
        }
    }
}

noise_rotate_point_module::noise_rotate_point_module() noexcept
{
    matrix_identity(_matrix);
}

void noise_rotate_point_module::set_xy_plane_rotation(float angle)
{
    _xy_plane_rotation = angle;
    recalculate_rotation_matrix();
}

void noise_rotate_point_module::set_yz_plane_rotation(float angle)
{
    _yz_plane_rotation = angle;
    recalculate_rotation_matrix();
}

void noise_rotate_point_module::set_zx_plane_rotation(float angle)
{
    _zx_plane_rotation = angle;
    recalculate_rotation_matrix();
}

void noise_rotate_point_module::set_xw_plane_rotation(float angle)
{
    _xw_plane_rotation = angle;
    recalculate_rotation_matrix();
}

void noise_rotate_point_module::set_yw_plane_rotation(float angle)
{
    _yw_plane_rotation = angle;
    recalculate_rotation_matrix();
}

void noise_rotate_point_module::set_zw_plane_rotation(float angle)
{
    _zw_plane_rotation = angle;
    recalculate_rotation_matrix();
}

void noise_rotate_point_module::on_configuration_changed()
{
}

void noise_rotate_point_module::recalculate_rotation_matrix()
{
    float xy_rotation_matrix[4][4];
    {
        float xy_cos = std::cos(_xy_plane_rotation);
        float xy_sin = std::sin(_xy_plane_rotation);

        matrix_identity(xy_rotation_matrix);
        xy_rotation_matrix[0][0] = xy_cos;
        xy_rotation_matrix[1][1] = xy_cos;
        xy_rotation_matrix[0][1] = -xy_sin;
        xy_rotation_matrix[1][0] = xy_sin;
    }
    float yz_rotation_matrix[4][4];
    {
        float yz_cos = std::cos(_yz_plane_rotation);
        float yz_sin = std::sin(_yz_plane_rotation);

        matrix_identity(yz_rotation_matrix);
        yz_rotation_matrix[1][1] = yz_cos;
        yz_rotation_matrix[2][2] = yz_cos;
        yz_rotation_matrix[1][2] = -yz_sin;
        yz_rotation_matrix[2][1] = yz_sin;
    }
    float zx_rotation_matrix[4][4];
    {
        float zx_cos = std::cos(_zx_plane_rotation);
        float zx_sin = std::sin(_zx_plane_rotation);

        matrix_identity(zx_rotation_matrix);
        zx_rotation_matrix[0][0] = zx_cos;
        zx_rotation_matrix[2][2] = zx_cos;
        zx_rotation_matrix[2][0] = -zx_sin;
        zx_rotation_matrix[0][2] = zx_sin;
    }
    float xw_rotation_matrix[4][4];
    {
        float xw_cos = std::cos(_xw_plane_rotation);
        float xw_sin = std::sin(_xw_plane_rotation);

        matrix_identity(xw_rotation_matrix);
        xw_rotation_matrix[0][0] = xw_cos;
        xw_rotation_matrix[3][3] = xw_cos;
        xw_rotation_matrix[0][3] = -xw_sin;
        xw_rotation_matrix[3][0] = xw_sin;
    }
    float yw_rotation_matrix[4][4];
    {
        float yw_cos = std::cos(_yw_plane_rotation);
        float yw_sin = std::sin(_yw_plane_rotation);

        matrix_identity(yw_rotation_matrix);
        yw_rotation_matrix[1][1] = yw_cos;
        yw_rotation_matrix[3][3] = yw_cos;
        yw_rotation_matrix[3][1] = -yw_sin;
        yw_rotation_matrix[1][3] = yw_sin;
    }
    float zw_rotation_matrix[4][4];
    {
        float zw_cos = std::cos(_zw_plane_rotation);
        float zw_sin = std::sin(_zw_plane_rotation);

        matrix_identity(zw_rotation_matrix);
        zw_rotation_matrix[2][2] = zw_cos;
        zw_rotation_matrix[3][3] = zw_cos;
        zw_rotation_matrix[3][2] = -zw_sin;
        xw_rotation_matrix[2][3] = zw_sin;
    }
    matrix_multiply(_matrix, xy_rotation_matrix, yz_rotation_matrix);
    matrix_multiply(_matrix, _matrix, zx_rotation_matrix);
    matrix_multiply(_matrix, _matrix, xw_rotation_matrix);
    matrix_multiply(_matrix, _matrix, yw_rotation_matrix);
    matrix_multiply(_matrix, _matrix, zw_rotation_matrix);
}

GNOISE_NAMESPACE_END