#pragma once

#include "../flow_chart_common.hpp"

FLOW_CHART_NAMESPACE_BEGIN

class pin_base : public QGraphicsWidget
{
public:
    friend class node_base;
    friend class link_base;
private:
    std::vector<link_base*> _links;
    node_base*              _parent_node = nullptr;
public:
    pin_base(QGraphicsWidget* parent = nullptr);
    ~pin_base();
public:
    node_base*              parent_node() const;

    int                     index() const;
    virtual pin_direction   direction() const = 0;
    virtual pin_link_mode   link_mode() const = 0;
    virtual QPointF         pin_pos() const = 0;

    std::vector<link_base*> links() const;
    size_t                  links_count() const;

    virtual void            on_connected(link_base* l) = 0;
    virtual void            on_disconnected(link_base* l) = 0;
    virtual bool            can_connect_to(pin_base* other) const = 0;
public:
    void                    about_to_remove();
private:
    void                    _connect(link_base* link);
    void                    _disconnect_no_delete(link_base* link);
    void                    _disconnect_delete(link_base* link);
};

FLOW_CHART_NAMESPACE_END