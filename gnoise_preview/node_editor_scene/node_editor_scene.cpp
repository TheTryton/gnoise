#include "node_editor_scene.hpp"
#include "node_editor/node.hpp"

node_editor_scene::node_editor_scene(QObject* parent) :
    QGraphicsScene(parent)
{
    
}

node_editor_view::node_editor_view(QWidget* parent) :
    QGraphicsView(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
}

void node_editor_view::mousePressEvent(QMouseEvent* event)
{
    if (itemAt(event->pos()) == nullptr)
    {
        if (event->button() & Qt::MouseButton::LeftButton)
        {
            for (auto item : items())
            {
                if (auto n = dynamic_cast<node*>(item))
                {
                    n->deselect();
                }
            }
            event->accept();
        }
    }

    QGraphicsView::mousePressEvent(event);
}
