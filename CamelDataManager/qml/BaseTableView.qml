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
    TableViewColumn {title: qsTr("名称"); role: "name"; width: 120}
    TableViewColumn {title: qsTr("类型"); role: "type"; width: 120}
    TableViewColumn {title: qsTr("大小"); role: "size"; width: 120}
    model: tableData
    alternatingRowColors: false
    backgroundVisible: false
}
