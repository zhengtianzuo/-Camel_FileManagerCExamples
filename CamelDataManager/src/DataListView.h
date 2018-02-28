/*!
 *@file DataListView.h
 *@brief DataListView
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#pragma once
#include <QAbstractListModel>
#include <QVector>

enum DataListViewRole {
    LNameRole,
    LPathRole
};

typedef struct {
    QString strName;
    QString strPath;
}stuListData;

class DataListViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DataListViewModel();
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    Q_INVOKABLE void add(QString strName, QString strPath);
    Q_INVOKABLE void set(int row, QString strName, QString strPath);
    Q_INVOKABLE void del(int row);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void move(int index, int lastindex);

private:
   QVector<stuListData> m_aryData;
};
