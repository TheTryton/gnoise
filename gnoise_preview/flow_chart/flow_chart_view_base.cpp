#include "flow_chart_view_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

flow_char_view_base::flow_char_view_base(QWidget* parent) :
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

void flow_char_view_base::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if (auto item = itemAt(event->pos()))
        {
            if (auto p = dynamic_cast<pin_base*>(item))
            {
                if (!_currently_created_link)
                {
                    if (p->direction() == pin_direction::input)
                    {
                        _currently_created_link = create_link();
                        _currently_created_link->set_to_pin(p);
                        _currently_created_link_pin = p;
                        _currently_created_link->set_from_point(mapToScene(event->pos()));
                        scene()->addItem(_currently_created_link);
                    }
                    else if (p->direction() == pin_direction::output)
                    {
                        _currently_created_link = create_link();
                        _currently_created_link->set_from_pin(p);
                        _currently_created_link_pin = p;
                        _currently_created_link->set_to_point(mapToScene(event->pos()));
                        scene()->addItem(_currently_created_link);
                    }
                }
                else
                {
                    if (p->can_connect_to(_currently_created_link_pin))
                    {
                        if (_currently_created_link_pin->direction() == pin_direction::input)
                        {
                            _currently_created_link->set_from_pin(p);
                        }
                        else if (_currently_created_link_pin->direction() == pin_direction::output)
                        {
                            _currently_created_link->set_to_pin(p);
                        }
                        _currently_created_link = nullptr;
                        _currently_created_link_pin = nullptr;
                    }
                    else
                    {
                        _currently_created_link->about_to_remove();
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
                    _currently_created_link->about_to_remove();
                    delete _currently_created_link;
                    _currently_created_link = nullptr;
                    _currently_created_link_pin = nullptr;
                }

                QGraphicsView::mousePressEvent(event);
                auto selected_items = scene()->selectedItems();
                if (!selected_items.empty())
                {
                    auto selected_item = selected_items.front();;
                    if (dynamic_cast<node_base*>(selected_item))
                    {
                        for (auto& item : scene()->items())
                        {
                            if (item != selected_item && dynamic_cast<node_base*>(item))
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
                _currently_created_link->about_to_remove();
                delete _currently_created_link;
                _currently_created_link = nullptr;
                _currently_created_link_pin = nullptr;
            }

            QGraphicsView::mousePressEvent(event);
        }
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
        if (_currently_created_link)
        {
            _currently_created_link->about_to_remove();
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
        else
        {
            if(auto n = dynamic_cast<node_base*>(item))
            {
                if(auto menu = n->context_menu_requested())
                {
                    menu->exec(event->globalPos());
                }
            }
            if (auto e = dynamic_cast<link_base*>(item))
            {
                if (auto menu = e->context_menu_requested())
                {
                    menu->exec(event->globalPos());
                }
            }
        }
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void flow_char_view_base::mouseMoveEvent(QMouseEvent* event)
{
    if (_currently_created_link)
    {
        auto p = dynamic_cast<pin_base*>(itemAt(event->pos()));
        if (p && p->can_connect_to(_currently_created_link_pin))
        {
            if (_currently_created_link_pin->direction() == pin_direction::input)
            {
                _currently_created_link->set_from_point(p->pin_pos());
            }
            else if (_currently_created_link_pin->direction() == pin_direction::output)
            {
                _currently_created_link->set_to_point(p->pin_pos());
            }
        }
        else
        {
            if (_currently_created_link_pin->direction() == pin_direction::input)
            {
                _currently_created_link->set_from_point(mapToScene(event->pos()));
                _currently_created_link->set_from_pin(nullptr);
            }
            else if (_currently_created_link_pin->direction() == pin_direction::output)
            {
                _currently_created_link->set_to_point(mapToScene(event->pos()));
                _currently_created_link->set_to_pin(nullptr);
            }
        }
    }
    if (event->buttons() & Qt::MouseButton::LeftButton)
    {
        for (auto& item : scene()->selectedItems())
        {
            if (auto n = dynamic_cast<node_base*>(item))
            {
                for (auto& i_p : n->pins(pin_direction::input))
                {
                    for (auto& l : i_p->links())
                    {
                        l->update_link_geometry();
                    }
                }
                for (auto& o_p : n->pins(pin_direction::output))
                {
                    for (auto& l : o_p->links())
                    {
                        l->update_link_geometry();
                    }
                }
            }
        }
    }
    if (event->buttons() & Qt::MouseButton::RightButton)
    {
        if (!_selection_rubber_band.isHidden())
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

void flow_char_view_base::mouseReleaseEvent(QMouseEvent * event)
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

void flow_char_view_base::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key::Key_Delete)
    {
        for (auto& item : scene()->selectedItems())
        {
            if (auto e = dynamic_cast<link_base*>(item))
            {
                if (e->removable())
                {
                    e->about_to_remove();
                    delete e;
                }
            }
        }
        for (auto& item : scene()->selectedItems())
        {
            if (auto n = dynamic_cast<node_base*>(item))
            {
                if(n->removable())
                {
                    n->about_to_remove();
                    delete n;
                }
            }
        }
    }
}

void flow_char_view_base::enterEvent(QEvent * event)
{
    QGraphicsView::enterEvent(event);

    viewport()->setCursor(Qt::ArrowCursor);
    setCursor(Qt::CursorShape::ArrowCursor);
}

FLOW_CHART_NAMESPACE_END
