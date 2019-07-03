#include "include/gnoise.hpp"
#include <iostream>
#define DLL_EXPORT _declspec(dllexport)

using namespace gnoise;

// ------------------------------- noise_module -------------------------------

extern "C" DLL_EXPORT float ModuleCompute1(noise_module* module, vector1f point)
{
    return module->compute(point);
}
extern "C" DLL_EXPORT float ModuleCompute2(noise_module* module, vector2f point)
{
    return module->compute(point);
}
extern "C" DLL_EXPORT float ModuleCompute3(noise_module* module, vector3f point)
{
    return module->compute(point);
}
extern "C" DLL_EXPORT float ModuleCompute4(noise_module* module, vector4f point)
{
    return module->compute(point);
}

extern "C" DLL_EXPORT void ModuleCompute5(noise_module* module, vector1f* points, float* returnArray, int size)
{
    auto result = module->compute(std::vector<vector1f>(points, points + size));
    std::copy(result.begin(), result.end(), returnArray);
}
extern "C" DLL_EXPORT void ModuleCompute6(noise_module* module, vector2f* points, float* returnArray, int size)
{
    auto result = module->compute(std::vector<vector2f>(points, points + size));
    std::copy(result.begin(), result.end(), returnArray);
}
extern "C" DLL_EXPORT void ModuleCompute7(noise_module* module, vector3f* points, float* returnArray, int size)
{
    auto result = module->compute(std::vector<vector3f>(points, points + size));
    std::copy(result.begin(), result.end(), returnArray);
}
extern "C" DLL_EXPORT void ModuleCompute8(noise_module* module, vector4f* points, float* returnArray, int size)
{
    auto result = module->compute(std::vector<vector4f>(points, points + size));
    std::copy(result.begin(), result.end(), returnArray);
}

extern "C" DLL_EXPORT void ModuleCompute9(noise_module* module, range1f range, precision1 precision, float* returnArray)
{
    auto result = module->compute(range, precision);
    std::copy(result.begin(), result.end(), returnArray);
}
extern "C" DLL_EXPORT void ModuleCompute10(noise_module* module, range2f range, precision2 precision, float* returnArray)
{
    auto result = module->compute(range, precision);
    std::copy(result.begin(), result.end(), returnArray);
}
extern "C" DLL_EXPORT void ModuleCompute11(noise_module* module, range3f range, precision3 precision, float* returnArray)
{
    auto result = module->compute(range, precision);
    std::copy(result.begin(), result.end(), returnArray);
}
extern "C" DLL_EXPORT void ModuleCompute12(noise_module* module, range4f range, precision4 precision, float* returnArray)
{
    auto result = module->compute(range, precision);
    std::copy(result.begin(), result.end(), returnArray);
}

extern "C" DLL_EXPORT int GetModuleType(noise_module* module)
{
    switch (module->module_type())
    {
    default:
    case module_type::generator:
        return 0;
    case module_type::modifier:
        return 1;
    case module_type::combiner:
        return 2;
    case module_type::selector:
        return 3;
    case module_type::transformer:
        return 4;
    case module_type::miscellaneous:
        return 5;
    case module_type::other:
        return 6;
    }
}

extern "C" DLL_EXPORT int ModuleGetComputationTarget(noise_module* module)
{
    switch (module->configuration().computation_target())
    {
    default:
    case module_computation_target::stcpu:
        return 0;
    case module_computation_target::mtcpu:
        return 1;
    case module_computation_target::gpu:
        return 2;
    }
}
extern "C" DLL_EXPORT void ModuleSetComputationTarget(noise_module* module, int target)
{
    switch (target)
    {
    default:
    case 0:
        module->configuration().set_computation_target(module_computation_target::stcpu);
        break;
    case 1:
        module->configuration().set_computation_target(module_computation_target::mtcpu);
        break;
    case 2:
        module->configuration().set_computation_target(module_computation_target::gpu);
        break;
    }
}

