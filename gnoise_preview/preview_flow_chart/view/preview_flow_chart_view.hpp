#pragma once

#include "flow_chart/default_flow_chart_view.hpp"
#include "../preview_common.hpp"

using namespace FLOW_CHART;

class preview_flow_chart_view : public default_flow_chart_view
{
    Q_OBJECT
public:
    preview_flow_chart_view(QWidget* parent = nullptr);
protected:
    virtual void        contextMenuEvent(QContextMenuEvent *event) override;
signals:
    void                selected_nodes_changed(QList<preview_node_base*> nodes);
};