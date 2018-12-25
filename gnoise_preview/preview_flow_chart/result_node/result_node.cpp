#include "result_node.hpp"
#include "flow_chart/flow_chart_default/default_pin.hpp"
#include "flow_chart/flow_chart_base/link_base.hpp"
#include "result_node_image.hpp"

#include <functional>
#include <chrono>

template<class T>
using function = std::function<T>;

using namespace std::chrono;

result_node_pin::result_node_pin(QGraphicsWidget * parent) :
    preview_pin_base("result module", pin_direction::input, pin_link_mode::exclusive)
{
}

void result_node_pin::on_connected(link_base* l)
{
    if (auto tn = dynamic_cast<result_node*>(parent_node()))
    {
        if (auto n = dynamic_cast<preview_node_base*>(l->from_pin()->parent_node()))
        {
            tn->_current_module = n->module_data()->module();
        }
    }
}

void result_node_pin::on_disconnected(link_base* l)
{
    if (auto tn = dynamic_cast<result_node*>(parent_node()))
    {
        tn->_current_module = nullptr;
    }
}

bool result_node_pin::can_connect_to(pin_base* other) const
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

    if(auto n = dynamic_cast<preview_node_base*>(other->parent_node()))
    {
        if(n->module_data()->module())
        {
            return true;
        }
    }
    
    return false;
}

noise_module* result_node_data::module()
{
    return nullptr;
}

QString result_node_data::module_name() const
{
    return "Computation Visualizer";
}

size_t result_node_data::input_modules_count() const
{
    return 0;
}

vector<QString> result_node_data::input_names() const
{
    return vector<QString>();
}

size_t result_node_data::property_count() const
{
    return 2;
}

QVariant result_node_data::property_value(size_t property_index) const
{
    if (property_index >= 2)
    {
        return QVariant();
    }

    const array<QVariant, 2> properties
    {
        _image_width,
        _image_height,
    };

    return properties[property_index];
}

bool result_node_data::set_property_value(size_t property_index, const QVariant& value)
{
    if (property_index >= 2)
    {
        return false;
    }

    const array<function<void(const QVariant&)>, 2> properties
    {
        [&](const QVariant& v) { _image_width = static_cast<size_t>(v.toInt()); },
        [&](const QVariant& v) { _image_height = static_cast<size_t>(v.toInt()); },
    };

    properties[property_index](value);

    return true;
}

QString result_node_data::property_name(size_t property_index) const
{
    if (property_index >= 2)
    {
        return QString();
    }

    const array<QString, 2> properties
    {
        "image width",
        "image height",
    };

    return properties[property_index];
}

