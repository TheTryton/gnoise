#include <CL/cl.hpp>
#include <iostream>
#include <chrono>
#include "include/modules/generators/perlin/noise_perlin_generator_module.hpp"

using namespace std;

int main()
{
    gnoise::noise_perlin_generator_module* mod = new gnoise::noise_perlin_generator_module;

    gnoise::range2f a;
    gnoise::precision2 b;
    a.set_dimension_min<1>(0.0f);
    a.set_dimension_max<1>(1.0f);
    a.set_dimension_min<2>(0.0f);
    a.set_dimension_max<2>(1.0f);
    b.set_dimension_precision<1>(1000);
    b.set_dimension_precision<2>(1000);
    mod->configuration().set_computation_target(gnoise::module_computation_target::multi_thread_cpu);
    mod->configuration().multithreaded_target_configuration()->set_percentage_affinity(1.0f);
    auto start = chrono::high_resolution_clock::now();
    auto values = mod->compute(a, b);
    auto end = chrono::high_resolution_clock::now();
    cout << (end - start).count() / 1e9 << "s" << endl;


    /*using namespace cl;

    vector<Platform> all_platforms;
    Platform::get(&all_platforms);

    if(all_platforms.empty())
    {
        cout << "no platforms found" << endl;
    }
    else
    {
        for(auto& platform : all_platforms)
        {
            cout << platform.getInfo<CL_PLATFORM_NAME>() << ":" << endl;

            cout << endl;
            vector<Device> all_devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
            if(all_devices.empty())
            {
                cout << "no devices found" << endl;
            }
            else
            {
                for (auto& device : all_devices)
                {
                    cout << device.getInfo<CL_DEVICE_NAME>() << endl;
                }
            }
            cout << endl;
        }
    }
    */
    cin.get();
    return 0;
}