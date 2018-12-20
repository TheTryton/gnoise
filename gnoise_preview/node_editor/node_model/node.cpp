#include "node.hpp"
#include "pin.hpp"

NODE_EDITOR_NAMESPACE_BEGIN

node::node(QGraphicsWidget* parent):
    QGraphicsWidget(parent)
{
    setMinimumSize(QSize(120, 60));

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);

    setBoundingRegionGranularity(1.0);

    _root_layout= new QGraphicsGridLayout;
    _root_layout->setContentsMargins(8, 8, 8, 8);
    _root_layout->setColumnFixedWidth(0, 16);
    _root_layout->setColumnFixedWidth(2, 16);
    setLayout(_root_layout);
    
    _input_pins_layout = new QGraphicsLinearLayout;
    _input_pins_layout->setOrientation(Qt::Vertical);
    _root_layout->addItem(_input_pins_layout, 0, 0);

    _output_pins_layout = new QGraphicsLinearLayout;
    _output_pins_layout->setOrientation(Qt::Vertical);
    _root_layout->addItem(_output_pins_layout, 0, 2);

    setAcceptHoverEvents(true);
}

std::vector<pin*> node::pins(pin_direction direction)
{
    if(direction == pin_direction::input)
    {
        return _input_pins;
    }
    else if(direction == pin_direction::output)
    {
        return _output_pins;
    }
    return std::vector<node_editor::pin*>();
}

unsigned int node::pin_index(const node_editor::pin* p)
{
    if(p->direction() == pin_direction::input)
    {
        auto result = find(_input_pins.begin(), _input_pins.end(), p);
        if (result != _input_pins.end())
        {
            return result - _input_pins.begin();
        }
    }
    else if (p->direction() == pin_direction::output)
    {
        auto result = find(_output_pins.begin(), _output_pins.end(), p);
        if (result != _output_pins.end())
        {
            return result - _output_pins.begin();
        }
    }
    return std::numeric_limits<unsigned int>::max();
}

pin* node::pin(pin_direction direction, unsigned int index)
{
    if (direction == pin_direction::input)
    {
        if(index < _input_pins.size())
        {
            return _input_pins[index];
        }
    }
    else if (direction == pin_direction::output)
    {
        if (index < _output_pins.size())
        {
            return _output_pins[index];
        }
    }
    return nullptr;
}

void node::set_content(QGraphicsLayoutItem* content)
{
    _content = content;
    _root_layout->addItem(content, 0, 1);
}

QGraphicsLayoutItem* node::content() const
{
    return _content;
}

pin* node::add_pin(pin_direction direction)
{
    if (direction == pin_direction::input)
    {
        node_editor::pin* p = new  node_editor::pin(this, pin_direction::input, pin_link_mode::exclusive);
        _input_pins_layout->addItem(p);
        _input_pins_layout->setAlignment(p, Qt::AlignVCenter | Qt::AlignLeft);
        _input_pins.push_back(p);
        return p;
    }
    else if (direction == pin_direction::output)
    {
        node_editor::pin* p = new  node_editor::pin(this, pin_direction::output, pin_link_mode::unconstrained);
        _output_pins_layout->addItem(p);
        _output_pins_layout->setAlignment(p, Qt::AlignVCenter | Qt::AlignRight);
        _output_pins.push_back(p);
        return p;
    }
    return nullptr;
}

pin* node::insert_pin(pin_direction direction, unsigned int index)
{
    if (direction == pin_direction::input)
    {
        if(index > _input_pins.size())
        {
            return nullptr;
        }
        node_editor::pin* p = new  node_editor::pin(this, pin_direction::input, pin_link_mode::exclusive);
        _input_pins_layout->insertItem(index, p);
        _input_pins_layout->setAlignment(p, Qt::AlignVCenter | Qt::AlignLeft);
        _input_pins.insert(_input_pins.begin() + index, p);
        return p;
    }
    else if (direction == pin_direction::output)
    {
        if (index > _output_pins.size())
        {
            return nullptr;
        }
        node_editor::pin* p = new  node_editor::pin(this, pin_direction::output, pin_link_mode::unconstrained);
        _output_pins_layout->insertItem(index, p);
        _output_pins_layout->setAlignment(p, Qt::AlignVCenter | Qt::AlignRight);
        _output_pins.insert(_input_pins.begin() + index, p);
        return p;
    }
    return nullptr;
}

void node::remove_pin(pin_direction direction, unsigned int index)
{
    if (direction == pin_direction::input)
    {
        if (index >= _input_pins.size())
        {
            return;
        }
        delete _input_pins[index];
        _input_pins.erase(_input_pins.begin() + index);
        _input_pins_layout->removeAt(index);
    }
    else if (direction == pin_direction::output)
    {
        if (index >= _output_pins.size())
        {
            return;
        }
        delete _output_pins[index];
        _output_pins.erase(_input_pins.begin() + index);
        _output_pins_layout->removeAt(index);
    }
}

void node::remove_pin(node_editor::pin* p)
{
    remove_pin(p->direction(), pin_index(p));
}

unsigned int node::pins_count(pin_direction direction) const
{
    if (direction == pin_direction::input)
    {
        return _input_pins.size();
    }
    else if (direction == pin_direction::output)
    {
        return _output_pins.size();
    }
    return 0;
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

    QPainterPath node_path;
    node_path.addRoundedRect(layout()->geometry().adjusted(3, 3, -3, -3), 10, 10);

    if(isSelected())
    {
        painter->setBrush(QColor(255, 165, 0));
        QPainterPath selected_path;
        selected_path.addRoundedRect(layout()->geometry(), 10, 10);
        painter->drawPath(selected_path.subtracted(node_path));
    }
    else if (option->state & QStyle::StateFlag::State_MouseOver)
    {
        painter->setBrush(QColor(135, 206, 250));
        QPainterPath hovered_path;
        hovered_path.addRoundedRect(layout()->geometry(), 10, 10);
        painter->drawPath(hovered_path.subtracted(node_path));
    }
    painter->setPen(QColor(180, 180, 180, 160));
    painter->setBrush(QColor(127, 127, 127, 160));
    painter->drawPath(node_path);
}

void node::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setCursor(Qt::CursorShape::ArrowCursor);
    QGraphicsWidget::hoverEnterEvent(event);
}

void node::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QMenu menu;
    menu.addAction("Delete node", [this]() {
        delete this;
    });
    menu.exec(event->screenPos());
}

NODE_EDITOR_NAMESPACE_END