extern "C" DLL_EXPORT float ModuleGetMultithreadAffinity(noise_module* module, bool& result)
{
    if (module->configuration().computation_target() != module_computation_target::mtcpu)
    {
        result = false;
        return 0.0f;
    }

    result = true;

    return module->configuration().multithreaded_target_configuration()->percentage_affinity();
}
extern "C" DLL_EXPORT void ModuleSetMultithreadAffinity(noise_module* module, float affinity, bool& result)
{
    if (module->configuration().computation_target() != module_computation_target::mtcpu)
    {
        result = false;
        return;
    }

    result = true;

    module->configuration().multithreaded_target_configuration()->set_percentage_affinity(affinity);
}

extern "C" DLL_EXPORT void ModuleSetGPUTarget(noise_module* module, cl_device_id device_id, bool& result)
{
    if (module->configuration().computation_target() != module_computation_target::gpu)
    {
        result = false;
        return;
    }

    result = true;

    module->configuration().accelerated_target_configuration()->set_target(device_id);
}
extern "C" DLL_EXPORT cl_device_id ModuleGetGPUTarget(noise_module* module, bool& result)
{
    if (module->configuration().computation_target() != module_computation_target::gpu)
    {
        result = false;
        return nullptr;
    }

    result = true;

    return module->configuration().accelerated_target_configuration()->target();
}

extern "C" DLL_EXPORT int GetAvailableGPUCount()
{
    cl_uint platform_count = 0;

    clGetPlatformIDs(0, nullptr, &platform_count);

    std::vector<cl_platform_id> platform_ids(platform_count);

    clGetPlatformIDs(platform_count, platform_ids.data(), nullptr);

    cl_uint available_devices_count = 0;

    for (auto& platform_id : platform_ids)
    {
        cl_uint available_platform_devices_count = 0;

        clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, nullptr, &available_platform_devices_count);

        available_devices_count += available_platform_devices_count;
    }

    return static_cast<int>(available_devices_count);
}

extern "C" DLL_EXPORT void GetAvailableGPUs(cl_device_id* devices)
{
    cl_uint platform_count = 0;

    clGetPlatformIDs(0, nullptr, &platform_count);

    std::vector<cl_platform_id> platform_ids(platform_count);

    clGetPlatformIDs(platform_count, platform_ids.data(), nullptr);

    cl_uint offset = 0;

    for (auto& platform_id : platform_ids)
    {
        cl_uint available_platform_devices_count = 0;

        clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, nullptr, &available_platform_devices_count);

        clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, available_platform_devices_count, devices + offset, nullptr);

        offset += available_platform_devices_count;
    }
}

extern "C" DLL_EXPORT void GetGPUName(cl_device_id device_id, int available_size, char* name, int& full_size)
{
    if (!device_id)
        return;

    if (!available_size || !name)
    {
        size_t required_size = 0;

        clGetDeviceInfo(device_id, CL_DEVICE_NAME, 0, nullptr, &required_size);

        full_size = static_cast<int>(required_size);
    }
    else
    {
        clGetDeviceInfo(device_id, CL_DEVICE_NAME, static_cast<size_t>(available_size), static_cast<void*>(name), nullptr);
    }
}

extern "C" DLL_EXPORT void DestroyModule(noise_module* module)
{
    if (module)
    {
        delete module;
        module = nullptr;
    }
}

// ------------------------------- module specific exports -------------------------------

// ------------------------------- billow_generator_module -------------------------------

extern "C" DLL_EXPORT noise_billow_generator_module* ConstructBillowGeneratorModule()
{
    return new noise_billow_generator_module;
}

extern "C" DLL_EXPORT float GetBillowFrequency(noise_billow_generator_module* module)
{
    return module->frequency();
}

extern "C" DLL_EXPORT void SetBillowFrequency(noise_billow_generator_module* module, float frequency)
{
    module->set_frequency(frequency);
}

extern "C" DLL_EXPORT float GetBillowLacunarity(noise_billow_generator_module* module)
{
    return module->lacunarity();
}

extern "C" DLL_EXPORT void SetBillowLacunarity(noise_billow_generator_module* module, float lacunarity)
{
    module->set_lacunarity(lacunarity);
}

