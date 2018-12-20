#pragma once

#include "common.hpp"

#define NODE_EDITOR node_editor
#define NODE_EDITOR_NAMESPACE_BEGIN namespace NODE_EDITOR{
#define NODE_EDITOR_NAMESPACE_END }

NODE_EDITOR_NAMESPACE_BEGIN

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

class node;
class pin;
class link;

NODE_EDITOR_NAMESPACE_END