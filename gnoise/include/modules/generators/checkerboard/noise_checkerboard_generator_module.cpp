#include "noise_checkerboard_generator_module.hpp"
#include "noise_checkerboard_generator_module_gpu_code.hpp"

#include <iostream>

GNOISE_NAMESPACE_BEGIN

void checkerboard::create_kernels(
    cl_device_id target_device, const cl_context& context,
    array<cl_program, 4>& program_points, array<cl_kernel, 4>& kernel_points,
    array<cl_program, 4>& program_ranges, array<cl_kernel, 4>& kernel_ranges
)
{
    //1D
    {
        //points
        {
            std::string checkerboard1Dpoints = std::string(gpu_generator_utility_gradient_noise_1D) + std::string(checkerboard_value_point_1D) + std::string(checkerboard_points_1D);
            const char* checkerboard1D_code_data = checkerboard1Dpoints.data();
            size_t checkerboard1D_code_data_size = checkerboard1Dpoints.size();
            program_points[0] = clCreateProgramWithSource(context, 1, &checkerboard1D_code_data, &checkerboard1D_code_data_size, nullptr);

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
            kernel_points[0] = clCreateKernel(program_points[0], "generate_checkerboard_points_1D", nullptr);
        }
        //ranges
        {
            std::string checkerboard1Dranges = std::string(gpu_generator_utility_gradient_noise_1D) + std::string(checkerboard_value_point_1D) + std::string(checkerboard_ranges_1D);
            const char* checkerboard1D_code_data = checkerboard1Dranges.data();
            size_t checkerboard1D_code_data_size = checkerboard1Dranges.size();
            program_ranges[0] = clCreateProgramWithSource(context, 1, &checkerboard1D_code_data, &checkerboard1D_code_data_size, nullptr);

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
            kernel_ranges[0] = clCreateKernel(program_ranges[0], "generate_checkerboard_ranges_1D", nullptr);
        }
    }
    //2D
    {
        //points
        {
            std::string checkerboard2Dpoints = std::string(gpu_generator_utility_gradient_noise_2D) + std::string(checkerboard_value_point_2D) + std::string(checkerboard_points_2D);
            const char* checkerboard2D_code_data = checkerboard2Dpoints.data();
            size_t checkerboard2D_code_data_size = checkerboard2Dpoints.size();
            program_points[1] = clCreateProgramWithSource(context, 1, &checkerboard2D_code_data, &checkerboard2D_code_data_size, nullptr);

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
            kernel_points[1] = clCreateKernel(program_points[1], "generate_checkerboard_points_2D", nullptr);
        }
        //ranges
        {
            std::string checkerboard2Dranges = std::string(gpu_generator_utility_gradient_noise_2D) + std::string(checkerboard_value_point_2D) + std::string(checkerboard_ranges_2D);
            const char* checkerboard2D_code_data = checkerboard2Dranges.data();
            size_t checkerboard2D_code_data_size = checkerboard2Dranges.size();
            program_ranges[1] = clCreateProgramWithSource(context, 1, &checkerboard2D_code_data, &checkerboard2D_code_data_size, nullptr);

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
            kernel_ranges[1] = clCreateKernel(program_ranges[1], "generate_checkerboard_ranges_2D", nullptr);
        }
    }
    //3D
    {
        //points
        {
            std::string checkerboard3Dpoints = std::string(gpu_generator_utility_gradient_noise_3D) + std::string(checkerboard_value_point_3D) + std::string(checkerboard_points_3D);
            const char* checkerboard3D_code_data = checkerboard3Dpoints.data();
            size_t checkerboard3D_code_data_size = checkerboard3Dpoints.size();
            program_points[2] = clCreateProgramWithSource(context, 1, &checkerboard3D_code_data, &checkerboard3D_code_data_size, nullptr);

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
            kernel_points[2] = clCreateKernel(program_points[2], "generate_checkerboard_points_3D", nullptr);
        }
        //ranges
        {
            std::string checkerboard3Dranges = std::string(gpu_generator_utility_gradient_noise_3D) + std::string(checkerboard_value_point_3D) + std::string(checkerboard_ranges_3D);
            const char* checkerboard3D_code_data = checkerboard3Dranges.data();
            size_t checkerboard3D_code_data_size = checkerboard3Dranges.size();
            program_ranges[2] = clCreateProgramWithSource(context, 1, &checkerboard3D_code_data, &checkerboard3D_code_data_size, nullptr);

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
            kernel_ranges[2] = clCreateKernel(program_ranges[2], "generate_checkerboard_ranges_3D", nullptr);
        }
    }
    //4D
    {
        //points
        {
            std::string checkerboard4Dpoints = std::string(gpu_generator_utility_gradient_noise_4D) + std::string(checkerboard_value_point_4D) + std::string(checkerboard_points_4D);
            const char* checkerboard4D_code_data = checkerboard4Dpoints.data();
            size_t checkerboard4D_code_data_size = checkerboard4Dpoints.size();
            program_points[3] = clCreateProgramWithSource(context, 1, &checkerboard4D_code_data, &checkerboard4D_code_data_size, nullptr);

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
            kernel_points[3] = clCreateKernel(program_points[3], "generate_checkerboard_points_4D", nullptr);
        }
        //ranges
        {
            std::string checkerboard4Dranges = std::string(gpu_generator_utility_gradient_noise_4D) + std::string(checkerboard_value_point_4D) + std::string(checkerboard_ranges_4D);
            const char* checkerboard4D_code_data = checkerboard4Dranges.data();
            size_t checkerboard4D_code_data_size = checkerboard4Dranges.size();
            program_ranges[3] = clCreateProgramWithSource(context, 1, &checkerboard4D_code_data, &checkerboard4D_code_data_size, nullptr);

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
            kernel_ranges[3] = clCreateKernel(program_ranges[3], "generate_checkerboard_ranges_4D", nullptr);
        }
    }
}

array<float, 0> checkerboard::get_module_config_f(const noise_checkerboard_generator_module* module)
{
    return array<float, 0>();
}

array<int, 0> checkerboard::get_module_config_i(const noise_checkerboard_generator_module* module)
{
    return array<int, 0>();
}

GNOISE_NAMESPACE_END