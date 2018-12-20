#pragma once

#include <QtWidgets>
#include "node_editor/node_model/link.hpp"

class node_editor_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    node_editor_scene(QObject* parent = nullptr);
protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
};

class node_editor_view : public QGraphicsView
{
    Q_OBJECT
public:
    node_editor_view(QWidget* parent = nullptr);
protected:
    virtual void                mousePressEvent(QMouseEvent* event) override;
    virtual void                mouseMoveEvent(QMouseEvent* event) override;
    virtual void                mouseReleaseEvent(QMouseEvent* event) override;
    virtual void                keyPressEvent(QKeyEvent* event) override;
    virtual void                enterEvent(QEvent *event) override;
private:
    QRubberBand                 _selection_rubber_band;
    QPoint                      _selection_origin;
    node_editor::link*          _currently_created_link = nullptr;
    node_editor::pin*           _currently_created_link_pin;
};