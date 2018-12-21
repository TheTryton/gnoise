#pragma once

#include "default_flowchart_common.hpp"
#include "../flow_chart_base/link_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class default_link final : public link_base
{
public:
    default_link(QGraphicsItem* parent = nullptr);
public:
    virtual QMenu*          context_menu_requested() const override;
    virtual bool            removable() const override;
    virtual void            on_connection_established() override;
    virtual void            on_connection_broken() override;
public:
    virtual QRectF          boundingRect() const override;
    virtual QPainterPath    shape() const override;
    virtual void            paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    QPainterPath            get_link_path_unstroked() const;
    QPainterPath            get_link_path_stroked() const;
};

FLOW_CHART_NAMESPACE_END