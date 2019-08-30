
// *@file DataListView.h
// *@brief DataListView
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#pragma once
#include <QAbstractListModel>
#include <QVector>

class DataListViewModel : public QAbstractListModel {
    Q_OBJECT
 public:
    DataListViewModel();
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    Q_INVOKABLE void add(QString strName, QString strPath);
    Q_INVOKABLE void set(int row, QString strName, QString strPath);
    Q_INVOKABLE void del(int row);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void move(int index, int lastindex);

 private:
    enum DataListViewRole {
        LNameRole,
        LPathRole
    };

    typedef struct {
        QString m_strName;
        QString m_strPath;
    }Cls_stuListData;

    QVector<Cls_stuListData> m_aryData;
};
