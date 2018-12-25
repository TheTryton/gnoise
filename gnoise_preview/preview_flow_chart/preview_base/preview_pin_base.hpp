#pragma once

#include "../preview_common.hpp"

class preview_pin_base : public pin_base
{
private:
    pin_direction               _direction;
    pin_link_mode               _pin_link_mode;

    QString                     _name;
public:
    preview_pin_base(const QString& name, pin_direction direction, pin_link_mode mode, QGraphicsWidget* parent = nullptr);
public:
    virtual pin_direction       direction() const override;
    virtual pin_link_mode       link_mode() const override;
    virtual QPointF             pin_pos() const override;

    virtual void                on_connected(link_base* l) override;
    virtual void                on_disconnected(link_base* l) override;
    virtual bool                can_connect_to(pin_base* other) const override;
public:
    virtual void                setGeometry(const QRectF& geometry) override;
    virtual QSizeF              sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
    virtual QRectF              boundingRect() const override;
    virtual void                paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
};
