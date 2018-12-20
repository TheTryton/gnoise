#pragma once

#include "model_common.hpp"

NODE_EDITOR_NAMESPACE_BEGIN

class pin : public QGraphicsWidget
{
public:
    friend class node;
    friend class link;
private:
    std::vector<link*>      _links;
    node*                   _parent_node = nullptr;
    pin_direction           _direction;
    pin_link_mode           _pin_link_mode;
    QString                 _name;
    QFont                   _name_font;
public:
    pin(node* parent_node, pin_direction direction, pin_link_mode mode, QGraphicsWidget* parent = nullptr);
    ~pin();
public:
    node*                   parent_node() const;

    QFont                   font() const;
    void                    set_font(const QFont& font);

    QString                 name() const;
    void                    set_name(const QString& name);

    unsigned int            index() const;
    pin_direction           direction() const;
    pin_link_mode           link_mode() const;
    void                    set_link_mode(pin_link_mode mode);
    QPointF                 pin_pos() const;

    std::vector<link*>      links() const;

    virtual void            on_connected(link* l);
    virtual void            on_disconnected(link* l);
private:
    void                    _connect(link* link);
    void                    _disconnect_no_delete(link* link);
    void                    _disconnect(link* link);
protected:
    virtual void            setGeometry(const QRectF& geometry) override;
    virtual QSizeF          sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
    virtual QRectF          boundingRect() const override;
    virtual void            paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
};

NODE_EDITOR_NAMESPACE_END