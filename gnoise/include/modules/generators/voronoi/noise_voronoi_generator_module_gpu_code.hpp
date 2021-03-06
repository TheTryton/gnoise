#pragma once

#include "../noise_generator_module_gpu_code.hpp"

constexpr std::string_view voronoi_value_point_1D =
"float voronoi_value_point_1D(vec1f v, global float* randoms, global int* generator_defaults, global float* config_f, global int* config_i)\n"
"{\n"
"   float freq = config_f[0];\n"
"   float disp = config_f[1];\n"
"   int _seed = config_i[0];\n"
"   bool uses_distance = config_i[1];\n"

"   v.x *= freq;\n"

"   vec1i vi;"
"   vi.x = v.x > 0.0f ? (int)v.x : (int)v.x - 1;\n"

"   float min_distance = 2147483647.0f;\n"

"   vec1f vc;\n"
"   vc.x = 0.0f;\n"

"   vec1i vcu;\n"

"   for (vcu.x = vi.x - 2; vcu.x <= vi.x + 2; vcu.x++)\n"
"   {\n"
"       vec1f vp;\n"
"       vp.x = vcu.x + value_noise_1D(vcu, _seed, randoms, generator_defaults);\n"

"       vec1f vd;\n"
"       vd.x = vp.x - v.x;\n"

"       float distance = vd.x * vd.x;\n"
"       if (distance < min_distance)\n"
"       {"
"           min_distance = distance;\n"
"           vc.x = vp.x;\n"
"       }\n"
"   }"

"   float value = 0.0f;\n"
"   if(uses_distance)\n"
"   {\n"
"       vec1f vd;\n"
"       vd.x = vc.x - v.x;\n"
"       value = vd.x * sqrt(3.0f) - 1.0f;\n"
"   }\n"

"   vec1i vci;\n"
"   vci.x = (int)floor(vc.x);\n"
"   return value + disp * value_noise_1D(vci, 0, randoms, generator_defaults);\n"
"}\n";

constexpr std::string_view voronoi_value_point_2D =
"float voronoi_value_point_2D(vec2f v, global float* randoms, global int* generator_defaults, global float* config_f, global int* config_i)\n"
"{\n"
"   float freq = config_f[0];\n"
"   float disp = config_f[1];\n"
"   int _seed = config_i[0];\n"
"   bool uses_distance = config_i[1];\n"

"   v.x *= freq;\n"
"   v.y *= freq;\n"

"   vec2i vi;\n"
"   vi.x = v.x > 0.0f ? (int)v.x : (int)v.x - 1;\n"
"   vi.y = v.y > 0.0f ? (int)v.y : (int)v.y - 1;\n"

"   float min_distance = 2147483647.0f;\n"

"   vec2f vc;\n"
"   vc.x = 0.0f;\n"
"   vc.y = 0.0f;\n"

"   vec2i vcu;\n"

"   for (vcu.x = vi.x - 2; vcu.x <= vi.x + 2; vcu.x++)\n"
"   {\n"
"       for (vcu.y = vi.y - 2; vcu.y <= vi.y + 2; vcu.y++)\n"
"       {\n"
"           vec2f vp;\n"
"           vp.x = vcu.x + value_noise_2D(vcu, _seed, randoms, generator_defaults);\n"
"           vp.y = vcu.y + value_noise_2D(vcu, _seed + 1, randoms, generator_defaults);\n"

"           vec2f vd;\n"
"           vd.x = vp.x - v.x;\n"
"           vd.y = vp.y - v.y;\n"

"           float distance = vd.x * vd.x + vd.y * vd.y;\n"
"           if (distance < min_distance)\n"
"           {\n"
"               min_distance = distance;\n"
"               vc.x = vp.x;\n"
"               vc.y = vp.y;\n"
"           }\n"
"       }\n"
"   }\n"

"   float value = 0.0f;\n"
"   if(uses_distance)\n"
"   {\n"
"       vec2f vd;\n"
"       vd.x = vc.x - v.x;\n"
"       vd.y = vc.y - v.y;\n"
"       value = sqrt(vd.x * vd.x + vd.y * vd.y) * sqrt(3.0f) - 1.0f;\n"
"   }\n"

"   vec2i vci;\n"
"   vci.x = (int)floor(vc.x);\n"
"   vci.y = (int)floor(vc.y);\n"
"   return value + disp * value_noise_2D(vci, 0, randoms, generator_defaults);\n"
"}\n";

