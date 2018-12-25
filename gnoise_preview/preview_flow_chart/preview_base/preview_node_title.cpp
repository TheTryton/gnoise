#include "preview_node_title.hpp"

preview_node_title::preview_node_title(const QString& title, module_type module_type, QGraphicsWidget* parent) :
    QGraphicsWidget(parent)
{
    _title = title;
    _type = module_type;
}

void preview_node_title::set_title(const QString& title)
{
    prepareGeometryChange();
    _title = title;
}

QString preview_node_title::title() const
{
    return _title;
}

void preview_node_title::setGeometry(const QRectF& geometry)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geometry);
    setPos(geometry.topLeft());
}

QSizeF preview_node_title::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
    case Qt::MaximumSize:
        return QSize(300, 50);
    default:
        break;
    }
    return constraint;
}

QRectF preview_node_title::boundingRect() const
{
    return QRectF(QPointF(0, 0), geometry().size());
}

void preview_node_title::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();

    auto rect = QRectF(QPointF(0, 0), geometry().size());

    QPainterPath clip_path;
    clip_path.addRoundedRect(rect, 10, 10);

    painter->setClipPath(clip_path);

    QLinearGradient gradient(QPoint(0, 0), QPoint(300, 50));

    switch (_type)
    {
    case generator:
        gradient.setColorAt(0, QColor(34, 139, 0, 160));
        gradient.setColorAt(1, QColor(37, 37, 38, 10));
        break;
    case combiner:
        gradient.setColorAt(0, QColor(0, 0, 204, 160));
        gradient.setColorAt(1, QColor(37, 37, 38, 10));
        break;
    case modifier:
        gradient.setColorAt(0, QColor(204, 204, 160));
        gradient.setColorAt(1, QColor(37, 37, 38, 10));
        break;
    case selector:
        gradient.setColorAt(0, QColor(204, 0, 0, 160));
        gradient.setColorAt(1, QColor(37, 37, 38, 10));
        break;
    case transformer:
        gradient.setColorAt(0, QColor(204, 0, 204, 160));
        gradient.setColorAt(1, QColor(37, 37, 38, 10));
        break;
    }

    painter->fillRect(QRectF(0, 0, 300, 50), gradient);

    QFont font = painter->font();
    font.setPixelSize(24);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QColor(255, 255, 255));
    painter->drawText(rect.adjusted(5, 5, -5, -5), Qt::AlignCenter, _title);

    painter->restore();
}