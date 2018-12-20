#include "node_editor_scene.hpp"
#include "node_editor/node_model/node.hpp"
#include "node_editor/node_model/pin.hpp"
#include "node_editor/node_model/link.hpp"

node_editor_scene::node_editor_scene(QObject* parent) :
    QGraphicsScene(parent)
{
    
}

node_editor_view::node_editor_view(QWidget* parent) :
    QGraphicsView(parent),
    _selection_rubber_band(QRubberBand::Shape::Rectangle, this)
{
    _selection_rubber_band.hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
    setCursor(Qt::CursorShape::ArrowCursor);
    setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::FullViewportUpdate);
}

void node_editor_view::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if(auto item = itemAt(event->pos()))
        {
            if(auto p = dynamic_cast<node_editor::pin*>(item))
            {
                if(!_currently_created_link)
                {
                    if(p->direction() == node_editor::pin_direction::input)
                    {
                        _currently_created_link = new node_editor::link;
                        _currently_created_link->set_to_pin(p);
                        _currently_created_link_pin = p;
                        _currently_created_link->set_from_point(mapToScene(event->pos()));
                        scene()->addItem(_currently_created_link);
                    }
                    else if(p->direction() == node_editor::pin_direction::output)
                    {
                        _currently_created_link = new node_editor::link;
                        _currently_created_link->set_from_pin(p);
                        _currently_created_link_pin = p;
                        _currently_created_link->set_to_point(mapToScene(event->pos()));
                        scene()->addItem(_currently_created_link);
                    }
                }
                else
                {
                    if(p != _currently_created_link_pin)
                    {
                        if(p->direction() == _currently_created_link_pin->direction())
                        {
                            delete _currently_created_link;
                            _currently_created_link = nullptr;
                            _currently_created_link_pin = nullptr;
                        }
                        else
                        {
                            if (_currently_created_link_pin->direction() == node_editor::pin_direction::input)
                            {
                                _currently_created_link->set_from_pin(p);
                            }
                            else if (_currently_created_link_pin->direction() == node_editor::pin_direction::output)
                            {
                                _currently_created_link->set_to_pin(p);
                            }
                            _currently_created_link->set_selectable(true);
                            _currently_created_link = nullptr;
                            _currently_created_link_pin = nullptr;
                        }
                    }
                    else
                    {
                        delete _currently_created_link;
                        _currently_created_link = nullptr;
                        _currently_created_link_pin = nullptr;
                    }
                }
            }
            else
            {
                if (_currently_created_link)
                {
                    delete _currently_created_link;
                    _currently_created_link = nullptr;
                    _currently_created_link_pin = nullptr;
                }

                QGraphicsView::mousePressEvent(event);
                auto selected_items = scene()->selectedItems();
                if(!selected_items.empty())
                {
                    auto selected_item = selected_items.front();;
                    if (dynamic_cast<node_editor::node*>(selected_item))
                    {
                        for (auto& item : scene()->items())
                        {
                            if (item != selected_item && dynamic_cast<node_editor::node*>(item))
                            {
                                if (item->zValue() == 1.0)
                                {
                                    item->setZValue(0.0);
                                }
                            }
                        }
                        selected_item->setZValue(1.0);
                    }
                }
            }
        }
        else
        {
            if (_currently_created_link)
            {
                delete _currently_created_link;
                _currently_created_link = nullptr;
                _currently_created_link_pin = nullptr;
            }

            QGraphicsView::mousePressEvent(event);
        }
    }
    else if(event->button() == Qt::MouseButton::RightButton)
    {
        if (_currently_created_link)
        {
            delete _currently_created_link;
            _currently_created_link = nullptr;
            _currently_created_link_pin = nullptr;
        }

        auto item = itemAt(event->pos());
        if (!item)
        {
            _selection_origin = event->pos();
            _selection_rubber_band.setGeometry(QRect(_selection_origin, QSize()));
            _selection_rubber_band.show();
            event->accept();
        }
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void node_editor_view::mouseMoveEvent(QMouseEvent* event)
{
    if(_currently_created_link)
    {
        auto p = dynamic_cast<node_editor::pin*>(itemAt(event->pos()));
        if (p && p != _currently_created_link_pin && p->direction() != _currently_created_link_pin->direction())
        {
            if (_currently_created_link_pin->direction() == node_editor::pin_direction::input)
            {
                _currently_created_link->set_from_point(p->pin_pos());
            }
            else if (_currently_created_link_pin->direction() == node_editor::pin_direction::output)
            {
                _currently_created_link->set_to_point(p->pin_pos());
            }
        }
        else
        {
            if (_currently_created_link_pin->direction() == node_editor::pin_direction::input)
            {
                _currently_created_link->set_from_point(mapToScene(event->pos()));
                _currently_created_link->set_from_pin(nullptr);
            }
            else if (_currently_created_link_pin->direction() == node_editor::pin_direction::output)
            {
                _currently_created_link->set_to_point(mapToScene(event->pos()));
                _currently_created_link->set_to_pin(nullptr);
            }
        }
    }
    if(event->buttons() & Qt::MouseButton::LeftButton)
    {
        for(auto& item : scene()->selectedItems())
        {
            if(auto n = dynamic_cast<node_editor::node*>(item))
            {
                for(auto& i_p : n->pins(node_editor::pin_direction::input))
                {
                    for (auto& l : i_p->links())
                    {
                        l->update_link();
                    }
                }
                for (auto& o_p : n->pins(node_editor::pin_direction::output))
                {
                    for(auto& l : o_p->links())
                    {
                        l->update_link();
                    }
                }
            }
        }
    }
    if(event->buttons() & Qt::MouseButton::RightButton)
    {
        if(!_selection_rubber_band.isHidden())
        {
            auto delta = event->pos() - _selection_origin;
            QRect area = QRect(_selection_origin, QSize(delta.x(), delta.y())).normalized();
            _selection_rubber_band.setGeometry(area);

            auto scene_area = mapToScene(area);
            QPainterPath path;
            path.addPolygon(scene_area);
            scene()->setSelectionArea(path, Qt::ItemSelectionMode::IntersectsItemShape);

            event->accept();
        }
        viewport()->setCursor(Qt::CursorShape::ArrowCursor);
        setCursor(Qt::CursorShape::ArrowCursor);
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void node_editor_view::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::MouseButton::RightButton)
    {
        _selection_rubber_band.hide();
        event->accept();
    }
    
    QGraphicsView::mouseReleaseEvent(event);

    viewport()->setCursor(Qt::CursorShape::ArrowCursor);
    setCursor(Qt::CursorShape::ArrowCursor);
}

void node_editor_view::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key::Key_Delete)
    {
        for (auto& item : scene()->selectedItems())
        {
            if (auto e = dynamic_cast<node_editor::link*>(item))
            {
                delete e;
            }
        }
        for (auto& item : scene()->selectedItems())
        {
            if (auto n = dynamic_cast<node_editor::node*>(item))
            {
                delete n;
            }
        }
    }
}

