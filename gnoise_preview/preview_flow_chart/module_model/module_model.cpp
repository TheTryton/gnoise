#include "module_model.hpp"

Q_DECLARE_METATYPE(noise_quality)

class bool_delegate : public QItemDelegate
{
public:
    bool_delegate(QWidget* parent = nullptr) :
        QItemDelegate(parent)
    {
    }

    virtual void        paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        if (index.data().canConvert<bool>()) {
            auto value = index.data(Qt::EditRole).value<bool>();

            if (option.state & QStyle::State_Selected)
                painter->fillRect(option.rect, option.palette.highlight());

            painter->setRenderHint(QPainter::Antialiasing, true);

            auto metrics = painter->fontMetrics();
            painter->drawText(option.rect.adjusted(metrics.width(' '), 0, 0, 0), Qt::AlignVCenter, value ? "true" : "false");
        }
        else
        {
            QItemDelegate::paint(painter, option, index);
        }
    }
    QWidget*            createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        return new QCheckBox(parent);
    }
    void                setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
        if (index.data().canConvert<bool>())
        {
            QCheckBox* e = static_cast<QCheckBox*>(editor);
            auto value = index.data(Qt::EditRole).value<bool>();
            e->setChecked(value);
        }
        else
        {
            return QItemDelegate::setEditorData(editor, index);
        }
    }
    void                setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
    {
        if (index.data().canConvert<bool>())
        {
            QCheckBox* e = static_cast<QCheckBox*>(editor);
            model->setData(index, QVariant::fromValue(e->isChecked()), Qt::EditRole);
        }
        else
        {
            return QItemDelegate::setModelData(editor, model, index);
        }
    }
};

class int_delegate : public QItemDelegate
{
public:
    int_delegate(QWidget* parent = nullptr) :
        QItemDelegate(parent)
    {
    }

    virtual void        paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
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
    QWidget*            createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        auto spinbox = new QSpinBox(parent);
        spinbox->setMinimum(std::numeric_limits<int>::min());
        spinbox->setMaximum(std::numeric_limits<int>::max());
        return spinbox;
    }
    void                setEditorData(QWidget* editor, const QModelIndex& index) const override
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
    void                setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
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
};

class float_delegate : public QItemDelegate
{
public:
    float_delegate(QWidget* parent = nullptr) :
        QItemDelegate(parent)
    {
    }

    virtual void        paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        if (index.data().canConvert<float>()) {
            auto value = index.data(Qt::EditRole).value<float>();

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
    QWidget*            createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        auto spinbox = new QDoubleSpinBox(parent);
        spinbox->setMinimum(std::numeric_limits<float>::min());
        spinbox->setMaximum(std::numeric_limits<float>::max());
        return spinbox;
    }
    void                setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
        if (index.data().canConvert<float>())
        {
            QDoubleSpinBox* e = static_cast<QDoubleSpinBox*>(editor);
            auto value = index.data(Qt::EditRole).value<float>();
            e->setValue(value);
        }
        else
        {
            return QItemDelegate::setEditorData(editor, index);
        }
    }
    void                setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
    {
        if (index.data().canConvert<float>())
        {
            QDoubleSpinBox* e = static_cast<QDoubleSpinBox*>(editor);
            model->setData(index, QVariant::fromValue(static_cast<float>(e->value())), Qt::EditRole);
        }
        else
        {
            return QItemDelegate::setModelData(editor, model, index);
        }
    }
};

struct noise_quality_enum_info
{
    using enum_type = noise_quality;

    static noise_quality name_to_value(const QString& name)
    {
        static std::map<QString, noise_quality> translator =
        {
            {"fast", noise_quality::fast},
            {"standard", noise_quality::standard},
            {"best", noise_quality::best}
        };
        return translator[name];
    }
    static QString value_to_name(const noise_quality& value)
    {
        static std::map<noise_quality, QString> translator =
        {
            {noise_quality::fast, "fast"},
            {noise_quality::standard, "standard"},
            {noise_quality::best, "best"}
        };
        return translator[value];
    }
    static QStringList names()
    {
        return { "fast", "standard", "best" };
    }
    static std::vector<noise_quality> values()
    {
        return { noise_quality::fast, noise_quality::standard, noise_quality::best };
    }
};

template<class E>
class enum_delegate : public QItemDelegate
{
public:
    enum_delegate(QWidget* parent = nullptr) :
        QItemDelegate(parent)
    {
    }

    virtual void        paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
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
            if (index != names.end())
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

module_data_model::module_data_model(module_data* data, QObject* parent) :
    QAbstractTableModel(parent),
    _data(data)
{
}

int module_data_model::rowCount(const QModelIndex& parent) const
{
    if(!_data)
    {
        return 0;
    }

    return static_cast<int>(_data->property_count());
}

int module_data_model::columnCount(const QModelIndex & parent) const
{
    if(!_data)
    {
        return 0;
    }
    return 1;
}

QVariant module_data_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Orientation::Horizontal)
        {
            if (section < 0 || section >= columnCount())
            {
                return QVariant();
            }

            return "value";
        }
        else if (orientation == Qt::Orientation::Vertical)
        {
            if (section < 0 || section >= rowCount())
            {
                return QVariant();
            }

            return _data->property_name(section);
        }
    }

    return QVariant();
}

QVariant module_data_model::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount() ||
        index.column() < 0 || index.column() >= columnCount())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return _data->property_value(index.row());
    }

    return QVariant();
}

bool module_data_model::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (index.row() < 0 || index.row() >= rowCount() ||
        index.column() < 0 || index.column() >= columnCount())
    {
        return false;
    }

    if (role == Qt::EditRole)
    {
        return _data->set_property_value(index.row(), value);
    }

    return false;
}

Qt::ItemFlags module_data_model::flags(const QModelIndex & index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QAbstractItemDelegate* module_data_model::delegateForRow(int row) const
{
    auto value = _data->property_value(row);
    if(QString(value.typeName()) == QString("int") || QString(value.typeName()) == QString("uint") || QString(value.typeName()) == QString("qulonglong"))
    {
        return new int_delegate;
    }
    
    if (QString(value.typeName()) == QString("bool"))
    {
        return new bool_delegate;
    }
    
    if (QString(value.typeName()) == QString("float") || QString(value.typeName()) == QString("double"))
    {
        return new float_delegate;
    }

    return new noise_quality_delegate;
}
