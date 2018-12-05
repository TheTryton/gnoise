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
            gnoise::noise_perlin_generator_module mod0;
            gnoise::noise_ridged_multifractal_generator_module mod1;
            gnoise::noise_billow_generator_module mod3;
            gnoise::noise_turbulence_module mod2;
            gnoise::noise_scale_point_module mod4;
            gnoise::range2f a;
            gnoise::precision2 b;
            a.set_dimension_min<0>(0.0f);
            a.set_dimension_max<0>(10.0f);
            a.set_dimension_min<1>(0.0f);
            a.set_dimension_max<1>(10.0f);
            b.set_dimension_precision<0>(2000);
            b.set_dimension_precision<1>(2000);
            mod0.configuration().set_computation_target(gnoise::module_computation_target::multi_thread_cpu);
            mod0.configuration().multithreaded_target_configuration()->set_percentage_affinity(1.0f);
            mod1.configuration().set_computation_target(gnoise::module_computation_target::multi_thread_cpu);
            mod1.configuration().multithreaded_target_configuration()->set_percentage_affinity(1.0f);
            mod2.configuration().set_computation_target(gnoise::module_computation_target::multi_thread_cpu);
            mod2.configuration().multithreaded_target_configuration()->set_percentage_affinity(1.0f);
            mod3.configuration().set_computation_target(gnoise::module_computation_target::multi_thread_cpu);
            mod3.configuration().multithreaded_target_configuration()->set_percentage_affinity(1.0f);
            mod4.configuration().set_computation_target(gnoise::module_computation_target::multi_thread_cpu);
            mod4.configuration().multithreaded_target_configuration()->set_percentage_affinity(1.0f);
            mod2.set_input_module(0, &mod3);
            mod2.set_input_module(1, &mod0);
            mod2.set_input_module(2, &mod1);
            mod4.set_input_module(0, &mod2);
            mod4.set_scale_x(10.0f);
            mod4.set_scale_y(10.0f);
            auto values = mod4.compute(a, b);

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