result_node::result_node(QGraphicsWidget* parent) :
    preview_node_base(_init_data(_data), parent)
{
    auto pin = new result_node_pin;
    _input_pins.push_back(pin);
    _input_pins_layout->addItem(pin);
    _set_pin_parent_to_this(pin);
    auto compute_button = new result_node_compute_button;
    _root_layout->addItem(compute_button);
    _root_layout->setAlignment(compute_button, Qt::AlignHCenter);
    auto time_taken = new QLabel;
    QFont font;
    font.setPointSize(18);
    time_taken->setFont(font);
    time_taken->setMinimumHeight(40);
    time_taken->setAlignment(Qt::AlignCenter);
    time_taken->setStyleSheet(
        "QWidget{\n"
        "   background-color: rgb(72, 74, 82);\n"
        "   color: white;\n"
        "}\n"
    );
    auto time_taken_proxy = new QGraphicsProxyWidget;
    time_taken_proxy->setWidget(time_taken);
    _root_layout->addItem(time_taken_proxy);
    auto image = new result_node_image;
    _root_layout->addItem(image);
    _root_layout->setAlignment(image, Qt::AlignHCenter);

    QObject::connect(compute_button, &result_node_compute_button::released, this, [=]() {
        if(_current_module)
        {
            gnoise::range2f a;
            gnoise::precision2 b;
            a.set_dimension_min<0>(0.0f);
            a.set_dimension_max<0>(1.0f);
            a.set_dimension_min<1>(0.0f);
            a.set_dimension_max<1>(1.0f);
            b.set_dimension_precision<0>(_data->_image_width);
            b.set_dimension_precision<1>(_data->_image_height);

            auto start = high_resolution_clock::now();
            auto values = _current_module->compute(a, b);
            auto end = high_resolution_clock::now();
            if (!values.empty())
            {
                time_taken->setText("Time taken: " + QString::number((end - start).count() / 1e9) + "s");

                QImage pm = QImage((int)b.dimension_precision<0>(), (int)b.dimension_precision<1>(), QImage::Format::Format_RGBA8888);

                float val_max = std::numeric_limits<float>::min();
                float val_min = std::numeric_limits<float>::max();

                for (size_t x = 0; x < b.dimension_precision<0>(); x++)
                {
                    for (size_t y = 0; y < b.dimension_precision<1>(); y++)
                    {
                        float& val = values[y*b.dimension_precision<0>() + x];
                        if (val_max < val)
                        {
                            val_max = val;
                        }
                        if (val_min > val)
                        {
                            val_min = val;
                        }
                    }
                }

                for (size_t x = 0; x < b.dimension_precision<0>(); x++)
                {
                    for (size_t y = 0; y < b.dimension_precision<1>(); y++)
                    {
                        auto& val_pre = values[y*b.dimension_precision<0>() + x];
                        auto val = (val_pre - val_min) / (val_max - val_min);
                        pm.setPixel(
                            QPoint(static_cast<int>(x), static_cast<int>(y)),
                            QColor(0.0, gnoise::generator_utility::clamp(255.0*val, 0.0, 255.0), gnoise::generator_utility::clamp(255.0*(1.0 - val), 0.0, 255.0)).rgba()
                        );
                    }
                }
                image->set_image(pm);
                update();
            }
            else
            {
                time_taken->setText("Failed to calculate noise values");
            }
        }
        else
        {
            time_taken->setText("No input module");
        }
    });
}

result_node::~result_node()
{
    delete _data;
}

::module_data* result_node::module_data()
{
    return _data;
}

result_node_compute_button::result_node_compute_button(QGraphicsWidget* parent):
    QGraphicsWidget(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

void result_node_compute_button::setGeometry(const QRectF& geometry)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geometry);
    setPos(geometry.topLeft());
}

QSizeF result_node_compute_button::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
        return QSizeF(150, 50);
    case Qt::MaximumSize:
        return QSizeF(300, 50);
    default:
        break;
    }
    return constraint;
}

QRectF result_node_compute_button::boundingRect() const
{
    return QRectF(QPointF(0, 0), geometry().size());
}

void result_node_compute_button::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    auto rect = QRectF(QPointF(0, 0), geometry().size());
    painter->setPen(Qt::PenStyle::NoPen);

    QPainterPath button_path;
    button_path.addRoundedRect(rect.adjusted(5, 5, -5, -5) , 10, 10);

    painter->setBrush(QColor(67, 68, 69, 210));

    if (option->state & QStyle::StateFlag::State_Sunken)
    {
        painter->setBrush(QColor(47, 48, 49, 210));
    }
    else if (option->state & QStyle::StateFlag::State_MouseOver)
    {
        painter->setBrush(QColor(57, 58, 59, 210));
    }

    painter->setPen(QColor(111, 112, 113, 210));
    painter->drawPath(button_path);

    QFont font = painter->font();
    font.setPixelSize(16);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QColor(255, 255, 255));
    painter->drawText(rect.adjusted(10, 10, -10, -10), Qt::AlignCenter, "Compute");
}

void result_node_compute_button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    update();
    emit pressed();
    QGraphicsWidget::mousePressEvent(event);
    event->accept();
}

void result_node_compute_button::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    update();
    emit released();
    QGraphicsWidget::mouseReleaseEvent(event);
    event->accept();
}