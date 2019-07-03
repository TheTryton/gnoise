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

    QObject::connect(&_zoom_animation, &QVariantAnimation::valueChanged, this, [this](const QVariant& v) {
        auto factor = v.toDouble() / this->_current_zoom;
        scale(factor, factor);
        this->_current_zoom = v.toDouble();
    });
}

void flow_char_view_base::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if (auto item = itemAt(event->pos()))
        {
            if (auto p = dynamic_cast<pin_base*>(item))
            {
                if (_is_creating_link())
                {
                    if (p->can_connect_to(_currently_created_link_pin) && _currently_created_link_pin->can_connect_to(p))
                    {
                        _finish_creating_link(p);
                    }
                    else
                    {
                        _delete_created_link();
                    }
                }
                else
                {
                    _start_creating_link(p, mapToScene(event->pos()));
                }
            }
            else
            {
                if (_is_creating_link())
                {
                    _delete_created_link();
                }

                QGraphicsView::mousePressEvent(event);
                _reorder_selected();
            }
        }
        else
        {
            if (_is_creating_link())
            {
                _delete_created_link();
            }

            QGraphicsView::mousePressEvent(event);
        }
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
        if (_is_creating_link())
        {
            _delete_created_link();
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
                scene()->clearSelection();
                n->setSelected(true);
                if(auto menu = n->context_menu_requested())
                {
                    menu->exec(event->globalPos());
                }
            }
            else if (auto e = dynamic_cast<link_base*>(item))
            {
                scene()->clearSelection();
                e->setSelected(true);
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
    if (_is_creating_link())
    {
        auto p = dynamic_cast<pin_base*>(itemAt(event->pos()));
        if (p && p->can_connect_to(_currently_created_link_pin) && _currently_created_link_pin->can_connect_to(p))
        {
            _update_created_link(p->pin_pos());
            _currently_created_link->set_can_be_created(true);
        }
        else
        {
            _update_created_link(mapToScene(event->pos()));
            _currently_created_link->set_can_be_created(false);
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
            _reorder_selected();

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

void flow_char_view_base::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::RightButton)
    {
        if (itemAt(event->pos()))
        {
            setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        }
        else
        {
            setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        }

        if(_selection_origin != event->pos())
        {
            setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        }

        if (!_selection_rubber_band.isHidden())
        {
            _selection_rubber_band.hide();
            event->accept();
        }
    }

    QGraphicsView::mouseReleaseEvent(event);

    viewport()->setCursor(Qt::CursorShape::ArrowCursor);
    setCursor(Qt::CursorShape::ArrowCursor);
}

void flow_char_view_base::wheelEvent(QWheelEvent* event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double angle = event->angleDelta().y();
    double factor = qPow(1.0015, angle);

    _zoom_animation.stop();
    _target_zoom = qMax(qMin(_target_zoom * factor, _max_zoom), _min_zoom);
    _zoom_animation.setStartValue(_current_zoom);
    _zoom_animation.setEndValue(_target_zoom);
    _zoom_animation.setDuration(100);
    _zoom_animation.start();
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
                    e->about_to_be_removed();
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
                    n->about_to_be_removed();
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

void flow_char_view_base::_reorder_selected() const
{
    auto selected_items = scene()->selectedItems();
    QList<node_base*> selected_nodes;
    for(auto& selected_item : selected_items)
    {
        if (auto n = dynamic_cast<node_base*>(selected_item))
        {
            selected_nodes.append(n);
        }
    }

    if (!selected_nodes.empty())
    {
        for (auto& item : scene()->items())
        {
            if(auto n = dynamic_cast<node_base*>(item))
            {
                if (!selected_nodes.contains(n))
                {
                    if (item->zValue() == 1.0)
                    {
                        item->setZValue(0.0);
                    }
                }
            }
            
        }

        for(auto& n : selected_nodes)
        {
            n->setZValue(1.0);
        }
    }
}

bool flow_char_view_base::_is_creating_link() const
{
    return _currently_created_link;
}

void flow_char_view_base::_update_created_link(const QPointF & pos)
{
    if (_currently_created_link_pin->direction() == pin_direction::input)
    {
        _currently_created_link->set_from_point(pos);
    }
    else if (_currently_created_link_pin->direction() == pin_direction::output)
    {
        _currently_created_link->set_to_point(pos);
    }
}

void flow_char_view_base::_start_creating_link(pin_base* p, const QPointF& pos)
{
    if (p->direction() == pin_direction::input)
    {
        _currently_created_link = create_link();
        _currently_created_link->set_to_point(p->pin_pos());
        _currently_created_link_pin = p;
        _currently_created_link->set_from_point(pos);
        scene()->addItem(_currently_created_link);
    }
    else if (p->direction() == pin_direction::output)
    {
        _currently_created_link = create_link();
        _currently_created_link->set_from_point(p->pin_pos());
        _currently_created_link_pin = p;
        _currently_created_link->set_to_point(pos);
        scene()->addItem(_currently_created_link);
    }

    for (auto& item : scene()->items())
    {
        if (auto p = dynamic_cast<pin_base*>(item))
        {
            p->set_created_link_pin(_currently_created_link_pin);
        }
    }
}

void flow_char_view_base::_delete_created_link()
{
    _currently_created_link->about_to_be_removed();
    delete _currently_created_link;
    _currently_created_link = nullptr;
    _currently_created_link_pin = nullptr;

    for(auto& item : scene()->items())
    {
        if(auto p = dynamic_cast<pin_base*>(item))
        {
            p->set_created_link_pin(nullptr);
        }
    }
}

void flow_char_view_base::_finish_creating_link(pin_base* p)
{
    if (_currently_created_link_pin->direction() == pin_direction::input)
    {
        _currently_created_link->set_from_pin(p);
        _currently_created_link->set_to_pin(_currently_created_link_pin);
    }
    else if (_currently_created_link_pin->direction() == pin_direction::output)
    {
        _currently_created_link->set_from_pin(_currently_created_link_pin);
        _currently_created_link->set_to_pin(p);
    }
    _currently_created_link->set_can_be_created(false);
    _currently_created_link = nullptr;
    _currently_created_link_pin = nullptr;

    for (auto& item : scene()->items())
    {
        if (auto p = dynamic_cast<pin_base*>(item))
        {
            p->set_created_link_pin(nullptr);
        }
    }
}

FLOW_CHART_NAMESPACE_END
