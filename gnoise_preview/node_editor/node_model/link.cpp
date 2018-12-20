#include "link.hpp"
#include "pin.hpp"

NODE_EDITOR_NAMESPACE_BEGIN

link::link(pin* from, pin* to, QGraphicsItem* parent) :
    QGraphicsItem(parent)
{
    setAcceptHoverEvents(true);
    setBoundingRegionGranularity(0.5);

    set_from_pin(from);
    set_to_pin(to);
    set_selectable(false);
    setFlag(ItemSendsGeometryChanges);

    setZValue(-1);
}

link::~link()
{
    if(_from && _to)
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

pin* link::from_pin() const
{
    return _from;
}

void link::set_from_pin(pin* from)
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

pin* link::to_pin() const
{
    return _to;
}

void link::set_to_pin(pin* to)
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

QPointF link::from_point() const
{
    return _from_point;
}

QPointF link::to_point() const
{
    return _to_point;
}

bool link::is_selectable() const
{
    return flags() & ItemIsSelectable;
}

void link::set_selectable(bool selectable)
{
    setFlag(ItemIsSelectable, selectable);
}

void link::set_from_point(const QPointF& from)
{
    prepareGeometryChange();
    _from_point = from;
}

void link::set_to_point(const QPointF& to)
{
    prepareGeometryChange();
    _to_point = to;
}

void link::update_link()
{
    prepareGeometryChange();
}

QRectF link::boundingRect() const
{
    return get_link_path().boundingRect();
}

QPainterPath link::shape() const
{
    return get_link_path();
}

void link::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::RenderHint::HighQualityAntialiasing);

    QPainterPath path = get_link_path_unstroked();

    QPainterPathStroker stroke;

    if(is_selectable())
    {
        if (isSelected())
        {
            stroke.setWidth(8);
            painter->fillPath(stroke.createStroke(path), QColor(255, 165, 0));
        }
        else if (option->state & QStyle::StateFlag::State_MouseOver)
        {
            stroke.setWidth(8);
            painter->fillPath(stroke.createStroke(path), QColor(135, 206, 250));
        }
    }
    
    stroke.setWidth(4);

    painter->fillPath(stroke.createStroke(path), QColor(220, 220, 220));
}

void link::on_connection_established()
{
}

void link::on_connection_broken()
{
}

void link::_on_connection_established()
{
    on_connection_established();
    _from->on_connected(this);
    _to->on_connected(this);
}

void link::_on_connection_broken()
{
    on_connection_broken();
    _from->on_disconnected(this);
    _to->on_disconnected(this);
}

QPainterPath link::get_link_path_unstroked() const
{
    QPointF from_point = _from_point;
    QPointF to_point = _to_point;
    if (_from)
    {
        from_point = _from->pin_pos();
    }
    if (_to)
    {
        to_point = _to->pin_pos();
    }

    QPointF from_control_point = from_point + QPointF(100, 0);
    QPointF to_control_point = to_point - QPointF(100, 0);

    QPainterPath path;
    path.moveTo(from_point);
    path.cubicTo(
        from_control_point,
        to_control_point,
        to_point
    );

    return path;
}

QPainterPath link::get_link_path() const
{
    auto path = get_link_path_unstroked();

    QPainterPathStroker stroke;
    stroke.setWidth(8);

    return stroke.createStroke(path);
}

void link::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    setCursor(Qt::CursorShape::ArrowCursor);
    QGraphicsItem::hoverEnterEvent(event);
}

NODE_EDITOR_NAMESPACE_END