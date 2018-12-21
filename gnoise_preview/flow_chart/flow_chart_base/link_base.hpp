#pragma once

#include "../flow_chart_common.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class link_base : public QGraphicsItem
{
private:
    QPointF                 _from_point;
    QPointF                 _to_point;
    pin_base*               _from = nullptr;
    pin_base*               _to = nullptr;
public:
    link_base(QGraphicsItem* parent = nullptr);
    ~link_base();
public:
    pin_base*               from_pin() const;
    void                    set_from_pin(pin_base* from);
    pin_base*               to_pin() const;
    void                    set_to_pin(pin_base* to);

    QPointF                 from_point() const;
    QPointF                 to_point() const;

    void                    set_from_point(const QPointF& from);
    void                    set_to_point(const QPointF& to);

    void                    update_link_geometry();

    virtual QMenu*          context_menu_requested() const = 0;
    virtual bool            removable() const = 0;
    virtual void            on_connection_established() = 0;
    virtual void            on_connection_broken() = 0;
public:
    void                    about_to_remove();
private:
    void                    _on_connection_established();
    void                    _on_connection_broken();
};

FLOW_CHART_NAMESPACE_END