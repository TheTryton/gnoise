#pragma once

#include "../noise_generator_module_gpu_code.hpp"

constexpr std::string_view checkerboard_value_point_1D =
"float checkerboard_value_point_1D(vec1f v, global float* randoms, global int* generator_defaults, global float* config_f, global int* config_i)\n"
"{\n"
"   vec1i v_i;"
"   v_i.x = (int)floor(make_int32_range(v.x));"
"   return (v_i.x & 1) ? -1.0f : 1.0f;\n"
"}\n";

constexpr std::string_view checkerboard_value_point_2D =
"float checkerboard_value_point_2D(vec2f v, global float* randoms, global int* generator_defaults, global float* config_f, global int* config_i)\n"
"{\n"
"   vec2i v_i;"
"   v_i.x = (int)floor(make_int32_range(v.x));"
"   v_i.y = (int)floor(make_int32_range(v.y));"
"   return (v_i.x & 1 ^ v_i.y & 1) ? -1.0f : 1.0f;\n"
"}\n";

constexpr std::string_view checkerboard_value_point_3D =
"float checkerboard_value_point_3D(vec3f v, global float* randoms, global int* generator_defaults, global float* config_f, global int* config_i)\n"
"{\n"
"   vec3i v_i;"
"   v_i.x = (int)floor(make_int32_range(v.x));"
"   v_i.y = (int)floor(make_int32_range(v.y));"
"   v_i.z = (int)floor(make_int32_range(v.z));"
"   return (v_i.x & 1 ^ v_i.y & 1 ^ v_i.z & 1) ? -1.0f : 1.0f;\n"
"}\n";

constexpr std::string_view checkerboard_value_point_4D =
"float checkerboard_value_point_4D(vec4f v, global float* randoms, global int* generator_defaults, global float* config_f, global int* config_i)\n"
"{\n"
"   vec4i v_i;"
"   v_i.x = (int)floor(make_int32_range(v.x));"
"   v_i.y = (int)floor(make_int32_range(v.y));"
"   v_i.z = (int)floor(make_int32_range(v.z));"
"   v_i.w = (int)floor(make_int32_range(v.w));"
"   return (v_i.x & 1 ^ v_i.y & 1 ^ v_i.z & 1 ^ v_i.w & 1) ? -1.0f : 1.0f;\n"
"}\n";

constexpr std::string_view checkerboard_points_1D =
"void kernel generate_checkerboard_points_1D(\n"
"   global float* results,\n"
"   global vec1f* points,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   results[n] = checkerboard_value_point_1D(points[n], randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view checkerboard_ranges_1D =
"void kernel generate_checkerboard_ranges_1D(\n"
"   global float* results,\n"
"   range1f range, precision1 precision,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   vec1i vz;\n"
"   vz.x = n%precision.x;\n"
"   vec1f vr;\n"
"   vr.x = vz.x/(float)(precision.x-1);\n"
"   vr.x = interpolate_linear(range.x.x, range.x.y, vr.x);\n"
"   results[n] = checkerboard_value_point_1D(vr, randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view checkerboard_points_2D =
"void kernel generate_checkerboard_points_2D(\n"
"   global float* results,\n"
"   global vec2f* points,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   results[n] = checkerboard_value_point_2D(points[n], randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view checkerboard_ranges_2D =
"void kernel generate_checkerboard_ranges_2D(\n"
"   global float* results,\n"
"   range2f range, precision2 precision,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   vec2i vz;\n"
"   vz.x = n%precision.x;\n"
"   vz.y = n/precision.x%precision.y;\n"
"   vec2f vr;\n"
"   vr.x = vz.x/(float)(precision.x-1);\n"
"   vr.y = vz.y/(float)(precision.y-1);\n"
"   vr.x = interpolate_linear(range.x.x, range.x.y, vr.x);\n"
"   vr.y = interpolate_linear(range.y.x, range.y.y, vr.y);\n"
"   results[n] = checkerboard_value_point_2D(vr, randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view checkerboard_points_3D =
"void kernel generate_checkerboard_points_3D(\n"
"   global float* results,\n"
"   global vec3f* points,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   results[n] = checkerboard_value_point_3D(points[n], randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view checkerboard_ranges_3D =
"void kernel generate_checkerboard_ranges_3D(\n"
"   global float* results,\n"
"   range3f range, precision3 precision,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   vec3i vz;\n"
"   vz.x = n%precision.x;\n"
"   vz.y = n/precision.x%precision.y;\n"
"   vz.z = n/precision.x/precision.y%precision.z;\n"
"   vec3f vr;\n"
"   vr.x = vz.x/(float)(precision.x-1);\n"
"   vr.y = vz.y/(float)(precision.y-1);\n"
"   vr.z = vz.z/(float)(precision.z-1);\n"
"   vr.x = interpolate_linear(range.x.x, range.x.y, vr.x);\n"
"   vr.y = interpolate_linear(range.y.x, range.y.y, vr.y);\n"
"   vr.z = interpolate_linear(range.z.x, range.z.y, vr.z);\n"
"   results[n] = checkerboard_value_point_3D(vr, randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view checkerboard_points_4D =
"void kernel generate_checkerboard_points_4D(\n"
"   global float* results,\n"
"   global vec4f* points,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   results[n] = checkerboard_value_point_4D(points[n], randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view checkerboard_ranges_4D =
"void kernel generate_checkerboard_ranges_4D(\n"
"   global float* results,\n"
"   range4f range, precision4 precision,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   vec4i vz;\n"
"   vz.x = n%precision.x;\n"
"   vz.y = n/precision.x%precision.y;\n"
"   vz.z = n/precision.x/precision.y%precision.z;\n"
"   vz.w = n/precision.x/precision.y/precision.z%precision.w;\n"
"   vec4f vr;\n"
"   vr.x = vz.x/(float)(precision.x-1);\n"
"   vr.y = vz.y/(float)(precision.y-1);\n"
"   vr.z = vz.z/(float)(precision.z-1);\n"
"   vr.w = vz.w/(float)(precision.w-1);\n"
"   vr.x = interpolate_linear(range.x.x, range.x.y, vr.x);\n"
"   vr.y = interpolate_linear(range.y.x, range.y.y, vr.y);\n"
"   vr.z = interpolate_linear(range.z.x, range.z.y, vr.z);\n"
"   vr.w = interpolate_linear(range.w.x, range.w.y, vr.w);\n"
"   results[n] = checkerboard_value_point_4D(vr, randoms, generator_defaults, config_f, config_i);\n"
"}\n";