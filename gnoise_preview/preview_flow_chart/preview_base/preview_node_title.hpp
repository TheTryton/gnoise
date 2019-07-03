#pragma once

#include "../preview_common.hpp"

class preview_node_title : public QGraphicsWidget
{
private:
    QString                     _title;
    module_type                 _type;
public:
    preview_node_title(const QString& title, module_type module_type, QGraphicsWidget* parent = nullptr);
public:
    void                        set_title(const QString& title);
    QString                     title() const;
public:
    virtual void                setGeometry(const QRectF& geometry) override;
    virtual QSizeF              sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
    virtual QRectF              boundingRect() const override;
    virtual void                paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
};
