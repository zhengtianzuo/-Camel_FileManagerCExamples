/*!
 *@file DBData.qml
 *@brief 浏览
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle{
    property int defaultMargin: 6

    id: frmWindow

    BaseTableView{
        id: tableView
        height: parent.height - control.height
        width: parent.width
    }

    Rectangle{
        id: control
        anchors.top: tableView.bottom
        anchors.topMargin: defaultMargin
        height: 48
        width: parent.width
        color: "#AAAAAA"
    }
}