constexpr std::string_view voronoi_value_point_3D =
"float voronoi_value_point_3D(vec3f v, global float* randoms, global int* generator_defaults, global float* config_f, global int* config_i)\n"
"{\n"
"   float freq = config_f[0];\n"
"   float disp = config_f[1];\n"
"   int _seed = config_i[0];\n"
"   bool uses_distance = config_i[1];\n"

"   v.x *= freq;\n"
"   v.y *= freq;\n"
"   v.z *= freq;\n"

"   vec3i vi;\n"
"   vi.x = v.x > 0.0f ? (int)v.x : (int)v.x - 1;\n"
"   vi.y = v.y > 0.0f ? (int)v.y : (int)v.y - 1;\n"
"   vi.z = v.z > 0.0f ? (int)v.z : (int)v.z - 1;\n"

"   float min_distance = 2147483647.0f;\n"

"   vec3f vc;\n"
"   vc.x = 0.0f;\n"
"   vc.y = 0.0f;\n"
"   vc.z = 0.0f;\n"

"   vec3i vcu;\n"

"   for (vcu.x = vi.x - 2; vcu.x <= vi.x + 2; vcu.x++)\n"
"   {\n"
"       for (vcu.y = vi.y - 2; vcu.y <= vi.y + 2; vcu.y++)\n"
"       {\n"
"           for (vcu.z = vi.z - 2; vcu.z <= vi.z + 2; vcu.z++)\n"
"           {\n"
"               vec3f vp;\n"
"               vp.x = vcu.x + value_noise_3D(vcu, _seed, randoms, generator_defaults);\n"
"               vp.y = vcu.y + value_noise_3D(vcu, _seed + 1, randoms, generator_defaults);\n"
"               vp.z = vcu.z + value_noise_3D(vcu, _seed + 2, randoms, generator_defaults);\n"

"               vec3f vd;\n"
"               vd.x = vp.x - v.x;\n"
"               vd.y = vp.y - v.y;\n"
"               vd.z = vp.z - v.z;\n"

"               float distance = vd.x * vd.x + vd.y * vd.y + vd.z * vd.z;\n"
"               if (distance < min_distance)\n"
"               {\n"
"                   min_distance = distance;\n"
"                   vc.x = vp.x;\n"
"                   vc.y = vp.y;\n"
"                   vc.z = vp.z;\n"
"               }\n"
"           }\n"
"       }\n"
"   }\n"

"   float value = 0.0f;\n"
"   if(uses_distance)\n"
"   {\n"
"       vec3f vd;\n"
"       vd.x = vc.x - v.x;\n"
"       vd.y = vc.y - v.y;\n"
"       vd.z = vc.z - v.z;\n"
"       value = sqrt(vd.x * vd.x + vd.y * vd.y + vd.z * vd.z) * sqrt(3.0f) - 1.0f;\n"
"   }\n"

"   vec3i vci;\n"
"   vci.x = (int)floor(vc.x);\n"
"   vci.y = (int)floor(vc.y);\n"
"   vci.z = (int)floor(vc.z);\n"
"   return value + disp * value_noise_3D(vci, 0, randoms, generator_defaults);\n"
"}\n";

constexpr std::string_view voronoi_value_point_4D =
"float voronoi_value_point_4D(vec4f v, global float* randoms, global int* generator_defaults, global float* config_f, global int* config_i)\n"
"{\n"
"   float freq = config_f[0];\n"
"   float disp = config_f[1];\n"
"   int _seed = config_i[0];\n"
"   bool uses_distance = config_i[1];\n"

"   v.x *= freq;\n"
"   v.y *= freq;\n"
"   v.z *= freq;\n"
"   v.w *= freq;\n"

"   vec4i vi;\n"
"   vi.x = v.x > 0.0f ? (int)v.x : (int)v.x - 1;\n"
"   vi.y = v.y > 0.0f ? (int)v.y : (int)v.y - 1;\n"
"   vi.z = v.z > 0.0f ? (int)v.z : (int)v.z - 1;\n"
"   vi.w = v.w > 0.0f ? (int)v.w : (int)v.w - 1;\n"

"   float min_distance = 2147483647.0f;\n"

"   vec4f vc;\n"
"   vc.x = 0.0f;\n"
"   vc.y = 0.0f;\n"
"   vc.z = 0.0f;\n"
"   vc.w = 0.0f;\n"

"   vec4i vcu;\n"

