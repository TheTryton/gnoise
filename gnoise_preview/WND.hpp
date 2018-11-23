#pragma once

#include <QtWidgets>
#include "include/modules/generators/voronoi/noise_voronoi_generator_module.hpp"
#include "include/modules/generators/perlin/noise_perlin_generator_module.hpp"
#include "include/modules/generators/ridged_multifractal/noise_ridged_multifractal_generator_module.hpp"
#include "include/modules/generators/billow/noise_billow_generator_module.hpp"
#include "include/modules/generators/checkerboard/noise_checkerboard_generator_module.hpp"
#include "include/modules/generators/spheres/noise_spheres_generator_module.hpp"
#include "include/modules/generators/cylinders/noise_cylinders_generator_module.hpp"

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
        auto button_perlin = new QPushButton("Perlin");
        button_layout->addWidget(button_perlin);
        auto image_rect = new QScrollArea();
        root_layout->addWidget(image_rect);
        auto image = new Image();
        image_rect->setWidget(image);
        QObject::connect(button_perlin, &QPushButton::released, this, [image]() {
            gnoise::noise_checkerboard_generator_module mod;
            gnoise::range2f a;
            gnoise::precision2 b;
            a.set_dimension_min<0>(0.0f);
            a.set_dimension_max<0>(10.0f);
            a.set_dimension_min<1>(0.0f);
            a.set_dimension_max<1>(10.0f);
            b.set_dimension_precision<0>(5000);
            b.set_dimension_precision<1>(5000);
            mod.configuration().set_computation_target(gnoise::module_computation_target::multi_thread_cpu);
            mod.configuration().multithreaded_target_configuration()->set_percentage_affinity(1.0f);
            auto values = mod.compute(a, b);

            QImage pm = QImage((int)b.dimension_precision<0>(), (int)b.dimension_precision<1>(), QImage::Format::Format_RGBA8888);

            for (size_t x = 0; x < b.dimension_precision<0>(); x++)
            {
                for (size_t y = 0; y < b.dimension_precision<1>(); y++)
                {
                    auto& val = values[y*b.dimension_precision<0>() + x];
                    pm.setPixel(QPoint(x, y), QColor(0.0, gnoise::generator_utility::clamp(255.0*val, 0.0, 255.0), gnoise::generator_utility::clamp(255.0*(1.0-val), 0.0, 255.0)).rgba());
                }
            }
            image->setImage(pm);
        });
    }
};
