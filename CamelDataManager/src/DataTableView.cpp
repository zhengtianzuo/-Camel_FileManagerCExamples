
// *@file DataTableView.h
// *@brief DataTableView
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#include "DataTableView.h"
#include <QDebug>

DataTableViewModel::DataTableViewModel() : QAbstractTableModel(0) {
}

int DataTableViewModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_aryData.size();
}

int DataTableViewModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return TEndRole;
}

QVariant DataTableViewModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row < 0 || row > rowCount()) {return QVariant();}
    if (role < 0 || role > columnCount()) {return QVariant();}
    return m_aryData[row][role];
}

QHash<int, QByteArray> DataTableViewModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TNameRole] = "name";
    roles[TTypeRole] = "type";
    roles[TSizeRole] = "size";
    return roles;
}

void DataTableViewModel::add(QString strName, QString strType, QString strSize) {
    beginInsertRows(QModelIndex(), m_aryData.size(), m_aryData.size());
    QVector<QString> list;
    list.push_back(strName);
    list.push_back(strType);
    list.push_back(strSize);
    m_aryData.push_back(list);
    endInsertRows();
}

void DataTableViewModel::set(int row, int column, QString strText) {
    if (row < 0 || row > rowCount()) { return; }
    if (column < 0 || column > columnCount()) { return; }
    beginResetModel();
    m_aryData[row][column] = strText;
    endResetModel();
}

void DataTableViewModel::del(int row) {
    if (row < 0 || row > rowCount()) { return; }
    beginRemoveRows(QModelIndex(), row, row);
    m_aryData.removeAt(row);
    endRemoveRows();
}

void DataTableViewModel::refresh() {
    beginResetModel();
    endResetModel();
}

void DataTableViewModel::update(QString strName, int column, QString strText) {
    beginResetModel();
    for (int i = 0; i < m_aryData.size(); i++) {
       QVector<QString>& list = m_aryData[i];
       if (list.at(0) != strName) { continue; }
       if (column < 0 || column > list.size()) { return; }
       list[column] = strText;
    }
    endResetModel();
}
