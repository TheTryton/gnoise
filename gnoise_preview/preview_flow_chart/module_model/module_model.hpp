#pragma once

#include <QtWidgets>
#include "../preview_common.hpp"

class module_data_model : public QAbstractTableModel
{
private:
    module_data*                    _data;
public:
    module_data_model(module_data* data, QObject* parent = nullptr);
public:
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
public:
    QAbstractItemDelegate*  delegateForRow(int row) const;
};