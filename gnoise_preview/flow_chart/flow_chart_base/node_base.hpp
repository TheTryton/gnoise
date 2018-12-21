#pragma once

#include "../flow_chart_common.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class node_base : public QGraphicsWidget
{
public:
    node_base(QGraphicsWidget* parent = nullptr);
    virtual ~node_base() noexcept override = default;
public:
    virtual std::vector<pin_base*>  pins(pin_direction direction) const = 0;
    virtual int                     pin_index(const pin_base* p) const = 0;
    virtual size_t                  pins_count(pin_direction direction) const = 0;
    virtual pin_base*               pin(pin_direction direction, int index) const = 0;

    size_t                          links_count() const;
    std::vector<link_base*>         links() const;

    virtual QMenu*                  context_menu_requested() const = 0;
    virtual bool                    removable() const = 0;
public:
    void                            about_to_remove();
protected:
    void                            _set_pin_parent_to_this(pin_base* p);
};

FLOW_CHART_NAMESPACE_END