#pragma once

#include "default_flowchart_common.hpp"
#include "../flow_chart_base/node_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class default_node final : public node_base
{
private:
    std::vector<pin_base*>          _input_pins;
    std::vector<pin_base*>          _output_pins;

    QGraphicsGridLayout*            _root_layout = nullptr;
    QGraphicsLinearLayout*          _input_pins_layout = nullptr;
    QGraphicsLinearLayout*          _output_pins_layout = nullptr;
    QGraphicsLayoutItem*            _content;
public:
    default_node(QGraphicsWidget* parent = nullptr);
    virtual ~default_node() noexcept override = default;
public:
    virtual std::vector<pin_base*>  pins(pin_direction direction) const override;
    virtual int                     pin_index(const pin_base* p) const override;
    virtual size_t                  pins_count(pin_direction direction) const override;
    virtual pin_base*               pin(pin_direction direction, int index) const override;

    void                            add_pin(pin_base* pin);
    void                            insert_pin(pin_base* pin, int index);
    void                            remove_pin(pin_direction direction, int index);
    void                            remove_pin(pin_base* pin);

    void                            set_content(QGraphicsLayoutItem* content);
    QGraphicsLayoutItem*            content() const;

    virtual QMenu*                  context_menu_requested() const override;
    virtual bool                    removable() const override;
public:
    virtual QRectF                  boundingRect() const override;
    virtual QPainterPath            shape() const override;
    virtual void                    paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

FLOW_CHART_NAMESPACE_END