#pragma once

#include "model_common.hpp"

NODE_EDITOR_NAMESPACE_BEGIN

class link : public QGraphicsItem
{
private:
    QPointF                 _from_point;
    QPointF                 _to_point;
    pin*                    _from = nullptr;
    pin*                    _to = nullptr;
public:
    link(pin* from = nullptr, pin* to = nullptr, QGraphicsItem* parent = nullptr);
    ~link();
public:
    pin*                    from_pin() const;
    void                    set_from_pin(pin* from);
    pin*                    to_pin() const;
    void                    set_to_pin(pin* to);

    QPointF                 from_point() const;
    QPointF                 to_point() const;

    bool                    is_selectable() const;
    void                    set_selectable(bool selectable);

    void                    set_from_point(const QPointF& from);
    void                    set_to_point(const QPointF& to);

    void                    update_link();

    virtual QRectF          boundingRect() const override;
    virtual QPainterPath    shape() const override;
    virtual void            paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void            on_connection_established();
    virtual void            on_connection_broken();
private:
    void                    _on_connection_established();
    void                    _on_connection_broken();
    QPainterPath            get_link_path_unstroked() const;
    QPainterPath            get_link_path() const;
protected:
    virtual void            hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
};

NODE_EDITOR_NAMESPACE_END