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
    virtual void                keyPressEvent(QKeyEvent* event) override;
    virtual void                enterEvent(QEvent *event) override;
private:
    QRubberBand                 _selection_rubber_band;
    QPoint                      _selection_origin;
    link_base*                  _currently_created_link = nullptr;
    pin_base*                   _currently_created_link_pin;
};

FLOW_CHART_NAMESPACE_END