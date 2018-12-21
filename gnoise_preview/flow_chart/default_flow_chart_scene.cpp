#include "default_flow_chart_scene.hpp"

FLOW_CHART_NAMESPACE_BEGIN

default_flow_chart_scene::default_flow_chart_scene(QObject* parent) :
    QGraphicsScene(parent)
{
}

void default_flow_chart_scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->fillRect(rect, QColor(105, 105, 105));

    constexpr float separation_thicker = 100.0f;
    constexpr float separation_thinner = 25.0f;
    QPointF start_thick = QPointF(qFloor(rect.left() / separation_thicker) * separation_thicker, qFloor(rect.top() / separation_thicker) * separation_thicker);
    QPointF start_thin = QPointF(qFloor(rect.left() / separation_thinner) * separation_thinner, qFloor(rect.top() / separation_thinner) * separation_thinner);

    QPen pen_thick;
    pen_thick.setWidthF(3);
    pen_thick.setColor(QColor(169, 169, 169, 127));
    painter->setPen(pen_thick);
    for (float current_thick_x = start_thick.x(); current_thick_x < rect.right(); current_thick_x += separation_thicker)
    {
        painter->drawLine(QPointF(current_thick_x, rect.top()), QPointF(current_thick_x, rect.bottom()));
    }
    for (float current_thick_y = start_thick.y(); current_thick_y < rect.bottom(); current_thick_y += separation_thicker)
    {
        painter->drawLine(QPointF(rect.left(), current_thick_y), QPointF(rect.right(), current_thick_y));
    }

    QPen pen_thin;
    pen_thick.setWidthF(1);
    pen_thick.setColor(QColor(192, 192, 192, 127));
    painter->setPen(pen_thick);
    for (float current_thin_x = start_thin.x(); current_thin_x < rect.right(); current_thin_x += separation_thinner)
    {
        painter->drawLine(QPointF(current_thin_x, rect.top()), QPointF(current_thin_x, rect.bottom()));
    }
    for (float current_thin_y = start_thick.y(); current_thin_y < rect.bottom(); current_thin_y += separation_thinner)
    {
        painter->drawLine(QPointF(rect.left(), current_thin_y), QPointF(rect.right(), current_thin_y));
    }
}

FLOW_CHART_NAMESPACE_END