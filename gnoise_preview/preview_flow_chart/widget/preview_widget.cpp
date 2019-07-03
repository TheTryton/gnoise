#include "preview_widget.hpp"
#include "../preview_base/preview_node_base.hpp"
#include "../module_model/module_model.hpp"

cl_device_combo_box::cl_device_combo_box(cl_device_id device, QWidget* parent)
{
    cl_uint platform_count = 0;
    clGetPlatformIDs(0, nullptr, &platform_count);
    std::vector<cl_platform_id> platform_ids(platform_count);
    clGetPlatformIDs(platform_count, platform_ids.data(), nullptr);

    for (auto& platform : platform_ids)
    {
        cl_uint device_count;
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &device_count);
        std::vector<cl_device_id> device_ids(device_count);
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, device_count, device_ids.data(), &device_count);

        for (auto& device : device_ids)
        {
            size_t device_name_size = 0;
            clGetDeviceInfo(device, CL_DEVICE_NAME, 0, nullptr, &device_name_size);
            std::string device_name;
            device_name.resize(device_name_size);
            clGetDeviceInfo(device, CL_DEVICE_NAME, device_name_size, device_name.data(), nullptr);

            _name_to_device[QString::fromStdString(device_name)] = device;
        }
    }

    QStringList names;
    _name_to_device["no device"] = nullptr;
    for (auto& dev : _name_to_device)
    {
        names.append(dev.first);
        _device_to_index[dev.second] = names.size() - 1;
    }

    addItems(names);
    set_current_device(device);

    QObject::connect(this, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        cl_device_id device = _name_to_device[text];
        emit device_changed(device);
    });
}

cl_device_id cl_device_combo_box::current_device() const
{
    return _name_to_device.at(currentText());
}

void cl_device_combo_box::set_current_device(cl_device_id id)
{
    setCurrentIndex(_device_to_index[id]);
}

target_configuration_widget::target_configuration_widget(noise_module& module, QWidget* parent) :
    QWidget(parent),
    _module(module)
{
    auto root_layout = new QVBoxLayout;
    setLayout(root_layout);

    auto config_choose_layout = new QHBoxLayout;

    auto config_label = new QLabel("module config:");
    config_choose_layout->addWidget(config_label, 0, Qt::AlignLeft);

    auto config = new QComboBox;
    config->addItems({ "singlethreaded","multithreaded","accelerated" });
    config_choose_layout->addWidget(config, 0, Qt::AlignRight);

    root_layout->addLayout(config_choose_layout);

    switch (module.configuration().computation_target())
    {
    case single_thread_cpu:
        _current_target_widget = new singlethreaded_configuration_widget(*module.configuration().singlethreaded_target_configuration());
        config->setCurrentIndex(0);
        break;
    case multi_thread_cpu:
        _current_target_widget = new multithreaded_configuration_widget(*module.configuration().multithreaded_target_configuration());
        config->setCurrentIndex(1);
        break;
    case gpu:
        _current_target_widget = new accelerated_configuration_widget(*module.configuration().accelerated_target_configuration());
        config->setCurrentIndex(2);
        break;
    }

    root_layout->addWidget(_current_target_widget, 0, Qt::AlignBottom);

    QObject::connect(config, &QComboBox::currentTextChanged, this, [=](const QString& text) {
        if (text == "singlethreaded")
        {
            _module.configuration().set_computation_target(single_thread_cpu);
        }
        else if (text == "multithreaded")
        {
            _module.configuration().set_computation_target(multi_thread_cpu);
        }
        else if (text == "accelerated")
        {
            _module.configuration().set_computation_target(gpu);
        }

        QWidget* new_widget = nullptr;

        switch (_module.configuration().computation_target())
        {
        case single_thread_cpu:
            new_widget = new singlethreaded_configuration_widget(*_module.configuration().singlethreaded_target_configuration());
            break;
        case multi_thread_cpu:
            new_widget = new multithreaded_configuration_widget(*_module.configuration().multithreaded_target_configuration());
            break;
        case gpu:
            new_widget = new accelerated_configuration_widget(*_module.configuration().accelerated_target_configuration());
            break;
        }

        root_layout->replaceWidget(_current_target_widget, new_widget);
        delete _current_target_widget;
        _current_target_widget = new_widget;
    });
}

singlethreaded_configuration_widget::singlethreaded_configuration_widget(singlethreaded_target_configuration& config, QWidget* parent) :
    QWidget(parent),
    _config(config)
{
    setMinimumWidth(200);
    setMinimumHeight(50);
}

