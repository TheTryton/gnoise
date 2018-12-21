#include "default_link.hpp"
#include "../flow_chart_base/pin_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

default_link::default_link(QGraphicsItem* parent) :
    link_base(parent)
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges);
}

QMenu* default_link::context_menu_requested() const
{
    QMenu* menu = new QMenu;
    menu->addAction("Delete link", [=]() {
        delete this;
    });
    return menu;
}

bool default_link::removable() const
{
    return true;
}

void default_link::on_connection_established()
{
    setFlag(ItemIsSelectable, true);
    qDebug() << "connection established link: " << this;
}

void default_link::on_connection_broken()
{
    setFlag(ItemIsSelectable, false);
    qDebug() << "connection broken link: " << this;
}

QRectF default_link::boundingRect() const
{
    return get_link_path_stroked().boundingRect();
}

QPainterPath default_link::shape() const
{
    return get_link_path_stroked();
}

void default_link::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::RenderHint::HighQualityAntialiasing);

    QPainterPath path = get_link_path_unstroked();

    QPainterPathStroker stroke;

    if(to_pin() && from_pin())
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

QPainterPath default_link::get_link_path_unstroked() const
{
    QPointF from_point = this->from_point();
    QPointF to_point = this->to_point();
    if (from_pin())
    {
        from_point = from_pin()->pin_pos();
    }
    if (to_pin())
    {
        to_point = to_pin()->pin_pos();
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

QPainterPath default_link::get_link_path_stroked() const
{
    auto path = get_link_path_unstroked();

    QPainterPathStroker stroke;
    stroke.setWidth(8);

    return stroke.createStroke(path);
}

FLOW_CHART_NAMESPACE_END