#pragma once

#include "default_flowchart_common.hpp"
#include "../flow_chart_base/pin_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class default_pin : public pin_base
{
private:
    pin_direction           _direction;
    pin_link_mode           _pin_link_mode;

    QString                 _name;
    QFont                   _name_font;
public:
    default_pin(pin_direction direction, pin_link_mode mode, QGraphicsWidget* parent = nullptr);
public:
    virtual pin_direction   direction() const override;
    virtual pin_link_mode   link_mode() const override;
    virtual QPointF         pin_pos() const override;

    QFont                   font() const;
    void                    set_font(const QFont& font);

    QString                 name() const;
    void                    set_name(const QString& name);

    virtual void            on_connected(link_base* l) override;
    virtual void            on_disconnected(link_base* l) override;
    virtual bool            can_connect_to(pin_base* other) const override;
public:
    virtual void            setGeometry(const QRectF& geometry) override;
    virtual QSizeF          sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
    virtual QRectF          boundingRect() const override;
    virtual void            paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
};

FLOW_CHART_NAMESPACE_END