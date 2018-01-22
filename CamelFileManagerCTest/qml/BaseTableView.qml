/*!
 *@file QmlTableView.qml
 *@brief QmlTableView
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.8
import QtQuick.Controls 1.4

TableView {
    id: tableView
    TableViewColumn {title: qsTr("接口"); role: "name"; width: (tableView.width - 150*2 - 80 - 20)/2;}
    TableViewColumn {title: qsTr("接口"); role: "cname"; width: (tableView.width - 150*2 - 80 - 20)/2;}
    TableViewColumn {horizontalAlignment: Text.AlignHCenter; title: qsTr("期望值");role: "expect"; width: 150;}
    TableViewColumn {horizontalAlignment: Text.AlignHCenter; title: qsTr("实际值"); role: "real"; width: 150}
    TableViewColumn {horizontalAlignment: Text.AlignHCenter; title: qsTr("结果"); role: "error"; width: 80}
    model: tableData
    alternatingRowColors: false
    backgroundVisible: false
}
