#pragma once

#include "flow_chart_common.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class default_flow_chart_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    default_flow_chart_scene(QObject* parent = nullptr);
protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
};

FLOW_CHART_NAMESPACE_END