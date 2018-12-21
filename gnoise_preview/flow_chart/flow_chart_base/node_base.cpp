#include "node_base.hpp"
#include "pin_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

node_base::node_base(QGraphicsWidget* parent) :
    QGraphicsWidget(parent)
{
}

size_t node_base::links_count() const
{
    size_t l_count = 0;
    for(auto& p : pins(pin_direction::input))
    {
        l_count += p->links_count();
    }
    for (auto& p : pins(pin_direction::output))
    {
        l_count += p->links_count();
    }
    return l_count;
}

vector<link_base*> node_base::links() const
{
    vector<link_base*> ls;
    for (auto& p : pins(pin_direction::input))
    {
        auto p_ls = p->links();
        ls.insert(ls.end(), p_ls.begin(), p_ls.end());
    }
    for (auto& p : pins(pin_direction::output))
    {
        auto p_ls = p->links();
        ls.insert(ls.end(), p_ls.begin(), p_ls.end());
    }
    return ls;
}

void node_base::about_to_remove()
{
    for(auto& pin : pins(pin_direction::input))
    {
        pin->about_to_remove();
    }
    for (auto& pin : pins(pin_direction::output))
    {
        pin->about_to_remove();
    }
}

void node_base::_set_pin_parent_to_this(pin_base* p)
{
    p->_parent_node = this;
}

FLOW_CHART_NAMESPACE_END