"   for (vcu.x = vi.x - 2; vcu.x <= vi.x + 2; vcu.x++)\n"
"   {\n"
"       for (vcu.y = vi.y - 2; vcu.y <= vi.y + 2; vcu.y++)\n"
"       {\n"
"           for (vcu.z = vi.z - 2; vcu.z <= vi.z + 2; vcu.z++)\n"
"           {\n"
"               for (vcu.w = vi.w - 2; vcu.w <= vi.w + 2; vcu.w++)\n"
"               {\n"
"                   vec4f vp;\n"
"                   vp.x = vcu.x + value_noise_4D(vcu, _seed, randoms, generator_defaults);\n"
"                   vp.y = vcu.y + value_noise_4D(vcu, _seed + 1, randoms, generator_defaults);\n"
"                   vp.z = vcu.z + value_noise_4D(vcu, _seed + 2, randoms, generator_defaults);\n"
"                   vp.w = vcu.w + value_noise_4D(vcu, _seed + 3, randoms, generator_defaults);\n"

"                   vec4f vd;\n"
"                   vd.x = vp.x - v.x;\n"
"                   vd.y = vp.y - v.y;\n"
"                   vd.z = vp.z - v.z;\n"
"                   vd.w = vp.w - v.w;\n"

"                   float distance = vd.x * vd.x + vd.y * vd.y + vd.z * vd.z + vd.w * vd.w;\n"
"                   if (distance < min_distance)\n"
"                   {\n"
"                       min_distance = distance;\n"
"                       vc.x = vp.x;\n"
"                       vc.y = vp.y;\n"
"                       vc.z = vp.z;\n"
"                       vc.w = vp.w;\n"
"                   }\n"
"               }\n"
"           }\n"
"       }\n"
"   }\n"

"   float value = 0.0f;\n"
"   if(uses_distance)\n"
"   {\n"
"       vec4f vd;\n"
"       vd.x = vc.x - v.x;\n"
"       vd.y = vc.y - v.y;\n"
"       vd.z = vc.z - v.z;\n"
"       vd.w = vc.w - v.w;\n"
"       value = sqrt(vd.x * vd.x + vd.y * vd.y + vd.z * vd.z + vd.w * vd.w) * sqrt(3.0f) - 1.0f;\n"
"   }\n"

"   vec4i vci;\n"
"   vci.x = (int)floor(vc.x);\n"
"   vci.y = (int)floor(vc.y);\n"
"   vci.z = (int)floor(vc.z);\n"
"   vci.w = (int)floor(vc.w);\n"
"   return value + disp * value_noise_4D(vci, 0, randoms, generator_defaults);\n"
"}\n";

constexpr std::string_view voronoi_points_1D =
"void kernel generate_voronoi_points_1D(\n"
"   global float* results,\n"
"   global vec1f* points,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   results[n] = voronoi_value_point_1D(points[n], randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view voronoi_ranges_1D =
"void kernel generate_voronoi_ranges_1D(\n"
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
"   results[n] = voronoi_value_point_1D(vr, randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view voronoi_points_2D =
"void kernel generate_voronoi_points_2D(\n"
"   global float* results,\n"
"   global vec2f* points,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   results[n] = voronoi_value_point_2D(points[n], randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view voronoi_ranges_2D =
"void kernel generate_voronoi_ranges_2D(\n"
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
"   results[n] = voronoi_value_point_2D(vr, randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view voronoi_points_3D =
"void kernel generate_voronoi_points_3D(\n"
"   global float* results,\n"
"   global vec3f* points,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   results[n] = voronoi_value_point_3D(points[n], randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view voronoi_ranges_3D =
"void kernel generate_voronoi_ranges_3D(\n"
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
"   results[n] = voronoi_value_point_3D(vr, randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view voronoi_points_4D =
"void kernel generate_voronoi_points_4D(\n"
"   global float* results,\n"
"   global vec4f* points,\n"
"   global float* randoms, global int* generator_defaults,\n"
"   global float* config_f, global int* config_i\n"
")\n"
"{\n"
"   int n = get_global_id(0);\n"
"   results[n] = voronoi_value_point_4D(points[n], randoms, generator_defaults, config_f, config_i);\n"
"}\n";

constexpr std::string_view voronoi_ranges_4D =
"void kernel generate_voronoi_ranges_4D(\n"
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
"   results[n] = voronoi_value_point_4D(vr, randoms, generator_defaults, config_f, config_i);\n"
"}\n";