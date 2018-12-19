#pragma once

#include "common.hpp"
#include <vector>

class int_delegate : public QItemDelegate
{
public:
    int_delegate(QWidget* parent = nullptr);

    virtual void        paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QWidget*            createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void                setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void                setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

struct noise_quality_enum_info
{
    using enum_type = noise_quality;

    static noise_quality name_to_value(const QString& name);
    static QString value_to_name(const noise_quality& value);
    static QStringList names();
    static std::vector<noise_quality> values();
};

template<class E>
class enum_delegate : public QItemDelegate
{
public:
    enum_delegate(QWidget* parent = nullptr) :
        QItemDelegate(parent)
    {
    }

    virtual void        paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index) const override
    {
        if (index.data().canConvert<E::enum_type>()) {
            auto enum_value = index.data(Qt::EditRole).value<E::enum_type>();

            if (option.state & QStyle::State_Selected)
                painter->fillRect(option.rect, option.palette.midlight());

            painter->setRenderHint(QPainter::Antialiasing, true);

            auto metrics = painter->fontMetrics();
            painter->drawText(option.rect.adjusted(metrics.width(' '), 0, 0, 0), Qt::AlignVCenter, E::value_to_name(enum_value));
        }
        else
        {
            QItemDelegate::paint(painter, option, index);
        }
    }
    QWidget*            createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QComboBox* editor = new QComboBox(parent);
        editor->addItems(E::names());
        return editor;
    }
    void                setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
        if (index.data().canConvert<E::enum_type>())
        {
            QComboBox* e = static_cast<QComboBox*>(editor);
            auto enum_value = index.data(Qt::EditRole).value<E::enum_type>();
            QString name = E::value_to_name(enum_value);
            auto names = E::names();
            auto index = std::find(names.begin(), names.end(), name);
            if(index != names.end())
            {
                e->setCurrentIndex(index - names.begin());
            }
            else
            {
                e->setCurrentIndex(0);
            }
        }
        else
        {
            return QItemDelegate::setEditorData(editor, index);
        }
    }
    void                setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
    {
        if (index.data().canConvert<E::enum_type>())
        {
            QComboBox* e = static_cast<QComboBox*>(editor);
            auto name = e->currentText();
            model->setData(index, QVariant::fromValue(E::name_to_value(name)), Qt::EditRole);
        }
        else
        {
            return QItemDelegate::setModelData(editor, model, index);
        }
    }
};

using noise_quality_delegate = enum_delegate<noise_quality_enum_info>;