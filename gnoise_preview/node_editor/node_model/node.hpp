#pragma once

#include "model_common.hpp"

NODE_EDITOR_NAMESPACE_BEGIN

class node : public QGraphicsWidget
{
    Q_OBJECT
public:
    node(QGraphicsWidget* parent = nullptr);
public:
    std::vector<pin*>               pins(pin_direction direction);
    unsigned int                    pin_index(const pin* p);
    pin*                            add_pin(pin_direction direction);
    pin*                            insert_pin(pin_direction direction, unsigned int index);
    void                            remove_pin(pin_direction direction, unsigned int index);
    void                            remove_pin(pin* p);
    unsigned int                    pins_count(pin_direction direction) const;
    pin*                            pin(pin_direction direction, unsigned int index);

    void                            set_content(QGraphicsLayoutItem* content);
    QGraphicsLayoutItem*            content() const;

    virtual QRectF                  boundingRect() const override;
    virtual QPainterPath            shape() const override;
    virtual void                    paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
protected:
    virtual void                    hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void                    contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
    QGraphicsGridLayout*            _root_layout = nullptr;
    QGraphicsLinearLayout*          _input_pins_layout = nullptr;
    std::vector<node_editor::pin*>  _input_pins;
    QGraphicsLinearLayout*          _output_pins_layout = nullptr;
    std::vector<node_editor::pin*>  _output_pins;
    QGraphicsLayoutItem*            _content;
};

NODE_EDITOR_NAMESPACE_END