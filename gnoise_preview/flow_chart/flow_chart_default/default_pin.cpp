#include "default_pin.hpp"
#include "../flow_chart_base/link_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

default_pin::default_pin(pin_direction direction, pin_link_mode mode, QGraphicsWidget* parent) :
    pin_base(parent),
    _direction(direction),
    _pin_link_mode(mode)
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges);
}

pin_direction default_pin::direction() const
{
    return _direction;
}

pin_link_mode default_pin::link_mode() const
{
    return _pin_link_mode;
}

QPointF default_pin::pin_pos() const
{
    QPointF pin_middle;
    QRectF pin_rect;
    if (direction() == pin_direction::input)
    {
        pin_middle = QPointF(10, geometry().height() / 2);
        pin_rect = QRectF(pin_middle - QPointF(10, 10), pin_middle + QPointF(10, 10));
    }
    else if (direction() == pin_direction::output)
    {
        pin_middle = QPointF(geometry().width() - 10, geometry().height() / 2);
        pin_rect = QRectF(pin_middle - QPointF(10, 10), pin_middle + QPointF(10, 10));
    }

    return mapToScene(pin_middle);
}

QFont default_pin::font() const
{
    return _name_font;
}

void default_pin::set_font(const QFont& font)
{
    _name_font = font;
    update();
}

QString default_pin::name() const
{
    return _name;
}

void default_pin::set_name(const QString& name)
{
    _name = name;
    update();
}

void default_pin::on_connected(link_base* l)
{
    if(direction() == pin_direction::input)
    {
        qDebug() << "pin " << this << " connected to pin: " << l->from_pin();
    }
    else if(direction() == pin_direction::output)
    {
        qDebug() << "pin " << this << " connected to pin: " << l->to_pin();
    }
}

void default_pin::on_disconnected(link_base * l)
{
    if (direction() == pin_direction::input)
    {
        qDebug() << "pin " << this << " disconnected from pin: " << l->from_pin();
    }
    else if (direction() == pin_direction::output)
    {
        qDebug() << "pin " << this << " disconnected from pin: " << l->to_pin();
    }
}

bool default_pin::can_connect_to(pin_base* other) const
{
    if(other->parent_node() == this->parent_node())
    {
        return false;
    }

    if(other == this)
    {
        return false;
    }

    if (other->direction() == this->direction())
    {
        return false;
    }

    return true;
}

QRectF default_pin::boundingRect() const
{
    return QRectF(QPointF(0, 0), geometry().size());
}

void default_pin::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    auto rect_hover = QRectF(QPointF(0, 0), geometry().size());

    QPointF pin_middle;
    QRectF pin_rect;
    if (direction() == pin_direction::input)
    {
        pin_middle = QPointF(10, rect_hover.center().y());
        pin_rect = QRectF(pin_middle - QPointF(10, 10), pin_middle + QPointF(10, 10));
    }
    else if (direction() == pin_direction::output)
    {
        pin_middle = QPointF(rect_hover.width() - 10, rect_hover.center().y());
        pin_rect = QRectF(pin_middle - QPointF(10, 10), pin_middle + QPointF(10, 10));
    }

    auto pin_outer_circle = pin_rect.adjusted(3, 3, -3, -3);
    auto pin_inner_circle = pin_rect.adjusted(6, 6, -6, -6);

    QRectF rect_name;

    if (direction() == pin_direction::input)
    {
        rect_name = rect_hover.adjusted(20, 0, 0, 0);
    }
    else if (direction() == pin_direction::output)
    {
        rect_name = rect_hover.adjusted(0, 0, -20, 0);
    }

    painter->setPen(Qt::PenStyle::NoPen);

    if(created_link_pin() && (!can_connect_to(created_link_pin()) || !created_link_pin()->can_connect_to(this)))
    {
        if(created_link_pin() != this)
        {
            painter->setOpacity(0.5);
        }
    }
    else
    {
        if (option->state & QStyle::StateFlag::State_Sunken)
        {
            painter->setBrush(QColor(0, 191, 255));
            painter->drawRoundedRect(rect_hover, 4, 4);
        }
        else if (option->state & QStyle::StateFlag::State_MouseOver)
        {
            painter->setBrush(QColor(135, 206, 250));
            painter->drawRoundedRect(rect_hover, 4, 4);
        }
    }
    
    if (links_count() || (created_link_pin() == this))
    {
        painter->setBrush(QColor(249, 48, 48));
        painter->drawEllipse(pin_outer_circle);
        painter->setBrush(QColor(220, 48, 48));
        painter->drawEllipse(pin_inner_circle);
    }
    else
    {
        painter->setBrush(QColor(255, 0, 0));
        painter->drawEllipse(pin_outer_circle);
        painter->setBrush(QColor(32, 32, 32));
        painter->drawEllipse(pin_inner_circle);
    }

    painter->setPen(QColor(255, 255, 255));
    painter->setBrush(QColor(255, 255, 255));
    painter->setFont(_name_font);
    painter->drawText(rect_name, Qt::AlignCenter, _name);
}

void default_pin::setGeometry(const QRectF& geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QSizeF default_pin::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    auto metrics = QFontMetrics(_name_font);
    auto text_size = metrics.size(Qt::TextSingleLine, _name);
    if (text_size.width() > 0)
    {
        text_size.setWidth(text_size.width() + 5);
    }

    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
        return QSize(20 + text_size.width(), qMax(20, text_size.height()));
    case Qt::MaximumSize:
        return QSize(20 + text_size.width(), qMax(20, text_size.height()));
    default:
        break;
    }
    return constraint;
}

FLOW_CHART_NAMESPACE_END