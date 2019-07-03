#pragma once

#include "flow_chart_view_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class default_flow_chart_view : public flow_char_view_base
{
    Q_OBJECT
public:
    default_flow_chart_view(QWidget* parent = nullptr);
protected:
    virtual link_base*          create_link() const override;
};

FLOW_CHART_NAMESPACE_END