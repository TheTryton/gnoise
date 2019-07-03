#include "default_flow_chart_view.hpp"
#include "default_flow_chart_scene.hpp"
#include "flow_chart_default/default_link.hpp"

FLOW_CHART_NAMESPACE_BEGIN

default_flow_chart_view::default_flow_chart_view(QWidget* parent) :
    flow_char_view_base(parent)
{
    setScene(new default_flow_chart_scene);
}

link_base* default_flow_chart_view::create_link() const
{
    return new default_link();
}

FLOW_CHART_NAMESPACE_END;