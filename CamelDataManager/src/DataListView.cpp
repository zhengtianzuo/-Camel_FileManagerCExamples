/*!
 *@file DataListView.h
 *@brief DataListView
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include "DataListView.h"
#include <QDebug>

DataListViewModel::DataListViewModel() : QAbstractListModel(0)
{
}

int DataListViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_aryData.size();
}

QVariant DataListViewModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row > rowCount()) return(QVariant());
    switch (role) {
    case LNameRole:
        return(m_aryData[row].strName);
        break;
    case LPathRole:
        return(m_aryData[row].strPath);
        break;
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> DataListViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[LNameRole] = "name";
    roles[LPathRole] = "path";
    return roles;
}

void DataListViewModel::add(QString strName, QString strPath)
{
    beginInsertRows(QModelIndex(), m_aryData.size(), m_aryData.size());
    foreach (stuListData listData, m_aryData) {
        if (listData.strPath == strPath) return;
    }
    stuListData listData;
    listData.strName = strName;
    listData.strPath = strPath;
    m_aryData.push_back(listData);
    endInsertRows();
}

void DataListViewModel::set(int row, QString strName, QString strPath)
{
    if (row < 0 || row > rowCount()) return;
    beginResetModel();
    m_aryData[row].strName = strName;
    m_aryData[row].strPath = strPath;
    endResetModel();
}

void DataListViewModel::del(int row)
{
    if (row < 0 || row > rowCount()) return;
    beginRemoveRows(QModelIndex(), row, row);
    m_aryData.removeAt(row);
    endRemoveRows();
}

void DataListViewModel::refresh()
{
    beginResetModel();
    endResetModel();
}

void DataListViewModel::move(int index, int lastindex)
{
    if (index < 0 || index > rowCount()) return;
    if (lastindex < 0 || lastindex > rowCount()) return;
    beginResetModel();
    QString strName = m_aryData[index].strName;
    QString strPath = m_aryData[index].strPath;
    QString strNamelast = m_aryData[lastindex].strName;
    QString strPathlast = m_aryData[lastindex].strPath;
    m_aryData[lastindex].strName = strName;
    m_aryData[lastindex].strPath = strPath;
    m_aryData[index].strName = strNamelast;
    m_aryData[index].strPath = strPathlast;
    endResetModel();
}
