#include "noise_voronoi_generator_module.hpp"
#include "noise_voronoi_generator_module_gpu_code.hpp"

#include <iostream>

GNOISE_NAMESPACE_BEGIN

void voronoi::create_kernels(
    cl_device_id target_device, const cl_context& context,
    array<cl_program, 4>& program_points, array<cl_kernel, 4>& kernel_points,
    array<cl_program, 4>& program_ranges, array<cl_kernel, 4>& kernel_ranges
)
{
    //1D
    {
        //points
        {
            std::string voronoi1Dpoints = std::string(gpu_generator_utility_value_noise_1D) + std::string(voronoi_value_point_1D) + std::string(voronoi_points_1D);
            const char* voronoi1D_code_data = voronoi1Dpoints.data();
            size_t voronoi1D_code_data_size = voronoi1Dpoints.size();
            program_points[0] = clCreateProgramWithSource(context, 1, &voronoi1D_code_data, &voronoi1D_code_data_size, nullptr);

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
            kernel_points[0] = clCreateKernel(program_points[0], "generate_voronoi_points_1D", nullptr);
        }
        //ranges
        {
            std::string voronoi1Dranges = std::string(gpu_generator_utility_value_noise_1D) + std::string(voronoi_value_point_1D) + std::string(voronoi_ranges_1D);
            const char* voronoi1D_code_data = voronoi1Dranges.data();
            size_t voronoi1D_code_data_size = voronoi1Dranges.size();
            program_ranges[0] = clCreateProgramWithSource(context, 1, &voronoi1D_code_data, &voronoi1D_code_data_size, nullptr);

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
            kernel_ranges[0] = clCreateKernel(program_ranges[0], "generate_voronoi_ranges_1D", nullptr);
        }
    }
    //2D
    {
        //points
        {
            std::string voronoi2Dpoints = std::string(gpu_generator_utility_value_noise_2D) + std::string(voronoi_value_point_2D) + std::string(voronoi_points_2D);
            const char* voronoi2D_code_data = voronoi2Dpoints.data();
            size_t voronoi2D_code_data_size = voronoi2Dpoints.size();
            program_points[1] = clCreateProgramWithSource(context, 1, &voronoi2D_code_data, &voronoi2D_code_data_size, nullptr);

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
            kernel_points[1] = clCreateKernel(program_points[1], "generate_voronoi_points_2D", nullptr);
        }
        //ranges
        {
            std::string voronoi2Dranges = std::string(gpu_generator_utility_value_noise_2D) + std::string(voronoi_value_point_2D) + std::string(voronoi_ranges_2D);
            const char* voronoi2D_code_data = voronoi2Dranges.data();
            size_t voronoi2D_code_data_size = voronoi2Dranges.size();
            program_ranges[1] = clCreateProgramWithSource(context, 1, &voronoi2D_code_data, &voronoi2D_code_data_size, nullptr);

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
            kernel_ranges[1] = clCreateKernel(program_ranges[1], "generate_voronoi_ranges_2D", nullptr);
        }
    }
    //3D
    {
        //points
        {
            std::string voronoi3Dpoints = std::string(gpu_generator_utility_value_noise_3D) + std::string(voronoi_value_point_3D) + std::string(voronoi_points_3D);
            const char* voronoi3D_code_data = voronoi3Dpoints.data();
            size_t voronoi3D_code_data_size = voronoi3Dpoints.size();
            program_points[2] = clCreateProgramWithSource(context, 1, &voronoi3D_code_data, &voronoi3D_code_data_size, nullptr);

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
            kernel_points[2] = clCreateKernel(program_points[2], "generate_voronoi_points_3D", nullptr);
        }
        //ranges
        {
            std::string voronoi3Dranges = std::string(gpu_generator_utility_value_noise_3D) + std::string(voronoi_value_point_3D) + std::string(voronoi_ranges_3D);
            const char* voronoi3D_code_data = voronoi3Dranges.data();
            size_t voronoi3D_code_data_size = voronoi3Dranges.size();
            program_ranges[2] = clCreateProgramWithSource(context, 1, &voronoi3D_code_data, &voronoi3D_code_data_size, nullptr);

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
            kernel_ranges[2] = clCreateKernel(program_ranges[2], "generate_voronoi_ranges_3D", nullptr);
        }
    }
    //4D
    {
        //points
        {
            std::string voronoi4Dpoints = std::string(gpu_generator_utility_value_noise_4D) + std::string(voronoi_value_point_4D) + std::string(voronoi_points_4D);
            const char* voronoi4D_code_data = voronoi4Dpoints.data();
            size_t voronoi4D_code_data_size = voronoi4Dpoints.size();
            program_points[3] = clCreateProgramWithSource(context, 1, &voronoi4D_code_data, &voronoi4D_code_data_size, nullptr);

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
            kernel_points[3] = clCreateKernel(program_points[3], "generate_voronoi_points_4D", nullptr);
        }
        //ranges
        {
            std::string voronoi4Dranges = std::string(gpu_generator_utility_value_noise_4D) + std::string(voronoi_value_point_4D) + std::string(voronoi_ranges_4D);
            const char* voronoi4D_code_data = voronoi4Dranges.data();
            size_t voronoi4D_code_data_size = voronoi4Dranges.size();
            program_ranges[3] = clCreateProgramWithSource(context, 1, &voronoi4D_code_data, &voronoi4D_code_data_size, nullptr);

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
            kernel_ranges[3] = clCreateKernel(program_ranges[3], "generate_voronoi_ranges_4D", nullptr);
        }
    }
}

array<float, 2> voronoi::get_module_config_f(const noise_voronoi_generator_module* module)
{
    return { module->frequency(), module->displacement() };
}

array<int, 2> voronoi::get_module_config_i(const noise_voronoi_generator_module* module)
{
    return { static_cast<int>(module->seed()), static_cast<int>(module->uses_distance()) };
}

void noise_voronoi_generator_module::set_frequency(float frequency)
{
    _frequency = frequency;
}

void noise_voronoi_generator_module::set_displacement(float displacement)
{
    _displacement = displacement;
}

void noise_voronoi_generator_module::set_seed(int seed)
{
    _seed = seed;
}

void noise_voronoi_generator_module::set_use_distance(bool use_distance)
{
    _use_distance = use_distance;
}

GNOISE_NAMESPACE_END