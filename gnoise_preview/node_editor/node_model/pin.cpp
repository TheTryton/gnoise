#include "pin.hpp"
#include "node.hpp"
#include "link.hpp"

NODE_EDITOR_NAMESPACE_BEGIN

pin::pin(node * parent_node, pin_direction direction, pin_link_mode mode, QGraphicsWidget * parent):
    QGraphicsWidget(parent),
    _parent_node(parent_node),
    _direction(direction),
    _pin_link_mode(mode)
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges);
}

pin::~pin()
{
    for(auto& link : _links)
    {
        delete link;
    }
}

node* pin::parent_node() const
{
    return _parent_node;
}

QFont pin::font() const
{
    return _name_font;
}

void pin::set_font(const QFont& font)
{
    _name_font = font;
    update();
}

QString pin::name() const
{
    return _name;
}

void pin::set_name(const QString& name)
{
    _name = name;
    update();
}

unsigned int pin::index() const
{
    return _parent_node->pin_index(this);
}

pin_direction pin::direction() const
{
    return _direction;
}

pin_link_mode pin::link_mode() const
{
    return _pin_link_mode;
}

void pin::set_link_mode(pin_link_mode mode)
{
    _pin_link_mode = mode;
}

QPointF pin::pin_pos() const
{
    QPointF pin_middle;
    QRectF pin_rect;
    if (direction() == pin_direction::input)
    {
        pin_middle = QPointF(10, geometry().height()/2);
        pin_rect = QRectF(pin_middle - QPointF(10, 10), pin_middle + QPointF(10, 10));
    }
    else if (direction() == pin_direction::output)
    {
        pin_middle = QPointF(geometry().width() - 10, geometry().height()/2);
        pin_rect = QRectF(pin_middle - QPointF(10, 10), pin_middle + QPointF(10, 10));
    }

    return mapToScene(pin_middle);
}

std::vector<link*> pin::links() const
{
    return _links;
}

void pin::on_connected(link* l)
{
}

void pin::on_disconnected(link* l)
{
}

void pin::_connect(link* link)
{
    if(_pin_link_mode == pin_link_mode::exclusive)
    {
        if(!_links.empty())
        {
            _disconnect(_links.front());
        }
    }

    _links.push_back(link);
}

void pin::_disconnect_no_delete(link * link)
{
    auto it = std::find(_links.begin(), _links.end(), link);
    _links.erase(it);
}

void pin::_disconnect(link* link)
{
    auto it = std::find(_links.begin(), _links.end(), link);
    if(it != _links.end())
    {
        delete *it;
    }
}

QRectF pin::boundingRect() const
{
    return QRectF(QPointF(0, 0), geometry().size());
}

void pin::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    auto rect_hover = QRectF(QPointF(0, 0), geometry().size());

    QPointF pin_middle; 
    QRectF pin_rect;
    if (direction() == pin_direction::input)
    {
        pin_middle = QPointF(10, rect_hover.center().y());
        pin_rect = QRectF(pin_middle - QPointF(10, 10), pin_middle + QPointF(10, 10));
    }
    else if(direction() == pin_direction::output)
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

    if (!_links.empty())
    {
        painter->setBrush(QColor(255, 0, 0));
        painter->drawEllipse(pin_outer_circle);
        painter->setBrush(QColor(255, 255, 255));
        painter->drawEllipse(pin_inner_circle);
    }
    else
    {
        painter->setBrush(QColor(255, 0, 0));
        painter->drawEllipse(pin_outer_circle);
        painter->setBrush(QColor(50, 50, 50));
        painter->drawEllipse(pin_inner_circle);
    }

    painter->setPen(QColor(255, 255, 255));
    painter->setBrush(QColor(255, 255, 255));
    painter->setFont(_name_font);
    painter->drawText(rect_name, Qt::AlignCenter, _name);
}

void pin::setGeometry(const QRectF& geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QSizeF pin::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    auto metrics = QFontMetrics(_name_font);
    auto text_size = metrics.size(Qt::TextSingleLine, _name);
    if(text_size.width() > 0)
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

NODE_EDITOR_NAMESPACE_END