extern "C" DLL_EXPORT float GetBillowPersistence(noise_billow_generator_module* module)
{
    return module->persistence();
}

extern "C" DLL_EXPORT void SetBillowPersistence(noise_billow_generator_module* module, float persistence)
{
    module->set_persistence(persistence);
}

extern "C" DLL_EXPORT unsigned int GetBillowOctaveCount(noise_billow_generator_module* module)
{
    return module->octave_count();
}

extern "C" DLL_EXPORT void SetBillowOctaveCount(noise_billow_generator_module* module, unsigned int octave_count)
{
    module->set_octave_count(octave_count);
}

extern "C" DLL_EXPORT int GetBillowSeed(noise_billow_generator_module* module)
{
    return module->seed();
}

extern "C" DLL_EXPORT void SetBillowSeed(noise_billow_generator_module* module, int seed)
{
    module->set_seed(seed);
}

int noise_quality_to_int(noise_quality quality)
{
    switch (quality)
    {
    default:
    case noise_quality::fast:
        return 0;
    case noise_quality::standard:
        return 1;
    case noise_quality::best:
        return 2;
    }
}

noise_quality int_to_noise_quality(int v)
{
    switch (v)
    {
    default:
    case 0:
        return noise_quality::fast;
    case 1:
        return noise_quality::standard;
    case 2:
        return noise_quality::best;
    }
}

extern "C" DLL_EXPORT int GetBillowQuality(noise_billow_generator_module* module)
{
    return noise_quality_to_int(module->quality());
}

extern "C" DLL_EXPORT void SetBillowQuality(noise_billow_generator_module* module, int quality)
{
    module->set_quality(int_to_noise_quality(quality));
}

// ------------------------------- checkerboard_generator_module -------------------------------

extern "C" DLL_EXPORT noise_checkerboard_generator_module* ConstructCheckerboardGeneratorModule()
{
    return new noise_checkerboard_generator_module;
}

// ------------------------------- const_generator_module -------------------------------

extern "C" DLL_EXPORT noise_const_generator_module* ConstructConstGeneratorModule()
{
    return new noise_const_generator_module;
}

extern "C" DLL_EXPORT float GetConstValue(noise_const_generator_module* module)
{
    return module->const_value();
}

extern "C" DLL_EXPORT void SetConstValue(noise_const_generator_module* module, float const_value)
{
    module->set_const_value(const_value);
}

// ------------------------------- cylinders_generator_module -------------------------------

extern "C" DLL_EXPORT noise_cylinders_generator_module* ConstructCylindersGeneratorModule()
{
    return new noise_cylinders_generator_module;
}

extern "C" DLL_EXPORT float GetCylindersFrequency(noise_cylinders_generator_module* module)
{
    return module->frequency();
}

extern "C" DLL_EXPORT void SetCylindersFrequency(noise_cylinders_generator_module* module, float frequency)
{
    module->set_frequency(frequency);
}

// ------------------------------- perlin_generator_module -------------------------------

extern "C" DLL_EXPORT noise_perlin_generator_module* ConstructPerlinGeneratorModule()
{
    return new noise_perlin_generator_module;
}

extern "C" DLL_EXPORT float GetPerlinFrequency(noise_perlin_generator_module* module)
{
    return module->frequency();
}

extern "C" DLL_EXPORT void SetPerlinFrequency(noise_perlin_generator_module* module, float frequency)
{
    module->set_frequency(frequency);
}

extern "C" DLL_EXPORT float GetPerlinLacunarity(noise_perlin_generator_module* module)
{
    return module->lacunarity();
}

extern "C" DLL_EXPORT void SetPerlinLacunarity(noise_perlin_generator_module* module, float lacunarity)
{
    module->set_lacunarity(lacunarity);
}

extern "C" DLL_EXPORT float GetPerlinPersistence(noise_perlin_generator_module* module)
{
    return module->persistence();
}

extern "C" DLL_EXPORT void SetPerlinPersistence(noise_perlin_generator_module* module, float persistence)
{
    module->set_persistence(persistence);
}

