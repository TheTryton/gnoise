#pragma once

#include "common.hpp"

#define FLOW_CHART flow_chart
#define FLOW_CHART_NAMESPACE_BEGIN namespace FLOW_CHART{
#define FLOW_CHART_NAMESPACE_END }

FLOW_CHART_NAMESPACE_BEGIN

enum pin_direction
{
    input,
    output
};

enum pin_link_mode
{
    exclusive,
    unconstrained
};

class node_base;
class pin_base;
class link_base;

FLOW_CHART_NAMESPACE_END