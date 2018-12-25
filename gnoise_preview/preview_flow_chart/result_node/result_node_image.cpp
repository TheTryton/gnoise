#include "result_node_image.hpp"

class image_widget : public QWidget
{
private:
    QImage                      _image;
public:
    image_widget(QWidget* parent = nullptr) :
        QWidget(parent)
    {

    }
public:
    void                        set_image(const QImage& image)
    {
        _image = image;
        setFixedSize(_image.size());
    }
    QImage                      image() const
    {
        return _image;
    }
protected:
    virtual void                paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.drawImage(_image.rect(), _image);
    }
};

result_node_image::result_node_image(QGraphicsWidget* parent) :
    QGraphicsProxyWidget(parent)
{
    setFlag(ItemSendsGeometryChanges);

    setMinimumSize(800, 600);

    auto* image_scroll_area = new QScrollArea;
    image_scroll_area->setStyleSheet(
        "QWidget{\n"
        "   background-color: rgb(72, 74, 82);\n"
        "   color: white;\n"
        "}\n"
    );
    image_scroll_area->setFixedSize(800, 600);
    _widget = new image_widget;
    image_scroll_area->setWidget(_widget);
    setWidget(image_scroll_area);
}

void result_node_image::set_image(const QImage& image)
{
    _widget->set_image(image);
    update();
}

QImage result_node_image::image() const
{
    return _widget->image();
}