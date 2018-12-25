#include "preview_node_base.hpp"
#include "preview_node_title.hpp"
#include "preview_pin_base.hpp"

preview_node_base::preview_node_base(::module_data* data, QGraphicsWidget* parent) :
    node_base(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);

    setBoundingRegionGranularity(1.0);

    _root_layout = new QGraphicsLinearLayout;
    _root_layout->setOrientation(Qt::Vertical);
    _root_layout->setContentsMargins(3, 3, 3, 6);
    _root_layout->setSpacing(5);
    setLayout(_root_layout);

    auto module_type = generator;
    if(auto module = data->module())
    {
        module_type = module->module_type();
    }

    auto title_item = new preview_node_title(data->module_name(), module_type);
    _root_layout->addItem(title_item);

    _pins_layout = new QGraphicsLinearLayout;
    _pins_layout->setOrientation(Qt::Horizontal);
    _root_layout->addItem(_pins_layout);

    _input_pins_layout = new QGraphicsLinearLayout;
    _input_pins_layout->setOrientation(Qt::Vertical);
    _input_pins_layout->setMinimumWidth(150);
    _pins_layout->addItem(_input_pins_layout);

    _output_pins_layout = new QGraphicsLinearLayout;
    _output_pins_layout->setOrientation(Qt::Vertical);
    _output_pins_layout->setMinimumWidth(150);
    _pins_layout->addItem(_output_pins_layout);

    for (auto& pin_name : data->input_names())
    {
        auto pin = new preview_pin_base(pin_name, pin_direction::input, pin_link_mode::exclusive);
        _input_pins.push_back(pin);
        _input_pins_layout->addItem(pin);
        _input_pins_layout->setAlignment(pin, Qt::AlignLeft);
        _set_pin_parent_to_this(pin);
    }

    if (data->module())
    {
        auto pin = new preview_pin_base("Output", pin_direction::output, pin_link_mode::unconstrained);
        _output_pins.push_back(pin);
        _output_pins_layout->addItem(pin);
        _output_pins_layout->setAlignment(pin, Qt::AlignRight);
        _set_pin_parent_to_this(pin);
    }

    setAcceptHoverEvents(true);
}

std::vector<pin_base*> preview_node_base::pins(pin_direction direction) const
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

int preview_node_base::pin_index(const pin_base* p) const
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

size_t preview_node_base::pins_count(pin_direction direction) const
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

pin_base* preview_node_base::pin(pin_direction direction, int index) const
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

module_data* preview_node_base::module_data()
{
    return nullptr;
}

QRectF preview_node_base::boundingRect() const
{
    return layout()->geometry();
}

QPainterPath preview_node_base::shape() const
{
    QPainterPath path;
    path.addRoundedRect(layout()->geometry(), 10, 10);
    return path;
}

void preview_node_base::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::PenStyle::NoPen);

    QPainterPath node_path;
    node_path.addRoundedRect(layout()->geometry().adjusted(3, 3, -3, -3), 10, 10);

    if (isSelected())
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

QMenu* preview_node_base::context_menu_requested()
{
    if(removable())
    {
        QMenu* menu = new QMenu;
        menu->addAction("Delete node", [=]() {
            about_to_be_removed();
            delete this;
        });
        return menu;
    }
    
    return nullptr;
}

bool preview_node_base::removable() const
{
    return true;
}