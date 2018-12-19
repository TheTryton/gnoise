#include "additional_delegates.hpp"
#include <map>

noise_quality noise_quality_enum_info::name_to_value(const QString& name)
{
    static std::map<QString, noise_quality> translator = 
    {
        {"fast", noise_quality::fast},
        {"standard", noise_quality::standard},
        {"best", noise_quality::best}
    };
    return translator[name];
}

QString noise_quality_enum_info::value_to_name(const noise_quality& value)
{
    static std::map<noise_quality, QString> translator =
    {
        {noise_quality::fast, "fast"},
        {noise_quality::standard, "standard"},
        {noise_quality::best, "best"}
    };
    return translator[value];
}

QStringList noise_quality_enum_info::names()
{
    return {"fast", "standard", "best"};
}

vector<noise_quality> noise_quality_enum_info::values()
{
    return { noise_quality::fast, noise_quality::standard, noise_quality::best };
}

int_delegate::int_delegate(QWidget * parent) :
    QItemDelegate(parent)
{
}

void int_delegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (index.data().canConvert<int>()) {
        auto value = index.data(Qt::EditRole).value<int>();

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        painter->setRenderHint(QPainter::Antialiasing, true);

        auto metrics = painter->fontMetrics();
        painter->drawText(option.rect.adjusted(metrics.width(' '), 0, 0, 0), Qt::AlignVCenter, QString::number(value));
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

QWidget * int_delegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QSpinBox* editor = new QSpinBox(parent);
    editor->setFocus();
    return editor;
}

void int_delegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
    if (index.data().canConvert<int>())
    {
        QSpinBox* e = static_cast<QSpinBox*>(editor);
        auto value = index.data(Qt::EditRole).value<int>();
        e->setValue(value);
    }
    else
    {
        return QItemDelegate::setEditorData(editor, index);
    }
}

void int_delegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
    if (index.data().canConvert<int>())
    {
        QSpinBox* e = static_cast<QSpinBox*>(editor);
        model->setData(index, QVariant::fromValue(e->value()), Qt::EditRole);
    }
    else
    {
        return QItemDelegate::setModelData(editor, model, index);
    }
}
