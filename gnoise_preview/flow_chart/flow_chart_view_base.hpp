#pragma once

#include "flow_chart_base/node_base.hpp"
#include "flow_chart_base/pin_base.hpp"
#include "flow_chart_base/link_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class flow_char_view_base : public QGraphicsView
{
    Q_OBJECT
public:
    flow_char_view_base(QWidget* parent = nullptr);
protected:
    virtual link_base*          create_link() const = 0;
protected:
    virtual void                mousePressEvent(QMouseEvent* event) override;
    virtual void                mouseMoveEvent(QMouseEvent* event) override;
    virtual void                mouseReleaseEvent(QMouseEvent* event) override;
    virtual void                wheelEvent(QWheelEvent* event) override;
    virtual void                keyPressEvent(QKeyEvent* event) override;
    virtual void                enterEvent(QEvent *event) override;
private:
    void                        _reorder_selected() const;

    bool                        _is_creating_link() const;
    void                        _update_created_link(const QPointF& pos);
    void                        _start_creating_link(pin_base* start_pin, const QPointF& pos);
    void                        _delete_created_link();
    void                        _finish_creating_link(pin_base* other_pin);
private:
    QRubberBand                 _selection_rubber_band;
    QPoint                      _selection_origin;
    link_base*                  _currently_created_link = nullptr;
    pin_base*                   _currently_created_link_pin;

    qreal                       _current_zoom = 1.0;
    qreal                       _target_zoom = 1.0;
    QVariantAnimation           _zoom_animation;

    constexpr static qreal      _min_zoom = 0.125;
    constexpr static qreal      _max_zoom = 15.0;
};

FLOW_CHART_NAMESPACE_END