extern "C" DLL_EXPORT unsigned int GetPerlinOctaveCount(noise_perlin_generator_module* module)
{
    return module->octave_count();
}

extern "C" DLL_EXPORT void SetPerlinOctaveCount(noise_perlin_generator_module* module, unsigned int octave_count)
{
    module->set_octave_count(octave_count);
}

extern "C" DLL_EXPORT int GetPerlinSeed(noise_perlin_generator_module* module)
{
    return module->seed();
}

extern "C" DLL_EXPORT void SetPerlinSeed(noise_perlin_generator_module* module, int seed)
{
    module->set_seed(seed);
}

extern "C" DLL_EXPORT int GetPerlinQuality(noise_perlin_generator_module* module)
{
    return noise_quality_to_int(module->quality());
}

extern "C" DLL_EXPORT void SetPerlinQuality(noise_perlin_generator_module* module, int quality)
{
    module->set_quality(int_to_noise_quality(quality));
}

// ------------------------------- ridged_multifractal_generator_module -------------------------------

extern "C" DLL_EXPORT noise_ridged_multifractal_generator_module* ConstructRidgedMultifractalGeneratorModule()
{
    return new noise_ridged_multifractal_generator_module;
}

extern "C" DLL_EXPORT float GetRidgedMultifractalFrequency(noise_ridged_multifractal_generator_module* module)
{
    return module->frequency();
}

extern "C" DLL_EXPORT void SetRidgedMultifractalFrequency(noise_ridged_multifractal_generator_module* module, float frequency)
{
    module->set_frequency(frequency);
}

extern "C" DLL_EXPORT float GetRidgedMultifractalLacunarity(noise_ridged_multifractal_generator_module* module)
{
    return module->lacunarity();
}

extern "C" DLL_EXPORT void SetRidgedMultifractalLacunarity(noise_ridged_multifractal_generator_module* module, float lacunarity)
{
    module->set_lacunarity(lacunarity);
}

extern "C" DLL_EXPORT unsigned int GetRidgedMultifractalOctaveCount(noise_ridged_multifractal_generator_module* module)
{
    return module->octave_count();
}

extern "C" DLL_EXPORT void SetRidgedMultifractalOctaveCount(noise_ridged_multifractal_generator_module* module, unsigned int octave_count)
{
    module->set_octave_count(octave_count);
}

extern "C" DLL_EXPORT int GetRidgedMultifractalSeed(noise_ridged_multifractal_generator_module* module)
{
    return module->seed();
}

extern "C" DLL_EXPORT void SetRidgedMultifractalSeed(noise_ridged_multifractal_generator_module* module, int seed)
{
    module->set_seed(seed);
}

extern "C" DLL_EXPORT int GetRidgedMultifractalQuality(noise_ridged_multifractal_generator_module* module)
{
    return noise_quality_to_int(module->quality());
}

extern "C" DLL_EXPORT void SetRidgedMultifractalQuality(noise_ridged_multifractal_generator_module* module, int quality)
{
    module->set_quality(int_to_noise_quality(quality));
}

// ------------------------------- spheres_generator_module -------------------------------

extern "C" DLL_EXPORT noise_spheres_generator_module* ConstructSpheresGeneratorModule()
{
    return new noise_spheres_generator_module;
}

extern "C" DLL_EXPORT float GetSpheresFrequency(noise_spheres_generator_module* module)
{
    return module->frequency();
}

extern "C" DLL_EXPORT void SetSpheresFrequency(noise_spheres_generator_module* module, float frequency)
{
    module->set_frequency(frequency);
}

// ------------------------------- voronoi_generator_module -------------------------------

extern "C" DLL_EXPORT noise_voronoi_generator_module* ConstructVoronoiGeneratorModule()
{
    return new noise_voronoi_generator_module;
}

extern "C" DLL_EXPORT float GetVoronoiFrequency(noise_voronoi_generator_module* module)
{
    return module->frequency();
}