void node_editor_view::enterEvent(QEvent * event)
{
    QGraphicsView::enterEvent(event);

    viewport()->setCursor(Qt::ArrowCursor);
    setCursor(Qt::CursorShape::ArrowCursor);
}

void node_editor_scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->fillRect(rect, QColor(105, 105, 105));

    constexpr float separation_thicker = 100.0f;
    constexpr float separation_thinner = 25.0f;
    QPointF start_thick = QPointF(qFloor(rect.left() / separation_thicker) * separation_thicker, qFloor(rect.top() / separation_thicker) * separation_thicker);
    QPointF start_thin = QPointF(qFloor(rect.left() / separation_thinner) * separation_thinner, qFloor(rect.top() / separation_thinner) * separation_thinner);

    QPen pen_thick;
    pen_thick.setWidthF(3);
    pen_thick.setColor(QColor(169, 169, 169, 127));
    painter->setPen(pen_thick);
    for (float current_thick_x = start_thick.x(); current_thick_x < rect.right(); current_thick_x += separation_thicker)
    {
        painter->drawLine(QPointF(current_thick_x, rect.top()), QPointF(current_thick_x, rect.bottom()));
    }
    for (float current_thick_y = start_thick.y(); current_thick_y < rect.bottom(); current_thick_y += separation_thicker)
    {
        painter->drawLine(QPointF(rect.left(), current_thick_y), QPointF(rect.right(), current_thick_y));
    }

    QPen pen_thin;
    pen_thick.setWidthF(1);
    pen_thick.setColor(QColor(192, 192, 192, 127));
    painter->setPen(pen_thick);
    for (float current_thin_x = start_thin.x(); current_thin_x < rect.right(); current_thin_x += separation_thinner)
    {
        painter->drawLine(QPointF(current_thin_x, rect.top()), QPointF(current_thin_x, rect.bottom()));
    }
    for (float current_thin_y = start_thick.y(); current_thin_y < rect.bottom(); current_thin_y += separation_thinner)
    {
        painter->drawLine(QPointF(rect.left(), current_thin_y), QPointF(rect.right(), current_thin_y));
    }
}
