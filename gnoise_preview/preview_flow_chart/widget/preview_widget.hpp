#pragma once

#include "../view/preview_flow_chart_view.hpp"

class cl_device_combo_box : public QComboBox
{
    Q_OBJECT
private:
    std::map<QString, cl_device_id> _name_to_device;
    std::map<cl_device_id, int> _device_to_index;
public:
    cl_device_combo_box(cl_device_id device = nullptr, QWidget* parent = nullptr);
public:
    cl_device_id        current_device() const;
    void                set_current_device(cl_device_id id);
signals:
    void                device_changed(void*);
};

class target_configuration_widget : public QWidget
{
    Q_OBJECT
private:
    noise_module&                           _module;
    QWidget*                                _current_target_widget;
public:
    target_configuration_widget(noise_module& module, QWidget* parent = nullptr);
};

class singlethreaded_configuration_widget : public QWidget
{
    Q_OBJECT
private:
    singlethreaded_target_configuration&     _config;
public:
    singlethreaded_configuration_widget(singlethreaded_target_configuration& config, QWidget* parent = nullptr);
};

class multithreaded_configuration_widget : public QWidget
{
    Q_OBJECT
private:
    multithreaded_target_configuration&     _config;
public:
    multithreaded_configuration_widget(multithreaded_target_configuration& config, QWidget* parent = nullptr);
};

class accelerated_configuration_widget : public QWidget
{
    Q_OBJECT
private:
    accelerated_target_configuration&     _config;
public:
    accelerated_configuration_widget(accelerated_target_configuration& config, QWidget* parent = nullptr);
};

class preview_widget : public QWidget
{
    Q_OBJECT
private:
    QWidget*            _current_widget = nullptr;
public:
    preview_widget(QWidget* parent = nullptr);
private:
    void                _set_current_nodes(QList<preview_node_base*> nodes);
};