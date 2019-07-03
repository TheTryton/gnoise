#pragma once

#include "../flow_chart/flow_chart_common.hpp"
#include "../flow_chart/flow_chart_base/node_base.hpp"
#include "../flow_chart/flow_chart_base/pin_base.hpp"

#include <QtWidgets>
#include "include/gnoise.hpp"

using namespace GNOISE;
using namespace FLOW_CHART;

class module_data
{
public:
    virtual noise_module*                   module() = 0;
    virtual QString                         module_name() const = 0;

    virtual size_t                          input_modules_count() const = 0;
    virtual vector<QString>                 input_names() const = 0;

    virtual size_t                          property_count() const = 0;
    virtual QVariant                        property_value(size_t property_index) const = 0;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) = 0;

    virtual QString                         property_name(size_t property_index) const = 0;
};

class preview_pin_base;
class preview_node_base;
class preview_result_node;