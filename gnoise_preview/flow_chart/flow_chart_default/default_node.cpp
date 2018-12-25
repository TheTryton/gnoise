#include "default_node.hpp"
#include "../flow_chart_base/pin_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

default_node::default_node(QGraphicsWidget* parent):
    node_base(parent)
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

std::vector<pin_base*> default_node::pins(pin_direction direction) const
{
    if (direction == pin_direction::input)
    {
        return _input_pins;
    }
    else if (direction == pin_direction::output)
    {
        return _output_pins;
    }
    return std::vector<pin_base*>();
}

int default_node::pin_index(const pin_base* p) const
{
    if (p->direction() == pin_direction::input)
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
    return -1;
}

size_t default_node::pins_count(pin_direction direction) const
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

pin_base* default_node::pin(pin_direction direction, int index) const
{
    if (index < 0)
    {
        return nullptr;
    }

    if (direction == pin_direction::input)
    {
        if (index < _input_pins.size())
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

void default_node::add_pin(pin_base* p)
{
    if(!p)
    {
        return;
    }

    if (p->direction() == pin_direction::input)
    {
        _set_pin_parent_to_this(p);
        _input_pins_layout->addItem(p);
        _input_pins_layout->setAlignment(p, Qt::AlignVCenter | Qt::AlignLeft);
        _input_pins.push_back(p);
    }
    else if (p->direction() == pin_direction::output)
    {
        _set_pin_parent_to_this(p);
        _output_pins_layout->addItem(p);
        _output_pins_layout->setAlignment(p, Qt::AlignVCenter | Qt::AlignRight);
        _output_pins.push_back(p);
    }
}

void default_node::insert_pin(pin_base* p, int index)
{
    if(index < 0 || !p)
    {
        return;
    }

    if (p->direction() == pin_direction::input)
    {
        if (index > _input_pins.size())
        {
            return;
        }
        _set_pin_parent_to_this(p);
        _input_pins_layout->insertItem(index, p);
        _input_pins_layout->setAlignment(p, Qt::AlignVCenter | Qt::AlignLeft);
        _input_pins.insert(_input_pins.begin() + index, p);
    }
    else if (p->direction() == pin_direction::output)
    {
        if (index > _output_pins.size())
        {
            return;
        }
        _set_pin_parent_to_this(p);
        _output_pins_layout->insertItem(index, p);
        _output_pins_layout->setAlignment(p, Qt::AlignVCenter | Qt::AlignRight);
        _output_pins.insert(_output_pins.begin() + index, p);
    }
}

void default_node::remove_pin(pin_direction direction, int index)
{
    if (index < 0)
    {
        return;
    }

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

void default_node::remove_pin(pin_base* p)
{
    remove_pin(p->direction(), pin_index(p));
}

void default_node::set_content(QGraphicsLayoutItem* content)
{
    _content = content;
    _root_layout->addItem(content, 0, 1);
}

QGraphicsLayoutItem* default_node::content() const
{
    return _content;
}

QRectF default_node::boundingRect() const
{
    return layout()->geometry();
}

QPainterPath default_node::shape() const
{
    QPainterPath path;
    path.addRoundedRect(layout()->geometry(), 10, 10);
    return path;
}

void default_node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::PenStyle::NoPen);

    QPainterPath node_path;
    node_path.addRoundedRect(layout()->geometry().adjusted(3, 3, -3, -3), 10, 10);

    if(isSelected())
    {
        painter->setBrush(QColor(255, 165, 0, 210));
        QPainterPath selected_path;
        selected_path.addRoundedRect(layout()->geometry(), 10, 10);
        painter->drawPath(selected_path.subtracted(node_path));
    }
    else if (option->state & QStyle::StateFlag::State_MouseOver)
    {
        painter->setBrush(QColor(135, 206, 250, 210));
        QPainterPath hovered_path;
        hovered_path.addRoundedRect(layout()->geometry(), 10, 10);
        painter->drawPath(hovered_path.subtracted(node_path));
    }
    
    painter->setPen(QColor(111, 112, 113, 210));
    painter->setBrush(QColor(37, 37, 38, 210));
    painter->drawPath(node_path);
}

QMenu* default_node::context_menu_requested()
{
    QMenu* menu = new QMenu;
    menu->addAction("Delete node", [=]() {
        about_to_be_removed();
        delete this;
    });
    return menu;
}

bool default_node::removable() const
{
    return true;
}

FLOW_CHART_NAMESPACE_END
