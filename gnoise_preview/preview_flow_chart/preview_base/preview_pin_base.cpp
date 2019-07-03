#pragma once

#include "preview_pin_base.hpp"
#include "preview_node_base.hpp"
#include "flow_chart/flow_chart_base/link_base.hpp"

preview_pin_base::preview_pin_base(const QString& name, pin_direction direction, pin_link_mode mode, QGraphicsWidget* parent) :
    pin_base(parent),
    _direction(direction),
    _pin_link_mode(mode),
    _name(name)
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges);
}

pin_direction preview_pin_base::direction() const
{
    return _direction;
}

pin_link_mode preview_pin_base::link_mode() const
{
    return _pin_link_mode;
}

QPointF preview_pin_base::pin_pos() const
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

void preview_pin_base::on_connected(link_base* l)
{
    if (direction() == pin_direction::input)
    {
        if (auto f = dynamic_cast<preview_node_base*>(l->from_pin()->parent_node()))
        {
            if (auto t = dynamic_cast<preview_node_base*>(parent_node()))
            {
                if (auto mod_t = dynamic_cast<noise_non_generator_module_base*>(t->module_data()->module()))
                {
                    mod_t->set_input_module(index(), f->module_data()->module());
                }
            }
        }
    }
}

void preview_pin_base::on_disconnected(link_base * l)
{
    if (direction() == pin_direction::input)
    {
        if (auto t = dynamic_cast<preview_node_base*>(parent_node()))
        {
            if (auto mod_t = dynamic_cast<noise_non_generator_module_base*>(t->module_data()->module()))
            {
                mod_t->set_input_module(index(), nullptr);
            }
        }
    }
}

bool is_dependent_on_node_impl(const node_base* n, const node_base* node_to_check_dependency)
{
    if (n == node_to_check_dependency)
    {
        return true;
    }

    for (auto& pin : node_to_check_dependency->pins(pin_direction::output))
    {
        for (auto& link : pin->links())
        {
            if (is_dependent_on_node_impl(n, link->to_pin()->parent_node()))
            {
                return true;
            }
        }
    }

    return false;
}

bool is_dependent_on_node(const node_base* n, const node_base* node_to_check_dependency)
{
    return is_dependent_on_node_impl(n, node_to_check_dependency);
}

bool preview_pin_base::can_connect_to(pin_base* other) const
{
    if (other->parent_node() == this->parent_node())
    {
        return false;
    }

    if (other == this)
    {
        return false;
    }

    if (other->direction() == this->direction())
    {
        return false;
    }

    if (this->direction() == pin_direction::output)
    {
        if (!is_dependent_on_node(this->parent_node(), other->parent_node()))
        {
            return true;
        }
    }
    else if (dynamic_cast<preview_node_base*>(other->parent_node()))
    {
        return true;
    }

    return false;
}

QRectF preview_pin_base::boundingRect() const
{
    return QRectF(QPointF(0, 0), geometry().size());
}

void preview_pin_base::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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

    if (created_link_pin() && (!can_connect_to(created_link_pin()) || !created_link_pin()->can_connect_to(this)))
    {
        if (created_link_pin() != this)
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
    painter->setFont(QFont());
    painter->drawText(rect_name, Qt::AlignCenter, _name);
}

void preview_pin_base::setGeometry(const QRectF& geometry)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geometry);
    setPos(geometry.topLeft());
}

QSizeF preview_pin_base::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    auto metrics = QFontMetrics(QFont());
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