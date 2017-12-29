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
    TableViewColumn {title: qsTr("名称"); role: "name"; width: tableView.width - 80*2 - 20}
    TableViewColumn {title: qsTr("类型"); role: "type"; width: 80}
    TableViewColumn {title: qsTr("大小"); role: "size"; width: 80}
    model: tableData
    alternatingRowColors: false
    backgroundVisible: false
}
