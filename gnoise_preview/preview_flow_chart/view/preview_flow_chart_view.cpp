#include "preview_flow_chart_view.hpp"
#include "../module_nodes/module_nodes.hpp"
#include "../result_node/result_node.hpp"

#include <array>
#include <utility>
#include <functional>

//RESULT NODES

static const std::array<std::pair<QString, std::function<node_base*()>>, 1> _creatable_result_nodes =
{
    std::make_pair("Result Visualizer", []() {return new result_node; })
};

//GENERATORS

static const std::array<std::pair<QString, std::function<node_base*()>>, 8> _creatable_generator_nodes =
{
    std::make_pair("Perlin", []() {return new perlin_module_node; }),
    std::make_pair("Const", []() {return new const_module_node; }),
    std::make_pair("Checkerboard", []() {return new checkerboard_module_node; }),
    std::make_pair("Cylinders", []() {return new cylinders_module_node; }),
    std::make_pair("Spheres", []() {return new spheres_module_node; }),
    std::make_pair("Billow", []() {return new billow_module_node; }),
    std::make_pair("Ridged Multifractal", []() {return new ridged_multifractal_module_node; }),
    std::make_pair("Voronoi", []() {return new voronoi_module_node; })
};

//COMBINERS

static const std::array<std::pair<QString, std::function<node_base*()>>, 7> _creatable_combiner_nodes =
{
    std::make_pair("Add", []() {return new add_module_node; }),
    std::make_pair("Subtract", []() {return new subtract_module_node; }),
    std::make_pair("Multiply", []() {return new multiply_module_node; }),
    std::make_pair("Divide", []() {return new divide_module_node; }),
    std::make_pair("Power", []() {return new power_module_node; }),
    std::make_pair("Min", []() {return new min_module_node; }),
    std::make_pair("Max", []() {return new max_module_node; })
};

//MODIFIERS

static const std::array<std::pair<QString, std::function<node_base*()>>, 5> _creatable_modifier_nodes =
{
    std::make_pair("Abs", []() {return new abs_module_node; }),
    std::make_pair("Clamp", []() {return new clamp_module_node; }),
    std::make_pair("Base", []() {return new base_module_node; }),
    std::make_pair("Exponent", []() {return new exponent_module_node; }),
    std::make_pair("Scale Bias", []() {return new scale_bias_module_node; })
};

//SELECTORS

static const std::array<std::pair<QString, std::function<node_base*()>>, 2> _creatable_selector_nodes =
{
    std::make_pair("Blend", []() {return new blend_module_node; }),
    std::make_pair("Select", []() {return new select_module_node; })
};

//TRANSFORMERS

static const std::array<std::pair<QString, std::function<node_base*()>>, 5> _creatable_transformer_nodes =
{
    std::make_pair("Displace", []() {return new displace_module_node; }),
    std::make_pair("Turbulence", []() {return new turbulence_module_node; }),
    std::make_pair("Translate Point", []() {return new translate_point_module_node; }),
    std::make_pair("Rotate Point", []() {return new rotate_point_module_node; }),
    std::make_pair("Scale Point", []() {return new scale_point_module_node; })
};

preview_flow_chart_view::preview_flow_chart_view(QWidget* parent) :
    default_flow_chart_view(parent)
{
    setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
    QObject::connect(scene(), &QGraphicsScene::selectionChanged, this, [this]() {
        auto items = scene()->selectedItems();
        QList<preview_node_base*> selected_nodes;
        for (auto& item : items)
        {
            if (auto n = dynamic_cast<preview_node_base*>(item))
            {
                selected_nodes.append(n);
            }
        }

        emit selected_nodes_changed(selected_nodes);
    });
}

void preview_flow_chart_view::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu;
    auto pos = mapToScene(event->pos());
    
    //result nodes
    {
        for (auto& creatable_node : _creatable_result_nodes)
        {
            menu.addAction(creatable_node.first, [pos, creatable_node, this]() {
                auto node = creatable_node.second();
                node->setPos(pos);
                scene()->addItem(node);
            });
        }
    }
    //generators
    {
        auto generators = menu.addMenu("Generators");
        for (auto& creatable_node : _creatable_generator_nodes)
        {
            generators->addAction(creatable_node.first, [pos, creatable_node, this]() {
                auto node = creatable_node.second();
                node->setPos(pos);
                scene()->addItem(node);
            });
        }
    }
    //combiners
    {
        auto combiners = menu.addMenu("Combiners");
        for (auto& creatable_node : _creatable_combiner_nodes)
        {
            combiners->addAction(creatable_node.first, [pos, creatable_node, this]() {
                auto node = creatable_node.second();
                node->setPos(pos);
                scene()->addItem(node);
            });
        }
    }
    //modifiers
    {
        auto modifiers = menu.addMenu("Modifiers");
        for (auto& creatable_node : _creatable_modifier_nodes)
        {
            modifiers->addAction(creatable_node.first, [pos, creatable_node, this]() {
                auto node = creatable_node.second();
                node->setPos(pos);
                scene()->addItem(node);
            });
        }
    }
    //selectors
    {
        auto selectors = menu.addMenu("Selectors");
        for (auto& creatable_node : _creatable_selector_nodes)
        {
            selectors->addAction(creatable_node.first, [pos, creatable_node, this]() {
                auto node = creatable_node.second();
                node->setPos(pos);
                scene()->addItem(node);
            });
        }
    }
    //transformers
    {
        auto transformers = menu.addMenu("Transformers");
        for (auto& creatable_node : _creatable_transformer_nodes)
        {
            transformers->addAction(creatable_node.first, [pos, creatable_node, this]() {
                auto node = creatable_node.second();
                node->setPos(pos);
                scene()->addItem(node);
            });
        }
    }
    
    menu.exec(event->globalPos());
}