extern "C" DLL_EXPORT void SetVoronoiFrequency(noise_voronoi_generator_module* module, float frequency)
{
    module->set_frequency(frequency);
}

extern "C" DLL_EXPORT float GetVoronoiDisplacement(noise_voronoi_generator_module* module)
{
    return module->displacement();
}

extern "C" DLL_EXPORT void SetVoronoiDisplacement(noise_voronoi_generator_module* module, float displacement)
{
    module->set_displacement(displacement);
}

extern "C" DLL_EXPORT int GetVoronoiSeed(noise_voronoi_generator_module* module)
{
    return module->seed();
}

extern "C" DLL_EXPORT void SetVoronoiSeed(noise_voronoi_generator_module* module, int seed)
{
    module->set_seed(seed);
}

extern "C" DLL_EXPORT bool GetVoronoiUseDistance(noise_voronoi_generator_module* module)
{
    return module->uses_distance();
}

extern "C" DLL_EXPORT void SetVoronoiUseDistance(noise_voronoi_generator_module* module, bool use_distance)
{
    module->set_use_distance(use_distance);
}

// ------------------------------- non_generator_module -------------------------------

// ------------------------------- combiner_module -------------------------------

extern "C" DLL_EXPORT int GetNonGeneratorInputModulesCount(noise_non_generator_module_base* module)
{
    return static_cast<int>(module->input_modules_count());
}

extern "C" DLL_EXPORT const noise_module* GetNonGeneratorInputModule(noise_non_generator_module_base* module, int index)
{
    return module->input_module(static_cast<size_t>(index));
}

extern "C" DLL_EXPORT bool SetNonGeneratorInputModule(noise_non_generator_module_base* module, int index, noise_module* input_module)
{
    return module->set_input_module(static_cast<size_t>(index), input_module);
}

// ------------------------------- add_module -------------------------------

extern "C" DLL_EXPORT noise_add_module* ConstructAddModule()
{
    return new noise_add_module;
}

// ------------------------------- subtract_module -------------------------------

extern "C" DLL_EXPORT noise_subtract_module* ConstructSubtractModule()
{
    return new noise_subtract_module;
}

// ------------------------------- multiply_module -------------------------------

extern "C" DLL_EXPORT noise_multiply_module* ConstructMultiplyModule()
{
    return new noise_multiply_module;
}

// ------------------------------- divide_module -------------------------------

extern "C" DLL_EXPORT noise_divide_module* ConstructDivideModule()
{
    return new noise_divide_module;
}

// ------------------------------- power_module -------------------------------

extern "C" DLL_EXPORT noise_power_module* ConstructPowerModule()
{
    return new noise_power_module;
}

// ------------------------------- min_module -------------------------------

extern "C" DLL_EXPORT noise_min_module* ConstructMinModule()
{
    return new noise_min_module;
}

// ------------------------------- max_module -------------------------------

extern "C" DLL_EXPORT noise_max_module* ConstructMaxModule()
{
    return new noise_max_module;
}

// ------------------------------- modifier_module -------------------------------

// ------------------------------- abs_module -------------------------------

extern "C" DLL_EXPORT noise_abs_module* ConstructAbsModule()
{
    return new noise_abs_module;
}

// ------------------------------- base_module -------------------------------

extern "C" DLL_EXPORT noise_base_module* ConstructBaseModule()
{
    return new noise_base_module;
}

extern "C" DLL_EXPORT float GetBaseModuleBase(noise_base_module* module)
{
    return module->base();
}

extern "C" DLL_EXPORT void SetBaseModuleBase(noise_base_module* module, float base)
{
    module->set_base(base);
}

// ------------------------------- clamp_module -------------------------------

extern "C" DLL_EXPORT noise_clamp_module* ConstructClampModule()
{
    return new noise_clamp_module;
}

extern "C" DLL_EXPORT float GetClampLowerBound(noise_clamp_module* module)
{
    return module->lower_bound();
}

extern "C" DLL_EXPORT void SetClampLowerBound(noise_clamp_module* module, float lower_bound)
{
    module->set_lower_bound(lower_bound);
}

