#include "node.hpp"

node::node(QGraphicsWidget* parent):
    QGraphicsWidget(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    auto layout = new QGraphicsGridLayout;
    setLayout(layout);
    layout->setContentsMargins(15, 15, 15, 15);
    for (int p = 0; p < _input_pins_count; p++)
    {
        layout->addItem(new pin, p, 0);
    }
    for (int p = 0; p < _output_pins_count; p++)
    {
        layout->addItem(new pin, p, 2);
    }

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}

void node::set_input_pins_count(unsigned int input_pins_count)
{
    _input_pins_count = input_pins_count;
}

unsigned int node::input_pins_count() const
{
    return _input_pins_count;
}

void node::set_output_pins_count(unsigned int output_pins_count)
{
    _output_pins_count = output_pins_count;
}

unsigned int node::output_pins_count() const
{
    return _output_pins_count;
}

bool node::is_selected() const
{
    return _selected;
}

void node::set_selected(bool select)
{
    if(select)
    {
        this->select();
    }
    else
    {
        deselect();
    }
}

void node::select()
{
    if (!_selected)
    {
        _selected = true;
        emit selectionChanged(_selected);
        update();
    }
}

void node::deselect()
{
    if(_selected)
    {
        _selected = false;
        emit selectionChanged(_selected);
        update();
    }
}

QRectF node::boundingRect() const
{
    return layout()->geometry();
}

QPainterPath node::shape() const
{
    QPainterPath path;
    path.addRoundedRect(layout()->geometry(), 10, 10);
    return path;
}

void node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::PenStyle::NoPen);
    if(is_selected())
    {
        painter->setBrush(QColor(255, 165, 0));
        painter->drawRoundedRect(layout()->geometry(), 10, 10);
    }
    else if (option->state & QStyle::StateFlag::State_MouseOver)
    {
        painter->setBrush(QColor(135, 206, 250));
        painter->drawRoundedRect(layout()->geometry(), 10, 10);
    }
    painter->setPen(QColor(180, 180, 180));
    painter->setBrush(QColor(127, 127, 127));
    painter->drawRoundedRect(layout()->geometry().adjusted(3, 3, -3, -3), 10, 10);
}

void node::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setCursor(Qt::CursorShape::ArrowCursor);
    QGraphicsWidget::hoverEnterEvent(event);
}

void node::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsWidget::hoverLeaveEvent(event);
}

void node::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsWidget::hoverMoveEvent(event);
}

void node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        select();
        event->accept();
    }

    QGraphicsWidget::mousePressEvent(event);
}

pin::pin(QGraphicsWidget* parent):
    QGraphicsWidget(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}

QRectF pin::boundingRect() const
{
    QPainterPath path;
    path.addRect(QRectF(-10, -10, 20, 20));
    return path.boundingRect();
}

QPainterPath pin::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(-10, -10, 20, 20));
    return path;
}

void pin::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::PenStyle::NoPen); 
    if (option->state & QStyle::StateFlag::State_Sunken)
    {
        painter->setBrush(QColor(0, 191, 255));
        painter->drawRoundedRect(QRectF(-10, -10, 20, 20), 4, 4);

        painter->setBrush(QColor(180, 0, 0));
        painter->drawEllipse(QRectF(-7, -7, 14, 14));
        painter->setBrush(QColor(100, 100, 100));
        painter->drawEllipse(QRectF(-4, -4, 8, 8));
    }
    else if (option->state & QStyle::StateFlag::State_MouseOver)
    {
        painter->setBrush(QColor(135, 206, 250));
        painter->drawRoundedRect(QRectF(-10, -10, 20, 20), 4, 4);

        painter->setBrush(QColor(255, 0, 0));
        painter->drawEllipse(QRectF(-7, -7, 14, 14));
        painter->setBrush(QColor(50, 50, 50));
        painter->drawEllipse(QRectF(-4, -4, 8, 8));
    }
    else
    {
        painter->setBrush(QColor(255, 0, 0));
        painter->drawEllipse(QRectF(-7, -7, 14, 14));
        painter->setBrush(QColor(50, 50, 50));
        painter->drawEllipse(QRectF(-4, -4, 8, 8));
    }
}
