﻿/*!
 *@file main.qml
 *@brief 主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: qsTr("崩溃报告开发组件测试程序")

    Button{
        id: button
        height: 48
        width: 120
        anchors.centerIn: parent
        text: "Go"
        font.pixelSize: 18
        onClicked: {
            crashReport.doSomething();
        }
    }
}
