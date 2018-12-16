#include "noise_ridged_multifractal_generator_module.hpp"
#include "noise_ridged_multifractal_generator_module_gpu_code.hpp"

#include <iostream>

GNOISE_NAMESPACE_BEGIN

void ridged_multifractal::create_kernels(
    cl_device_id target_device, const cl_context& context,
    array<cl_program, 4>& program_points, array<cl_kernel, 4>& kernel_points,
    array<cl_program, 4>& program_ranges, array<cl_kernel, 4>& kernel_ranges
)
{
    //1D
    {
        //points
        {
            std::string ridged_multifractal1Dpoints = std::string(gpu_generator_utility_gradient_noise_1D) + std::string(ridged_multifractal_value_point_1D) + std::string(ridged_multifractal_points_1D);
            const char* ridged_multifractal1D_code_data = ridged_multifractal1Dpoints.data();
            size_t ridged_multifractal1D_code_data_size = ridged_multifractal1Dpoints.size();
            program_points[0] = clCreateProgramWithSource(context, 1, &ridged_multifractal1D_code_data, &ridged_multifractal1D_code_data_size, nullptr);

            if (clBuildProgram(program_points[0], 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
            {
                size_t build_log_size = 0;
                clGetProgramBuildInfo(program_points[0], target_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size);
                std::string build_log;
                build_log.resize(build_log_size);
                clGetProgramBuildInfo(program_points[0], target_device, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr);

                std::cout << build_log << std::endl;

                clReleaseProgram(program_points[0]);
                program_points[0] = nullptr;
            }
            kernel_points[0] = clCreateKernel(program_points[0], "generate_ridged_multifractal_points_1D", nullptr);
        }
        //ranges
        {
            std::string ridged_multifractal1Dranges = std::string(gpu_generator_utility_gradient_noise_1D) + std::string(ridged_multifractal_value_point_1D) + std::string(ridged_multifractal_ranges_1D);
            const char* ridged_multifractal1D_code_data = ridged_multifractal1Dranges.data();
            size_t ridged_multifractal1D_code_data_size = ridged_multifractal1Dranges.size();
            program_ranges[0] = clCreateProgramWithSource(context, 1, &ridged_multifractal1D_code_data, &ridged_multifractal1D_code_data_size, nullptr);

            if (clBuildProgram(program_ranges[0], 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
            {
                size_t build_log_size = 0;
                clGetProgramBuildInfo(program_ranges[0], target_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size);
                std::string build_log;
                build_log.resize(build_log_size);
                clGetProgramBuildInfo(program_ranges[0], target_device, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr);

                std::cout << build_log << std::endl;

                clReleaseProgram(program_ranges[0]);
                program_ranges[0] = nullptr;
            }
            kernel_ranges[0] = clCreateKernel(program_ranges[0], "generate_ridged_multifractal_ranges_1D", nullptr);
        }
    }
    //2D
    {
        //points
        {
            std::string ridged_multifractal2Dpoints = std::string(gpu_generator_utility_gradient_noise_2D) + std::string(ridged_multifractal_value_point_2D) + std::string(ridged_multifractal_points_2D);
            const char* ridged_multifractal2D_code_data = ridged_multifractal2Dpoints.data();
            size_t ridged_multifractal2D_code_data_size = ridged_multifractal2Dpoints.size();
            program_points[1] = clCreateProgramWithSource(context, 1, &ridged_multifractal2D_code_data, &ridged_multifractal2D_code_data_size, nullptr);

            if (clBuildProgram(program_points[1], 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
            {
                size_t build_log_size = 0;
                clGetProgramBuildInfo(program_points[1], target_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size);
                std::string build_log;
                build_log.resize(build_log_size);
                clGetProgramBuildInfo(program_points[1], target_device, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr);

                std::cout << build_log << std::endl;

                clReleaseProgram(program_points[1]);
                program_points[1] = nullptr;
            }
            kernel_points[1] = clCreateKernel(program_points[1], "generate_ridged_multifractal_points_2D", nullptr);
        }
        //ranges
        {
            std::string ridged_multifractal2Dranges = std::string(gpu_generator_utility_gradient_noise_2D) + std::string(ridged_multifractal_value_point_2D) + std::string(ridged_multifractal_ranges_2D);
            const char* ridged_multifractal2D_code_data = ridged_multifractal2Dranges.data();
            size_t ridged_multifractal2D_code_data_size = ridged_multifractal2Dranges.size();
            program_ranges[1] = clCreateProgramWithSource(context, 1, &ridged_multifractal2D_code_data, &ridged_multifractal2D_code_data_size, nullptr);

            if (clBuildProgram(program_ranges[1], 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
            {
                size_t build_log_size = 0;
                clGetProgramBuildInfo(program_ranges[1], target_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size);
                std::string build_log;
                build_log.resize(build_log_size);
                clGetProgramBuildInfo(program_ranges[1], target_device, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr);

                std::cout << build_log << std::endl;

                clReleaseProgram(program_ranges[1]);
                program_ranges[1] = nullptr;
            }
            kernel_ranges[1] = clCreateKernel(program_ranges[1], "generate_ridged_multifractal_ranges_2D", nullptr);
        }
    }
    //3D
    {
        //points
        {
            std::string ridged_multifractal3Dpoints = std::string(gpu_generator_utility_gradient_noise_3D) + std::string(ridged_multifractal_value_point_3D) + std::string(ridged_multifractal_points_3D);
            const char* ridged_multifractal3D_code_data = ridged_multifractal3Dpoints.data();
            size_t ridged_multifractal3D_code_data_size = ridged_multifractal3Dpoints.size();
            program_points[2] = clCreateProgramWithSource(context, 1, &ridged_multifractal3D_code_data, &ridged_multifractal3D_code_data_size, nullptr);

            if (clBuildProgram(program_points[2], 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
            {
                size_t build_log_size = 0;
                clGetProgramBuildInfo(program_points[2], target_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size);
                std::string build_log;
                build_log.resize(build_log_size);
                clGetProgramBuildInfo(program_points[2], target_device, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr);

                std::cout << build_log << std::endl;

                clReleaseProgram(program_points[2]);
                program_points[2] = nullptr;
            }
            kernel_points[2] = clCreateKernel(program_points[2], "generate_ridged_multifractal_points_3D", nullptr);
        }
        //ranges
        {
            std::string ridged_multifractal3Dranges = std::string(gpu_generator_utility_gradient_noise_3D) + std::string(ridged_multifractal_value_point_3D) + std::string(ridged_multifractal_ranges_3D);
            const char* ridged_multifractal3D_code_data = ridged_multifractal3Dranges.data();
            size_t ridged_multifractal3D_code_data_size = ridged_multifractal3Dranges.size();
            program_ranges[2] = clCreateProgramWithSource(context, 1, &ridged_multifractal3D_code_data, &ridged_multifractal3D_code_data_size, nullptr);

            if (clBuildProgram(program_ranges[2], 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
            {
                size_t build_log_size = 0;
                clGetProgramBuildInfo(program_ranges[2], target_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size);
                std::string build_log;
                build_log.resize(build_log_size);
                clGetProgramBuildInfo(program_ranges[2], target_device, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr);

                std::cout << build_log << std::endl;

                clReleaseProgram(program_ranges[2]);
                program_ranges[2] = nullptr;
            }
            kernel_ranges[2] = clCreateKernel(program_ranges[2], "generate_ridged_multifractal_ranges_3D", nullptr);
        }
    }
    //4D
    {
        //points
        {
            std::string ridged_multifractal4Dpoints = std::string(gpu_generator_utility_gradient_noise_4D) + std::string(ridged_multifractal_value_point_4D) + std::string(ridged_multifractal_points_4D);
            const char* ridged_multifractal4D_code_data = ridged_multifractal4Dpoints.data();
            size_t ridged_multifractal4D_code_data_size = ridged_multifractal4Dpoints.size();
            program_points[3] = clCreateProgramWithSource(context, 1, &ridged_multifractal4D_code_data, &ridged_multifractal4D_code_data_size, nullptr);

            if (clBuildProgram(program_points[3], 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
            {
                size_t build_log_size = 0;
                clGetProgramBuildInfo(program_points[3], target_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size);
                std::string build_log;
                build_log.resize(build_log_size);
                clGetProgramBuildInfo(program_points[3], target_device, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr);

                std::cout << build_log << std::endl;

                clReleaseProgram(program_points[3]);
                program_points[3] = nullptr;
            }
            kernel_points[3] = clCreateKernel(program_points[3], "generate_ridged_multifractal_points_4D", nullptr);
        }
        //ranges
        {
            std::string ridged_multifractal4Dranges = std::string(gpu_generator_utility_gradient_noise_4D) + std::string(ridged_multifractal_value_point_4D) + std::string(ridged_multifractal_ranges_4D);
            const char* ridged_multifractal4D_code_data = ridged_multifractal4Dranges.data();
            size_t ridged_multifractal4D_code_data_size = ridged_multifractal4Dranges.size();
            program_ranges[3] = clCreateProgramWithSource(context, 1, &ridged_multifractal4D_code_data, &ridged_multifractal4D_code_data_size, nullptr);

            if (clBuildProgram(program_ranges[3], 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
            {
                size_t build_log_size = 0;
                clGetProgramBuildInfo(program_ranges[3], target_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size);
                std::string build_log;
                build_log.resize(build_log_size);
                clGetProgramBuildInfo(program_ranges[3], target_device, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr);

                std::cout << build_log << std::endl;

                clReleaseProgram(program_ranges[3]);
                program_ranges[3] = nullptr;
            }
            kernel_ranges[3] = clCreateKernel(program_ranges[3], "generate_ridged_multifractal_ranges_4D", nullptr);
        }
    }
}

array<float, maximum_octave_count + 2> ridged_multifractal::get_module_config_f(const noise_ridged_multifractal_generator_module* module)
{
    array<float, maximum_octave_count + 2> data;
    std::copy(module->weights().begin(), module->weights().end(), data.begin() + 2);
    data[0] = module->frequency();
    data[1] = module->lacunarity();
    return data;
}

array<int, 3> ridged_multifractal::get_module_config_i(const noise_ridged_multifractal_generator_module* module)
{
    return { static_cast<int>(module->octave_count()), module->seed(), static_cast<int>(module->quality()) };
}

void noise_ridged_multifractal_generator_module::set_frequency(float frequency)
{
    _frequency = frequency;
}

void noise_ridged_multifractal_generator_module::set_lacunarity(float lacunarity)
{
    _lacunarity = lacunarity;
    calculate_weights();
}

bool noise_ridged_multifractal_generator_module::set_octave_count(unsigned int octave_count)
{
    if (octave_count > maximum_octave_count)
    {
        return false;
    }
    _octave_count = octave_count;
    return true;
}

void noise_ridged_multifractal_generator_module::set_seed(int seed)
{
    _seed = seed;
}

void noise_ridged_multifractal_generator_module::set_quality(noise_quality quality)
{
    _quality = quality;
}

void noise_ridged_multifractal_generator_module::calculate_weights()
{
    float h = 1.0f;
    float freq = 1.0f;
    for (unsigned int i = 0; i < maximum_octave_count; i++)
    {
        _weights[i] = std::pow(freq, -h);
        freq *= _lacunarity;
    }
}

noise_ridged_multifractal_generator_module::noise_ridged_multifractal_generator_module() noexcept :
    noise_generator_module_def_impl()
{
    calculate_weights();
}

GNOISE_NAMESPACE_END