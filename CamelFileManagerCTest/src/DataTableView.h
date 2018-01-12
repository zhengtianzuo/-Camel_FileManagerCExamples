/*!
 *@file DataTableView.h
 *@brief DataTableView
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#pragma once
#include <QAbstractTableModel>
#include <QVector>

enum Role {
    NameRole,
    ExpectRole,
    RealRole,
    ErrorRole
};

class DataTableViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DataTableViewModel();
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    Q_INVOKABLE void add(QString strName, QString strExpect, QString strReal, QString strError);
    Q_INVOKABLE void set(int row, int column, QString strText);
    Q_INVOKABLE void del(int row);
    Q_INVOKABLE void refresh();
private:
   QVector<QVector<QString>> m_aryData;
};
