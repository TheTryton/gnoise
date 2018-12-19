#pragma once

#include "common.hpp"

class pin : public QGraphicsWidget
{
public:
    pin(QGraphicsWidget* parent = nullptr);
public:
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

class node : public QGraphicsWidget
{
    Q_OBJECT
public:
    node(QGraphicsWidget* parent = nullptr);
public:
    void                    set_input_pins_count(unsigned int input_pins_count);
    unsigned int            input_pins_count() const;

    void                    set_output_pins_count(unsigned int output_pins_count);
    unsigned int            output_pins_count() const;

    bool                    is_selected() const;
    void                    set_selected(bool select);
    void                    select();
    void                    deselect();

    virtual QRectF          boundingRect() const override;
    virtual QPainterPath    shape() const override;
    virtual void            paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    virtual void            hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void            hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void            hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

    virtual void            mousePressEvent(QGraphicsSceneMouseEvent* event) override;
private:
    unsigned int            _input_pins_count = 1;
    unsigned int            _output_pins_count = 1;
    bool                    _selected = false;
signals:
    void                    selectionChanged(bool selected);
};