#include "module_models.hpp"
#include "../delegates/additional_delegates.hpp"

#include <functional>

module_model::module_model(QObject* parent) : 
    QAbstractTableModel(parent)
{
}

perlin_module_model::perlin_module_model(noise_perlin_generator_module* module, QObject* parent) :
    module_model(parent),
    _module(module)
{
}

int perlin_module_model::rowCount(const QModelIndex& parent) const
{
    return 6;
}

int perlin_module_model::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant perlin_module_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Orientation::Horizontal)
        {
            if(section < 0 || section >= columnCount())
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

            array<QVariant, 6> variable_names =
            {
                "frequency",
                "lacunarity",
                "persistence",
                "seed",
                "octave_count",
                "quality"
            };

            return variable_names[section];
        }
    }

    return QVariant();
}

QVariant perlin_module_model::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount() || 
        index.column() < 0 || index.column() >= columnCount())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        array<QVariant, 6> values =
        {
            _module->frequency(),
            _module->lacunarity(),
            _module->persistence(),
            _module->seed(),
            _module->octave_count(),
            _module->quality()
        };

        return values[index.row()];
    }
    return QVariant();
}

bool perlin_module_model::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.row() < 0 || index.row() >= rowCount() ||
        index.column() < 0 || index.column() >= columnCount())
    {
        return false;
    }

    if (role == Qt::EditRole)
    {
        array<std::function<bool(QVariant)>, 6> values =
        {
            [this](const QVariant& value) {
                _module->set_frequency(value.toFloat());
                return true;
            },
            [this](const QVariant& value) {
                _module->set_lacunarity(value.toFloat());
                return true;
            },
            [this](const QVariant& value) {
                _module->set_persistence(value.toFloat());
                return true;
            },
            [this](const QVariant& value) {
                _module->set_seed(value.toInt());
                return true;
            },
            [this](const QVariant& value) {
                unsigned int v_c = std::min(static_cast<unsigned int>(value.toInt()),gnoise::maximum_octave_count);
                return _module->set_octave_count(v_c);
            },
            [this](const QVariant& value) {
                _module->set_quality(value.value<noise_quality>());
                return true;
            },
        };

        return values[index.row()](value);
    }
    return true;
}

Qt::ItemFlags perlin_module_model::flags(const QModelIndex& index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QAbstractItemDelegate* perlin_module_model::delegateForRow(int row) const
{
    if (row == 3 || row == 4)
    {
        return new int_delegate();
    }
    if(row == 5)
    {
        return new noise_quality_delegate();
    }
    return nullptr;
}
