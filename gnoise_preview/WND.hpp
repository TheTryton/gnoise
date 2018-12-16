#pragma once

#include <QtWidgets>
#include "include/modules/generators/voronoi/noise_voronoi_generator_module.hpp"
#include "include/modules/generators/perlin/noise_perlin_generator_module.hpp"
#include "include/modules/generators/ridged_multifractal/noise_ridged_multifractal_generator_module.hpp"
#include "include/modules/generators/billow/noise_billow_generator_module.hpp"
#include "include/modules/generators/checkerboard/noise_checkerboard_generator_module.hpp"
#include "include/modules/generators/spheres/noise_spheres_generator_module.hpp"
#include "include/modules/generators/cylinders/noise_cylinders_generator_module.hpp"
#include "include/modules/non_generator_modules/combiners/noise_combiner_module.hpp"
#include "include/modules/non_generator_modules/transformers/displace/noise_displace_module.hpp"
#include "include/modules/non_generator_modules/transformers/turbulence/noise_turbulence_module.hpp"
#include "include/modules/non_generator_modules/transformers/linear_transformer/rotate_point/noise_rotate_point_module.hpp"
#include "include/modules/non_generator_modules/transformers/linear_transformer/scale_point/noise_scale_point_module.hpp"

#include <chrono>
#include <iostream>

using namespace std::chrono;

class Image : public QWidget
{
    Q_OBJECT
public:
    Image(QWidget *parent = nullptr) :
        QWidget(parent)
    {
    }
protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.drawImage(QRect(0, 0, img.width(), img.height()), img);
    }
public:
    void setImage(const QImage& im)
    {
        img = im;
        setFixedSize(im.width(), im.height());
    }
private:
    QImage img;
};

#include <iostream>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) :
        QWidget(parent)
    {
        auto root_layout = new QVBoxLayout();
        auto button_layout = new QHBoxLayout();
        setLayout(root_layout);
        root_layout->addLayout(button_layout);
        auto button_perlin = new QPushButton("Compute");
        button_layout->addWidget(button_perlin);
        auto image_rect = new QScrollArea();
        root_layout->addWidget(image_rect);
        auto image = new Image();
        image_rect->setWidget(image);
        QObject::connect(button_perlin, &QPushButton::released, this, [image]() {

            gnoise::noise_voronoi_generator_module mod0;
            gnoise::noise_ridged_multifractal_generator_module mod1;
            gnoise::noise_perlin_generator_module modC;

            gnoise::noise_turbulence_module modF;

            gnoise::range2f a;
            gnoise::precision2 b;
            a.set_dimension_min<0>(0.0f);
            a.set_dimension_max<0>(10.0f);
            a.set_dimension_min<1>(0.0f);
            a.set_dimension_max<1>(10.0f);
            b.set_dimension_precision<0>(10000);
            b.set_dimension_precision<1>(10000);

            mod0.configuration().set_computation_target(gnoise::module_computation_target::gpu);
            mod1.configuration().set_computation_target(gnoise::module_computation_target::gpu);
            modC.configuration().set_computation_target(gnoise::module_computation_target::gpu);

            cl_device_id default_device = nullptr;

            cl_uint platform_count = 0;
            clGetPlatformIDs(0, nullptr, &platform_count);
            std::vector<cl_platform_id> platform_ids(platform_count);
            clGetPlatformIDs(platform_count, platform_ids.data(), nullptr);
            
            for(auto& platform : platform_ids)
            {
                cl_uint device_count;
                clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &device_count);
                std::vector<cl_device_id> device_ids(device_count);
                clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, device_count, device_ids.data(), &device_count);

                size_t platform_name_size = 0;
                clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, nullptr, &platform_name_size);
                std::string platform_name;
                platform_name.resize(platform_name_size);
                clGetPlatformInfo(platform, CL_PLATFORM_NAME, platform_name_size, platform_name.data(), nullptr);
                std::cout << platform_name << std::endl;

                for(auto& device : device_ids)
                {
                    size_t device_name_size = 0;
                    clGetDeviceInfo(device, CL_DEVICE_NAME, 0, nullptr, &device_name_size);
                    std::string device_name;
                    device_name.resize(device_name_size);
                    clGetDeviceInfo(device, CL_DEVICE_NAME, device_name_size, device_name.data(), nullptr);
                    std::cout << device_name << std::endl;
                    if(!default_device)
                    {
                        default_device = device;
                    }
                    else if(device_name.find("GTX") != std::string::npos)
                    {
                        default_device = device;
                    }
                }
            }
            
            size_t device_name_size = 0;
            clGetDeviceInfo(default_device, CL_DEVICE_NAME, 0, nullptr, &device_name_size);
            std::string device_name;
            device_name.resize(device_name_size);
            clGetDeviceInfo(default_device, CL_DEVICE_NAME, device_name_size, device_name.data(), nullptr);
            std::cout << device_name << std::endl;
            

            mod0.configuration().accelerated_target_configuration()->set_target(default_device);
            mod1.configuration().accelerated_target_configuration()->set_target(default_device);
            modC.configuration().accelerated_target_configuration()->set_target(default_device);

            modF.configuration().set_computation_target(gnoise::module_computation_target::multi_thread_cpu);
            modF.configuration().multithreaded_target_configuration()->set_percentage_affinity(1.0f);

            modF.set_x_turbulence_module(&mod0);
            modF.set_y_turbulence_module(&mod1);
            modF.set_computation_module(&modC);

            auto start = high_resolution_clock::now();
            auto values = modF.compute(a, b);
            auto end = high_resolution_clock::now();
            std::cout << (end - start).count() / 1e9 << "s" << std::endl;

            QImage pm = QImage((int)b.dimension_precision<0>(), (int)b.dimension_precision<1>(), QImage::Format::Format_RGBA8888);

            float val_max = std::numeric_limits<float>::min();
            float val_min = std::numeric_limits<float>::max();

            for (size_t x = 0; x < b.dimension_precision<0>(); x++)
            {
                for (size_t y = 0; y < b.dimension_precision<1>(); y++)
                {
                    float& val = values[y*b.dimension_precision<0>() + x];
                    if(val_max < val)
                    {
                        val_max = val;
                    }
                    if (val_min > val)
                    {
                        val_min = val;
                    }
                }
            }

            for (size_t x = 0; x < b.dimension_precision<0>(); x++)
            {
                for (size_t y = 0; y < b.dimension_precision<1>(); y++)
                {
                    auto& val_pre = values[y*b.dimension_precision<0>() + x];
                    auto val = (val_pre - val_min) / (val_max - val_min);
                    pm.setPixel(QPoint(x, y), QColor(0.0, gnoise::generator_utility::clamp(255.0*val, 0.0, 255.0), gnoise::generator_utility::clamp(255.0*(1.0-val), 0.0, 255.0)).rgba());
                }
            }
            image->setImage(pm);
        });
    }
};