multithreaded_configuration_widget::multithreaded_configuration_widget(multithreaded_target_configuration& config, QWidget* parent) :
    QWidget(parent),
    _config(config)
{
    auto root_layout = new QHBoxLayout;
    setLayout(root_layout);

    auto affinity_label = new QLabel("percentage affinity: ");
    root_layout->addWidget(affinity_label, 0, Qt::AlignLeft);

    auto affinity = new QLineEdit;
    affinity->setValidator(new QDoubleValidator(0.0, 1.0, 2));
    affinity->setText(QString::number(config.percentage_affinity()));
    QObject::connect(affinity, &QLineEdit::textChanged, this, [this](const QString& text) {
        _config.set_percentage_affinity(static_cast<float>(text.toDouble()));
    });

    root_layout->addWidget(affinity, 0, Qt::AlignRight);

    setMinimumWidth(200);
    setMinimumHeight(50);
}

accelerated_configuration_widget::accelerated_configuration_widget(accelerated_target_configuration& config, QWidget* parent) :
    QWidget(parent),
    _config(config)
{
    auto root_layout = new QHBoxLayout;
    setLayout(root_layout);

    auto device_label = new QLabel("device: ");
    root_layout->addWidget(device_label, 0, Qt::AlignLeft);

    auto device_combo = new cl_device_combo_box(config.target());
    QObject::connect(device_combo, &cl_device_combo_box::device_changed, this, [this](void* device) {
        _config.set_target(reinterpret_cast<cl_device_id>(device));
    });

    root_layout->addWidget(device_combo, 0, Qt::AlignRight);

    setMinimumWidth(200);
    setMinimumHeight(50);
}

preview_widget::preview_widget(QWidget* parent) :
    QWidget(parent)
{
    setWindowTitle("GNoise Preview");
    setStyleSheet(
        "QHeaderView::section{\n"
        "   background-color: rgb(82, 84, 92);\n"
        "   border: 1px solid white;\n"
        "}\n"
        "QWidget{\n"
        "   background-color: rgb(72, 74, 82);\n"
        "   color: white;\n"
        "}\n"
    );

    auto layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    auto flow_chart = new preview_flow_chart_view;
    flow_chart->setMinimumSize(QSize(800, 600));
    layout->addWidget(flow_chart);

    _set_current_nodes(QList<preview_node_base*>());

    QObject::connect(flow_chart, &preview_flow_chart_view::selected_nodes_changed, this, [this](QList<preview_node_base*> n) {
        _set_current_nodes(n);
    });
}

void preview_widget::_set_current_nodes(QList<preview_node_base*> nodes)
{
    auto l = static_cast<QHBoxLayout*>(layout());

    if(_current_widget)
    {
        QWidget* widget = nullptr;
        if(nodes.size() == 1)
        {
            if (nodes.front()->module_data()->module())
            {
                auto container = new QWidget;
                auto layout = new QVBoxLayout;
                layout->setMargin(0);
                layout->setContentsMargins(0, 0, 0, 0);
                layout->setSpacing(5);
                container->setLayout(layout);

                auto module_data_view = new QTableView;
                module_data_view->setMinimumWidth(200);
                auto model = new module_data_model(nodes.front()->module_data());
                module_data_view->setModel(model);
                for (int row = 0; row < model->rowCount(); row++)
                {
                    module_data_view->setItemDelegateForRow(row, model->delegateForRow(row));
                }
                layout->addWidget(module_data_view);

                auto config = new target_configuration_widget(*nodes.front()->module_data()->module());
                layout->addWidget(config);

                widget = container;
            }
            else
            {
                auto module_data_view = new QTableView;
                module_data_view->setMinimumWidth(200);
                auto model = new module_data_model(nodes.front()->module_data());
                module_data_view->setModel(model);
                for (int row = 0; row < model->rowCount(); row++)
                {
                    module_data_view->setItemDelegateForRow(row, model->delegateForRow(row));
                }
                widget = module_data_view;
            }
        }
        else if(nodes.empty())
        {
            auto label = new QLabel("No node selected");
            QFont font;
            font.setPointSize(12);
            label->setFont(font);
            label->setMinimumWidth(200);
            label->setAlignment(Qt::AlignCenter);

            widget = label;
        }
        else
        {
            auto label = new QLabel("Multiple nodes selected");
            QFont font;
            font.setPointSize(12);
            label->setFont(font);
            label->setMinimumWidth(200);
            label->setAlignment(Qt::AlignCenter);

            widget = label;
        }

        l->replaceWidget(_current_widget, widget);
        delete _current_widget;
        _current_widget = widget;
    }
    else
    {
        auto label = new QLabel("No node selected");
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setMinimumWidth(200);
        label->setAlignment(Qt::AlignCenter);

        l->addWidget(label);
        _current_widget = label;
    }
}
