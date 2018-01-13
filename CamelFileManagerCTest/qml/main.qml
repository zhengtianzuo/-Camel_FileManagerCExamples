/*!
 *@file main.qml
 *@brief 主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("")

    BaseTableView{
        id: tableView
        height: parent.height - btnStart.height - btnStart.anchors.bottomMargin*2
        width: parent.width
    }

    Button{
        id: btnStart
        height: 32
        width: 120
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        text: qsTr("开始")
        font.pixelSize: 18
        onClicked: {
            fmTest.cls_funStartTest();
        }
    }
}
