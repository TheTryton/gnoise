#include "link_base.hpp"
#include "pin_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

link_base::link_base(QGraphicsItem* parent) :
    QGraphicsItem(parent)
{
    setZValue(-1);
}

link_base::~link_base()
{
}

pin_base* link_base::from_pin() const
{
    return _from;
}

void link_base::set_from_pin(pin_base* from)
{
    if (_from && _to && !from)
    {
        _on_connection_broken();
    }

    if (_from)
    {
        _from->_disconnect_no_delete(this);
    }
    prepareGeometryChange();
    _from = from;
    if (_from)
    {
        _from->_connect(this);
    }

    if (_from && _to)
    {
        _on_connection_established();
    }
}

pin_base* link_base::to_pin() const
{
    return _to;
}

void link_base::set_to_pin(pin_base* to)
{
    if (_from && _to && !to)
    {
        _on_connection_broken();
    }

    if(_to)
    {
        _to->_disconnect_no_delete(this);
    }
    prepareGeometryChange();
    _to = to;
    if (_to)
    {
        _to->_connect(this);
    }

    if(_from && _to)
    {
        _on_connection_established();
    }
}

QPointF link_base::from_point() const
{
    return _from_point;
}

QPointF link_base::to_point() const
{
    return _to_point;
}

void link_base::set_from_point(const QPointF& from)
{
    prepareGeometryChange();
    _from_point = from;
}

void link_base::set_to_point(const QPointF& to)
{
    prepareGeometryChange();
    _to_point = to;
}

void link_base::update_link_geometry()
{
    prepareGeometryChange();
}

void link_base::about_to_remove()
{
    if (_from && _to)
    {
        _on_connection_broken();
    }

    if (_from)
    {
        _from->_disconnect_no_delete(this);
    }
    if (_to)
    {
        _to->_disconnect_no_delete(this);
    }
}

void link_base::_on_connection_established()
{
    on_connection_established();
    _from->on_connected(this);
    _to->on_connected(this);
}

void link_base::_on_connection_broken()
{
    on_connection_broken();
    _from->on_disconnected(this);
    _to->on_disconnected(this);
}

FLOW_CHART_NAMESPACE_END