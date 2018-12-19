#pragma once

#include "common.hpp"

using namespace gnoise;

class module_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    module_model(QObject* parent = nullptr);
    virtual QAbstractItemDelegate* delegateForRow(int row) const = 0;
};

class perlin_module_model : public module_model
{
    Q_OBJECT
private:
    noise_perlin_generator_module* _module;
public:
    perlin_module_model(noise_perlin_generator_module* module, QObject* parent = nullptr);
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QAbstractItemDelegate* delegateForRow(int row) const override;
};