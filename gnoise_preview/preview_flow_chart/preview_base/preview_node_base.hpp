#pragma once

#include "../preview_common.hpp"

class preview_node_base : public node_base
{
protected:
    std::vector<pin_base*>          _input_pins;
    std::vector<pin_base*>          _output_pins;

    QGraphicsLinearLayout*          _root_layout = nullptr;
    QGraphicsLinearLayout*          _pins_layout = nullptr;
    QGraphicsLinearLayout*          _input_pins_layout = nullptr;
    QGraphicsLinearLayout*          _output_pins_layout = nullptr;
public:
    preview_node_base(module_data* data, QGraphicsWidget* parent = nullptr);
    virtual ~preview_node_base() noexcept override = default;
public:
    virtual std::vector<pin_base*>  pins(pin_direction direction) const override;
    virtual int                     pin_index(const pin_base* p) const override;
    virtual size_t                  pins_count(pin_direction direction) const override;
    virtual pin_base*               pin(pin_direction direction, int index) const override;

    virtual module_data*            module_data() = 0;

    virtual QMenu*                  context_menu_requested() override;

    virtual bool                    removable() const override;
public:
    virtual QRectF                  boundingRect() const override;
    virtual QPainterPath            shape() const override;
    virtual void                    paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};