#pragma once

#include "../preview_common.hpp"

class image_widget;

class result_node_image : public QGraphicsProxyWidget
{
private:
    image_widget*               _widget;
public:
    result_node_image(QGraphicsWidget* parent = nullptr);
public:
    void                        set_image(const QImage& image);
    QImage                      image() const;
};