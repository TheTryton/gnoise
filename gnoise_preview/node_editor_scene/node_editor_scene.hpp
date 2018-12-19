#pragma once

#include <QtWidgets>

class node_editor_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    node_editor_scene(QObject* parent = nullptr);
};

class node_editor_view : public QGraphicsView
{
    Q_OBJECT
public:
    node_editor_view(QWidget* parent = nullptr);
public:
    virtual void mousePressEvent(QMouseEvent* event) override;
};