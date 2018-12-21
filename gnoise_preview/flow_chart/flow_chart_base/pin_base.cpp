#include "pin_base.hpp"
#include "node_base.hpp"
#include "link_base.hpp"

FLOW_CHART_NAMESPACE_BEGIN

pin_base::pin_base(QGraphicsWidget * parent):
    QGraphicsWidget(parent)
{
}

pin_base::~pin_base()
{
}

node_base* pin_base::parent_node() const
{
    return _parent_node;
}

int pin_base::index() const
{
    if(!_parent_node)
    {
        return -1;
    }
    return _parent_node->pin_index(this);
}

std::vector<link_base*> pin_base::links() const
{
    return _links;
}

size_t pin_base::links_count() const
{
    return _links.size();
}

void pin_base::about_to_remove()
{
    for (auto& link : _links)
    {
        link->about_to_remove();
        delete link;
    }
}

void pin_base::_connect(link_base* link)
{
    if(link_mode() == pin_link_mode::exclusive)
    {
        if(!_links.empty())
        {
            _disconnect_delete(_links.front());
        }
    }

    _links.push_back(link);
}

void pin_base::_disconnect_no_delete(link_base * link)
{
    auto it = std::find(_links.begin(), _links.end(), link);
    _links.erase(it);
}

void pin_base::_disconnect_delete(link_base* link)
{
    auto it = std::find(_links.begin(), _links.end(), link);
    if(it != _links.end())
    {
        auto link = *it;
        link->about_to_remove();
        delete link;
    }
}

FLOW_CHART_NAMESPACE_END