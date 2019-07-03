#pragma once

#include "../preview_base/preview_node_base.hpp"
#include "../preview_base/preview_pin_base.hpp"

class result_node_pin final : public preview_pin_base
{
public:
    result_node_pin(QGraphicsWidget* parent = nullptr);
public:
    virtual void                    on_connected(link_base* l) override;
    virtual void                    on_disconnected(link_base* l) override;
    virtual bool                    can_connect_to(pin_base* other) const override;
};

class result_node_data : public module_data
{
public:
    friend class result_node;
private:
    size_t                                  _image_width = 100;
    size_t                                  _image_height = 100;
public:
    virtual noise_module*                   module() override;
    virtual QString                         module_name() const override;

    virtual size_t                          input_modules_count() const override;
    virtual vector<QString>                 input_names() const override;

    virtual size_t                          property_count() const override;
    virtual QVariant                        property_value(size_t property_index) const override;
    virtual bool                            set_property_value(size_t property_index, const QVariant& value) override;

    virtual QString                         property_name(size_t property_index) const override;
};

class result_node_compute_button : public QGraphicsWidget
{
    Q_OBJECT
public:
    result_node_compute_button(QGraphicsWidget* parent = nullptr);
public:
    virtual void                setGeometry(const QRectF& geometry) override;
    virtual QSizeF              sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
    virtual QRectF              boundingRect() const override;
    virtual void                paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
public:
    virtual void                mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void                mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
signals:
    void                        pressed();
    void                        released();
};

class result_node final : public preview_node_base
{
    Q_OBJECT
public:
    friend class result_node_pin;
private:
    static result_node_data* _init_data(result_node_data*& data)
    {
        data = new result_node_data;
        return data;
    }
private:
    result_node_data*               _data;
    noise_module*                   _current_module = nullptr;
public:
    result_node(QGraphicsWidget* parent = nullptr);
    virtual ~result_node() noexcept override;
public:
    virtual ::module_data*          module_data() override;
};