extern "C" DLL_EXPORT float GetClampUpperBound(noise_clamp_module* module)
{
    return module->upper_bound();
}

extern "C" DLL_EXPORT void SetClampUpperBound(noise_clamp_module* module, float upper_bound)
{
    module->set_upper_bound(upper_bound);
}

// ------------------------------- exponent_module -------------------------------

extern "C" DLL_EXPORT noise_exponent_module* ConstructExponentModule()
{
    return new noise_exponent_module;
}

extern "C" DLL_EXPORT float GetExponentModuleExponent(noise_exponent_module* module)
{
    return module->exponent();
}

extern "C" DLL_EXPORT void SetExponentModuleExponent(noise_exponent_module* module, float exponent)
{
    module->set_exponent(exponent);
}

// ------------------------------- scale_bias_module -------------------------------

extern "C" DLL_EXPORT noise_scale_bias_module* ConstructScaleBiasModule()
{
    return new noise_scale_bias_module;
}

extern "C" DLL_EXPORT float GetScaleBiasScale(noise_scale_bias_module* module)
{
    return module->scale();
}

extern "C" DLL_EXPORT void SetScaleBiasScale(noise_scale_bias_module* module, float scale)
{
    module->set_scale(scale);
}

extern "C" DLL_EXPORT float GetScaleBiasBias(noise_scale_bias_module* module)
{
    return module->bias();
}

extern "C" DLL_EXPORT void SetScaleBiasBias(noise_scale_bias_module* module, float bias)
{
    module->set_bias(bias);
}

// ------------------------------- selector_module -------------------------------

// ------------------------------- blend_module -------------------------------

extern "C" DLL_EXPORT noise_blend_module* ConstructBlendModule()
{
    return new noise_blend_module;
}

// ------------------------------- select_module -------------------------------

extern "C" DLL_EXPORT noise_select_module* ConstructSelectModule()
{
    return new noise_select_module;
}

extern "C" DLL_EXPORT float GetSelectFalloff(noise_select_module* module)
{
    return module->falloff();
}

extern "C" DLL_EXPORT void SetSelectFalloff(noise_select_module* module, float falloff)
{
    module->set_falloff(falloff);
}

extern "C" DLL_EXPORT float GetSelectMin(noise_select_module* module)
{
    return module->min();
}

extern "C" DLL_EXPORT void SetSelectMin(noise_select_module* module, float min)
{
    module->set_min(min);
}

extern "C" DLL_EXPORT float GetSelectMax(noise_select_module* module)
{
    return module->min();
}

extern "C" DLL_EXPORT void SetSelectMax(noise_select_module* module, float max)
{
    module->set_max(max);
}

// ------------------------------- transformer_module -------------------------------

// ------------------------------- turbulence_module -------------------------------

extern "C" DLL_EXPORT noise_turbulence_module* ConstructTurbulenceModule()
{
    return new noise_turbulence_module;
}

extern "C" DLL_EXPORT float GetTurbulencePower(noise_turbulence_module* module)
{
    return module->power();
}

extern "C" DLL_EXPORT void SetTurbulencePower(noise_turbulence_module* module, float power)
{
    module->set_power(power);
}

// ------------------------------- displace_module -------------------------------

extern "C" DLL_EXPORT noise_displace_module* ConstructDisplaceModule()
{
    return new noise_displace_module;
}

// ------------------------------- linear_transformation_module -------------------------------

// ------------------------------- rotate_point_module -------------------------------

extern "C" DLL_EXPORT noise_rotate_point_module* ConstructRotatePointModule()
{
    return new noise_rotate_point_module;
}

extern "C" DLL_EXPORT float GetXYPlaneRotation(noise_rotate_point_module* module)
{
    return module->xy_plane_rotation();
}

extern "C" DLL_EXPORT void SetXYPlaneRotation(noise_rotate_point_module* module, float rotation)
{
    module->set_xy_plane_rotation(rotation);
}

extern "C" DLL_EXPORT float GetYZPlaneRotation(noise_rotate_point_module* module)
{
    return module->yz_plane_rotation();
}

extern "C" DLL_EXPORT void SetYZPlaneRotation(noise_rotate_point_module* module, float rotation)
{
    module->set_yz_plane_rotation(rotation);
}

extern "C" DLL_EXPORT float GetZXPlaneRotation(noise_rotate_point_module* module)
{
    return module->zx_plane_rotation();
}

extern "C" DLL_EXPORT void SetZXPlaneRotation(noise_rotate_point_module* module, float rotation)
{
    module->set_zx_plane_rotation(rotation);
}

extern "C" DLL_EXPORT float GetXWPlaneRotation(noise_rotate_point_module* module)
{
    return module->xw_plane_rotation();
}

extern "C" DLL_EXPORT void SetXWPlaneRotation(noise_rotate_point_module* module, float rotation)
{
    module->set_xw_plane_rotation(rotation);
}

extern "C" DLL_EXPORT float GetYWPlaneRotation(noise_rotate_point_module* module)
{
    return module->yw_plane_rotation();
}

extern "C" DLL_EXPORT void SetYWPlaneRotation(noise_rotate_point_module* module, float rotation)
{
    module->set_yw_plane_rotation(rotation);
}

extern "C" DLL_EXPORT float GetZWPlaneRotation(noise_rotate_point_module* module)
{
    return module->zw_plane_rotation();
}

extern "C" DLL_EXPORT void SetZWPlaneRotation(noise_rotate_point_module* module, float rotation)
{
    module->set_zw_plane_rotation(rotation);
}

// ------------------------------- translate_point_module -------------------------------

extern "C" DLL_EXPORT noise_translate_point_module* ConstructTranslatePointModule()
{
    return new noise_translate_point_module;
}

extern "C" DLL_EXPORT float GetXTranslation(noise_translate_point_module* module)
{
    return module->translation_x();
}

extern "C" DLL_EXPORT void SetXTranslation(noise_translate_point_module* module, float translation)
{
    module->set_translation_x(translation);
}

extern "C" DLL_EXPORT float GetYTranslation(noise_translate_point_module* module)
{
    return module->translation_y();
}

extern "C" DLL_EXPORT void SetYTranslation(noise_translate_point_module* module, float translation)
{
    module->set_translation_y(translation);
}

extern "C" DLL_EXPORT float GetZTranslation(noise_translate_point_module* module)
{
    return module->translation_z();
}

extern "C" DLL_EXPORT void SetZTranslation(noise_translate_point_module* module, float translation)
{
    module->set_translation_z(translation);
}

extern "C" DLL_EXPORT float GetWTranslation(noise_translate_point_module* module)
{
    return module->translation_w();
}

extern "C" DLL_EXPORT void SetWTranslation(noise_translate_point_module* module, float translation)
{
    module->set_translation_w(translation);
}

// ------------------------------- scale_point_module -------------------------------

extern "C" DLL_EXPORT noise_scale_point_module* ConstructScalePointModule()
{
    return new noise_scale_point_module;
}

extern "C" DLL_EXPORT float GetXScale(noise_scale_point_module* module)
{
    return module->scale_x();
}

extern "C" DLL_EXPORT void SetXScale(noise_scale_point_module* module, float translation)
{
    module->set_scale_x(translation);
}

extern "C" DLL_EXPORT float GetYScale(noise_scale_point_module* module)
{
    return module->scale_y();
}

extern "C" DLL_EXPORT void SetYScale(noise_scale_point_module* module, float translation)
{
    module->set_scale_y(translation);
}

extern "C" DLL_EXPORT float GetZScale(noise_scale_point_module* module)
{
    return module->scale_z();
}

extern "C" DLL_EXPORT void SetZScale(noise_scale_point_module* module, float translation)
{
    module->set_scale_z(translation);
}

extern "C" DLL_EXPORT float GetWScale(noise_scale_point_module* module)
{
    return module->scale_w();
}

extern "C" DLL_EXPORT void SetWScale(noise_scale_point_module* module, float translation)
{
    module->set_scale_w(translation);
}